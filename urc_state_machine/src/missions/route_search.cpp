#include "urc_state_machine/nav_coordinator.hpp"

namespace nav_coordinator
{
void NavCoordinator::searchForMarker()
{
  if (markerFresh()) {
    spiral_search_->cancel();
    if (navigation_->busy()) {
      navigation_->cancel();
    } else {
      changeState(State::NAVIGATING);
    }
    return;
  }
  if (mission_.navigation_reached) {
    stopMission(
      State::PAUSED, Route::Result::NAVIGATION_FAILED,
      "Spiral path exhausted without an ArUco detection");
    return;
  }
  if (spiral_search_->failed()) {
    stopMission(
      State::PAUSED, Route::Result::NAVIGATION_FAILED,
      "Spiral search did not provide a valid traversability-checked path");
    return;
  }
  if (!mission_.operation_started) {
    if (navigation_->busy()) {
      return;
    }
    auto center = mission_.waypoint;
    center.header.stamp = now();
    mission_.operation_started = spiral_search_->request(center, parameters_.spiral_search_radius);
    return;
  }
  if (auto path = spiral_search_->takePath()) {
    navigation_->follow(*path);
  }
}
}  // namespace nav_coordinator
