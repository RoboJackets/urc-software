#include "urc_trajectory_following/lqr/lqr_tracker.hpp"

#include "urc_trajectory_following/lqr/discrete_lqr.hpp"

#include <tf2/LinearMath/Transform.h>
#include <tf2/utils.h>
#include <tf2_geometry_msgs/tf2_geometry_msgs.hpp>

#include <algorithm>
#include <cmath>
#include <stdexcept>
#include <utility>
#include <vector>

namespace lqr
{
namespace
{
constexpr double kPathSmoothingWindow = 0.4;
constexpr double kHeadingAlignmentGain = 2.0;

/**
 * Small-error path tracking model, state [lateral_error, heading_error], input extra yaw rate:
 * lateral_error' = speed * heading_error, heading_error' = input. Discretized exactly.
 */
LinearModel pathTrackingModel(double speed, double period)
{
  LinearModel model{Eigen::MatrixXd(2, 2), Eigen::MatrixXd(2, 1)};
  model.state_matrix << 1.0, speed * period, 0.0, 1.0;
  model.input_matrix << speed * period * period / 2.0, period;
  return model;
}

QuadraticCost brysonCost(const LqrParams & params)
{
  QuadraticCost cost{Eigen::MatrixXd::Zero(2, 2), Eigen::MatrixXd(1, 1)};
  cost.state_weight(0, 0) = 1.0 / std::pow(params.max_lateral_error, 2);
  cost.state_weight(1, 1) = 1.0 / std::pow(params.max_heading_error, 2);
  cost.input_weight(0, 0) = 1.0 / std::pow(params.max_angular_correction, 2);
  return cost;
}

/** map_to_base_link maps map points into base_link, so its inverse is the rover pose in map. */
PlanarPose roverPoseInMap(const geometry_msgs::msg::TransformStamped & map_to_base_link)
{
  tf2::Transform map_from_rover;
  tf2::fromMsg(map_to_base_link.transform, map_from_rover);
  map_from_rover = map_from_rover.inverse();
  const tf2::Vector3 & origin = map_from_rover.getOrigin();
  return PlanarPose{
    Eigen::Vector2d(origin.x(), origin.y()), tf2::getYaw(map_from_rover.getRotation())};
}
}  // namespace

LqrTracker::LqrTracker(const LqrParams & params)
: params_(params)
{
  if (params.desired_linear_velocity <= 0.0 || params.control_period <= 0.0) {
    throw std::invalid_argument("LQR needs a positive desired_linear_velocity and control_period");
  }
  const auto gain = solveDiscreteLqr(
    pathTrackingModel(params.desired_linear_velocity, params.control_period), brysonCost(params));
  if (!gain) {
    throw std::invalid_argument("LQR gain did not converge for the given parameters");
  }
  gain_ = gain->transpose();
}

void LqrTracker::setPath(const nav_msgs::msg::Path & path)
{
  path_header_ = path.header;
  std::vector<Eigen::Vector2d> points;
  points.reserve(path.poses.size());
  for (const auto & pose : path.poses) {
    points.emplace_back(pose.pose.position.x, pose.pose.position.y);
  }
  try {
    geometry_.emplace(std::move(points), kPathSmoothingWindow);
  } catch (const std::invalid_argument &) {
    geometry_.reset();
  }
}

trajectory_following::TrajectoryOutput LqrTracker::getCommandVelocity(
  const rclcpp::Logger & logger,
  const geometry_msgs::msg::TransformStamped & map_to_base_link)
{
  trajectory_following::TrajectoryOutput output;
  output.cmd_vel.header = path_header_;
  output.tracking_point.header = path_header_;
  if (!geometry_) {
    RCLCPP_WARN_ONCE(logger, "LQR has no usable path (needs two distinct poses); stopping");
    return output;
  }

  const PathTrackingError error = geometry_->trackingError(roverPoseInMap(map_to_base_link));
  output.cmd_vel.twist = steer(error);

  const Eigen::Vector2d tracking_point =
    geometry_->pointAt(error.arc_length + params_.lookahead_distance);
  output.tracking_point.point.x = tracking_point.x();
  output.tracking_point.point.y = tracking_point.y();
  return output;
}

geometry_msgs::msg::Twist LqrTracker::steer(const PathTrackingError & error) const
{
  geometry_msgs::msg::Twist twist;
  if (std::abs(error.heading_error) > params_.heading_alignment_tolerance) {
    twist.angular.z = std::clamp(
      -kHeadingAlignmentGain * error.heading_error,
      -params_.max_angular_velocity, params_.max_angular_velocity);
    return twist;
  }

  const double speed = params_.desired_linear_velocity;
  const double feedback = gain_.dot(Eigen::Vector2d(error.lateral_error, error.heading_error));
  twist.linear.x = speed;
  twist.angular.z = std::clamp(
    speed * error.curvature - feedback,
    -params_.max_angular_velocity, params_.max_angular_velocity);
  return twist;
}
}  // namespace lqr
