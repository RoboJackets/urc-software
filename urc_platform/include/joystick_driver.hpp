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

namespace joystick_driver
{
class JoystickDriver : public rclcpp::Node
{
public:
  explicit JoystickDriver(const rclcpp::NodeOptions& options);

private:
  rclcpp::Subscription<sensor_msgs::msg::Joy>::SharedPtr joy_subscriber;
  void JoyCallback(const sensor_msgs::msg::Joy& msg);

  // drivetrain
  std::shared_ptr<rclcpp::Publisher<geometry_msgs::msg::TwistStamped>> drivetrain_cmd_publisher;
  double max_velocity;
  std::pair<int, int> velocity_axis;
  std::pair<bool, bool> invert_pair;
};
}  // namespace joystick_driver

#endif