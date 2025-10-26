#include "urc_controllers/swerve_drive_controller.hpp"
#include <algorithm>
#include <cmath>
#include <controller_interface/controller_interface_base.hpp>
#include <hardware_interface/loaned_command_interface.hpp>
#include <memory>
#include <rclcpp/logging.hpp>
#include <rclcpp/qos.hpp>
#include <string>

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
  const double module_x = get_node()->declare_parameter("module_x", 0.3);
  const double module_y = get_node()->declare_parameter("module_y", 0.3);

  modules_.clear();
  modules_.push_back({"fl", module_x, module_y});     // Front Left
  modules_.push_back({"fr", module_x, -module_y});    // Front Right
  modules_.push_back({"bl", -module_x, module_y});    // Back Left
  modules_.push_back({"br", -module_x, -module_y});   // Back Right

  RCLCPP_INFO(
    get_node()->get_logger(),
    "Configured swerve drive with module positions: x=%.2f, y=%.2f",
    module_x, module_y);

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
      module.name + "_drive/velocity");

    // Steer motor position command
    command_interfaces_configuration.names.push_back(
      module.name + "_steer/position");
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
      module.name + "_drive/velocity");

    // Steer motor position state
    state_interfaces_configuration.names.push_back(
      module.name + "_steer/position");
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
  wheel_speed = std::sqrt(wheel_vx * wheel_vx + wheel_vy * wheel_vy);
  if (wheel_speed > 0.001) {  // Avoid atan2 with very small values
    wheel_angle = std::atan2(wheel_vy, wheel_vx);
  } else {
    // Keep previous angle if speed is negligible
    wheel_angle = 0.0;
  }
}

controller_interface::return_type SwerveDriveController::update(
  const rclcpp::Time &,
  const rclcpp::Duration &)
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
    std::string drive_interface_name = module.name + "_drive/velocity";
    std::string steer_interface_name = module.name + "_steer/position";

    if (command_interface_map_.find(drive_interface_name) != command_interface_map_.end()) {
      command_interface_map_[drive_interface_name]->get().set_value(wheel_speed);
    }

    if (command_interface_map_.find(steer_interface_name) != command_interface_map_.end()) {
      command_interface_map_[steer_interface_name]->get().set_value(wheel_angle);
    }

    // Optional: Read from state interfaces to get current wheel states
    // (useful for debugging or advanced control algorithms)
    // double current_drive_velocity = state_interface_map_[drive_interface_name]->get().get_value();
    // double current_steer_position = state_interface_map_[steer_interface_name]->get().get_value();
  }

  return controller_interface::return_type::OK;
}

} // namespace urc_controllers
