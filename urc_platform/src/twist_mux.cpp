#include "twist_mux.hpp"
#include <rclcpp/logging.hpp>

namespace twist_mux
{
TwistMux::TwistMux(const rclcpp::NodeOptions & options)
: Node("twist_mux", options)
{
  declare_parameter("autonomous_cmd_vel_topic", "/cmd_vel_autonomous");
  declare_parameter("teleop_cmd_vel_topic", "/cmd_vel_teleop");
  declare_parameter("enabled_topic", "/cmd_vel_enabled");
  declare_parameter("mode_topic", "/cmd_vel_mode");
  declare_parameter("cmd_out_topic", "/rover_drivetrain_controller/cmd_vel");

  enabled = true;
  mode = "autonomous";

  cmd_publisher = create_publisher<geometry_msgs::msg::TwistStamped>(
    get_parameter("cmd_out_topic").as_string(), rclcpp::SystemDefaultsQoS());

  autonomous_subscriber = create_subscription<geometry_msgs::msg::TwistStamped>(
    get_parameter("autonomous_cmd_vel_topic").as_string(),
    rclcpp::SystemDefaultsQoS(),
    [this](const geometry_msgs::msg::TwistStamped::SharedPtr msg) {
      if (enabled && mode == "autonomous") {
        cmd_publisher->publish(*msg);
      }
    });

  teleop_subscriber = create_subscription<geometry_msgs::msg::TwistStamped>(
    get_parameter("teleop_cmd_vel_topic").as_string(),
    rclcpp::SystemDefaultsQoS(),
    [this](const geometry_msgs::msg::TwistStamped::SharedPtr msg) {
      if (enabled && mode == "teleop") {
        cmd_publisher->publish(*msg);
      }
    });

  enabled_subscriber = create_subscription<std_msgs::msg::Bool>(
    get_parameter("enabled_topic").as_string(), rclcpp::SystemDefaultsQoS(),
    [this](const std_msgs::msg::Bool::SharedPtr msg) {
      enabled = msg->data;
      if (!enabled) {
        geometry_msgs::msg::TwistStamped msg;
        msg.header.stamp = now();
        cmd_publisher->publish(msg);
      }
      // RCLCPP_WARN(get_logger(), "Enabled: %d", enabled);
    });

  mode_subscriber = create_subscription<std_msgs::msg::String>(
    get_parameter("mode_topic").as_string(), rclcpp::SystemDefaultsQoS(),
    [this](const std_msgs::msg::String::SharedPtr msg) {mode = msg->data;});
}
} // namespace twist_mux

RCLCPP_COMPONENTS_REGISTER_NODE(twist_mux::TwistMux)
