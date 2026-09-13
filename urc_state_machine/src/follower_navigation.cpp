#include "urc_state_machine/nav_coordinator.hpp"

#include <chrono>
#include <functional>

namespace nav_coordinator
{
void NavCoordinator::sendFollowerGoal(const geometry_msgs::msg::PoseStamped & waypoint)
{
  if (!follower_client_->wait_for_action_server(std::chrono::seconds(2))) {
    handleError(
      ErrorType::SERVER_UNAVAILABLE,
      "Follower action server '" + follower_action_name_ + "' not available.");
    transitionTo(urc_state_machine::MissionState::FAILED, "follower action server unavailable");
    return;
  }

  NavigateToWaypoint::Goal goal_msg;
  goal_msg.goal = waypoint;
  goal_msg.has_goal = true;
  goal_msg.has_path = false;
  goal_msg.enforce_goal_heading = false;

  transitionTo(urc_state_machine::MissionState::NAVIGATING, "forwarding waypoint to follower");

  rclcpp_action::Client<NavigateToWaypoint>::SendGoalOptions options;
  options.goal_response_callback = std::bind(
    &NavCoordinator::handleGoalResponse, this, std::placeholders::_1);
  options.feedback_callback = std::bind(
    &NavCoordinator::handleFeedback, this, std::placeholders::_1, std::placeholders::_2);
  options.result_callback = std::bind(
    &NavCoordinator::handleResult, this, std::placeholders::_1);

  follower_client_->async_send_goal(goal_msg, options);
}

void NavCoordinator::handleGoalResponse(const GoalHandleNavigate::SharedPtr & goal_handle)
{
  if (!goal_handle) {
    handleError(ErrorType::FOLLOWER_FAILURE, "Follower action server rejected the goal.");
    transitionTo(urc_state_machine::MissionState::FAILED, "follower rejected goal");
    return;
  }

  active_goal_handle_ = goal_handle;
}

void NavCoordinator::handleFeedback(
  GoalHandleNavigate::SharedPtr,
  const std::shared_ptr<const NavigateToWaypoint::Feedback> feedback)
{
  RCLCPP_DEBUG(
    get_logger(), "Feedback: dist=%.2f planning=%s replans=%u",
    feedback->distance_to_goal,
    feedback->is_planning ? "true" : "false",
    feedback->replan_count);
}

void NavCoordinator::handleResult(const GoalHandleNavigate::WrappedResult & result)
{
  active_goal_handle_.reset();

  if (result.code == rclcpp_action::ResultCode::SUCCEEDED) {
    if (result.result->error_code == NavigateToWaypoint::Result::SUCCESS) {
      transitionTo(urc_state_machine::MissionState::SUCCEEDED, "follower reported success");
      return;
    }

    switch (result.result->error_code) {
      case NavigateToWaypoint::Result::OBSTACLE_DETECTED:
        handleError(ErrorType::OBSTACLE_DETECTED, "Obstacle detected during trajectory following.");
        break;
      case NavigateToWaypoint::Result::PLANNING_FAILED:
        handleError(ErrorType::PLANNING_FAILED_IN_FOLLOWER, "Path planning failed in follower.");
        break;
      case NavigateToWaypoint::Result::FAILURE:
        handleError(ErrorType::FOLLOWER_FAILURE, "Follower reported generic failure.");
        break;
      default:
        handleError(
          ErrorType::UNKNOWN_ERROR,
          "Follower finished with error_code=" + std::to_string(result.result->error_code));
        break;
    }
    transitionTo(urc_state_machine::MissionState::FAILED, "follower finished with error");
    return;
  }

  if (result.code == rclcpp_action::ResultCode::ABORTED) {
    handleError(ErrorType::FOLLOWER_FAILURE, "Follower aborted goal.");
    transitionTo(urc_state_machine::MissionState::FAILED, "follower aborted goal");
    return;
  }

  if (result.code == rclcpp_action::ResultCode::CANCELED) {
    transitionTo(urc_state_machine::MissionState::CANCELED, "follower canceled goal");
    return;
  }

  handleError(
    ErrorType::UNKNOWN_ERROR,
    "Unknown follower result code: " + std::to_string(static_cast<int>(result.code)));
  transitionTo(urc_state_machine::MissionState::FAILED, "unknown follower result code");
}

}
