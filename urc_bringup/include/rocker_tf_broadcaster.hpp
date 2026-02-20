#pragma once

#include <atomic>
#include <memory>
#include <string>

#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/joint_state.hpp>
#include <std_msgs/msg/float64.hpp>

#include <geometry_msgs/msg/transform_stamped.hpp>
#include <tf2/LinearMath/Quaternion.h>
#include <tf2_ros/transform_broadcaster.h>
#include <atomic>

namespace urc_bringup
{

class RockerTfBroadcaster : public rclcpp::Node
{
public:
  explicit RockerTfBroadcaster(const rclcpp::NodeOptions & options);

private:
  void onJointState(const sensor_msgs::msg::JointState::SharedPtr msg);

  // Params
  std::string left_joint_name_;
  std::string right_joint_name_;
  std::string joint_state_topic_;

  // Optional TF output (you can disable in .cpp by not creating broadcaster)
  std::string parent_frame_;
  std::string child_frame_;

    bool invert_sign_{true};

  rclcpp::Subscription<sensor_msgs::msg::JointState>::SharedPtr js_sub_;
  rclcpp::Publisher<std_msgs::msg::Float64>::SharedPtr angle_pub_;
  std::unique_ptr<tf2_ros::TransformBroadcaster> tf_broadcaster_;

  double bias_rad_{0.0};
  bool auto_bias_{true};
  bool bias_set_{false};                 // <-- ADD THIS
  std::atomic<double> calibrated_bias_{0.0};

  rclcpp::Publisher<std_msgs::msg::Float64>::SharedPtr pitch_pub_;

  int left_index_{-1};
  int right_index_{-1};
};

}  // namespace urc_bringup