#include "urc_platform/twist_mux.hpp"

#include <cmath>
#include <initializer_list>
#include <stdexcept>
#include <rclcpp_components/register_node_macro.hpp>

namespace twist_mux
{
TwistMux::TwistMux(const rclcpp::NodeOptions & options)
: Node("twist_mux", options)
{
  declare_parameter("autonomous_cmd_vel_topic", "/cmd_vel_autonomous");
  declare_parameter("teleop_cmd_vel_topic", "/cmd_vel_teleop");
  declare_parameter("enabled_topic", "/cmd_vel_enabled");
  declare_parameter("mode_topic", "/cmd_vel_mode");
  declare_parameter("mode_state_topic", "/drive_mode");
  declare_parameter("cmd_out_topic", "/rover_drivetrain_controller/cmd_vel");
  const bool stamped = declare_parameter("cmd_out_stamped", true);
  command_timeout_ = declare_parameter("command_timeout", 0.5);
  if (!std::isfinite(command_timeout_) || command_timeout_ <= 0.0) {
    throw std::invalid_argument("command_timeout must be finite and positive");
  }
  for (const auto * name : {"autonomous_cmd_vel_topic", "teleop_cmd_vel_topic", "enabled_topic",
      "mode_topic", "mode_state_topic", "cmd_out_topic"})
  {
    if (get_parameter(name).as_string().empty()) {
      throw std::invalid_argument(std::string(name) + " must not be empty");
    }
  }
  const auto output = get_parameter("cmd_out_topic").as_string();
  if (stamped) {
    stamped_publisher_ = create_publisher<geometry_msgs::msg::TwistStamped>(output, rclcpp::QoS(1));
  } else {
    twist_publisher_ = create_publisher<geometry_msgs::msg::Twist>(output, rclcpp::QoS(1));
  }
  mode_publisher_ = create_publisher<std_msgs::msg::String>(
    get_parameter("mode_state_topic").as_string(), rclcpp::QoS(1).reliable().transient_local());
  initializeInputs();
  selectMode("teleop");
  watchdog_ = create_wall_timer(
    std::chrono::duration<double>(command_timeout_ / 2.0), [this]() {checkCommandTimeout();});
}

void TwistMux::initializeInputs()
{
  autonomous_subscriber_ = create_subscription<geometry_msgs::msg::TwistStamped>(
    get_parameter("autonomous_cmd_vel_topic").as_string(), rclcpp::QoS(1),
    [this](geometry_msgs::msg::TwistStamped::ConstSharedPtr command) {
      forward(*command, "autonomous");
    });
  teleop_subscriber_ = create_subscription<geometry_msgs::msg::TwistStamped>(
    get_parameter("teleop_cmd_vel_topic").as_string(), rclcpp::QoS(1),
    [this](geometry_msgs::msg::TwistStamped::ConstSharedPtr command) {
      forward(*command, "teleop");
    });
  enabled_subscriber_ = create_subscription<std_msgs::msg::Bool>(
    get_parameter("enabled_topic").as_string(), rclcpp::QoS(1),
    [this](std_msgs::msg::Bool::ConstSharedPtr command) {
      if (enabled_ != command->data) {
        enabled_ = command->data;
        selectMode(enabled_ ? mode_ : "teleop");
      }
    });
  mode_subscriber_ = create_subscription<std_msgs::msg::String>(
    get_parameter("mode_topic").as_string(), rclcpp::QoS(1),
    [this](std_msgs::msg::String::ConstSharedPtr command) {
      if (command->data != "autonomous" && command->data != "teleop") {
        RCLCPP_WARN_THROTTLE(get_logger(), *get_clock(), 5000, "Invalid drive mode");
        return;
      }
      if (command->data == "autonomous" && !enabled_) {
        return;
      }
      if (command->data == mode_) {
        publishMode();
        return;
      }
      selectMode(command->data);
    });
}

void TwistMux::selectMode(const std::string & mode)
{
  mode_ = mode;
  mode_changed_at_ = now();
  last_command_ = std::chrono::steady_clock::time_point{};
  publishStop();
  publishMode();
}

void TwistMux::publishMode()
{
  std_msgs::msg::String state;
  state.data = enabled_ ? mode_ : "disabled";
  mode_publisher_->publish(state);
}

void TwistMux::forward(
  const geometry_msgs::msg::TwistStamped & command, const std::string & source)
{
  if (!enabled_ || mode_ != source || command.header.stamp.sec < 0 ||
    command.header.stamp.nanosec >= 1000000000U)
  {
    return;
  }
  const rclcpp::Time stamp(command.header.stamp);
  const double age = (now() - stamp).seconds();
  if (stamp <= mode_changed_at_ || age < 0.0 || age > command_timeout_) {
    return;
  }
  const auto & velocity = command.twist;
  if (!std::isfinite(velocity.linear.x) || !std::isfinite(velocity.linear.y) ||
    !std::isfinite(velocity.linear.z) || !std::isfinite(velocity.angular.x) ||
    !std::isfinite(velocity.angular.y) || !std::isfinite(velocity.angular.z))
  {
    return;
  }
  last_command_ = std::chrono::steady_clock::now();
  publishVelocity(command);
}

void TwistMux::publishVelocity(const geometry_msgs::msg::TwistStamped & command)
{
  if (stamped_publisher_) {
    stamped_publisher_->publish(command);
  } else {
    twist_publisher_->publish(command.twist);
  }
}

void TwistMux::publishStop()
{
  geometry_msgs::msg::TwistStamped stop;
  stop.header.stamp = now();
  publishVelocity(stop);
}

void TwistMux::checkCommandTimeout()
{
  if (!enabled_ || std::chrono::duration<double>(
      std::chrono::steady_clock::now() - last_command_).count() >= command_timeout_)
  {
    publishStop();
  }
}
}  // namespace twist_mux
RCLCPP_COMPONENTS_REGISTER_NODE(twist_mux::TwistMux)
