#include "urc_controllers/swerve_drive_controller.hpp"
#include <algorithm>
#include <cmath>
#include <controller_interface/controller_interface_base.hpp>
#include <hardware_interface/loaned_command_interface.hpp>
#include <memory>
#include <nav_msgs/msg/odometry.hpp>
#include <rclcpp/logging.hpp>
#include <rclcpp/qos.hpp>
#include <string>
#include <geometry_msgs/msg/quaternion.hpp>
#include <tf2/LinearMath/Quaternion.h>
#include <tf2_geometry_msgs/tf2_geometry_msgs.hpp>

#include "pluginlib/class_list_macros.hpp"
PLUGINLIB_EXPORT_CLASS(
  urc_controllers::SwerveDriveController,
  controller_interface::ControllerInterface);

namespace urc_controllers
{

SwerveDriveController::SwerveDriveController()
: cmd_vel_subscriber_(nullptr), velocity_command_(VelocityCommand{}) {}

controller_interface::CallbackReturn SwerveDriveController::on_init()
{
  return controller_interface::CallbackReturn::SUCCESS;
}

controller_interface::CallbackReturn SwerveDriveController::on_configure(
  const rclcpp_lifecycle::State &)
{
  // Read module configuration from parameters
  // TODO: Read these from a config file instead of hardcoding
  const double module_x = get_node()->get_parameter("module_x").as_double();
  const double module_y = get_node()->get_parameter("module_y").as_double();
  const double wheel_radius = get_node()->get_parameter("wheel_radius").as_double();

  modules_.clear();
  modules_.push_back({"FL", module_x, module_y, wheel_radius});     // Front Left
  modules_.push_back({"FR", module_x, -module_y, wheel_radius});    // Front Right
  modules_.push_back({"BL", -module_x, module_y, wheel_radius});    // Back Left
  modules_.push_back({"BR", -module_x, -module_y, wheel_radius});   // Back Right

  RCLCPP_INFO(
    get_node()->get_logger(),
    "Configured swerve drive with module positions: x=%.2f, y=%.2f, wheel_radius=%.4f",
    module_x, module_y, wheel_radius);

  return controller_interface::CallbackReturn::SUCCESS;
}

controller_interface::InterfaceConfiguration SwerveDriveController::command_interface_configuration()
const
{
  controller_interface::InterfaceConfiguration command_interfaces_configuration;
  command_interfaces_configuration.type =
    controller_interface::interface_configuration_type::INDIVIDUAL;

  // For each module, we need drive velocity and steer position command interfaces
  for (const auto & module : modules_) {
    // Drive motor velocity command
    command_interfaces_configuration.names.push_back(
      module.name + "_Wheel_Joint/velocity");

    // Steer motor position command
    command_interfaces_configuration.names.push_back(
      module.name + "_Swivel_Joint/position");
  }

  return command_interfaces_configuration;
}

controller_interface::InterfaceConfiguration SwerveDriveController::state_interface_configuration()
const
{
  controller_interface::InterfaceConfiguration state_interfaces_configuration;
  state_interfaces_configuration.type =
    controller_interface::interface_configuration_type::INDIVIDUAL;

  // For each module, we can read current drive velocity and steer position
  for (const auto & module : modules_) {
    // Drive motor velocity state
    state_interfaces_configuration.names.push_back(
      module.name + "_Wheel_Joint/velocity");

    // Steer motor position state
    state_interfaces_configuration.names.push_back(
      module.name + "_Swivel_Joint/position");
  }

  return state_interfaces_configuration;
}

controller_interface::CallbackReturn SwerveDriveController::on_activate(
  const rclcpp_lifecycle::State &)
{
  // Populate command interface map
  for (auto & interface : command_interfaces_) {
    command_interface_map_.emplace(
      interface.get_name(),
      std::make_shared<std::reference_wrapper<hardware_interface::LoanedCommandInterface>>(
        interface));
  }

  // Populate state interface map
  for (auto & interface : state_interfaces_) {
    state_interface_map_.emplace(
      interface.get_name(),
      std::make_shared<std::reference_wrapper<hardware_interface::LoanedStateInterface>>(
        interface));
  }

  // Verify all interfaces are available
  size_t expected_interfaces = modules_.size() * 2;  // 2 interfaces per module (drive + steer)
  if (command_interface_map_.size() != expected_interfaces) {
    RCLCPP_ERROR(
      get_node()->get_logger(),
      "Not all command interfaces are initialized! Expected %zu, got %zu",
      expected_interfaces, command_interface_map_.size());
    return controller_interface::CallbackReturn::ERROR;
  }

  if (state_interface_map_.size() != expected_interfaces) {
    RCLCPP_ERROR(
      get_node()->get_logger(),
      "Not all state interfaces are initialized! Expected %zu, got %zu",
      expected_interfaces, state_interface_map_.size());
    return controller_interface::CallbackReturn::ERROR;
  }

  // Create subscriber to cmd_vel
  cmd_vel_subscriber_ = get_node()->create_subscription<geometry_msgs::msg::Twist>(
    "/cmd_vel",
    rclcpp::SystemDefaultsQoS(),
    [this](std::shared_ptr<geometry_msgs::msg::Twist> msg)
    {
      VelocityCommand cmd;
      cmd.vx = msg->linear.x;
      cmd.vy = msg->linear.y;
      cmd.omega = msg->angular.z;
      velocity_command_.writeFromNonRT(cmd);
    });

  // Create odometry publisher
  odom_publisher_ = std::make_shared<realtime_tools::RealtimePublisher<nav_msgs::msg::Odometry>>(
    get_node()->create_publisher<nav_msgs::msg::Odometry>(
      "/odom",
      rclcpp::SystemDefaultsQoS()));

  // Initialize odometry state
  odom_x_ = 0.0;
  odom_y_ = 0.0;
  odom_theta_ = 0.0;

  RCLCPP_INFO(get_node()->get_logger(), "SwerveDriveController activated!");
  return controller_interface::CallbackReturn::SUCCESS;
}

controller_interface::CallbackReturn SwerveDriveController::on_deactivate(
  const rclcpp_lifecycle::State &)
{
  cmd_vel_subscriber_.reset();
  command_interface_map_.clear();
  state_interface_map_.clear();
  return controller_interface::CallbackReturn::SUCCESS;
}

controller_interface::CallbackReturn SwerveDriveController::on_cleanup(
  const rclcpp_lifecycle::State &)
{
  cmd_vel_subscriber_.reset();
  return controller_interface::CallbackReturn::SUCCESS;
}

controller_interface::CallbackReturn SwerveDriveController::on_error(
  const rclcpp_lifecycle::State &)
{
  cmd_vel_subscriber_.reset();
  return controller_interface::CallbackReturn::SUCCESS;
}

controller_interface::CallbackReturn SwerveDriveController::on_shutdown(
  const rclcpp_lifecycle::State &)
{
  cmd_vel_subscriber_.reset();
  return controller_interface::CallbackReturn::SUCCESS;
}

void SwerveDriveController::calculateModuleKinematics(
  const ModuleConfig & module,
  double vx, double vy, double omega,
  double & wheel_speed, double & wheel_angle)
{
  // Calculate wheel velocity components
  // vx, vy: desired robot velocity in x, y
  // omega: desired robot angular velocity

  // Velocity due to translation
  double wheel_vx = vx;
  double wheel_vy = vy;

  // Velocity due to rotation around robot center
  wheel_vx += -omega * module.y;
  wheel_vy += omega * module.x;

  // Calculate wheel angle and speed
  double linear_speed = std::sqrt(wheel_vx * wheel_vx + wheel_vy * wheel_vy);
  if (linear_speed > 0.001) {  // Avoid atan2 with very small values
    wheel_angle = std::atan2(wheel_vy, wheel_vx);
  } else {
    // Keep previous angle if speed is negligible
    wheel_angle = 0.0;
  }
  // Convert linear speed (m/s) to angular speed (rad/s)
  wheel_speed = linear_speed / module.wheel_radius;
}

void SwerveDriveController::calculateRobotVelocityFromWheels(
  double & vx, double & vy, double & omega)
{
  // Inverse kinematics: compute robot velocity from wheel states
  // Uses least-squares solution for overdetermined system

  // Read wheel states for all modules
  std::vector<double> wheel_speeds;
  std::vector<double> wheel_angles;

  for (const auto & module : modules_) {
    std::string drive_interface_name = module.name + "_Wheel_Joint/velocity";
    std::string steer_interface_name = module.name + "_Swivel_Joint/position";

    if (state_interface_map_.find(drive_interface_name) != state_interface_map_.end() &&
      state_interface_map_.find(steer_interface_name) != state_interface_map_.end())
    {
      double speed = state_interface_map_[drive_interface_name]->get().get_value();
      double angle = state_interface_map_[steer_interface_name]->get().get_value();

      wheel_speeds.push_back(speed);
      wheel_angles.push_back(angle);
    }
  }

  // Convert wheel velocities to Cartesian components
  double sum_vx = 0.0;
  double sum_vy = 0.0;
  double sum_omega = 0.0;

  for (size_t i = 0; i < modules_.size() && i < wheel_speeds.size(); ++i) {
    const auto & module = modules_[i];
    double angular_speed = wheel_speeds[i];  // rad/s from state interface
    double angle = wheel_angles[i];

    // Convert angular velocity to linear velocity
    double linear_speed = angular_speed * module.wheel_radius;

    // Wheel velocity in robot frame
    double wheel_vx = linear_speed * std::cos(angle);
    double wheel_vy = linear_speed * std::sin(angle);

    // Contribution to linear velocity (average all modules)
    sum_vx += wheel_vx;
    sum_vy += wheel_vy;

    // Contribution to angular velocity
    // omega = (wheel_vy - robot_vy) / module.x  or  (robot_vx - wheel_vx) / module.y
    // Use cross product: omega_contribution = (wheel_vel cross module_position) / module_distance^2
    double module_dist_sq = module.x * module.x + module.y * module.y;
    if (module_dist_sq > 0.001) {
      // Cross product in 2D: (wheel_vx, wheel_vy) x (module.x, module.y)
      double omega_contrib = (wheel_vy * module.x - wheel_vx * module.y) / module_dist_sq;
      sum_omega += omega_contrib;
    }
  }

  // Average the contributions
  int num_modules = static_cast<int>(modules_.size());
  if (num_modules > 0) {
    vx = sum_vx / num_modules;
    vy = sum_vy / num_modules;
    omega = sum_omega / num_modules;
  } else {
    vx = 0.0;
    vy = 0.0;
    omega = 0.0;
  }
}

controller_interface::return_type SwerveDriveController::update(
  const rclcpp::Time & time,
  const rclcpp::Duration & period)
{
  // Read the latest velocity command from the realtime buffer
  auto velocity_cmd = *velocity_command_.readFromRT();

  // Calculate and write commands for each module
  for (const auto & module : modules_) {
    double wheel_speed, wheel_angle;
    calculateModuleKinematics(
      module,
      velocity_cmd.vx,
      velocity_cmd.vy,
      velocity_cmd.omega,
      wheel_speed,
      wheel_angle);

    // Write to command interfaces
    std::string drive_interface_name = module.name + "_Wheel_Joint/velocity";
    std::string steer_interface_name = module.name + "_Swivel_Joint/position";

    if (command_interface_map_.find(drive_interface_name) != command_interface_map_.end()) {
      command_interface_map_[drive_interface_name]->get().set_value(wheel_speed);
    }

    if (command_interface_map_.find(steer_interface_name) != command_interface_map_.end()) {
      command_interface_map_[steer_interface_name]->get().set_value(wheel_angle);
    }
  }

  // Compute odometry from wheel states (inverse kinematics)
  double robot_vx, robot_vy, robot_omega;
  calculateRobotVelocityFromWheels(robot_vx, robot_vy, robot_omega);

  // Integrate velocity to get position
  double dt = period.seconds();
  double delta_x = (robot_vx * std::cos(odom_theta_) - robot_vy * std::sin(odom_theta_)) * dt;
  double delta_y = (robot_vx * std::sin(odom_theta_) + robot_vy * std::cos(odom_theta_)) * dt;
  double delta_theta = robot_omega * dt;

  odom_x_ += delta_x;
  odom_y_ += delta_y;
  odom_theta_ += delta_theta;

  // Publish odometry message
  if (odom_publisher_ && odom_publisher_->trylock()) {
    auto & odom_msg = odom_publisher_->msg_;

    odom_msg.header.stamp = time;
    odom_msg.header.frame_id = "odom";
    odom_msg.child_frame_id = "base_link";

    // Position
    odom_msg.pose.pose.position.x = odom_x_;
    odom_msg.pose.pose.position.y = odom_y_;
    odom_msg.pose.pose.position.z = 0.0;

    // Orientation (convert from yaw to quaternion)
    tf2::Quaternion q;
    q.setRPY(0.0, 0.0, odom_theta_);
    geometry_msgs::msg::Quaternion quat_msg;
    odom_msg.pose.pose.orientation = tf2::toMsg(q);

    // Velocity (in robot frame)
    odom_msg.twist.twist.linear.x = robot_vx;
    odom_msg.twist.twist.linear.y = robot_vy;
    odom_msg.twist.twist.linear.z = 0.0;
    odom_msg.twist.twist.angular.x = 0.0;
    odom_msg.twist.twist.angular.y = 0.0;
    odom_msg.twist.twist.angular.z = robot_omega;

    odom_publisher_->unlockAndPublish();
  }

  return controller_interface::return_type::OK;
}

} // namespace urc_controllers
