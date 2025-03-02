#include "joy_drive.hpp"
#include <rclcpp/qos.hpp>
#include <string>

namespace joy_drive
{

JoyDrive::JoyDrive(const rclcpp::NodeOptions & options)
: rclcpp::Node("joy_drive", options)
{
  // Declare parameters
  declare_parameter("max_linear_velocity_ms", 0.0);
  declare_parameter("max_angular_velocity_radians", 0.0);
  declare_parameter("joy_command_topic", "/joy");
  declare_parameter("cmd_vel_topic", "/cmd_vel");
  declare_parameter("target_axes", std::vector<int64_t>{1, 3});
  declare_parameter("invert_linear_velocity", false);
  declare_parameter("invert_angular_velocity", false);

  // Get parameters
  max_linear_ = get_parameter("max_linear_velocity_ms").as_double();
  max_angular_ = get_parameter("max_angular_velocity_radians").as_double();
  joy_command_topic_ = get_parameter("joy_command_topic").as_string();
  cmd_vel_topic_ = get_parameter("cmd_vel_topic").as_string();
  auto axes = get_parameter("target_axes").as_integer_array();
  target_axes_ = std::make_pair(axes[0], axes[1]);
  invert_axes_ = std::make_pair(
    get_parameter("invert_linear_velocity").as_bool(),
    get_parameter("invert_angular_velocity").as_bool());

  // Register parameter callback
  param_callback_handle_ = add_on_set_parameters_callback(
    [this](const std::vector<rclcpp::Parameter> & params) {
      return on_param_update(params);
    });

  // Create subscribers and publishers
  joy_subscriber_ = create_subscription<sensor_msgs::msg::Joy>(
    joy_command_topic_, rclcpp::SystemDefaultsQoS(),
    [this](const sensor_msgs::msg::Joy & msg) {joy_callback(msg);});

  cmd_vel_publisher_ = create_publisher<geometry_msgs::msg::TwistStamped>(
    cmd_vel_topic_, rclcpp::SystemDefaultsQoS());

  // Log startup message
  RCLCPP_INFO(get_logger(), "Joy Drive Started.");
  RCLCPP_INFO(
    get_logger(), "Default Settings: [linear velocity %f m/s], [angular velocity %f rad/s]",
    max_linear_, max_angular_);
}

void JoyDrive::joy_callback(const sensor_msgs::msg::Joy & msg)
{
  geometry_msgs::msg::TwistStamped twist;
  twist.twist.linear.x = msg.axes[target_axes_.first] * max_linear_ * (invert_axes_.first ? -1 : 1);
  twist.twist.angular.z = msg.axes[target_axes_.second] * max_angular_ * (invert_axes_.second ? -1 : 1);
  twist.header.stamp = now();

  cmd_vel_publisher_->publish(twist);
}

rcl_interfaces::msg::SetParametersResult JoyDrive::on_param_update(const std::vector<rclcpp::Parameter> & params)
{
  rcl_interfaces::msg::SetParametersResult result;
  result.successful = true;

  for (const auto & param : params) {
    if (param.get_name() == "max_linear_velocity_ms") {
      max_linear_ = param.as_double();
      RCLCPP_INFO(get_logger(), "Max linvel updated to %f m/s.", max_linear_);
    } else if (param.get_name() == "max_angular_velocity_radians") {
      max_angular_ = param.as_double();
      RCLCPP_INFO(get_logger(), "Max angvel updated to %f rad/s.", max_angular_);
    } else if (param.get_name() == "target_axes") {
      auto axes = param.as_integer_array();
      target_axes_ = std::make_pair(axes[0], axes[1]);
      RCLCPP_INFO(get_logger(), "Axes updated to [%ld, %ld].", target_axes_.first, target_axes_.second);
    } else if (param.get_name() == "invert_linear_velocity") {
      invert_axes_.first = param.as_bool();
      RCLCPP_INFO(get_logger(), "Linear velocity inversion: %s", invert_axes_.first ? "true" : "false");
    } else if (param.get_name() == "invert_angular_velocity") {
      invert_axes_.second = param.as_bool();
      RCLCPP_INFO(get_logger(), "Angular velocity inversion: %s", invert_axes_.second ? "true" : "false");
    }
  }

  return result;
}

}  // namespace joy_drive

#include <rclcpp_components/register_node_macro.hpp>
RCLCPP_COMPONENTS_REGISTER_NODE(joy_drive::JoyDrive)