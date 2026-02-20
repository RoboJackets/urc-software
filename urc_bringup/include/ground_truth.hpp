#ifndef GROUND_TRUTH_HPP_
#define GROUND_TRUTH_HPP_

#include <nav_msgs/msg/odometry.hpp>
#include <rclcpp/rclcpp.hpp>
#include <tf2_msgs/msg/tf_message.hpp>

#include <string>

namespace ground_truth
{

class GroundTruth : public rclcpp::Node
{
public:
  explicit GroundTruth(const rclcpp::NodeOptions & options);

private:
  void handleTransforms(const tf2_msgs::msg::TFMessage::SharedPtr msg) const;

  rclcpp::Publisher<nav_msgs::msg::Odometry>::SharedPtr odom_publisher_;
  rclcpp::Subscription<tf2_msgs::msg::TFMessage>::SharedPtr tf_subscription_;

  std::string target_child_frame_;
  std::string odom_frame_id_;
  std::string base_frame_id_;
};

}  // namespace ground_truth

#endif  // GROUND_TRUTH_HPP_
