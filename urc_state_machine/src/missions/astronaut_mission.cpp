#include "urc_state_machine/nav_coordinator.hpp"
#include "urc_state_machine/mission_geometry.hpp"

namespace nav_coordinator
{
void NavCoordinator::driveToAstronaut(const Pose & rover)
{
  if (!mission_.operation_started) {
    startNavigation(mission_.waypoint);
    mission_.operation_started = true;
    return;
  }
  if (!mission_.navigation_reached) {
    return;
  }
  if (urc_state_machine::distanceTo(rover, mission_.waypoint) <= parameters_.astronaut_radius) {
    transitionOn(Event::NAVIGATION_REACHED);
  } else {
    retryStateOrPause(
      State::GO_TO_ASTRONAUT, Astronaut::Result::NAVIGATION_FAILED,
      "Initial waypoint arrival was outside tolerance");
  }
}

bool NavCoordinator::requireAstronautObservation()
{
  if (astronautFresh()) {
    return true;
  }
  retryStateOrPause(
    mission_.state, Astronaut::Result::TARGET_LOST, "Astronaut observation missing or stale");
  return false;
}

void NavCoordinator::followAstronaut(const Pose & rover)
{
  if (!requireAstronautObservation()) {
    return;
  }
  if (tracking_.stationary(parameters_.stationary_duration) &&
    urc_state_machine::distanceTo(rover, *tracking_.pose()) <= parameters_.astronaut_radius)
  {
    if (navigation_->busy()) {
      navigation_->cancel();
    } else {
      transitionOn(Event::PERSON_STOPPED);
    }
    return;
  }
  updateAstronautNavigation(rover);
}

void NavCoordinator::waitForStay(const Pose & rover)
{
  if (!requireAstronautObservation()) {
    return;
  }
  if (!tracking_.stationary(parameters_.stationary_duration) ||
    urc_state_machine::distanceTo(rover, *tracking_.pose()) > parameters_.astronaut_radius)
  {
    transitionOn(Event::PERSON_MOVED);
  }
}

void NavCoordinator::returnToAstronaut(const Pose & rover)
{
  if (!requireAstronautObservation()) {
    return;
  }
  if (mission_.navigation_reached &&
    urc_state_machine::distanceTo(rover, *tracking_.pose()) <= parameters_.astronaut_radius)
  {
    transitionOn(Event::NAVIGATION_REACHED);
    return;
  }
  updateAstronautNavigation(rover);
}

void NavCoordinator::updateAstronautNavigation(const Pose & rover)
{
  if (!mission_.operation_started) {
    mission_.navigation_goal.reset();
    mission_.operation_started = true;
  }
  const auto goal = urc_state_machine::standoffGoal(
    rover, *tracking_.pose(), parameters_.follow_distance);
  const double elapsed = std::chrono::duration<double>(
    urc_state_machine::MissionClock::now() - mission_.last_goal_update).count();
  const bool moved = !mission_.navigation_goal ||
    urc_state_machine::distanceTo(
    goal,
    *mission_.navigation_goal) >= parameters_.goal_update_distance;
  if (!mission_.navigation_goal ||
    (elapsed >= parameters_.goal_update_period && (moved || !navigation_->busy())))
  {
    startNavigation(goal);
  }
}

void NavCoordinator::completeToolPlaceholder()
{
  if (!parameters_.tool_placeholder_success) {
    stopMission(
      State::PAUSED, Astronaut::Result::TOOL_FAILED,
      "Autonomous arm unavailable; test placeholder is disabled");
    return;
  }
  if (phaseElapsed() < parameters_.placeholder_duration) {
    return;
  }
  // Replace this simulated completion with a confirmed arm action result.
  RCLCPP_WARN(
    get_logger(), "Simulating %s completion; no arm moved",
    urc_state_machine::stateName(mission_.state));
  transitionOn(
    mission_.state ==
    State::FETCHING ? Event::GRASP_CONFIRMED : Event::RELEASE_CONFIRMED);
}
}  // namespace nav_coordinator
