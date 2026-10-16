#ifndef PURE_PURSUIT_HPP_
#define PURE_PURSUIT_HPP_

#include "urc_trajectory_following/trajectory_controller.hpp"
#include <geometry_msgs/msg/point_stamped.hpp>
#include <geometry_msgs/msg/pose_stamped.hpp>
#include <geometry_msgs/msg/twist_stamped.hpp>
#include <nav_msgs/msg/path.hpp>
#include <rclcpp/rclcpp.hpp>

namespace pure_pursuit
{
template<typename Iterator, typename UnaryPredicate>
Iterator find_min_by(Iterator first, Iterator last, UnaryPredicate pred)
{
  auto minValue = pred(*first);
  auto minIt = first;
  while (first != last) {
    auto compareValue = pred(*first);
    if (compareValue < minValue) {
      minValue = compareValue;
      minIt = first;
    }

    ++first;
  }
  return minIt;
}

struct PurePursuitParams
{
  double lookahead_distance;
  double desired_linear_velocity;
  double max_angular_velocity;
  double heading_alignment_tolerance;
  bool enable_swerve_motion;
};


class PurePursuit : public trajectory_following::TrajectoryController
{
public:
  explicit PurePursuit(PurePursuitParams params);

  /**
   * @brief Set the path to follow
   * @param path The path to follow in the local frame (usually the base_link
   * frame)
   */
  void setPath(const nav_msgs::msg::Path & path) override;

  /**
   * @brief Get the desired velocity command and lookahead point given the
   * current pose
   * @param map_to_base_link Transform from the map frame to base link
   */
  trajectory_following::TrajectoryOutput getCommandVelocity(
    const rclcpp::Logger & logger,
    const geometry_msgs::msg::TransformStamped & map_to_base_link) override;

private:
  /**
   * @brief Get the lookahead pose
   * @param path The path to follow in the local frame (usually the base_link
   * frame)
   * @param lookahead_distance The distance to look ahead (m)
   */
  geometry_msgs::msg::PoseStamped
  getLookaheadPose(
    const rclcpp::Logger & logger,
    const nav_msgs::msg::Path & path, double lookahead_distance);

  nav_msgs::msg::Path path_;

  PurePursuitParams params_;
};
} // namespace pure_pursuit

#endif // PURE_PURSUIT_HPP_
