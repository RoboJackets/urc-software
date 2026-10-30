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

  waypoint_publisher_ = create_publisher<geometry_msgs::msg::PoseStamped>(
    declare_parameter("waypoint_topic", "/nav/waypoint"), 10);
  marker_publisher_ = create_publisher<visualization_msgs::msg::MarkerArray>(
    declare_parameter("marker_topic", "mission_waypoints"),
    rclcpp::QoS(1).transient_local());
  state_subscriber_ = create_subscription<std_msgs::msg::String>(
    declare_parameter("coordinator_state_topic", "nav_coordinator_state"), 10,
    std::bind(&WaypointMission::handleCoordinatorState, this, std::placeholders::_1));
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
  return waypoint_publisher_->get_subscription_count() > 0 &&
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
  geometry_msgs::msg::PoseStamped goal;
  goal.header.frame_id = frame_id_;
  goal.header.stamp = get_clock()->now();
  goal.pose.position = route_[current_index_];
  goal.pose.orientation.w = 1.0;
  ++attempts_;
  phase_ = Phase::AwaitingAcceptance;
  waypoint_publisher_->publish(goal);
  publishMarkers();
  RCLCPP_INFO(
    get_logger(), "Waypoint %zu/%zu (%.1f, %.1f), attempt %d", current_index_ + 1, route_.size(),
    goal.pose.position.x, goal.pose.position.y, attempts_);
}

void WaypointMission::handleCoordinatorState(const std_msgs::msg::String::SharedPtr msg)
{
  const std::string state = parseState(msg->data);
  // Terminal states are only trusted after this waypoint was accepted, so a
  // result left over from the previous waypoint cannot advance the route
  if (phase_ == Phase::AwaitingAcceptance) {
    if (state == "NAVIGATING") {
      phase_ = Phase::Tracking;
    } else if (state == "FAILED") {
      handleFailure(msg->data);
    }
    return;
  }
  if (phase_ != Phase::Tracking) {
    return;
  }
  if (state == "SUCCEEDED") {
    handleSuccess();
  } else if (state == "FAILED" || state == "CANCELED") {
    handleFailure(msg->data);
  }
}

void WaypointMission::handleSuccess()
{
  RCLCPP_INFO(get_logger(), "Reached waypoint %zu/%zu", current_index_ + 1, route_.size());
  advance();
}

void WaypointMission::handleFailure(const std::string & state)
{
  if (attempts_ < max_attempts_) {
    RCLCPP_WARN(
      get_logger(), "Waypoint %zu failed (%s); retrying", current_index_ + 1, state.c_str());
    phase_ = Phase::RetryPending;
    retry_at_ = get_clock()->now() + rclcpp::Duration::from_seconds(retry_delay_s_);
    return;
  }
  RCLCPP_ERROR(
    get_logger(), "Skipping waypoint %zu after %d attempts (%s)", current_index_ + 1, attempts_,
    state.c_str());
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
