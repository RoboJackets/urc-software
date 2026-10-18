#include "spiral_search_server.hpp"

#include <grid_map_ros/GridMapRosConverter.hpp>
#include <tf2/LinearMath/Quaternion.h>
#include <tf2/LinearMath/Transform.h>
#include <tf2/exceptions.h>
#include <tf2_geometry_msgs/tf2_geometry_msgs.hpp>

#include <chrono>
#include <cmath>
#include <memory>
#include <optional>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

namespace urc_perception
{
namespace
{
constexpr double kDegreesToRadians = M_PI / 180.0;

/// Request fields are optional overrides; a non-positive value defers to the server default.
double overrideOrDefault(double requested, double fallback)
{
  return requested > 0.0 ? requested : fallback;
}

double polylineLength(const nav_msgs::msg::Path & path)
{
  double length = 0.0;
  for (std::size_t index = 1; index < path.poses.size(); ++index) {
    const auto & from = path.poses[index - 1].pose.position;
    const auto & to = path.poses[index].pose.position;
    length += std::hypot(to.x - from.x, to.y - from.y);
  }
  return length;
}
} // namespace

SpiralSearchServer::SpiralSearchServer(const rclcpp::NodeOptions & options)
: rclcpp::Node("spiral_search_server", options)
{
  map_frame_ = declare_parameter<std::string>("map_frame", "map");
  default_waypoint_spacing_ = declare_parameter<double>("waypoint_spacing", 0.5);

  camera_coverage_.horizontal_fov =
    declare_parameter<double>("camera_horizontal_fov_degrees", 87.0) * kDegreesToRadians;
  camera_coverage_.max_detection_range = declare_parameter<double>("max_detection_range", 3.0);
  camera_coverage_.overlap_fraction = declare_parameter<double>("coverage_overlap_fraction", 0.5);

  const std::string coverage_error = validateCameraCoverage(camera_coverage_);
  if (!coverage_error.empty()) {
    throw std::invalid_argument("Invalid camera coverage parameters: " + coverage_error);
  }

  if (!(default_waypoint_spacing_ > 0.0)) {
    throw std::invalid_argument("Parameter waypoint_spacing must be positive.");
  }

  const int max_waypoints = declare_parameter<int>("max_waypoints", 2000);
  if (max_waypoints < 2) {
    throw std::invalid_argument("Parameter max_waypoints must allow at least two waypoints.");
  }
  max_waypoints_ = static_cast<std::size_t>(max_waypoints);

  const double configured_track_spacing = declare_parameter<double>("track_spacing", 0.0);
  if (configured_track_spacing < 0.0) {
    throw std::invalid_argument(
            "Parameter track_spacing must be positive, or zero to derive it from camera coverage.");
  }
  default_track_spacing_ = configured_track_spacing > 0.0 ?
    configured_track_spacing :
    trackSpacingFromCoverage(camera_coverage_);

  const double configured_start_radius = declare_parameter<double>("start_radius", 0.0);
  if (configured_start_radius < 0.0) {
    throw std::invalid_argument(
            "Parameter start_radius must be positive, or zero to derive it from track spacing.");
  }
  start_radius_ = configured_start_radius > 0.0 ?
    configured_start_radius :
    innerTrackRadius(default_track_spacing_);

  traversability_criteria_.cost_layer =
    declare_parameter<std::string>("traversability_cost_layer", "traversability_inflated");
  traversability_criteria_.validity_layer =
    declare_parameter<std::string>("traversability_validity_layer", "traversability");
  traversability_criteria_.max_cost = declare_parameter<double>("max_traversability_cost", 0.05);
  traversability_criteria_.allow_unknown =
    declare_parameter<bool>("allow_unknown_terrain", false);
  if (!std::isfinite(traversability_criteria_.max_cost) || traversability_criteria_.max_cost < 0.0) {
    throw std::invalid_argument("Parameter max_traversability_cost must be zero or positive.");
  }

  max_map_age_ = declare_parameter<double>("max_map_age", 2.0);
  if (!(max_map_age_ > 0.0)) {
    throw std::invalid_argument("Parameter max_map_age must be positive.");
  }
  require_traversability_map_ = declare_parameter<bool>("require_traversability_map", true);

  tf_buffer_ = std::make_unique<tf2_ros::Buffer>(get_clock());
  tf_listener_ = std::make_shared<tf2_ros::TransformListener>(*tf_buffer_);

  traversability_subscriber_ = create_subscription<grid_map_msgs::msg::GridMap>(
    declare_parameter<std::string>("traversability_map_topic", "/costmap"),
    rclcpp::QoS(1),
    std::bind(&SpiralSearchServer::handleTraversabilityMap, this, std::placeholders::_1));

  path_publisher_ = create_publisher<nav_msgs::msg::Path>(
    declare_parameter<std::string>("path_topic", "/spiral_search_path"),
    rclcpp::SystemDefaultsQoS());
  raw_path_publisher_ = create_publisher<nav_msgs::msg::Path>(
    declare_parameter<std::string>("raw_path_topic", "/spiral_search_path_raw"),
    rclcpp::SystemDefaultsQoS());

  spiral_service_ = create_service<urc_msgs::srv::GenerateSpiralSearch>(
    declare_parameter<std::string>("service_name", "generate_spiral_search"),
    std::bind(
      &SpiralSearchServer::generateSpiralSearch, this, std::placeholders::_1,
      std::placeholders::_2));

  RCLCPP_INFO(
    get_logger(),
    "Spiral search server started. Track spacing %.2f m, start radius %.2f m, "
    "waypoint spacing %.2f m. Routing on '%s' layer '%s' (max cost %.3f).",
    default_track_spacing_, start_radius_, default_waypoint_spacing_,
    traversability_subscriber_->get_topic_name(), traversability_criteria_.cost_layer.c_str(),
    traversability_criteria_.max_cost);
}

void SpiralSearchServer::generateSpiralSearch(
  const std::shared_ptr<urc_msgs::srv::GenerateSpiralSearch::Request> request,
  std::shared_ptr<urc_msgs::srv::GenerateSpiralSearch::Response> response)
{
  const SpiralSearchParameters parameters = resolveParameters(*request);

  const std::string error = validateSpiralParameters(parameters);
  if (!error.empty()) {
    RCLCPP_WARN(get_logger(), "Rejecting spiral search request: %s.", error.c_str());
    response->error_code = urc_msgs::srv::GenerateSpiralSearch::Response::INVALID_REQUEST;
    return;
  }

  using Response = urc_msgs::srv::GenerateSpiralSearch::Response;

  try {
    const SpiralPath spiral = generateArchimedeanSpiral(parameters);
    const nav_msgs::msg::Path spiral_path = toPath(spiral.waypoints, request->center);
    response->track_spacing = parameters.track_spacing;
    publishPath(raw_path_publisher_, spiral_path);

    RoutedPath summary;
    std::string reason;
    std::optional<nav_msgs::msg::Path> routed =
      routeSpiral(spiral_path, parameters.waypoint_spacing, summary, reason);

    if (!routed) {
      if (require_traversability_map_) {
        RCLCPP_WARN(
          get_logger(), "Rejecting spiral search request: traversability map unusable (%s).",
          reason.c_str());
        response->error_code = Response::MAP_UNAVAILABLE;
        return;
      }

      RCLCPP_WARN(
        get_logger(),
        "Traversability map unusable (%s); returning the spiral without terrain checks.",
        reason.c_str());
      response->path = spiral_path;
      response->path_length = spiral.arc_length;
      response->traversability_checked = false;
      response->error_code = Response::SUCCESS;
    } else if (routed->poses.empty()) {
      RCLCPP_WARN(
        get_logger(), "Rejecting spiral search request: every waypoint is blocked or unreachable.");
      response->traversability_checked = true;
      response->truncated = true;
      response->skipped_waypoints = static_cast<uint32_t>(summary.skipped_waypoints);
      response->error_code = Response::NO_TRAVERSABLE_PATH;
      return;
    } else {
      response->path = std::move(*routed);
      response->path_length = polylineLength(response->path);
      response->traversability_checked = true;
      response->truncated = summary.truncated;
      response->skipped_waypoints = static_cast<uint32_t>(summary.skipped_waypoints);
      response->error_code = Response::SUCCESS;

      RCLCPP_INFO(
        get_logger(), "Routed spiral: %zu detours, %zu of %zu waypoints skipped%s.",
        summary.detour_count, summary.skipped_waypoints, spiral.waypoints.size(),
        summary.truncated ? ", outer spiral unreachable" : "");
    }

    RCLCPP_INFO(
      get_logger(),
      "Returning spiral with %zu waypoints covering %.1f m out to a %.1f m radius.",
      response->path.poses.size(), response->path_length, parameters.search_radius);

    publishPath(path_publisher_, response->path);
  } catch (const std::exception & e) {
    RCLCPP_ERROR(get_logger(), "Error generating spiral search: %s", e.what());
    response->error_code = Response::FAILURE;
  }
}

void SpiralSearchServer::handleTraversabilityMap(
  grid_map_msgs::msg::GridMap::ConstSharedPtr message)
{
  latest_map_ = std::move(message);
  // TraversabilityMapping leaves the map timestamp unset, so freshness is judged on arrival.
  latest_map_receipt_time_ = now();
}

std::optional<grid_map::GridMap> SpiralSearchServer::currentTraversabilityMap(
  std::string & reason) const
{
  if (!latest_map_) {
    reason = "no map received on " + std::string(traversability_subscriber_->get_topic_name());
    return std::nullopt;
  }

  const double age = (now() - latest_map_receipt_time_).seconds();
  if (age > max_map_age_) {
    reason = "latest map is " + std::to_string(age) + " s old, limit is " +
      std::to_string(max_map_age_) + " s";
    return std::nullopt;
  }

  grid_map::GridMap map;
  if (!grid_map::GridMapRosConverter::fromMessage(*latest_map_, map)) {
    reason = "map message could not be converted";
    return std::nullopt;
  }

  reason = validateTraversabilityMap(map, traversability_criteria_);
  if (!reason.empty()) {
    return std::nullopt;
  }
  return map;
}

std::optional<nav_msgs::msg::Path> SpiralSearchServer::routeSpiral(
  const nav_msgs::msg::Path & spiral,
  double waypoint_spacing,
  RoutedPath & summary,
  std::string & reason) const
{
  std::optional<grid_map::GridMap> map = currentTraversabilityMap(reason);
  if (!map) {
    return std::nullopt;
  }

  const rclcpp::Time map_stamp(latest_map_->header.stamp, get_clock()->get_clock_type());
  const tf2::TimePoint lookup_time = map_stamp.nanoseconds() == 0 ?
    tf2::TimePointZero :
    tf2::TimePoint(std::chrono::nanoseconds(map_stamp.nanoseconds()));

  tf2::Transform spiral_to_map;
  try {
    tf2::fromMsg(
      tf_buffer_->lookupTransform(map->getFrameId(), spiral.header.frame_id, lookup_time).transform,
      spiral_to_map);
  } catch (const tf2::TransformException & e) {
    reason = "no transform from '" + spiral.header.frame_id + "' to '" + map->getFrameId() +
      "': " + e.what();
    return std::nullopt;
  }

  std::vector<grid_map::Position> waypoints;
  waypoints.reserve(spiral.poses.size());
  for (const auto & pose : spiral.poses) {
    const tf2::Vector3 point =
      spiral_to_map * tf2::Vector3(pose.pose.position.x, pose.pose.position.y, pose.pose.position.z);
    waypoints.emplace_back(point.x(), point.y());
  }

  const double plane_height = spiral.poses.empty() ? 0.0 : spiral.poses.front().pose.position.z;
  const double map_plane_height =
    (spiral_to_map * tf2::Vector3(0.0, 0.0, plane_height)).z();

  const TraversabilityRouter router(std::move(*map), traversability_criteria_);
  summary = router.route(waypoints, waypoint_spacing);

  nav_msgs::msg::Path routed;
  routed.header = spiral.header;
  routed.poses.reserve(summary.points.size());

  const tf2::Transform map_to_spiral = spiral_to_map.inverse();
  for (const RoutedPoint & point : summary.points) {
    if (point.source_index) {
      routed.poses.push_back(spiral.poses[*point.source_index]);
      continue;
    }

    const tf2::Vector3 position =
      map_to_spiral * tf2::Vector3(point.position.x(), point.position.y(), map_plane_height);
    geometry_msgs::msg::PoseStamped pose;
    pose.header = spiral.header;
    pose.pose.position.x = position.x();
    pose.pose.position.y = position.y();
    pose.pose.position.z = plane_height;
    routed.poses.push_back(pose);
  }

  // Detour points never end the path, so each one can face the point after it.
  for (std::size_t index = 0; index + 1 < summary.points.size(); ++index) {
    if (summary.points[index].source_index) {
      continue;
    }
    const auto & here = routed.poses[index].pose.position;
    const auto & ahead = routed.poses[index + 1].pose.position;
    tf2::Quaternion heading;
    heading.setRPY(0.0, 0.0, std::atan2(ahead.y - here.y, ahead.x - here.x));
    routed.poses[index].pose.orientation = tf2::toMsg(heading);
  }

  return routed;
}

SpiralSearchParameters SpiralSearchServer::resolveParameters(
  const urc_msgs::srv::GenerateSpiralSearch::Request & request) const
{
  SpiralSearchParameters parameters;
  parameters.search_radius = request.search_radius;
  parameters.start_radius = start_radius_;
  parameters.track_spacing = overrideOrDefault(request.track_spacing, default_track_spacing_);
  parameters.waypoint_spacing =
    overrideOrDefault(request.waypoint_spacing, default_waypoint_spacing_);
  parameters.max_waypoints = max_waypoints_;

  return parameters;
}

nav_msgs::msg::Path SpiralSearchServer::toPath(
  const std::vector<SpiralWaypoint> & waypoints,
  const geometry_msgs::msg::PoseStamped & center) const
{
  nav_msgs::msg::Path path;
  path.header.frame_id = center.header.frame_id.empty() ? map_frame_ : center.header.frame_id;
  path.header.stamp = now();
  path.poses.reserve(waypoints.size());

  for (const auto & waypoint : waypoints) {
    tf2::Quaternion tangent;
    tangent.setRPY(0.0, 0.0, waypoint.heading);

    geometry_msgs::msg::PoseStamped pose;
    pose.header = path.header;
    pose.pose.position.x = center.pose.position.x + waypoint.x;
    pose.pose.position.y = center.pose.position.y + waypoint.y;
    pose.pose.position.z = center.pose.position.z;
    pose.pose.orientation = tf2::toMsg(tangent);

    path.poses.push_back(pose);
  }

  return path;
}

void SpiralSearchServer::publishPath(
  const rclcpp::Publisher<nav_msgs::msg::Path>::SharedPtr & publisher,
  const nav_msgs::msg::Path & path)
{
  if (publisher->get_subscription_count() == 0) {
    return;
  }

  publisher->publish(std::make_unique<nav_msgs::msg::Path>(path));
}

} // namespace urc_perception

int main(int argc, char ** argv)
{
  rclcpp::init(argc, argv);
  auto node = std::make_shared<urc_perception::SpiralSearchServer>(rclcpp::NodeOptions());
  rclcpp::spin(node);
  rclcpp::shutdown();
  return 0;
}
