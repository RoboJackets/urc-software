#ifndef ORIENTATION_POSE_BRIDGE_HPP_
#define ORIENTATION_POSE_BRIDGE_HPP_

#include <rclcpp/rclcpp.hpp>
#include <tf2_msgs/msg/tf_message.hpp>
#include <urc_msgs/msg/orientation_poses.hpp>

#include <string>

namespace orientation_pose_bridge
{

class OrientationPoseBridge : public rclcpp::Node
{
public:
  explicit OrientationPoseBridge(const rclcpp::NodeOptions & options);

private:
  void handleTransforms(const tf2_msgs::msg::TFMessage::SharedPtr msg) const;

  rclcpp::Publisher<urc_msgs::msg::OrientationPoses>::SharedPtr publisher_;
  rclcpp::Subscription<tf2_msgs::msg::TFMessage>::SharedPtr subscription_;
  std::string target_child_frame_;
};

}  // namespace orientation_pose_bridge

#endif  // ORIENTATION_POSE_BRIDGE_HPP_
