#include "urc_state_machine/nav_coordinator.hpp"

#include <functional>
#include <cmath>
#include <stdexcept>

namespace nav_coordinator
{
namespace
{
bool hasValidPose(const geometry_msgs::msg::Pose & pose)
{
  const auto & position = pose.position;
  const auto & orientation = pose.orientation;
  const double orientation_norm =
    orientation.x * orientation.x + orientation.y * orientation.y +
    orientation.z * orientation.z + orientation.w * orientation.w;
  constexpr double quaternion_norm_tolerance = 1e-3;

  return std::isfinite(position.x) && std::isfinite(position.y) &&
         std::isfinite(position.z) && std::isfinite(orientation_norm) &&
         std::abs(orientation_norm - 1.0) <= quaternion_norm_tolerance;
}
}

void NavCoordinator::initializeMissionActionServer()
{
  const auto action_name = declare_parameter<std::string>(
    "mission_action_name", "execute_autonomous_mission");

  if (action_name.empty()) {
    throw std::invalid_argument("mission_action_name must not be empty");
  }

  mission_server_ = rclcpp_action::create_server<ExecuteMission>(
    this,
    action_name,
    std::bind(
      &NavCoordinator::handleMissionGoal, this,
      std::placeholders::_1, std::placeholders::_2),
    std::bind(
      &NavCoordinator::handleMissionCancel, this,
      std::placeholders::_1),
    std::bind(
      &NavCoordinator::handleMissionAccepted, this,
      std::placeholders::_1));
}

rclcpp_action::GoalResponse NavCoordinator::handleMissionGoal(
  const rclcpp_action::GoalUUID &,
  std::shared_ptr<const ExecuteMission::Goal> goal)
{
  if (!goal || goal->search_mode != ExecuteMission::Goal::SEARCH_NONE ||
    goal->waypoint.header.frame_id != map_frame_id_ || !hasValidPose(goal->waypoint.pose))
  {
    return rclcpp_action::GoalResponse::REJECT;
  }

  if (active_mission_ || active_goal_handle_ || !follower_client_->action_server_is_ready()) {
    return rclcpp_action::GoalResponse::REJECT;
  }

  return rclcpp_action::GoalResponse::ACCEPT_AND_EXECUTE;
}

rclcpp_action::CancelResponse NavCoordinator::handleMissionCancel(
  std::shared_ptr<MissionGoalHandle> goal_handle)
{
  if (!active_mission_ || active_mission_->goal_handle != goal_handle) {
    return rclcpp_action::CancelResponse::REJECT;
  }

  active_mission_->cancellation_requested = true;
  if (active_goal_handle_) {
    follower_client_->async_cancel_goal(active_goal_handle_);
  }

  return rclcpp_action::CancelResponse::ACCEPT;
}

void NavCoordinator::handleMissionAccepted(
  std::shared_ptr<MissionGoalHandle> goal_handle)
{
  active_mission_ = std::make_shared<urc_state_machine::ActiveMission>();
  active_mission_->goal_handle = goal_handle;
  active_mission_->original_waypoint = goal_handle->get_goal()->waypoint;
  active_mission_->search_mode = urc_state_machine::SearchMode::NONE;
  last_error_ = ErrorType::NONE;
  last_error_details_.clear();

  sendMissionNavigation();
}

}
