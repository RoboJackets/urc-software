#include "urc_state_machine/nav_coordinator.hpp"
#include "urc_state_machine/mission_geometry.hpp"

namespace nav_coordinator
{
NavCoordinator::Pose NavCoordinator::routeNavigationGoal(const Pose & rover) const
{
  if (mission_.kind != Kind::ROUTE || !markerFresh()) {
    return mission_.waypoint;
  }
  const auto approach = urc_state_machine::standoffGoal(
    rover, *mission_.marker, parameters_.aruco_standoff);
  if (urc_state_machine::distanceTo(approach, mission_.waypoint) > parameters_.route_radius) {
    return mission_.waypoint;
  }
  return approach;
}

void NavCoordinator::driveToWaypoint(const Pose & rover)
{
  if (mission_.kind == Kind::ROUTE &&
    urc_state_machine::distanceTo(rover, mission_.waypoint) <= parameters_.route_radius)
  {
    if (parameters_.aruco_refinement && !markerFresh()) {
      if (mission_.navigation_reached) {
        stopMission(State::SEARCHING_ARUCO, 0, "Coordinate reached; searching for ArUco");
        return;
      }
    } else if (!markerFresh() ||
      urc_state_machine::distanceTo(rover, *mission_.marker) <= parameters_.route_radius)
    {
      stopMission(State::SUCCEEDED, 0, "Route target reached");
      return;
    }
  }
  const auto goal = routeNavigationGoal(rover);
  if (!mission_.operation_started) {
    startNavigation(goal);
    mission_.operation_started = true;
    return;
  }
  if (mission_.navigation_reached) {
    if (mission_.kind == Kind::WAYPOINT) {
      stopMission(State::SUCCEEDED, 0, "Waypoint reached");
    } else {
      retryStateOrPause(
        State::NAVIGATING, Route::Result::NAVIGATION_FAILED,
        "Follower finished outside route arrival tolerance");
    }
    return;
  }
  const double elapsed = std::chrono::duration<double>(
    urc_state_machine::MissionClock::now() - mission_.last_goal_update).count();
  if (mission_.kind == Kind::ROUTE && mission_.navigation_goal &&
    elapsed >= parameters_.goal_update_period &&
    urc_state_machine::distanceTo(
      goal,
      *mission_.navigation_goal) >= parameters_.goal_update_distance)
  {
    startNavigation(goal);
  }
}
}  // namespace nav_coordinator
