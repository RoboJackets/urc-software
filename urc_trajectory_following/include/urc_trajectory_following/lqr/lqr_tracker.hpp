#ifndef LQR_TRACKER_HPP_
#define LQR_TRACKER_HPP_

#include "urc_trajectory_following/lqr/path_geometry.hpp"
#include "urc_trajectory_following/trajectory_controller.hpp"

#include <Eigen/Dense>
#include <nav_msgs/msg/path.hpp>
#include <std_msgs/msg/header.hpp>

#include <optional>

namespace lqr
{
/**
 * Weights follow Bryson's rule: each is the largest value we accept for that error or input.
 * Lengths in m, angles in rad, rates in rad/s, control_period in s.
 */
struct LqrParams
{
  double desired_linear_velocity;
  double max_angular_velocity;
  double heading_alignment_tolerance;
  double lookahead_distance;
  double control_period;
  double max_lateral_error;
  double max_heading_error;
  double max_angular_correction;
};

/**
 * Tracks a path by driving forward at a constant speed and steering with
 * omega = speed * curvature - K [lateral_error, heading_error].
 */
class LqrTracker : public trajectory_following::TrajectoryController
{
public:
  /** @throws std::invalid_argument if the parameters do not give a stabilizing gain. */
  explicit LqrTracker(const LqrParams & params);

  void setPath(const nav_msgs::msg::Path & path) override;

  trajectory_following::TrajectoryOutput getCommandVelocity(
    const rclcpp::Logger & logger,
    const geometry_msgs::msg::TransformStamped & map_to_base_link) override;

private:
  geometry_msgs::msg::Twist steer(const PathTrackingError & error) const;

  LqrParams params_;
  Eigen::Vector2d gain_;
  std_msgs::msg::Header path_header_;
  std::optional<PathGeometry> geometry_;
};
}  // namespace lqr

#endif  // LQR_TRACKER_HPP_
