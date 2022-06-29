#ifndef JOYSTICK_DRIVER_H
#define JOYSTICK_DRIVER_H

#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/joy.hpp>
#include <memory>
#include <urc_msgs/msg/velocity_pair.hpp>
#include <rclcpp_components/register_node_macro.hpp>


namespace joystick_driver
{
class JoystickDriver : public rclcpp::Node
{
public:
  explicit JoystickDriver(const rclcpp::NodeOptions & options);

private:
  rclcpp::Publisher<urc_msgs::msg::VelocityPair>::SharedPtr _cmd_publisher;
  rclcpp::Subscription<sensor_msgs::msg::Joy>::SharedPtr _joy_subscriber;

  double absoluteMaxVel, maxVel, maxVelIncr;
  int leftJoyAxis, rightJoyAxis;
  bool leftInverted, rightInverted;

  void joyCallback(const sensor_msgs::msg::Joy & msg);
};
}


#endif
