#include "joystick_driver.hpp"

namespace joystick_driver
{

JoystickDriver::JoystickDriver(const rclcpp::NodeOptions & options)
: rclcpp::Node("joystick_driver", options)
{
  _cmd_publisher = create_publisher<urc_msgs::msg::VelocityPair>(
    "~/motors",
    rclcpp::SystemDefaultsQoS());


  _joy_subscriber = create_subscription<sensor_msgs::msg::Joy>(
    "~/joy", rclcpp::SystemDefaultsQoS(), [this](const sensor_msgs::msg::Joy msg) {
      joyCallback(msg);
    });

  get_parameter_or("absoluteMaxVel", absoluteMaxVel, 1.0);
  get_parameter_or("maxVel", maxVel, 1.6);
  get_parameter_or("maxVelIncr", maxVelIncr, 0.1);
  get_parameter_or("leftJoyAxis", leftJoyAxis, 1);
  get_parameter_or("rightJoyAxis", rightJoyAxis, 4);
  get_parameter_or("leftInverted", leftInverted, false);
  get_parameter_or("rightInverted", rightInverted, false);
}

void JoystickDriver::joyCallback(const sensor_msgs::msg::Joy & msg)
{
  if (msg.buttons[1]) {
    maxVel -= maxVelIncr;
  } else if (msg.buttons[3]) {
    maxVel += maxVelIncr;
  }
  maxVel = std::min(maxVel, absoluteMaxVel);
  maxVel = std::max(maxVel, 0.0);

  set_parameter(rclcpp::Parameter("maxVel", maxVel));

  auto cmd = urc_msgs::msg::VelocityPair();
  cmd.left_velocity = msg.axes[leftJoyAxis] * maxVel * (leftInverted ? -1.0 : 1.0);
  cmd.right_velocity = msg.axes[rightJoyAxis] * maxVel * (rightInverted ? -1.0 : 1.0);
  cmd.header.stamp = this->get_clock()->now();

  _cmd_publisher->publish(cmd);
}
}

RCLCPP_COMPONENTS_REGISTER_NODE(joystick_driver::JoystickDriver)
