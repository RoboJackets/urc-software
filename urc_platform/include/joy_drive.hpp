#ifndef JOY_DRIVE_HPP
#define JOY_DRIVE_HPP

#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/joy.hpp>
#include <geometry_msgs/msg/twist_stamped.hpp>
#include <rcl_interfaces/msg/set_parameters_result.hpp>
#include <utility>

namespace joy_drive
{

class JoyDrive : public rclcpp::Node
{
public:
  explicit JoyDrive(const rclcpp::NodeOptions & options);

private:
  double max_linear_;
  double max_angular_;
  std::string joy_command_topic_;
  std::string cmd_vel_topic_;
  std::pair<int64_t, int64_t> target_axes_;
  std::pair<bool, bool> invert_axes_;

  rclcpp::Subscription<sensor_msgs::msg::Joy>::SharedPtr joy_subscriber_;
  rclcpp::Publisher<geometry_msgs::msg::TwistStamped>::SharedPtr cmd_vel_publisher_;

  rclcpp::node_interfaces::OnSetParametersCallbackHandle::SharedPtr param_callback_handle_;
  rcl_interfaces::msg::SetParametersResult on_param_update(const std::vector<rclcpp::Parameter> & params);

  void joy_callback(const sensor_msgs::msg::Joy & msg);
};

}  // namespace joy_drive

#endif