#include "urc_state_machine/nav_coordinator.hpp"

namespace nav_coordinator
{
void NavCoordinator::transitionOn(Event event)
{
  const State next = urc_state_machine::astronautTransition(mission_.state, event);
  if (next == mission_.state) {
    return;
  }
  mission_.retries = 0;
  if (next == State::SUCCEEDED || next == State::STAYING) {
    stopMission(next, 0, next == State::SUCCEEDED ? "Mission completed" : "Remote STAY");
    return;
  }
  if (event == Event::START) {
    beginResume(next);
  } else {
    changeState(next);
  }
}

void NavCoordinator::changeState(State state)
{
  arrival_indicated_ = mission_.state != State::RECOVERING && mission_.state != State::RESUMING &&
    (state == State::WAIT_FOLLOW || state == State::WAIT_STAY || state == State::WAIT_GIVE);
  spiral_search_->cancel();
  mission_.state = state;
  mission_.phase_started = urc_state_machine::MissionClock::now();
  mission_.operation_started = false;
  mission_.navigation_reached = false;
  mission_.reason.clear();
  publishState();
}

void NavCoordinator::startNavigation(const Pose & goal)
{
  mission_.navigation_goal = goal;
  mission_.navigation_reached = false;
  mission_.last_goal_update = urc_state_machine::MissionClock::now();
  navigation_->replace(goal);
}

void NavCoordinator::updateNavigationOutcome(urc_state_machine::NavigationResult result)
{
  using Result = urc_state_machine::NavigationResult;
  if (mission_.state == State::STOPPING || mission_.state == State::RECOVERING ||
    mission_.state == State::PAUSED || mission_.state == State::RESUMING ||
    result == Result::STOPPED)
  {
    return;
  }
  if (result != Result::REACHED) {
    retryStateOrPause(
      mission_.state, Route::Result::NAVIGATION_FAILED,
      "Navigation failed or was canceled externally");
    return;
  }
  mission_.navigation_reached = true;
}

void NavCoordinator::updateMission()
{
  if (mission_.kind == Kind::NONE) {
    updateResume();
    return;
  }
  if (auto result = navigation_->takeResult()) {
    updateNavigationOutcome(*result);
  }
  if (mission_.state == State::PAUSED || mission_.state == State::RESUMING) {
    updateResume();
    publishFeedback();
    return;
  }
  if (mission_.state == State::STOPPING) {
    updateStopping();
    publishFeedback();
    return;
  }
  if (mission_.state == State::RECOVERING) {
    updateRecovery();
    publishFeedback();
    return;
  }
  const double timeout = urc_state_machine::phaseTimeout(mission_.state, parameters_.timeouts);
  if (timeout > 0.0 && phaseElapsed() > timeout) {
    stopMission(
      State::PAUSED, Route::Result::TIMEOUT,
      std::string(urc_state_machine::stateName(mission_.state)) + " deadline exceeded");
    return;
  }
  updateCurrentState();
  publishFeedback();
}

void NavCoordinator::updateCurrentState()
{
  if (mission_.state == State::FETCHING || mission_.state == State::GIVING) {
    completeToolPlaceholder();
    return;
  }
  if (mission_.state == State::WAIT_FOLLOW || mission_.state == State::STAYING ||
    mission_.state == State::HOLDING_HAMMER || mission_.state == State::WAIT_GIVE)
  {
    return;
  }
  const auto rover = roverPose();
  if (!rover) {
    retryStateOrPause(
      mission_.state, Route::Result::NAVIGATION_FAILED, "Rover localization missing or stale");
    return;
  }
  switch (mission_.state) {
    case State::SEARCHING_ARUCO: searchForMarker(); break;
    case State::NAVIGATING: driveToWaypoint(*rover); break;
    case State::GO_TO_ASTRONAUT: driveToAstronaut(*rover); break;
    case State::FOLLOWING: followAstronaut(*rover); break;
    case State::WAIT_STAY: waitForStay(*rover); break;
    case State::COMING: returnToAstronaut(*rover); break;
    default: break;
  }
}
}  // namespace nav_coordinator
