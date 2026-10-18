#include "spiral_search_server.hpp"

#include <tf2/LinearMath/Quaternion.h>
#include <tf2_geometry_msgs/tf2_geometry_msgs.hpp>

#include <cmath>
#include <memory>
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

  path_publisher_ = create_publisher<nav_msgs::msg::Path>(
    declare_parameter<std::string>("path_topic", "/spiral_search_path"),
    rclcpp::SystemDefaultsQoS());

  spiral_service_ = create_service<urc_msgs::srv::GenerateSpiralSearch>(
    declare_parameter<std::string>("service_name", "generate_spiral_search"),
    std::bind(
      &SpiralSearchServer::generateSpiralSearch, this, std::placeholders::_1,
      std::placeholders::_2));

  RCLCPP_INFO(
    get_logger(),
    "Spiral search server started. Track spacing %.2f m, start radius %.2f m, "
    "waypoint spacing %.2f m.",
    default_track_spacing_, start_radius_, default_waypoint_spacing_);
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

  try {
    const SpiralPath spiral = generateArchimedeanSpiral(parameters);

    response->path = toPath(spiral.waypoints, request->center);
    response->track_spacing = parameters.track_spacing;
    response->path_length = spiral.arc_length;
    response->error_code = urc_msgs::srv::GenerateSpiralSearch::Response::SUCCESS;

    RCLCPP_INFO(
      get_logger(),
      "Returning spiral with %ld waypoints covering %.1f m out to a %.1f m radius.",
      response->path.poses.size(), spiral.arc_length, parameters.search_radius);

    publishPath(response->path);
  } catch (const std::exception & e) {
    RCLCPP_ERROR(get_logger(), "Error generating spiral search: %s", e.what());
    response->error_code = urc_msgs::srv::GenerateSpiralSearch::Response::FAILURE;
  }
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

void SpiralSearchServer::publishPath(const nav_msgs::msg::Path & path)
{
  if (path_publisher_->get_subscription_count() == 0) {
    return;
  }

  path_publisher_->publish(std::make_unique<nav_msgs::msg::Path>(path));
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
