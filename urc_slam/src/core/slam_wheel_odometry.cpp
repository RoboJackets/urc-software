#include "urc_slam/slam_node.hpp"

#include <algorithm>
#include <cmath>
#include <iterator>

#include <Eigen/Geometry>
#include <gtsam/geometry/Pose2.h>

namespace urc_slam
{
namespace
{

constexpr double minimum_quaternion_norm = 1e-6;

gtsam::Pose2 wheelPose(const nav_msgs::msg::Odometry & odometry)
{
  const auto & pose = odometry.pose.pose;
  const auto & q = pose.orientation;
  const Eigen::Quaterniond orientation = Eigen::Quaterniond(q.w, q.x, q.y, q.z).normalized();
  return gtsam::Pose2(
    pose.position.x, pose.position.y, gtsam::Rot3(orientation).yaw());
}

}  // namespace

void SlamNode::odomCallback(const nav_msgs::msg::Odometry::SharedPtr msg)
{
  const auto & p = msg->pose.pose.position;
  const auto & q = msg->pose.pose.orientation;
  const auto & v = msg->twist.twist.linear;

  const Eigen::Quaterniond orientation(q.w, q.x, q.y, q.z);
  if (msg->header.frame_id != parameters.frames.wheel_odometry ||
    msg->child_frame_id != parameters.frames.base_link ||
    !std::isfinite(p.x) || !std::isfinite(p.y) || !orientation.coeffs().allFinite() ||
    !std::isfinite(orientation.norm()) || orientation.norm() < minimum_quaternion_norm ||
    !std::isfinite(v.x) ||
    !std::isfinite(v.y))
  {
    RCLCPP_WARN_THROTTLE(
      get_logger(), *get_clock(), 5000, "Discarding invalid or incorrectly framed wheel odometry");
    return;
  }

  const rclcpp::Time stamp(msg->header.stamp);
  if (last_accepted_odom_stamp && stamp <= *last_accepted_odom_stamp) {
    return;
  }

  odom_buffer.push_back(*msg);
  last_accepted_odom_stamp = stamp;
  while (odom_buffer.size() > maximum_odom_buffer_size) {
    odom_buffer.pop_front();
  }

  if (applyWheelOdometryMatches()) {
    path_pub->publish(path_msg);
  }
}

void SlamNode::matchBufferedOdometry()
{
  const auto & stamps = keyframe_map.stamps();
  while (!odom_buffer.empty()) {
    const auto & odom = odom_buffer.front();
    const rclcpp::Time odom_stamp(odom.header.stamp);

    // Wait until keyframes bracket this measurement's time
    if (odom_stamp > stamps.back()) {
      break;
    }

    auto nearest = std::lower_bound(
      stamps.begin(), stamps.end(), odom_stamp,
      [](const rclcpp::Time & keyframe, const rclcpp::Time & stamp) {
        return keyframe < stamp;
      });
    if (nearest == stamps.end()) {
      --nearest;
    }
    if (nearest != stamps.begin()) {
      const auto previous = std::prev(nearest);
      if (std::abs((*previous - odom_stamp).seconds()) <
        std::abs((*nearest - odom_stamp).seconds()))
      {
        nearest = previous;
      }
    }
    const double best_dt = std::abs((*nearest - odom_stamp).seconds());
    const auto best_index = static_cast<std::size_t>(std::distance(stamps.begin(), nearest));

    if (best_dt <= parameters.wheel_time_tolerance_s) {
      matched_odom.push_back({best_index, odom});
    }

    odom_buffer.pop_front();
  }
}

bool SlamNode::applyWheelOdometryMatches()
{
  if (keyframe_map.size() == 0) {
    return false;
  }

  matchBufferedOdometry();

  bool has_odom_updates = false;
  while (matched_odom.size() >= 2) {
    const auto & previous = matched_odom[0];
    const auto & post = matched_odom[1];

    // Two measurements on one keyframe constrain nothing; keep the earlier
    if (post.keyframe_index <= previous.keyframe_index) {
      matched_odom.erase(matched_odom.begin() + 1);
      continue;
    }

    const auto pose_change = wheelPose(previous.measurement).between(wheelPose(post.measurement));
    const auto & velocity = post.measurement.twist.twist.linear;
    backend.addWheelOdometryFactors(
      previous.keyframe_index, post.keyframe_index, pose_change,
      gtsam::Vector2(velocity.x, velocity.y), parameters.wheel_velocity_sigmas_mps);

    matched_odom.pop_front();
    has_odom_updates = true;
  }

  if (has_odom_updates) {
    backend.optimize();
    keyframe_map.markPosesChanged();
    rebuildPath();
  }
  return has_odom_updates;
}

}  // namespace urc_slam
