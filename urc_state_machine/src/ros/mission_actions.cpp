#include "urc_state_machine/nav_coordinator.hpp"

namespace nav_coordinator
{
void NavCoordinator::initializeRouteAction()
{
  route_server_ = rclcpp_action::create_server<Route>(
    this, parameters_.route_action,
    [this](const rclcpp_action::GoalUUID &, std::shared_ptr<const Route::Goal> goal) {
      if (!canAccept(goal->waypoint)) {
        return rclcpp_action::GoalResponse::REJECT;
      }
      return rclcpp_action::GoalResponse::ACCEPT_AND_EXECUTE;
    },
    [this](std::shared_ptr<RouteHandle> handle) {
      if (handle != route_handle_) {
        return rclcpp_action::CancelResponse::REJECT;
      }
      stopMission(State::CANCELED, Route::Result::CANCELED, "Mission canceled");
      return rclcpp_action::CancelResponse::ACCEPT;
    },
    [this](std::shared_ptr<RouteHandle> handle) {
      route_handle_ = handle;
      begin(Kind::ROUTE, handle->get_goal()->waypoint);
      beginResume(State::NAVIGATING);
    });
}

void NavCoordinator::initializeAstronautAction()
{
  astronaut_server_ = rclcpp_action::create_server<Astronaut>(
    this, parameters_.astronaut_action,
    [this](const rclcpp_action::GoalUUID &, std::shared_ptr<const Astronaut::Goal> goal) {
      return canAccept(goal->waypoint) ? rclcpp_action::GoalResponse::ACCEPT_AND_EXECUTE :
      rclcpp_action::GoalResponse::REJECT;
    },
    [this](std::shared_ptr<AstronautHandle> handle) {
      if (handle != astronaut_handle_) {
        return rclcpp_action::CancelResponse::REJECT;
      }
      stopMission(State::CANCELED, Astronaut::Result::CANCELED, "Mission canceled");
      return rclcpp_action::CancelResponse::ACCEPT;
    },
    [this](std::shared_ptr<AstronautHandle> handle) {
      astronaut_handle_ = handle;
      begin(Kind::ASTRONAUT, handle->get_goal()->waypoint);
      transitionOn(Event::START);
    });
}

}  // namespace nav_coordinator
