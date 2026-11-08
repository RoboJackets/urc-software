#ifndef GROUND_TRUTH_HPP_
#define GROUND_TRUTH_HPP_

#include <nav_msgs/msg/odometry.hpp>
#include <rclcpp/rclcpp.hpp>
#include <tf2/LinearMath/Transform.h>
#include <tf2_msgs/msg/tf_message.hpp>

#include <deque>
#include <optional>
#include <string>
#include <utility>

namespace urc_localization
{

class GroundTruth : public rclcpp::Node
{
public:
  explicit GroundTruth(const rclcpp::NodeOptions & options);

private:
  void handleTransforms(const tf2_msgs::msg::TFMessage::SharedPtr msg);
  // Latches world_T_start_ once the pose has stayed still for the settle window
  bool updateStartFrame(const tf2::Transform & world_T_base, const rclcpp::Time & now);

  rclcpp::Publisher<nav_msgs::msg::Odometry>::SharedPtr odom_publisher_;
  rclcpp::Subscription<tf2_msgs::msg::TFMessage>::SharedPtr tf_subscription_;

  std::string target_child_frame_;
  std::string odom_frame_id_;
  std::string base_frame_id_;
  bool relative_to_first_pose_;
  // Yaw-only frame at the first settled pose, used when relative_to_first_pose_ is set
  std::optional<tf2::Transform> world_T_start_;
  std::deque<std::pair<rclcpp::Time, tf2::Transform>> recent_poses_;
};

}  // namespace urc_localization

#endif  // GROUND_TRUTH_HPP_
