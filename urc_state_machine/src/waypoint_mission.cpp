#include "urc_state_machine/waypoint_mission.hpp"

#include <chrono>
#include <stdexcept>

#include <std_msgs/msg/color_rgba.hpp>
#include <tf2/time.h>

namespace waypoint_mission
{
namespace
{
constexpr auto kStepPeriod = std::chrono::milliseconds(200);
constexpr double kMarkerDiameterM = 0.4;

// NavCoordinator publishes "state=<STATE> error=<TYPE> ..."
std::string parseState(const std::string & message)
{
  const std::string prefix = "state=";
  const auto start = message.find(prefix);
  if (start == std::string::npos) {
    return "";
  }
  const auto value_start = start + prefix.size();
  return message.substr(value_start, message.find(' ', value_start) - value_start);
}
// NavCoordinator keeps a paused mission open until teleop resumes or cancels it
constexpr char kPausedState[] = "PAUSED";

std_msgs::msg::ColorRGBA color(float r, float g, float b)
{
  std_msgs::msg::ColorRGBA c;
  c.r = r;
  c.g = g;
  c.b = b;
  c.a = 1.0f;
  return c;
}
}  // namespace

WaypointMission::WaypointMission(const rclcpp::NodeOptions & options)
: Node("waypoint_mission", options)
{
  frame_id_ = declare_parameter("frame_id", "map");
  base_frame_id_ = declare_parameter("base_frame_id", "base_link");
  laps_ = declare_parameter("laps", 1);
  max_attempts_ = declare_parameter("max_attempts_per_waypoint", 3);
  start_delay_s_ = declare_parameter("start_delay_s", 5.0);
  retry_delay_s_ = declare_parameter("retry_delay_s", 2.0);
  if (laps_ < 0 || max_attempts_ < 1 || start_delay_s_ < 0.0 || retry_delay_s_ < 0.0) {
    throw std::invalid_argument(
            "laps must be >= 0 (0 repeats forever), max_attempts_per_waypoint >= 1, "
            "and delays non-negative");
  }
  loadRoute();
  ready_since_ = get_clock()->now();
  retry_at_ = ready_since_;

  tf_buffer_ = std::make_unique<tf2_ros::Buffer>(get_clock());
  tf_listener_ = std::make_shared<tf2_ros::TransformListener>(*tf_buffer_);

  route_client_ = rclcpp_action::create_client<Route>(
    this, declare_parameter("mission_action_name", "execute_autonomous_mission"));
  marker_publisher_ = create_publisher<visualization_msgs::msg::MarkerArray>(
    declare_parameter("marker_topic", "mission_waypoints"),
    rclcpp::QoS(1).transient_local());
  timer_ = create_wall_timer(kStepPeriod, std::bind(&WaypointMission::step, this));

  publishMarkers();
  RCLCPP_INFO(get_logger(), "Loaded %zu waypoints; waiting for localization", route_.size());
}

void WaypointMission::loadRoute()
{
  const std::vector<double> flat = declare_parameter("waypoints", std::vector<double>{});
  if (flat.size() < 2 || flat.size() % 2 != 0) {
    throw std::invalid_argument("waypoints must be a non-empty flat list of x, y pairs");
  }
  for (std::size_t i = 0; i < flat.size(); i += 2) {
    geometry_msgs::msg::Point point;
    point.x = flat[i];
    point.y = flat[i + 1];
    route_.push_back(point);
  }
}

bool WaypointMission::startupReady()
{
  return route_client_->action_server_is_ready() &&
         tf_buffer_->canTransform(frame_id_, base_frame_id_, tf2::TimePointZero);
}

void WaypointMission::step()
{
  const rclcpp::Time now = get_clock()->now();
  if (phase_ == Phase::WaitingForStartup) {
    if (!startupReady()) {
      ready_since_ = now;
      return;
    }
    // Lets the costmap fill in before the first plan request
    if ((now - ready_since_).seconds() >= start_delay_s_) {
      sendCurrentWaypoint();
    }
  } else if (phase_ == Phase::RetryPending && now >= retry_at_) {
    sendCurrentWaypoint();
  }
}

void WaypointMission::sendCurrentWaypoint()
{
  Route::Goal goal;
  goal.waypoint.header.frame_id = frame_id_;
  goal.waypoint.header.stamp = get_clock()->now();
  goal.waypoint.pose.position = route_[current_index_];
  goal.waypoint.pose.orientation.w = 1.0;
  ++attempts_;
  phase_ = Phase::Active;
  goal_handle_.reset();
  cancel_requested_ = false;
  const std::uint64_t generation = ++goal_generation_;

  rclcpp_action::Client<Route>::SendGoalOptions options;
  options.goal_response_callback = [this, generation](RouteGoalHandle::SharedPtr handle) {
      handleGoalResponse(generation, handle);
    };
  options.feedback_callback = [this, generation](
    RouteGoalHandle::SharedPtr, const std::shared_ptr<const Route::Feedback> feedback) {
      handleFeedback(generation, feedback->state);
    };
  options.result_callback = [this, generation](const RouteGoalHandle::WrappedResult & result) {
      handleResult(generation, result);
    };
  route_client_->async_send_goal(goal, options);
  publishMarkers();
  RCLCPP_INFO(
    get_logger(), "Waypoint %zu/%zu (%.1f, %.1f), attempt %d", current_index_ + 1, route_.size(),
    goal.waypoint.pose.position.x, goal.waypoint.pose.position.y, attempts_);
}

void WaypointMission::handleGoalResponse(
  std::uint64_t generation, const RouteGoalHandle::SharedPtr & handle)
{
  if (generation != goal_generation_) {
    return;
  }
  if (!handle) {
    handleFailure("coordinator rejected the mission");
    return;
  }
  goal_handle_ = handle;
}

void WaypointMission::handleFeedback(std::uint64_t generation, const std::string & state)
{
  if (generation != goal_generation_ || state != kPausedState || cancel_requested_ ||
    !goal_handle_)
  {
    return;
  }
  RCLCPP_WARN(
    get_logger(), "Coordinator paused waypoint %zu; canceling the mission", current_index_ + 1);
  cancel_requested_ = true;
  route_client_->async_cancel_goal(goal_handle_);
}

void WaypointMission::handleResult(
  std::uint64_t generation, const RouteGoalHandle::WrappedResult & result)
{
  if (generation != goal_generation_) {
    return;
  }
  goal_handle_.reset();
  if (result.code == rclcpp_action::ResultCode::SUCCEEDED) {
    RCLCPP_INFO(get_logger(), "Reached waypoint %zu/%zu", current_index_ + 1, route_.size());
    advance();
    return;
  }
  handleFailure(result.result ? result.result->message : "mission ended without a result");
}

void WaypointMission::handleFailure(const std::string & reason)
{
  if (attempts_ < max_attempts_) {
    RCLCPP_WARN(
      get_logger(), "Waypoint %zu failed (%s); retrying", current_index_ + 1, reason.c_str());
    phase_ = Phase::RetryPending;
    retry_at_ = get_clock()->now() + rclcpp::Duration::from_seconds(retry_delay_s_);
    return;
  }
  RCLCPP_ERROR(
    get_logger(), "Skipping waypoint %zu after %d attempts (%s)", current_index_ + 1, attempts_,
    reason.c_str());
  advance();
}

void WaypointMission::advance()
{
  attempts_ = 0;
  if (++current_index_ == route_.size()) {
    current_index_ = 0;
    ++laps_completed_;
    RCLCPP_INFO(get_logger(), "Completed lap %d", laps_completed_);
    if (laps_ != 0 && laps_completed_ >= laps_) {
      phase_ = Phase::Complete;
      publishMarkers();
      RCLCPP_INFO(get_logger(), "Mission complete");
      return;
    }
  }
  sendCurrentWaypoint();
}

void WaypointMission::publishMarkers() const
{
  visualization_msgs::msg::Marker route_line;
  route_line.header.frame_id = frame_id_;
  route_line.ns = "route";
  route_line.type = visualization_msgs::msg::Marker::LINE_STRIP;
  route_line.scale.x = 0.05;
  route_line.color = color(0.6f, 0.6f, 0.65f);
  route_line.color.a = 0.6f;
  route_line.pose.orientation.w = 1.0;
  route_line.points = route_;
  route_line.points.push_back(route_.front());

  visualization_msgs::msg::Marker spheres = route_line;
  spheres.ns = "waypoints";
  spheres.id = 1;
  spheres.type = visualization_msgs::msg::Marker::SPHERE_LIST;
  spheres.scale.x = spheres.scale.y = spheres.scale.z = kMarkerDiameterM;
  spheres.points = route_;
  for (std::size_t i = 0; i < route_.size(); ++i) {
    const bool is_target = phase_ != Phase::Complete && phase_ != Phase::WaitingForStartup &&
      i == current_index_;
    spheres.colors.push_back(is_target ? color(1.0f, 0.55f, 0.0f) : color(0.3f, 0.6f, 1.0f));
  }

  visualization_msgs::msg::MarkerArray markers;
  markers.markers = {route_line, spheres};
  marker_publisher_->publish(markers);
}

}  // namespace waypoint_mission

#include <rclcpp_components/register_node_macro.hpp>
RCLCPP_COMPONENTS_REGISTER_NODE(waypoint_mission::WaypointMission)
