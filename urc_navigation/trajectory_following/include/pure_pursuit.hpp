#ifndef PURE_PURSUIT_HPP_
#define PURE_PURSUIT_HPP_

#include <bits/stdc++.h>
#include <geometry_msgs/msg/pose.hpp>
#include <nav_msgs/msg/path.hpp>
#include <geometry_msgs/msg/twist_stamped.hpp>
#include <geometry_msgs/msg/pose_stamped.hpp>

namespace pure_pursuit
{
  struct PurePursuitParams
  {
    double lookahead_distance;
    double desired_linear_velocity;
  };

  class PurePursuit
  {
  public:
    explicit PurePursuit(PurePursuitParams params);

    void setPath(const nav_msgs::msg::Path &path);

    geometry_msgs::msg::TwistStamped getCommandVelocity(
        const geometry_msgs::msg::PoseStamped &current_pose);

  private:
    geometry_msgs::msg::PoseStamped getLookaheadPose(const nav_msgs::msg::Path &path, double lookahead_distance);

    nav_msgs::msg::Path path_;

    PurePursuitParams params_;
  };
} // namespace pure_pursuit

#endif // PURE_PURSUIT_HPP_
