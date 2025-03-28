#ifndef JOYSTICK_DRIVER_H
#define JOYSTICK_DRIVER_H

#include "geometry_msgs/msg/twist_stamped.hpp"
#include <rclcpp/publisher.hpp>
#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/joy.hpp>
#include <memory>
#include <rclcpp_components/register_node_macro.hpp>
#include <std_msgs/msg/detail/int8__struct.hpp>
#include <utility>
#include <urc_msgs/srv/set_teleop_mode.hpp>

namespace joystick_driver
{

class JoystickDriver : public rclcpp::Node
{
public:
  explicit JoystickDriver(const rclcpp::NodeOptions & options);

private:
  rclcpp::Subscription<sensor_msgs::msg::Joy>::SharedPtr joy_subscriber;
  void JoyCallback(const sensor_msgs::msg::Joy & msg);

  // Service server for mode control
  rclcpp::Service<urc_msgs::srv::SetTeleopMode>::SharedPtr mode_service;
  void ModeCallback(
    const std::shared_ptr<urc_msgs::srv::SetTeleopMode::Request> request,
    std::shared_ptr<urc_msgs::srv::SetTeleopMode::Response> response);

  // drivetrain
  std::shared_ptr<rclcpp::Publisher<geometry_msgs::msg::TwistStamped>> cmd_vel_publisher;
  double max_linear_velocity;
  double max_angular_velocity;
  std::pair<int, int> velocity_axis;
  std::pair<bool, bool> invert_pair;

  int mode;
};
}  // namespace joystick_driver

#endif
