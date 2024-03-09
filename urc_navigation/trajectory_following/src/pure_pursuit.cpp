#include "pure_pursuit.hpp"
#include "geometry_util.hpp"

namespace pure_pursuit
{

  PurePursuit::PurePursuit(PurePursuitParams params)
  {
    params_ = params;
  }

  void PurePursuit::setPath(const nav_msgs::msg::Path &path)
  {
    path_ = path;
  }

  geometry_msgs::msg::PoseStamped PurePursuit::getLookaheadPose(const nav_msgs::msg::Path &path, double lookahead_distance)
  {
    // Find the first point outside the lookahead distance
    auto pose = std::find_if(path.poses.begin(), path.poses.end(), [&](const geometry_msgs::msg::PoseStamped &pose)
                             { return geometry_util::dist2D(pose.pose.position, path.poses.front().pose.position) > lookahead_distance; });

    // If no point is found, return the last pose in the path
    if (pose == path.poses.end())
    {
      return path.poses.back();
    }

    auto prev_pose = std::prev(pose);

    // Find the intersection of the lookahead circle and the line segment between prev_pose and pose, where prev_pose
    // is guaranteed to be within the lookahead circle.
    auto point = geometry_util::circleSegmentIntersection(prev_pose->pose.position, pose->pose.position, lookahead_distance);

    geometry_msgs::msg::PoseStamped lookahead_point;
    lookahead_point.header.frame_id = prev_pose->header.frame_id;
    lookahead_point.header.stamp = prev_pose->header.stamp;
    lookahead_point.pose.position = point;

    return lookahead_point;
  }

  geometry_msgs::msg::TwistStamped PurePursuit::getCommandVelocity(
      const geometry_msgs::msg::PoseStamped &current_pose)
  {
    auto lookahead_pose = getLookaheadPose(path_, params_.lookahead_distance);

    double linear_vel, angular_vel;
    linear_vel = params_.desired_linear_velocity;

    double curvature = geometry_util::calcCurvature(current_pose.pose.position, lookahead_pose.pose.position);
    angular_vel = linear_vel * curvature;

    geometry_msgs::msg::TwistStamped cmd_vel;
    cmd_vel.header = current_pose.header;
    cmd_vel.twist.linear.x = linear_vel;
    cmd_vel.twist.angular.z = angular_vel;

    return cmd_vel;
  }

} // namespace pure_pursuit
