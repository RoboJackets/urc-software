#include "urc_state_machine/nav_coordinator.hpp"

namespace nav_coordinator
{
void NavCoordinator::transitionOn(Event event)
{
  const State next = mission_.kind == Kind::ROUTE ?
    urc_state_machine::routeTransition(mission_.state, event) :
    urc_state_machine::astronautTransition(mission_.state, event);
  if (next == mission_.state) {
    return;
  }
  if (mission_.kind == Kind::ASTRONAUT || next == State::SEARCHING_ARUCO) {
    mission_.retries = 0;
  }
  if (next == State::SUCCEEDED || next == State::STAYING) {
    stopMission(next, 0, next == State::SUCCEEDED ? "Mission completed" : "Remote STAY");
    return;
  }
  changeState(next);
}

void NavCoordinator::changeState(State state)
{
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
    result == Result::STOPPED)
  {
    return;
  }
  if (result != Result::REACHED) {
    retryStateOrFail(
      mission_.state, Route::Result::NAVIGATION_FAILED,
      "Navigation failed or was canceled externally");
    return;
  }
  mission_.navigation_reached = true;
}

void NavCoordinator::updateMission()
{
  if (mission_.kind == Kind::NONE) {
    return;
  }
  if (auto result = navigation_->takeResult()) {
    updateNavigationOutcome(*result);
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
  if (phaseElapsed() > parameters_.phase_timeout) {
    stopMission(State::FAILED, Route::Result::TIMEOUT, "Phase deadline exceeded");
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
    retryStateOrFail(
      mission_.state, Route::Result::NAVIGATION_FAILED, "Rover localization missing or stale");
    return;
  }
  switch (mission_.state) {
    case State::NAVIGATING: driveToWaypoint(); break;
    case State::SEARCHING_ARUCO: searchForMarker(); break;
    case State::CALCULATING_APPROACH: calculateMarkerApproach(*rover); break;
    case State::NAVIGATING_TO_ARUCO: driveToMarker(); break;
    case State::VERIFY_ARRIVAL: verifyMarkerArrival(*rover); break;
    case State::GO_TO_ASTRONAUT: driveToAstronaut(*rover); break;
    case State::FOLLOWING: followAstronaut(*rover); break;
    case State::WAIT_STAY: waitForStay(*rover); break;
    case State::COMING: returnToAstronaut(*rover); break;
    default: break;
  }
}
}  // namespace nav_coordinator
