#include "urc_state_machine/nav_coordinator.hpp"
#include "urc_state_machine/mission_geometry.hpp"

namespace nav_coordinator
{
void NavCoordinator::driveToWaypoint()
{
  if (!mission_.operation_started) {
    startNavigation(mission_.waypoint);
    mission_.operation_started = true;
    return;
  }
  if (mission_.navigation_reached) {
    if (mission_.kind == Kind::WAYPOINT) {
      stopMission(State::SUCCEEDED, 0, "Waypoint reached");
    } else {
      transitionOn(Event::NAVIGATION_REACHED);
    }
  }
}

void NavCoordinator::searchForMarker()
{
  // Spiral-search integration will own search motion; for now only observe detections.
  if (!markerFresh()) {
    return;
  }
  if (navigation_->busy()) {
    navigation_->cancel();
  } else {
    transitionOn(Event::MARKER_FOUND);
  }
}

void NavCoordinator::calculateMarkerApproach(const Pose & rover)
{
  if (!markerFresh()) {
    retryStateOrFail(
      State::SEARCHING_ARUCO, Route::Result::TARGET_NOT_FOUND, "Marker observation stale");
    return;
  }
  mission_.navigation_goal = urc_state_machine::standoffGoal(
    rover, *mission_.marker, parameters_.aruco_standoff);
  transitionOn(Event::APPROACH_READY);
}

void NavCoordinator::driveToMarker()
{
  if (!mission_.operation_started) {
    if (!mission_.navigation_goal) {
      stopMission(State::FAILED, Route::Result::APPROACH_FAILED, "Approach goal missing");
      return;
    }
    startNavigation(*mission_.navigation_goal);
    mission_.operation_started = true;
    return;
  }
  if (mission_.navigation_reached) {
    transitionOn(Event::NAVIGATION_REACHED);
  }
}

void NavCoordinator::verifyMarkerArrival(const Pose & rover)
{
  if (markerFresh() &&
    urc_state_machine::distanceTo(rover, *mission_.marker) <= parameters_.aruco_radius)
  {
    transitionOn(Event::ARRIVAL_CONFIRMED);
    return;
  }
  retryStateOrFail(
    State::CALCULATING_APPROACH, Route::Result::APPROACH_FAILED,
    "Arrival requires a fresh marker measurement within tolerance");
}
}  // namespace nav_coordinator
