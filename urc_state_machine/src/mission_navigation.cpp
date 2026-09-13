#include "urc_state_machine/nav_coordinator.hpp"

#include <rclcpp/exceptions/exceptions.hpp>

namespace nav_coordinator
{

void NavCoordinator::sendMissionNavigation()
{
  if (!active_mission_) {
    return;
  }

  if (!follower_client_->action_server_is_ready()) {
    failMissionNavigation("Follower action server is unavailable.");
    return;
  }

  NavigateToWaypoint::Goal goal;
  goal.goal = active_mission_->original_waypoint;
  goal.has_goal = true;
  goal.has_path = false;
  goal.enforce_goal_heading = false;

  const auto mission = active_mission_;
  rclcpp_action::Client<NavigateToWaypoint>::SendGoalOptions options;
  options.goal_response_callback =
    [this, mission](const GoalHandleNavigate::SharedPtr & handle) {
      if (active_mission_ != mission) {
        if (handle) {
          follower_client_->async_cancel_goal(handle);
        }
        return;
      }
      if (!handle) {
        failMissionNavigation("Follower rejected the navigation goal.");
        return;
      }
      active_goal_handle_ = handle;
      if (mission->cancellation_requested) {
        follower_client_->async_cancel_goal(handle);
      }
    };
  options.feedback_callback = [this, mission](
    GoalHandleNavigate::SharedPtr,
    const std::shared_ptr<const NavigateToWaypoint::Feedback> feedback) {
      if (active_mission_ != mission) {
        return;
      }

      auto mission_feedback = std::make_shared<ExecuteMission::Feedback>();
      mission_feedback->mission_state = ExecuteMission::Feedback::STATE_NAVIGATING;
      mission_feedback->distance_to_goal = feedback->distance_to_goal;
      mission_feedback->replan_count = feedback->replan_count;
      mission->goal_handle->publish_feedback(mission_feedback);
    };
  options.result_callback = [this, mission](
    const GoalHandleNavigate::WrappedResult & result) {
      if (active_mission_ != mission) {
        return;
      }
      finishMissionNavigation(result);
    };

  transitionTo(urc_state_machine::MissionState::NAVIGATING, "sending mission navigation goal");
  try {
    follower_client_->async_send_goal(goal, options);
  } catch (const rclcpp::exceptions::RCLError & error) {
    failMissionNavigation(error.what());
  }
}

void NavCoordinator::finishMissionNavigation(const GoalHandleNavigate::WrappedResult & result)
{
  if (!active_mission_) {
    return;
  }

  active_goal_handle_.reset();
  if (result.code == rclcpp_action::ResultCode::CANCELED &&
    active_mission_->cancellation_requested)
  {
    finishCanceledMission();
    return;
  }

  if (result.code != rclcpp_action::ResultCode::SUCCEEDED || !result.result ||
    result.result->error_code != NavigateToWaypoint::Result::SUCCESS)
  {
    failMissionNavigation("Follower navigation did not succeed.");
    return;
  }

  auto mission_result = std::make_shared<ExecuteMission::Result>();
  mission_result->error_code = ExecuteMission::Result::SUCCESS;
  mission_result->message = "Reached the mission waypoint.";
  active_mission_->goal_handle->succeed(mission_result);
  active_mission_.reset();
  transitionTo(urc_state_machine::MissionState::SUCCEEDED, "mission navigation completed");
}

void NavCoordinator::finishCanceledMission()
{
  if (!active_mission_) {
    return;
  }

  auto result = std::make_shared<ExecuteMission::Result>();
  result->error_code = ExecuteMission::Result::CANCELED;
  result->message = "Mission canceled.";
  active_mission_->goal_handle->canceled(result);
  active_goal_handle_.reset();
  active_mission_.reset();
  transitionTo(urc_state_machine::MissionState::CANCELED, "mission canceled");
}

void NavCoordinator::failMissionNavigation(const std::string & reason)
{
  if (!active_mission_) {
    return;
  }

  auto result = std::make_shared<ExecuteMission::Result>();
  result->error_code = ExecuteMission::Result::NAVIGATION_FAILED;
  result->message = reason;
  active_mission_->goal_handle->abort(result);
  active_mission_.reset();
  active_goal_handle_.reset();
  handleError(ErrorType::FOLLOWER_FAILURE, reason);
  transitionTo(urc_state_machine::MissionState::FAILED, reason);
}

}
