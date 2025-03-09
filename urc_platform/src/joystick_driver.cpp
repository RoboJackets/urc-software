#include "joystick_driver.hpp"
#include "preprocessing.hpp"

#include <rclcpp/qos.hpp>
#include <string>
#include <utility>

namespace joystick_driver
{

JoystickDriver::JoystickDriver(const rclcpp::NodeOptions & options)
: rclcpp::Node("joystick_driver", options)
{
  declare_parameter("max_linear_velocity", 3.0);
  declare_parameter("max_angular_velocity", 5.0);
  declare_parameter("delta_velocity", 0.1);

  declare_parameter("driver_joystick_topic", "/driver/joy");
  declare_parameter("driver_velocity_x_axis", 1);
  declare_parameter("driver_velocity_z_axis", 3);
  declare_parameter("driver_left_invert", false);
  declare_parameter("driver_right_invert", false);
  declare_parameter("drivetrain_topic", "/cmd_vel_teleop");

  joy_subscriber = create_subscription<sensor_msgs::msg::Joy>(
    get_parameter("driver_joystick_topic").as_string(), rclcpp::SystemDefaultsQoS(),
    [this](const sensor_msgs::msg::Joy msg) {JoyCallback(msg);});

  drivetrain_cmd_publisher = create_publisher<geometry_msgs::msg::TwistStamped>(
    get_parameter("drivetrain_topic").as_string(), rclcpp::SystemDefaultsQoS());
  max_linear_velocity = get_parameter("max_linear_velocity").as_double();
  max_angular_velocity = get_parameter("max_angular_velocity").as_double();
  velocity_axis = std::make_pair(
    get_parameter("driver_velocity_x_axis").as_int(),
    get_parameter("driver_velocity_z_axis").as_int());
  invert_pair =
    std::make_pair(
    get_parameter("driver_left_invert").as_bool(),
    get_parameter("driver_right_invert").as_bool());
}

void JoystickDriver::JoyCallback(const sensor_msgs::msg::Joy & msg)
{
  geometry_msgs::msg::TwistStamped drive_velocity;
  drive_velocity.twist.linear.x =
    PreProcessing::preprocess(msg.axes[velocity_axis.first], max_linear_velocity, invert_pair.first);
  drive_velocity.twist.angular.z =
    PreProcessing::preprocess(msg.axes[velocity_axis.second], max_angular_velocity, invert_pair.second);
  drivetrain_cmd_publisher->publish(drive_velocity);
}

}  // namespace joystick_driver

RCLCPP_COMPONENTS_REGISTER_NODE(joystick_driver::JoystickDriver)
