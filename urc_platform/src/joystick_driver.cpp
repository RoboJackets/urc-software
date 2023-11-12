#include "joystick_driver.hpp"

namespace joystick_driver
{

JoystickDriver::JoystickDriver(const rclcpp::NodeOptions & options)
: rclcpp::Node("joystick_driver", options)
{
  _cmd_publisher = create_publisher<geometry_msgs::msg::Twist>(
    "~/motors",
    rclcpp::SystemDefaultsQoS());

  _joy_subscriber = create_subscription<sensor_msgs::msg::Joy>(
    "~/joy", rclcpp::SystemDefaultsQoS(), [this](const sensor_msgs::msg::Joy msg) {
      joyCallback(msg);
    });

  updater_ptr = std::make_unique<diagnostic_updater::Updater>(this);
  updater_ptr->setHardwareID("Joystick");
  updater_ptr->add("Joystick Diagnostic", this, &JoystickDriver::joystick_diagnostic);

  // absoluteMaxVel = declare_parameter<double>("absoluteMaxVel");
  // maxVel = declare_parameter<double>("maxVel");
  // maxVelIncr = declare_parameter<double>("maxVelIncr");
  // leftJoyAxis = declare_parameter<int>("leftJoyAxis");
  // rightJoyAxis = declare_parameter<int>("rightJoyAxis");
  linearVel = declare_parameter<double>("linearVel");
  angularVel = declare_parameter<double>("angularVel");
  angularVelScale = declare_parameter<double>("angularVelScale");
  // leftInverted = declare_parameter<bool>("leftInverted");
  // rightInverted = declare_parameter<bool>("rightInverted");
}

void JoystickDriver::joystick_diagnostic(diagnostic_updater::DiagnosticStatusWrapper & stat)
{
  stat.summary(diagnostic_msgs::msg::DiagnosticStatus::OK, "Joystick Online");
  stat.add("linear_velocity", linearVel);
  stat.add("angular_velocity", angularVel);
}

void JoystickDriver::joyCallback(const sensor_msgs::msg::Joy & msg)
{
  // if (msg.buttons[1]) {
  //   maxVel -= maxVelIncr;
  // } else if (msg.buttons[3]) {
  //   maxVel += maxVelIncr;
  // }
  linearVel = msg.axes[1];
  angularVel = msg.axes[0] * angularVelScale;

  set_parameter(rclcpp::Parameter("linearVel", linearVel));
  set_parameter(rclcpp::Parameter("angularVel", angularVel));

  updater_ptr->force_update();

  auto cmd = geometry_msgs::msg::Twist();
  cmd.linear.x = linearVel;
  cmd.angular.z = angularVel;
  // cmd.left_velocity = msg.axes[leftJoyAxis] * maxVel * (leftInverted ? -1.0 : 1.0);
  // cmd.right_velocity = msg.axes[rightJoyAxis] * maxVel * (rightInverted ? -1.0 : 1.0);
  // cmd.header.stamp = this->get_clock()->now();

  _cmd_publisher->publish(cmd);
}
}

RCLCPP_COMPONENTS_REGISTER_NODE(joystick_driver::JoystickDriver)
