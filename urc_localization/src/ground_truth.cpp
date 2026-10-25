#include "urc_localization/ground_truth.hpp"

#include <algorithm>
#include <functional>
#include <geometry_msgs/msg/pose.hpp>
#include <tf2/LinearMath/Matrix3x3.h>
#include <tf2/LinearMath/Quaternion.h>

namespace urc_localization
{

namespace
{
// Matches SLAM's start condition: the rover spawns in the air and settles, so
// the origin is taken only after the pose has been still for this long
constexpr double kSettledWindowS = 1.0;
constexpr double kSettledMaximumTranslationM = 0.02;
constexpr double kSettledMaximumRotationRad = 0.05;
}  // namespace

GroundTruth::GroundTruth(const rclcpp::NodeOptions & options)
: rclcpp::Node("ground_truth", options)
{
  const auto tf_topic = declare_parameter<std::string>("tf_topic", "/ground_truth_pose");
  const auto odom_topic =
    declare_parameter<std::string>("odom_topic", "/ground_truth/odom");
  target_child_frame_ = declare_parameter<std::string>("target_child_frame", "walli");
  odom_frame_id_ = declare_parameter<std::string>("odom_frame_id", "map");
  base_frame_id_ = declare_parameter<std::string>("base_frame_id", "walli");
  // Publish relative to the first pose with the same convention as SLAM's map
  // frame: start position at the origin, start heading along +x, and absolute
  // roll and pitch kept
  relative_to_first_pose_ = declare_parameter<bool>("relative_to_first_pose", false);

  odom_publisher_ = create_publisher<nav_msgs::msg::Odometry>(
    odom_topic,
    rclcpp::SystemDefaultsQoS());

  tf_subscription_ = create_subscription<tf2_msgs::msg::TFMessage>(
    tf_topic,
    rclcpp::SystemDefaultsQoS(),
    std::bind(&GroundTruth::handleTransforms, this, std::placeholders::_1));
}

void GroundTruth::handleTransforms(const tf2_msgs::msg::TFMessage::SharedPtr msg)
{
  if (!odom_publisher_ || msg->transforms.empty()) {
    return;
  }

  const auto matching_target = std::find_if(
    msg->transforms.begin(),
    msg->transforms.end(),
    [this](const geometry_msgs::msg::TransformStamped & tf)
    {
      return tf.child_frame_id == target_child_frame_;
    });
  if (matching_target == msg->transforms.end()) {
    return;
  }

  const auto & target_tf = *matching_target;

  const auto & translation = target_tf.transform.translation;
  const auto & rotation = target_tf.transform.rotation;
  tf2::Transform pose_tf(
    tf2::Quaternion(rotation.x, rotation.y, rotation.z, rotation.w),
    tf2::Vector3(translation.x, translation.y, translation.z));

  if (relative_to_first_pose_) {
    if (!updateStartFrame(pose_tf, now())) {
      return;
    }
    pose_tf = world_T_start_->inverse() * pose_tf;
  }

  geometry_msgs::msg::Pose pose;
  pose.position.x = pose_tf.getOrigin().x();
  pose.position.y = pose_tf.getOrigin().y();
  pose.position.z = pose_tf.getOrigin().z();
  const tf2::Quaternion orientation = pose_tf.getRotation();
  pose.orientation.x = orientation.x();
  pose.orientation.y = orientation.y();
  pose.orientation.z = orientation.z();
  pose.orientation.w = orientation.w();

  nav_msgs::msg::Odometry odom_msg;
  odom_msg.header = target_tf.header;
  odom_msg.header.frame_id = odom_frame_id_;
  odom_msg.child_frame_id = base_frame_id_;
  odom_msg.pose.pose = pose;

  odom_publisher_->publish(std::move(odom_msg));
}

bool GroundTruth::updateStartFrame(const tf2::Transform & world_T_base, const rclcpp::Time & now)
{
  if (world_T_start_) {
    return true;
  }

  recent_poses_.emplace_back(now, world_T_base);
  while ((now - recent_poses_.front().first).seconds() > kSettledWindowS) {
    recent_poses_.pop_front();
  }
  if ((now - recent_poses_.front().first).seconds() < 0.9 * kSettledWindowS) {
    return false;
  }
  for (const auto & [stamp, pose] : recent_poses_) {
    const tf2::Transform motion = pose.inverseTimes(world_T_base);
    if (motion.getOrigin().length() > kSettledMaximumTranslationM ||
      motion.getRotation().getAngleShortestPath() > kSettledMaximumRotationRad)
    {
      return false;
    }
  }

  double roll = 0.0;
  double pitch = 0.0;
  double yaw = 0.0;
  tf2::Matrix3x3(world_T_base.getRotation()).getRPY(roll, pitch, yaw);
  tf2::Quaternion start_heading;
  start_heading.setRPY(0.0, 0.0, yaw);
  world_T_start_ = tf2::Transform(start_heading, world_T_base.getOrigin());
  recent_poses_.clear();
  RCLCPP_INFO(get_logger(), "Ground truth origin set at the settled start pose");
  return true;
}

}  // namespace urc_localization

#include "rclcpp_components/register_node_macro.hpp"
RCLCPP_COMPONENTS_REGISTER_NODE(urc_localization::GroundTruth)
