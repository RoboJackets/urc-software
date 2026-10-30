#ifndef URC_SLAM__SLAM_MESSAGES_HPP_
#define URC_SLAM__SLAM_MESSAGES_HPP_

#include <string>

#include <geometry_msgs/msg/pose_stamped.hpp>
#include <geometry_msgs/msg/transform.hpp>
#include <geometry_msgs/msg/transform_stamped.hpp>
#include <gtsam/geometry/Pose3.h>
#include <gtsam/navigation/NavState.h>
#include <nav_msgs/msg/odometry.hpp>
#include <rclcpp/time.hpp>

namespace urc_slam
{

struct OdometryFrames
{
  std::string map_frame;
  std::string base_link_frame;
};

// pose_covariance is GTSAM's [rotation, translation] tangent covariance in
// base_link; velocity_covariance is in the map frame. The message carries
// pose covariance in the map frame (ROS order x y z roll pitch yaw) and
// twist in base_link. Angular velocity is not estimated and is marked
// unknown with a large variance.
nav_msgs::msg::Odometry toOdometryMsg(
  const gtsam::NavState & state,
  const gtsam::Matrix6 & pose_covariance,
  const gtsam::Matrix3 & velocity_covariance,
  const rclcpp::Time & stamp,
  const OdometryFrames & frames
);

geometry_msgs::msg::PoseStamped toPoseStampedMsg(
  const gtsam::Pose3 & pose,
  const rclcpp::Time & stamp,
  const std::string & frame_id
);

geometry_msgs::msg::TransformStamped toTransformMsg(
  const gtsam::Pose3 & parent_T_child,
  const rclcpp::Time & stamp,
  const OdometryFrames & frames
);

gtsam::Pose3 toPose3(const geometry_msgs::msg::Transform & transform);

}  // namespace urc_slam

#endif  // URC_SLAM__SLAM_MESSAGES_HPP_
