#pragma once

#include <rclcpp/rclcpp.hpp>
#include <rclcpp_action/rclcpp_action.hpp>

#include <nav_msgs/msg/path.hpp>
#include <visualization_msgs/msg/marker.hpp>
#include "urc_msgs/action/navigate_to_waypoint.hpp"

namespace trajectory_following
{

class SquareBoxSearchPattern : public rclcpp::Node
{
public:
  explicit SquareBoxSearchPattern(const rclcpp::NodeOptions & options);

private:
  nav_msgs::msg::Path buildPath() const;
  void sendNextPathGoal();

  rclcpp::Publisher<nav_msgs::msg::Path>::SharedPtr path_publisher_;
  rclcpp::Publisher<visualization_msgs::msg::Marker>::SharedPtr marker_publisher_;
  rclcpp_action::Client<urc_msgs::action::NavigateToWaypoint>::SharedPtr action_client_;
  rclcpp::TimerBase::SharedPtr send_timer_;
  nav_msgs::msg::Path generated_path_;

  bool goal_in_flight_{false};
  bool completed_{false};
  bool auto_send_{true};

  // Parameters
  std::string frame_id_;
  std::string action_name_;
  double start_x_{0.0};
  double start_y_{0.0};
  double start_z_{0.0};
  double leg_step_{2.0};
  double segment_resolution_{0.5};
  double max_radius_{20.0};
};

}  // namespace trajectory_following
