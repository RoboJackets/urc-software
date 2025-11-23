#ifndef ROVER_POSE_BRIDGE_HPP_
#define ROVER_POSE_BRIDGE_HPP_

#include <rclcpp/rclcpp.hpp>
#include <tf2_msgs/msg/tf_message.hpp>
#include <urc_msgs/msg/rover_poses.hpp>
#include <tf2_ros/transform_broadcaster.h>


#include <string>

namespace rover_pose_bridge
{

class RoverPoseBridge : public rclcpp::Node
{
public:
  explicit RoverPoseBridge(const rclcpp::NodeOptions & options);

private:
  void handleTransforms(const tf2_msgs::msg::TFMessage::SharedPtr msg) const;
  
  rclcpp::Publisher<urc_msgs::msg::RoverPoses>::SharedPtr publisher_;
  rclcpp::Subscription<tf2_msgs::msg::TFMessage>::SharedPtr subscription_;
  std::unique_ptr<tf2_ros::TransformBroadcaster> tf_broadcaster_;
  
  std::string target_child_frame_;
};

}  // namespace rover_pose_bridge

#endif  // ROVER_POSE_BRIDGE_HPP_