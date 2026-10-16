#pragma once

#include <string>

#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/joint_state.hpp>
#include <std_msgs/msg/float64.hpp>

namespace urc_controllers
{

// Publishes signed mean rocker angle in radians; does not publish TF.
class RockerTfBroadcaster : public rclcpp::Node
{
public:
  explicit RockerTfBroadcaster(const rclcpp::NodeOptions & options);

private:
  void onJointState(const sensor_msgs::msg::JointState::SharedPtr msg);

  std::string left_joint_name_;
  std::string right_joint_name_;
  std::string joint_state_topic_;
  std::string pitch_topic_;
  bool invert_sign_{true};

  rclcpp::Subscription<sensor_msgs::msg::JointState>::SharedPtr js_sub_;
  rclcpp::Publisher<std_msgs::msg::Float64>::SharedPtr pitch_pub_;
};

}  // namespace urc_controllers
