#ifndef ORIENTATION_POSE_BRIDGE_HPP_
#define ORIENTATION_POSE_BRIDGE_HPP_

#include <rclcpp/rclcpp.hpp>
#include <geometry_msgs/msg/quaternion.hpp>
#include <sensor_msgs/msg/imu.hpp>
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
  void handleTransforms(const tf2_msgs::msg::TFMessage::SharedPtr msg);
  void handleImu(const sensor_msgs::msg::Imu::SharedPtr msg);

  rclcpp::Publisher<urc_msgs::msg::OrientationPoses>::SharedPtr orientation_publisher_;
  rclcpp::Subscription<tf2_msgs::msg::TFMessage>::SharedPtr tf_subscription_;
  rclcpp::Publisher<sensor_msgs::msg::Imu>::SharedPtr imu_publisher_;
  rclcpp::Subscription<sensor_msgs::msg::Imu>::SharedPtr imu_subscription_;
  std::string target_child_frame_;
  geometry_msgs::msg::Quaternion latest_quaternion_;
  bool have_orientation_{false};
};

}  // namespace orientation_pose_bridge

#endif  // ORIENTATION_POSE_BRIDGE_HPP_
