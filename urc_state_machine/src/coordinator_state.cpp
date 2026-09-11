#include "urc_state_machine/nav_coordinator.hpp"

namespace nav_coordinator
{
void NavCoordinator::transitionTo(State new_state, const std::string & reason)
{
  if (state_ == new_state) {
    return;
  }

  RCLCPP_INFO(
    get_logger(), "State transition: %s -> %s (%s)", stateToString(state_).c_str(),
    stateToString(new_state).c_str(), reason.c_str());
  state_ = new_state;
  publishState();
}

void NavCoordinator::handleError(ErrorType error_type, const std::string & details)
{
  last_error_ = error_type;
  last_error_details_ = details;

  switch (error_type) {
    case ErrorType::PLANNER_FAILURE:
      RCLCPP_ERROR(get_logger(), "[PLANNER_FAILURE] %s", details.c_str());
      break;
    case ErrorType::OBSTACLE_DETECTED:
      RCLCPP_WARN(get_logger(), "[OBSTACLE_DETECTED] %s", details.c_str());
      break;
    case ErrorType::PLANNING_FAILED_IN_FOLLOWER:
      RCLCPP_ERROR(get_logger(), "[PLANNING_FAILED] %s", details.c_str());
      break;
    case ErrorType::FOLLOWER_FAILURE:
      RCLCPP_ERROR(get_logger(), "[FOLLOWER_FAILURE] %s", details.c_str());
      break;
    case ErrorType::SERVER_UNAVAILABLE:
      RCLCPP_ERROR(get_logger(), "[SERVER_UNAVAILABLE] %s", details.c_str());
      break;
    case ErrorType::UNKNOWN_ERROR:
      RCLCPP_ERROR(get_logger(), "[UNKNOWN_ERROR] %s", details.c_str());
      break;
    default:
      RCLCPP_ERROR(get_logger(), "[UNHANDLED_ERROR] %s", details.c_str());
      break;
  }
  publishState();
}

std::string NavCoordinator::errorTypeToString(ErrorType error_type) const
{
  switch (error_type) {
    case ErrorType::NONE:
      return "NONE";
    case ErrorType::PLANNER_FAILURE:
      return "PLANNER_FAILURE";
    case ErrorType::OBSTACLE_DETECTED:
      return "OBSTACLE_DETECTED";
    case ErrorType::PLANNING_FAILED_IN_FOLLOWER:
      return "PLANNING_FAILED";
    case ErrorType::FOLLOWER_FAILURE:
      return "FOLLOWER_FAILURE";
    case ErrorType::SERVER_UNAVAILABLE:
      return "SERVER_UNAVAILABLE";
    case ErrorType::UNKNOWN_ERROR:
      return "UNKNOWN_ERROR";
    default:
      return "UNHANDLED";
  }
}

std::string NavCoordinator::stateToString(State state) const
{
  switch (state) {
    case State::IDLE:
      return "IDLE";
    case State::WAITING_FOR_SERVER:
      return "WAITING_FOR_SERVER";
    case State::SENDING_GOAL:
      return "SENDING_GOAL";
    case State::TRACKING_GOAL:
      return "TRACKING_GOAL";
    case State::SUCCEEDED:
      return "SUCCEEDED";
    case State::FAILED:
      return "FAILED";
    case State::CANCELED:
      return "CANCELED";
    default:
      return "UNKNOWN";
  }
}

void NavCoordinator::publishState()
{
  std_msgs::msg::String msg;
  msg.data = "state=" + stateToString(state_) + " error=" + errorTypeToString(last_error_);
  if (!last_error_details_.empty()) {
    msg.data += " details=" + last_error_details_;
  }
  state_publisher_->publish(msg);
}

}
