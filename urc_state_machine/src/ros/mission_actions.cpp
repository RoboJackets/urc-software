#include "urc_state_machine/nav_coordinator.hpp"

namespace nav_coordinator
{
void NavCoordinator::initializeRouteAction()
{
  route_server_ = rclcpp_action::create_server<Route>(
    this, parameters_.route_action,
    [this](const rclcpp_action::GoalUUID &, std::shared_ptr<const Route::Goal> goal) {
      if (!canAccept(goal->waypoint) ||
      (goal->marker_id != Route::Goal::ARUCO_1 && goal->marker_id != Route::Goal::ARUCO_2))
      {
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
      mission_.marker_id = handle->get_goal()->marker_id;
      transitionOn(Event::START);
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

void NavCoordinator::command(const Command & input)
{
  if (mission_.kind != Kind::ASTRONAUT ||
    !fresh(input.stamp, parameters_.command_max_age) ||
    rclcpp::Time(input.stamp) <= last_command_stamp_)
  {
    return;
  }
  const auto source = input.command == Command::FOLLOW ? Command::GESTURE : Command::REMOTE;
  if (input.source != source) {
    return;
  }
  // Commands are events, never stored for a future phase or replayed after a retry.
  last_command_stamp_ = rclcpp::Time(input.stamp);
  Event event;
  switch (input.command) {
    case Command::FOLLOW: event = Event::FOLLOW; break;
    case Command::STAY: event = Event::STAY; break;
    case Command::FETCH: event = Event::FETCH; break;
    case Command::COME: event = Event::COME; break;
    case Command::GIVE: event = Event::GIVE; break;
    default: return;
  }
  if (event == Event::STAY && mission_.state == State::RECOVERING &&
    (mission_.resume == State::FOLLOWING || mission_.resume == State::WAIT_STAY))
  {
    stopMission(State::STAYING, 0, "Remote STAY");
    return;
  }
  transitionOn(event);
}
}  // namespace nav_coordinator
