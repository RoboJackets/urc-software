#ifndef PURE_PURSUIT_HPP_
#define PURE_PURSUIT_HPP_

#include <bits/stdc++.h>
#include <nav_msgs/msg/path.hpp>
#include <geometry_msgs/msg/twist_stamped.hpp>
#include <geometry_msgs/msg/pose_stamped.hpp>
#include <geometry_msgs/msg/point_stamped.hpp>

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
};

struct PurePursuitOutput
{
  geometry_msgs::msg::TwistStamped cmd_vel;
  geometry_msgs::msg::PointStamped lookahead_point;
};

class PurePursuit
{
public:
  explicit PurePursuit(PurePursuitParams params);

  void setPath(const nav_msgs::msg::Path & path);

  PurePursuitOutput getCommandVelocity(
    const geometry_msgs::msg::PoseStamped & current_pose);

private:
  geometry_msgs::msg::PoseStamped getLookaheadPose(
    const nav_msgs::msg::Path & path,
    double lookahead_distance,
    const geometry_msgs::msg::PoseStamped & current_pose);

  nav_msgs::msg::Path path_;

  PurePursuitParams params_;
};
} // namespace pure_pursuit

#endif // PURE_PURSUIT_HPP_
