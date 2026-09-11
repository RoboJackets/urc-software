#include "urc_state_machine/nav_coordinator.hpp"

#include <rclcpp/exceptions/exceptions.hpp>

namespace nav_coordinator
{

void NavCoordinator::sendMissionNavigation()
{
  if (!follower_client_->action_server_is_ready()) {
    failMissionNavigation("Follower action server is unavailable.");
    return;
  }

  NavigateToWaypoint::Goal goal;
  goal.goal = active_waypoint_;
  goal.has_goal = true;
  goal.has_path = false;
  goal.enforce_goal_heading = false;

  rclcpp_action::Client<NavigateToWaypoint>::SendGoalOptions options;
  options.goal_response_callback = [this](const GoalHandleNavigate::SharedPtr & handle) {
      if (!handle) {
        failMissionNavigation("Follower rejected the navigation goal.");
        return;
      }
      active_goal_handle_ = handle;
      transitionTo(State::TRACKING_GOAL, "follower accepted mission navigation");
    };
  options.result_callback = [this](const GoalHandleNavigate::WrappedResult & result) {
      finishMissionNavigation(result);
    };

  transitionTo(State::SENDING_GOAL, "sending mission navigation goal");
  try {
    follower_client_->async_send_goal(goal, options);
  } catch (const rclcpp::exceptions::RCLError & error) {
    failMissionNavigation(error.what());
  }
}

void NavCoordinator::finishMissionNavigation(const GoalHandleNavigate::WrappedResult & result)
{
  if (!active_mission_handle_) {
    return;
  }

  active_goal_handle_.reset();
  if (result.code != rclcpp_action::ResultCode::SUCCEEDED || !result.result ||
    result.result->error_code != NavigateToWaypoint::Result::SUCCESS)
  {
    failMissionNavigation("Follower navigation did not succeed.");
    return;
  }

  const auto transition = state_machine_.handle(
    urc_state_machine::MissionEvent::NAVIGATION_SUCCEEDED);
  if (!transition.accepted ||
    transition.command != urc_state_machine::MissionCommand::COMPLETE_SUCCESS)
  {
    failMissionNavigation("Unexpected mission transition after navigation.");
    return;
  }

  auto mission_result = std::make_shared<ExecuteMission::Result>();
  mission_result->error_code = ExecuteMission::Result::SUCCESS;
  mission_result->message = "Reached the mission waypoint.";
  active_mission_handle_->succeed(mission_result);
  active_mission_handle_.reset();
  mission_reserved_ = false;
  transitionTo(State::SUCCEEDED, "mission navigation completed");
}

void NavCoordinator::failMissionNavigation(const std::string & reason)
{
  if (!active_mission_handle_) {
    return;
  }

  state_machine_.handle(urc_state_machine::MissionEvent::OPERATION_FAILED);
  auto result = std::make_shared<ExecuteMission::Result>();
  result->error_code = ExecuteMission::Result::NAVIGATION_FAILED;
  result->message = reason;
  active_mission_handle_->abort(result);
  active_mission_handle_.reset();
  active_goal_handle_.reset();
  mission_reserved_ = false;
  handleError(ErrorType::FOLLOWER_FAILURE, reason);
  transitionTo(State::FAILED, reason);
}

}
