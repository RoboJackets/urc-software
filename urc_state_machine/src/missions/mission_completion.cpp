#include "urc_state_machine/nav_coordinator.hpp"
#include <limits>
#include "urc_state_machine/mission_geometry.hpp"

namespace nav_coordinator
{
void NavCoordinator::finishMission()
{
  mission_.state = mission_.after_stop;
  arrival_indicated_ = mission_.state == State::SUCCEEDED && mission_.kind != Kind::ASTRONAUT;
  if (route_handle_) {
    auto result = std::make_shared<Route::Result>();
    result->error_code = mission_.error_code;
    result->message = mission_.reason;
    result->has_aruco_pose = mission_.marker.has_value();
    if (mission_.marker) {
      result->aruco_pose = *mission_.marker;
    }
    if (mission_.state == State::SUCCEEDED) {
      route_handle_->succeed(result);
    } else {
      route_handle_->canceled(result);
    }
    route_handle_.reset();
  }
  if (astronaut_handle_) {
    auto result = std::make_shared<Astronaut::Result>();
    result->error_code = mission_.error_code;
    result->message = mission_.reason;
    if (parameters_.tool_placeholder_success) {
      result->message += " (arm simulated)";
    }
    if (mission_.state == State::SUCCEEDED) {
      astronaut_handle_->succeed(result);
    } else {
      astronaut_handle_->canceled(result);
    }
    astronaut_handle_.reset();
  }
  mission_.kind = Kind::NONE;
  if (mission_.state == State::CANCELED) {
    setAutonomousMode(false);
  }
  publishState();
}

void NavCoordinator::publishFeedback()
{
  if (route_handle_) {
    auto feedback = std::make_shared<Route::Feedback>();
    feedback->state = urc_state_machine::stateName(mission_.state);
    feedback->distance_to_goal = navigation_->distance();
    feedback->replan_count = navigation_->replans();
    route_handle_->publish_feedback(feedback);
  }
  if (astronaut_handle_) {
    auto feedback = std::make_shared<Astronaut::Feedback>();
    feedback->state = urc_state_machine::stateName(mission_.state);
    feedback->distance_to_astronaut = std::numeric_limits<float>::infinity();
    const auto rover = roverPose();
    if (rover && astronautFresh()) {
      feedback->distance_to_astronaut = urc_state_machine::distanceTo(*rover, *tracking_.pose());
    }
    feedback->tool_placeholder_enabled = parameters_.tool_placeholder_success;
    astronaut_handle_->publish_feedback(feedback);
  }
}
}  // namespace nav_coordinator
