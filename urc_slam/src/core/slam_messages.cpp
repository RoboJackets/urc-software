#include "urc_slam/slam_messages.hpp"

#include <array>

namespace urc_slam
{

namespace
{
constexpr double kUnknownVariance = 1e6;

geometry_msgs::msg::Pose toPoseMsg(const gtsam::Pose3 & pose)
{
  const gtsam::Point3 & position = pose.translation();
  const gtsam::Quaternion orientation = pose.rotation().toQuaternion();
  geometry_msgs::msg::Pose msg;
  msg.position.x = position.x();
  msg.position.y = position.y();
  msg.position.z = position.z();
  msg.orientation.w = orientation.w();
  msg.orientation.x = orientation.x();
  msg.orientation.y = orientation.y();
  msg.orientation.z = orientation.z();
  return msg;
}

// Maps GTSAM's body-frame [rotation, translation] perturbation onto the
// map-frame [translation, rotation] order used by ROS covariances
gtsam::Matrix6 toRosPoseCovariance(
  const gtsam::Matrix6 & tangent_covariance,
  const gtsam::Rot3 & map_R_base
)
{
  const gtsam::Matrix3 rotation = map_R_base.matrix();
  gtsam::Matrix6 jacobian = gtsam::Matrix6::Zero();
  jacobian.block<3, 3>(0, 3) = rotation;
  jacobian.block<3, 3>(3, 0) = rotation;
  return jacobian * tangent_covariance * jacobian.transpose();
}

template<std::size_t Size>
void copyCovariance(const gtsam::Matrix6 & covariance, std::array<double, Size> & destination)
{
  for (int row = 0; row < 6; ++row) {
    for (int col = 0; col < 6; ++col) {
      destination[row * 6 + col] = covariance(row, col);
    }
  }
}
}  // namespace

nav_msgs::msg::Odometry toOdometryMsg(
  const gtsam::NavState & state,
  const gtsam::Matrix6 & pose_covariance,
  const gtsam::Matrix3 & velocity_covariance,
  const rclcpp::Time & stamp,
  const OdometryFrames & frames
)
{
  const gtsam::Rot3 & map_R_base = state.pose().rotation();
  const gtsam::Vector3 body_velocity = map_R_base.unrotate(state.v());

  nav_msgs::msg::Odometry msg;
  msg.header.stamp = stamp;
  msg.header.frame_id = frames.map_frame;
  msg.child_frame_id = frames.base_link_frame;
  msg.pose.pose = toPoseMsg(state.pose());
  copyCovariance(toRosPoseCovariance(pose_covariance, map_R_base), msg.pose.covariance);

  msg.twist.twist.linear.x = body_velocity.x();
  msg.twist.twist.linear.y = body_velocity.y();
  msg.twist.twist.linear.z = body_velocity.z();

  const gtsam::Matrix3 base_R_map = map_R_base.transpose();
  gtsam::Matrix6 twist_covariance = gtsam::Matrix6::Zero();
  twist_covariance.block<3, 3>(0, 0) = base_R_map * velocity_covariance * base_R_map.transpose();
  twist_covariance.block<3, 3>(3, 3) = gtsam::I_3x3 * kUnknownVariance;
  copyCovariance(twist_covariance, msg.twist.covariance);
  return msg;
}

geometry_msgs::msg::PoseStamped toPoseStampedMsg(
  const gtsam::Pose3 & pose,
  const rclcpp::Time & stamp,
  const std::string & frame_id
)
{
  geometry_msgs::msg::PoseStamped msg;
  msg.header.stamp = stamp;
  msg.header.frame_id = frame_id;
  msg.pose = toPoseMsg(pose);
  return msg;
}

geometry_msgs::msg::TransformStamped toTransformMsg(
  const gtsam::Pose3 & parent_T_child,
  const rclcpp::Time & stamp,
  const OdometryFrames & frames
)
{
  const geometry_msgs::msg::Pose pose = toPoseMsg(parent_T_child);
  geometry_msgs::msg::TransformStamped msg;
  msg.header.stamp = stamp;
  msg.header.frame_id = frames.map_frame;
  msg.child_frame_id = frames.base_link_frame;
  msg.transform.translation.x = pose.position.x;
  msg.transform.translation.y = pose.position.y;
  msg.transform.translation.z = pose.position.z;
  msg.transform.rotation = pose.orientation;
  return msg;
}

gtsam::Pose3 toPose3(const geometry_msgs::msg::Transform & transform)
{
  return gtsam::Pose3(
    gtsam::Rot3::Quaternion(
      transform.rotation.w,
      transform.rotation.x,
      transform.rotation.y,
      transform.rotation.z),
    gtsam::Point3(
      transform.translation.x,
      transform.translation.y,
      transform.translation.z));
}

}  // namespace urc_slam
