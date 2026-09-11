#include "urc_state_machine/nav_coordinator.hpp"
#include "urc_state_machine/gps_waypoint_conversion.hpp"

#include <stdexcept>

namespace nav_coordinator
{
void NavCoordinator::handleWaypoint(const geometry_msgs::msg::PoseStamped::SharedPtr msg)
{
  active_waypoint_ = *msg;
  RCLCPP_INFO(
    get_logger(), "Received waypoint: frame=%s x=%.3f y=%.3f",
    active_waypoint_.header.frame_id.c_str(),
    active_waypoint_.pose.position.x,
    active_waypoint_.pose.position.y);

  if (active_goal_handle_ && cancel_on_new_waypoint_) {
    transitionTo(State::CANCELED, "canceling current goal due to new waypoint");
    follower_client_->async_cancel_goal(active_goal_handle_);
    active_goal_handle_.reset();
  }

  sendFollowerGoal(active_waypoint_);
}

void NavCoordinator::handleGpsWaypoint(const urc_msgs::msg::Waypoint::SharedPtr msg)
{
  geometry_msgs::msg::PoseStamped converted_waypoint;
  try {
    converted_waypoint = convertGpsToMapWaypoint(
      *msg, *tf_buffer_, map_frame_id_, utm_frame_id_,
      now());
  } catch (const std::exception & ex) {
    handleError(
      ErrorType::PLANNER_FAILURE,
      std::string("Cannot process GPS waypoint: ") + ex.what());
    transitionTo(State::FAILED, "gps waypoint rejected - transform unavailable");
    return;
  }

  active_waypoint_ = converted_waypoint;

  RCLCPP_INFO(
    get_logger(),
    "Received GPS waypoint: lat=%.8f lon=%.8f -> frame=%s x=%.3f y=%.3f",
    msg->latitude,
    msg->longitude,
    active_waypoint_.header.frame_id.c_str(),
    active_waypoint_.pose.position.x,
    active_waypoint_.pose.position.y);

  if (active_goal_handle_ && cancel_on_new_waypoint_) {
    transitionTo(State::CANCELED, "canceling current goal due to new GPS waypoint");
    follower_client_->async_cancel_goal(active_goal_handle_);
    active_goal_handle_.reset();
  }

  sendFollowerGoal(active_waypoint_);
}

}
