#ifndef PURE_PURSUIT_HPP_
#define PURE_PURSUIT_HPP_

#include <bits/stdc++.h>
#include <geometry_msgs/msg/pose.hpp>
#include <nav_msgs/msg/path.hpp>

namespace pure_pursuit
{
    class PurePursuit
    {
    public:
        explicit PurePursuit();

        void setPath(const nav_msgs::msg::Path &path);
        void setLookaheadDistance(double distance);
        void setCurrentPose(const geometry_msgs::msg::Pose &pose);

        geometry_msgs::msg::Pose getTargetPose();

    private:
        nav_msgs::msg::Path path_;
        double lookahead_distance_;
        geometry_msgs::msg::Pose current_pose_;
    };
} // namespace pure_pursuit

#endif // PURE_PURSUIT_HPP_