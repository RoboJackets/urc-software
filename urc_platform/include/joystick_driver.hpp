#ifndef JOYSTICK_DRIVER_H
#define JOYSTICK_DRIVER_H

#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/joy.hpp>
#include <geometry_msgs/msg/twist.hpp>
#include <memory>
#include <urc_msgs/msg/velocity_pair.hpp>
#include <rclcpp_components/register_node_macro.hpp>
#include <diagnostic_updater/diagnostic_updater.hpp>
#include <diagnostic_updater/publisher.hpp>

namespace joystick_driver
{
class JoystickDriver : public rclcpp::Node
{
public:
  explicit JoystickDriver(const rclcpp::NodeOptions & options);

private:
  rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr _cmd_publisher;
  rclcpp::Subscription<sensor_msgs::msg::Joy>::SharedPtr _joy_subscriber;

  std::unique_ptr<diagnostic_updater::Updater> updater_ptr;
  double linearVel, angularVel, angularVelScale;
  // int leftJoyAxis, rightJoyAxis;
  // bool leftInverted, rightInverted;

  void joystick_diagnostic(diagnostic_updater::DiagnosticStatusWrapper & stat);
  void joyCallback(const sensor_msgs::msg::Joy & msg);
};
}


#endif
