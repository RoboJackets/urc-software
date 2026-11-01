#ifndef URC_PLATFORM__TWIST_MUX_HPP_
#define URC_PLATFORM__TWIST_MUX_HPP_

#include <chrono>
#include <string>
#include <geometry_msgs/msg/twist.hpp>
#include <geometry_msgs/msg/twist_stamped.hpp>
#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/bool.hpp>
#include <std_msgs/msg/string.hpp>

namespace twist_mux
{
class TwistMux : public rclcpp::Node
{
public:
  explicit TwistMux(const rclcpp::NodeOptions & options);

private:
  void initializeInputs();
  void selectMode(const std::string & mode);
  void publishMode();
  void forward(const geometry_msgs::msg::TwistStamped & command, const std::string & source);
  void publishVelocity(const geometry_msgs::msg::TwistStamped & command);
  void publishStop();
  void checkCommandTimeout();

  rclcpp::Subscription<geometry_msgs::msg::TwistStamped>::SharedPtr autonomous_subscriber_;
  rclcpp::Subscription<geometry_msgs::msg::TwistStamped>::SharedPtr teleop_subscriber_;
  rclcpp::Subscription<std_msgs::msg::Bool>::SharedPtr enabled_subscriber_;
  rclcpp::Subscription<std_msgs::msg::String>::SharedPtr mode_subscriber_;
  rclcpp::Publisher<std_msgs::msg::String>::SharedPtr mode_publisher_;
  rclcpp::Publisher<geometry_msgs::msg::TwistStamped>::SharedPtr stamped_publisher_;
  rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr twist_publisher_;
  rclcpp::TimerBase::SharedPtr watchdog_;
  bool enabled_{true};
  std::string mode_{"teleop"};
  double command_timeout_{0.5};
  rclcpp::Time mode_changed_at_{0, 0, RCL_ROS_TIME};
  std::chrono::steady_clock::time_point last_command_{};
};
}  // namespace twist_mux
#endif  // URC_PLATFORM__TWIST_MUX_HPP_
