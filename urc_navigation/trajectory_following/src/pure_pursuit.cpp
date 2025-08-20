#include "pure_pursuit.hpp"
#include "geometry_util.hpp"
#include <tf2_geometry_msgs/tf2_geometry_msgs.hpp>

namespace pure_pursuit
{

PurePursuit::PurePursuit(PurePursuitParams params)
{
  params_ = params;
}

void PurePursuit::setPath(const nav_msgs::msg::Path & path)
{
  path_ = path;
}

geometry_msgs::msg::PoseStamped PurePursuit::getLookaheadPose(
  const nav_msgs::msg::Path & path,
  double lookahead_distance)
{
  // Find the closest pose in the path
  auto closestPoseIt = find_min_by(
    path.poses.begin(), path.poses.end(), [&](const geometry_msgs::msg::PoseStamped & pose)
    {return geometry_util::magnitude(pose.pose.position);});

  // Find the first point outside the lookahead distance, starting at the pose closest to the current pose
  auto pose = std::find_if(
    closestPoseIt, path.poses.end(), [&](const geometry_msgs::msg::PoseStamped & pose)
    {return geometry_util::magnitude(pose.pose.position) > lookahead_distance;});

  // If no point is found, return the last pose in the path
  if (pose == path.poses.end()) {
    return path.poses.back();
  }

  auto prev_pose = std::prev(pose);

  // Find the intersection of the lookahead circle and the line segment between prev_pose and pose, where prev_pose
  // is guaranteed to be within the lookahead circle.
  auto point = geometry_util::circleSegmentIntersection(
    prev_pose->pose.position,
    pose->pose.position, lookahead_distance);

  geometry_msgs::msg::PoseStamped lookahead_point;
  lookahead_point.header.frame_id = pose->header.frame_id;
  lookahead_point.header.stamp = pose->header.stamp;
  lookahead_point.pose.position = point;

  return lookahead_point;
}

PurePursuitOutput PurePursuit::getCommandVelocity(
  const geometry_msgs::msg::TransformStamped & map_to_base_link)
{

  nav_msgs::msg::Path transformed_path_;

  for (const auto & pose : path_.poses) {
    geometry_msgs::msg::PoseStamped transformed_pose;
    tf2::doTransform(pose, transformed_pose, map_to_base_link);
    transformed_path_.poses.push_back(transformed_pose);
  }

  auto lookahead_pose = getLookaheadPose(transformed_path_, params_.lookahead_distance);

  double linear_vel, angular_vel;
  linear_vel = params_.desired_linear_velocity;

  double curvature = geometry_util::calcCurvature(lookahead_pose.pose.position);
  angular_vel = linear_vel * curvature;

  PurePursuitOutput output;

  geometry_msgs::msg::TwistStamped cmd_vel;
  cmd_vel.header = path_.header;
  cmd_vel.twist.linear.x = linear_vel;
  cmd_vel.twist.angular.z = angular_vel;

  output.cmd_vel = cmd_vel;

  // Get inverse of odom_to_base_link
  geometry_msgs::msg::TransformStamped base_link_to_map;
  base_link_to_map.header.stamp = map_to_base_link.header.stamp;
  base_link_to_map.header.frame_id = map_to_base_link.child_frame_id;
  base_link_to_map.child_frame_id = map_to_base_link.header.frame_id;

  tf2::Transform tf_map_to_base_link;
  tf2::fromMsg(map_to_base_link.transform, tf_map_to_base_link);
  base_link_to_map.transform = tf2::toMsg(tf_map_to_base_link.inverse());

  geometry_msgs::msg::PointStamped lookahead_point;
  lookahead_point.header = path_.header;
  lookahead_point.point = lookahead_pose.pose.position;

  tf2::doTransform(lookahead_point, lookahead_point, base_link_to_map);
  output.lookahead_point = lookahead_point;

  return output;
}

} // namespace pure_pursuit
