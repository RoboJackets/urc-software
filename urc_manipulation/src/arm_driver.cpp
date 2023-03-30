#include "arm_driver.hpp"

namespace arm_driver
{

ArmDriver::ArmDriver(const rclcpp::NodeOptions & options)
: rclcpp::Node("arm_driver", options)
{
  _cmd_publisher = create_publisher<urc_msgs::msg::VelocityPair>(
    "~/motors",
    rclcpp::SystemDefaultsQoS());

  _joy_subscriber = create_subscription<sensor_msgs::msg::Joy>(
    "~/joy", rclcpp::SystemDefaultsQoS(), [this](const sensor_msgs::msg::Joy msg) {
      joyCallback(msg);
    });

  absoluteMaxVel = declare_parameter<double>("absoluteMaxVel");
  maxVel = declare_parameter<double>("maxVel");
  maxVelIncr = declare_parameter<double>("maxVelIncr");
  leftJoyAxis = declare_parameter<int>("leftJoyAxis");
  rightJoyAxis = declare_parameter<int>("rightJoyAxis");
  leftInverted = declare_parameter<bool>("leftInverted");
  rightInverted = declare_parameter<bool>("rightInverted");
}

void JoystickDriver::joyCallback(const sensor_msgs::msg::Joy & msg)
{
  if (msg.buttons[1]) {
    maxVel -= maxVelIncr;
  } else if (msg.buttons[3]) {
    maxVel += maxVelIncr;
  }

  maxVel = std::max(std::min(maxVel, absoluteMaxVel), 0.0);
  set_parameter(rclcpp::Parameter("maxVel", maxVel));

  updater_ptr->force_update();

  auto cmd = urc_msgs::msg::VelocityPair();
  cmd.left_velocity = msg.axes[leftJoyAxis] * maxVel * (leftInverted ? -1.0 : 1.0);
  cmd.right_velocity = msg.axes[rightJoyAxis] * maxVel * (rightInverted ? -1.0 : 1.0);
  cmd.header.stamp = this->get_clock()->now();

  _cmd_publisher->publish(cmd);
}
}

RCLCPP_COMPONENTS_REGISTER_NODE(joystick_driver::JoystickDriver)
