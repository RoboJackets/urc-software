#ifndef URC_CONTROLLERS__SWERVE_DRIVE_CONTROLLER_HPP_
#define URC_CONTROLLERS__SWERVE_DRIVE_CONTROLLER_HPP_

#include <controller_interface/controller_interface.hpp>
#include <geometry_msgs/msg/twist.hpp>
#include <hardware_interface/loaned_command_interface.hpp>
#include <hardware_interface/loaned_state_interface.hpp>
#include <memory>
#include <nav_msgs/msg/odometry.hpp>
#include <rclcpp/publisher.hpp>
#include <rclcpp/subscription.hpp>
#include <rclcpp_lifecycle/node_interfaces/lifecycle_node_interface.hpp>
#include <rclcpp_lifecycle/state.hpp>
#include <realtime_tools/realtime_tools/realtime_buffer.h>
#include <realtime_tools/realtime_tools/realtime_publisher.h>
#include <string>
#include <unordered_map>
#include <vector>

namespace urc_controllers
{

class SwerveDriveController : public controller_interface::ControllerInterface
{
public:
  SwerveDriveController();

  controller_interface::InterfaceConfiguration command_interface_configuration() const override;
  controller_interface::InterfaceConfiguration state_interface_configuration() const override;

  controller_interface::return_type update(
    const rclcpp::Time & time,
    const rclcpp::Duration & period) override;

  controller_interface::CallbackReturn on_init() override;

  controller_interface::CallbackReturn on_configure(const rclcpp_lifecycle::State & previous_state)
  override;

  controller_interface::CallbackReturn on_activate(const rclcpp_lifecycle::State & previous_state)
  override;

  controller_interface::CallbackReturn on_deactivate(const rclcpp_lifecycle::State & previous_state)
  override;

  controller_interface::CallbackReturn on_cleanup(const rclcpp_lifecycle::State & previous_state)
  override;

  controller_interface::CallbackReturn on_error(const rclcpp_lifecycle::State & previous_state)
  override;

  controller_interface::CallbackReturn on_shutdown(const rclcpp_lifecycle::State & previous_state)
  override;

protected:
  // Module configuration
  struct ModuleConfig
  {
    std::string name;
    double x;  // Position relative to robot center (meters)
    double y;
    double wheel_radius;  // Wheel radius (meters)
  };

  std::vector<ModuleConfig> modules_;

  // Velocity command from /cmd_vel topic
  struct VelocityCommand
  {
    double vx{0.0};
    double vy{0.0};
    double omega{0.0};
  };

  std::shared_ptr<rclcpp::Subscription<geometry_msgs::msg::Twist>> cmd_vel_subscriber_;
  realtime_tools::RealtimeBuffer<VelocityCommand> velocity_command_;

  // Odometry publisher
  std::shared_ptr<realtime_tools::RealtimePublisher<nav_msgs::msg::Odometry>> odom_publisher_;

  // Odometry state
  double odom_x_{0.0};
  double odom_y_{0.0};
  double odom_theta_{0.0};

  // Command interfaces (write to hardware)
  std::unordered_map<std::string,
    std::shared_ptr<std::reference_wrapper<hardware_interface::LoanedCommandInterface>>>
  command_interface_map_;

  // State interfaces (read from hardware)
  std::unordered_map<std::string,
    std::shared_ptr<std::reference_wrapper<hardware_interface::LoanedStateInterface>>>
  state_interface_map_;

  // Interface names for each module
  const std::vector<std::string> DRIVE_COMMAND_INTERFACES{"velocity"};
  const std::vector<std::string> STEER_COMMAND_INTERFACES{"position"};
  const std::vector<std::string> STATE_INTERFACES{"velocity", "position"};

  // Helper methods
  void calculateModuleKinematics(
    const ModuleConfig & module,
    double vx, double vy, double omega,
    double & wheel_speed, double & wheel_angle);

  void calculateRobotVelocityFromWheels(
    double & vx, double & vy, double & omega);
};

} // namespace urc_controllers

#endif // URC_CONTROLLERS__SWERVE_DRIVE_CONTROLLER_HPP_
