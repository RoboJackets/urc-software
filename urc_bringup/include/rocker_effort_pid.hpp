#pragma once

#include <string>

#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/float64.hpp>
#include <std_msgs/msg/float64_multi_array.hpp>

namespace urc_bringup
{

class RockerEffortPid : public rclcpp::Node
{
public:
  explicit RockerEffortPid(const rclcpp::NodeOptions & options);

private:
  void onPitch(const std_msgs::msg::Float64::SharedPtr msg);

  // Params
  std::string pitch_topic_;
  std::string command_topic_;

  // PID gains
  double kp_{200.0};
  double ki_{0.0};
  double kd_{5.0};
  double effort_limit_{1200.0};
  double i_clamp_{100.0};
  double pitch_target_{0.0};

  // Correction command shaping
  double min_spin_effort_{50.0};      // minimum torque to overcome stiction

  // State
  double last_error_{0.0};
  double integ_error_{0.0};
  rclcpp::Time last_stamp_{};

  // ROS interfaces
  rclcpp::Subscription<std_msgs::msg::Float64>::SharedPtr pitch_sub_;
  rclcpp::Publisher<std_msgs::msg::Float64MultiArray>::SharedPtr cmd_pub_;
};

}  // namespace urc_bringup
