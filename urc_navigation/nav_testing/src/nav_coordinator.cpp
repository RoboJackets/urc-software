#include "nav_coordinator.hpp"

namespace nav_coordinator
{
NavCoordinator::NavCoordinator(const rclcpp::NodeOptions & options)
: rclcpp::Node("nav_coordinator", options)
{
  declare_parameter<std::string>("waypoint_topic", "/nav/waypoint");
  declare_parameter<std::string>("gps_waypoint_topic", "/waypoint");
  declare_parameter<std::string>("follower_action_name", "navigate_to_waypoint");
  declare_parameter<bool>("cancel_on_new_waypoint", true);
  declare_parameter<std::string>("map_frame_id", "map");
  declare_parameter<double>("map_origin_latitude", 0.0);
  declare_parameter<double>("map_origin_longitude", 0.0);
  declare_parameter<double>("map_origin_altitude", 0.0);

  follower_action_name_ = get_parameter("follower_action_name").as_string();
  cancel_on_new_waypoint_ = get_parameter("cancel_on_new_waypoint").as_bool();
  map_frame_id_ = get_parameter("map_frame_id").as_string();
  state_ = State::IDLE;
  last_error_ = ErrorType::NONE;
  gps_conversion_ready_ = true;

  geographic_msgs::msg::GeoPoint map_origin;
  map_origin.latitude = get_parameter("map_origin_latitude").as_double();
  map_origin.longitude = get_parameter("map_origin_longitude").as_double();
  map_origin.altitude = get_parameter("map_origin_altitude").as_double();

  if (
    map_origin.latitude < -90.0 || map_origin.latitude > 90.0 ||
    map_origin.longitude < -180.0 || map_origin.longitude > 180.0)
  {
    gps_conversion_ready_ = false;
    RCLCPP_WARN(
      get_logger(),
      "Invalid map origin lat/lon for GPS conversion (lat=%.8f lon=%.8f). "
      "GPS waypoints will be rejected.",
      map_origin.latitude,
      map_origin.longitude);
  } else {
    geodesy::fromMsg(map_origin, map_origin_utm_);
  }

  state_publisher_ = create_publisher<std_msgs::msg::String>("nav_coordinator_state", 10);
  follower_client_ = rclcpp_action::create_client<NavigateToWaypoint>(this, follower_action_name_);

  waypoint_subscriber_ = create_subscription<geometry_msgs::msg::PoseStamped>(
    get_parameter("waypoint_topic").as_string(),
    rclcpp::SystemDefaultsQoS(),
    std::bind(&NavCoordinator::handleWaypoint, this, std::placeholders::_1));

  gps_waypoint_subscriber_ = create_subscription<urc_msgs::msg::Waypoint>(
    get_parameter("gps_waypoint_topic").as_string(),
    rclcpp::SystemDefaultsQoS(),
    std::bind(&NavCoordinator::handleGpsWaypoint, this, std::placeholders::_1));

  RCLCPP_INFO(
    get_logger(),
    "Nav Coordinator ready. Pose waypoints on '%s', GPS waypoints on '%s', forwarding to action '%s'.",
    get_parameter("waypoint_topic").as_string().c_str(),
    get_parameter("gps_waypoint_topic").as_string().c_str(),
    follower_action_name_.c_str());
  
  if (state_publisher_) {
    publishState();
  }
}

void NavCoordinator::handleWaypoint(const geometry_msgs::msg::PoseStamped::SharedPtr msg)
{
  active_waypoint_ = *msg;
  RCLCPP_INFO(
    get_logger(), "Received waypoint: frame=%s x=%.3f y=%.3f",
    active_waypoint_.header.frame_id.c_str(),
    active_waypoint_.pose.position.x,
    active_waypoint_.pose.position.y);

  if (active_goal_handle_ && cancel_on_new_waypoint_) {
    transitionTo(State::CANCELED, "canceling current goal due to new waypoint");
    follower_client_->async_cancel_goal(active_goal_handle_);
    active_goal_handle_.reset();
  }

  sendFollowerGoal(active_waypoint_);
}

void NavCoordinator::handleGpsWaypoint(const urc_msgs::msg::Waypoint::SharedPtr msg)
{
  if (!gps_conversion_ready_) {
    handleError(
      ErrorType::PLANNER_FAILURE,
      "Cannot process GPS waypoint: invalid map origin parameters for conversion.");
    transitionTo(State::FAILED, "gps waypoint rejected - conversion unavailable");
    return;
  }

  const auto converted_waypoint = convertGpsToMapWaypoint(*msg);
  active_waypoint_ = converted_waypoint;

  RCLCPP_INFO(
    get_logger(),
    "Received GPS waypoint: lat=%.8f lon=%.8f -> frame=%s x=%.3f y=%.3f",
    msg->latitude,
    msg->longitude,
    active_waypoint_.header.frame_id.c_str(),
    active_waypoint_.pose.position.x,
    active_waypoint_.pose.position.y);

  if (active_goal_handle_ && cancel_on_new_waypoint_) {
    transitionTo(State::CANCELED, "canceling current goal due to new GPS waypoint");
    follower_client_->async_cancel_goal(active_goal_handle_);
    active_goal_handle_.reset();
  }

  sendFollowerGoal(active_waypoint_);
}

geometry_msgs::msg::PoseStamped NavCoordinator::convertGpsToMapWaypoint(
  const urc_msgs::msg::Waypoint & waypoint) const
{
  geographic_msgs::msg::GeoPoint geo_point;
  geo_point.latitude = waypoint.latitude;
  geo_point.longitude = waypoint.longitude;
  geo_point.altitude = 0.0;

  geodesy::UTMPoint waypoint_utm;
  geodesy::fromMsg(geo_point, waypoint_utm);

  geometry_msgs::msg::PoseStamped pose;
  pose.header.stamp = now();
  pose.header.frame_id = map_frame_id_;
  pose.pose.position.x = waypoint_utm.easting - map_origin_utm_.easting;
  pose.pose.position.y = waypoint_utm.northing - map_origin_utm_.northing;
  pose.pose.position.z = 0.0;
  pose.pose.orientation.w = 1.0;

  return pose;
}

void NavCoordinator::sendFollowerGoal(const geometry_msgs::msg::PoseStamped & waypoint)
{
  transitionTo(State::WAITING_FOR_SERVER, "checking follower action server");
  if (!follower_client_->wait_for_action_server(std::chrono::seconds(2))) {
    handleError(
      ErrorType::SERVER_UNAVAILABLE,
      "Follower action server '" + follower_action_name_ + "' not available.");
    transitionTo(State::FAILED, "follower action server unavailable");
    return;
  }

  NavigateToWaypoint::Goal goal_msg;
  goal_msg.goal = waypoint;
  goal_msg.has_goal = true;
  goal_msg.has_path = false;
  goal_msg.enforce_goal_heading = false;

  transitionTo(State::SENDING_GOAL, "forwarding waypoint to follower");

  rclcpp_action::Client<NavigateToWaypoint>::SendGoalOptions options;
  options.goal_response_callback = std::bind(
    &NavCoordinator::handleGoalResponse, this, std::placeholders::_1);
  options.feedback_callback = std::bind(
    &NavCoordinator::handleFeedback, this, std::placeholders::_1, std::placeholders::_2);
  options.result_callback = std::bind(
    &NavCoordinator::handleResult, this, std::placeholders::_1);

  follower_client_->async_send_goal(goal_msg, options);
}

void NavCoordinator::handleGoalResponse(const GoalHandleNavigate::SharedPtr & goal_handle)
{
  if (!goal_handle) {
    handleError(ErrorType::FOLLOWER_FAILURE, "Follower action server rejected the goal.");
    transitionTo(State::FAILED, "follower rejected goal");
    return;
  }

  active_goal_handle_ = goal_handle;
  transitionTo(State::TRACKING_GOAL, "follower accepted goal");
}

void NavCoordinator::handleFeedback(
  GoalHandleNavigate::SharedPtr,
  const std::shared_ptr<const NavigateToWaypoint::Feedback> feedback)
{
  RCLCPP_DEBUG(
    get_logger(), "Feedback: dist=%.2f planning=%s replans=%u",
    feedback->distance_to_goal,
    feedback->is_planning ? "true" : "false",
    feedback->replan_count);
}

void NavCoordinator::handleResult(const GoalHandleNavigate::WrappedResult & result)
{
  active_goal_handle_.reset();

  if (result.code == rclcpp_action::ResultCode::SUCCEEDED) {
    if (result.result->error_code == NavigateToWaypoint::Result::SUCCESS) {
      transitionTo(State::SUCCEEDED, "follower reported success");
      return;
    }

    switch (result.result->error_code) {
      case NavigateToWaypoint::Result::OBSTACLE_DETECTED:
        handleError(ErrorType::OBSTACLE_DETECTED, "Obstacle detected during trajectory following.");
        break;
      case NavigateToWaypoint::Result::PLANNING_FAILED:
        handleError(ErrorType::PLANNING_FAILED_IN_FOLLOWER, "Path planning failed in follower.");
        break;
      case NavigateToWaypoint::Result::FAILURE:
        handleError(ErrorType::FOLLOWER_FAILURE, "Follower reported generic failure.");
        break;
      default:
        handleError(ErrorType::UNKNOWN_ERROR, "Follower finished with error_code=" + std::to_string(result.result->error_code));
        break;
    }
    transitionTo(State::FAILED, "follower finished with error");
    return;
  }

  if (result.code == rclcpp_action::ResultCode::ABORTED) {
    handleError(ErrorType::FOLLOWER_FAILURE, "Follower aborted goal.");
    transitionTo(State::FAILED, "follower aborted goal");
    return;
  }

  if (result.code == rclcpp_action::ResultCode::CANCELED) {
    transitionTo(State::CANCELED, "follower canceled goal");
    return;
  }

  handleError(ErrorType::UNKNOWN_ERROR, "Unknown follower result code: " + std::to_string(static_cast<int>(result.code)));
  transitionTo(State::FAILED, "unknown follower result code");
}

void NavCoordinator::transitionTo(State new_state, const std::string & reason)
{
  if (state_ == new_state) {
    return;
  }

  const auto state_name = [](State state) -> const char* {
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
  };

  RCLCPP_INFO(
    get_logger(), "State transition: %s -> %s (%s)", state_name(state_),
    state_name(new_state), reason.c_str());
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
  auto msg = std::make_shared<std_msgs::msg::String>();
  msg->data = "state=" + stateToString(state_) + " error=" + errorTypeToString(last_error_);
  if (!last_error_details_.empty()) {
    msg->data += " details=" + last_error_details_;
  }
  state_publisher_->publish(*msg);
}

} // namespace nav_coordinator

#include <rclcpp_components/register_node_macro.hpp>
RCLCPP_COMPONENTS_REGISTER_NODE(nav_coordinator::NavCoordinator)
