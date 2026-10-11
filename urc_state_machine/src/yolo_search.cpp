#include "urc_state_machine/nav_coordinator.hpp"
#include <algorithm>
#include <cmath>
#include <stdexcept>
#include <string>
#include <vector>
#include <std_msgs/msg/header.hpp>

namespace nav_coordinator
{
namespace
{

std::vector<urc_state_machine::DetectionCandidate> toDetectionCandidates(const vision_msgs::msg::Detection2DArray & detections)
{
  std::vector<urc_state_machine::DetectionCandidate> candidates;
  candidates.reserve(detections.detections.size());

  for (const auto & detection : detections.detections) {
    if (detection.results.empty()) {
      continue;
    }
    const auto best_result = std::max_element(
      detection.results.begin(), detection.results.end(),
      [](const auto & lhs, const auto & rhs) {
        return lhs.hypothesis.score < rhs.hypothesis.score;
      });

    urc_state_machine::DetectionCandidate candidate;
    candidate.class_name = best_result->hypothesis.class_id;
    candidate.confidence = best_result->hypothesis.score;
    candidate.center_x = detection.bbox.center.position.x;
    candidate.center_y = detection.bbox.center.position.y;
    candidate.width = detection.bbox.size_x;
    candidate.height = detection.bbox.size_y;
    candidates.push_back(candidate);
  }
  return candidates;
}

// Rounds a pixel coordinate into [0, limit - 1], or [0, inf) when the image size is unknown.

std::uint32_t toPixel(double value, std::uint32_t limit)
{
  double clamped = std::max(0.0, std::round(value));
  if (limit > 0) {
    clamped = std::min(clamped, static_cast<double>(limit - 1));
  }
  return static_cast<std::uint32_t>(clamped);
}

urc_msgs::msg::DetectionBoundingBox toBoundingBox(const urc_state_machine::DetectionCandidate & candidate, const std_msgs::msg::Header & header, std::uint32_t image_width, std::uint32_t image_height)
{
  urc_msgs::msg::DetectionBoundingBox box;
  box.header = header;
  box.class_name = candidate.class_name;
  box.confidence = static_cast<float>(candidate.confidence);
  box.image_width = image_width;
  box.image_height = image_height;
  box.x_min = toPixel(candidate.center_x - candidate.width / 2.0, image_width);
  box.y_min = toPixel(candidate.center_y - candidate.height / 2.0, image_height);
  box.x_max = toPixel(candidate.center_x + candidate.width / 2.0, image_width);
  box.y_max = toPixel(candidate.center_y + candidate.height / 2.0, image_height);
  return box;
}

geometry_msgs::msg::PoseStamped toSearchWaypoint(
  const urc_state_machine::PlanarPose & pose, const std_msgs::msg::Header & header, double z)
{
  geometry_msgs::msg::PoseStamped waypoint;
  waypoint.header = header;
  waypoint.pose.position.x = pose.x;
  waypoint.pose.position.y = pose.y;
  waypoint.pose.position.z = z;
  waypoint.pose.orientation.z = std::sin(pose.yaw / 2.0);
  waypoint.pose.orientation.w = std::cos(pose.yaw / 2.0);
  return waypoint;
}
}  // namespace

void NavCoordinator::initializeYoloSearch()
{
  urc_state_machine::DetectionConfirmationConfig confirmation_config;

  confirmation_config.target_classes = declare_parameter<std::vector<std::string>>("yolo_target_classes", std::vector<std::string>{});
  confirmation_config.min_confidence = declare_parameter<double>("yolo_min_confidence", 0.5);
  confirmation_config.required_hits = declare_parameter<int>("yolo_confirmation_hits", 3);
  confirmation_config.window_frames = declare_parameter<int>("yolo_confirmation_window", 5);

  yolo_confirmation_.emplace(confirmation_config);

  spiral_search_config_.radius_m = declare_parameter<double>("search_radius_m", 20.0);

  spiral_search_config_.ring_spacing_m = declare_parameter<double>("search_ring_spacing_m", 4.0);

  spiral_search_config_.point_spacing_m = declare_parameter<double>("search_point_spacing_m", 4.0);

  urc_state_machine::validateSpiralSearchConfig(spiral_search_config_);

  max_consecutive_search_leg_failures_ = declare_parameter<int>("max_consecutive_search_leg_failures", 3);

  if (max_consecutive_search_leg_failures_ < 1) {
    throw std::invalid_argument("max_consecutive_search_leg_failures must be >= 1");
  }

  const auto detections_topic = declare_parameter<std::string>("yolo_detections_topic", "/yolo/detections");
  const auto camera_info_topic = declare_parameter<std::string>("yolo_camera_info_topic", "/camera/color/camera_info");

  if (detections_topic.empty()) {
    throw std::invalid_argument("yolo_detections_topic must not be empty");
  }

  yolo_detection_subscriber_ = create_subscription<vision_msgs::msg::Detection2DArray>(
    detections_topic, rclcpp::SensorDataQoS(),
    [this](vision_msgs::msg::Detection2DArray::ConstSharedPtr msg) {
      handleYoloDetections(*msg);
    });

  // Camera info only fills in the image size reported with the bounding box.
  if (!camera_info_topic.empty()) {
    camera_info_subscriber_ = create_subscription<sensor_msgs::msg::CameraInfo>(
      camera_info_topic, rclcpp::SensorDataQoS(),
      [this](sensor_msgs::msg::CameraInfo::ConstSharedPtr msg) {
        camera_image_width_ = msg->width;
        camera_image_height_ = msg->height;
      });
  }
}

void NavCoordinator::startYoloSearch()
{
  const auto & center = active_mission_->original_waypoint;
  const auto spiral = urc_state_machine::generateSpiralSearch(
    center.pose.position.x, center.pose.position.y, spiral_search_config_);

  std_msgs::msg::Header header;
  header.frame_id = center.header.frame_id;
  header.stamp = now();

  auto & waypoints = active_mission_->search_waypoints;
  waypoints.clear();
  waypoints.reserve(spiral.size());
  for (const auto & pose : spiral) {
    waypoints.push_back(toSearchWaypoint(pose, header, center.pose.position.z));
  }

  active_mission_->navigation_leg = urc_state_machine::NavigationLeg::SEARCH_PATTERN;
  active_mission_->next_search_waypoint = 0;
  active_mission_->consecutive_search_leg_failures = 0;
  yolo_confirmation_->reset();

  RCLCPP_INFO(
    get_logger(), "Starting YOLO spiral search: %zu waypoints within %.1f m.",
    waypoints.size(), spiral_search_config_.radius_m);
  transitionTo(
    urc_state_machine::MissionState::SEARCHING_YOLO,
    "initial waypoint reached; starting spiral search");
  sendNextSearchLeg();
}

void NavCoordinator::sendNextSearchLeg()
{
  if (!active_mission_) {
    return;
  }

  auto & mission = *active_mission_;
  if (mission.next_search_waypoint >= mission.search_waypoints.size()) {
    failMission(
      ExecuteMission::Result::TARGET_NOT_FOUND, ErrorType::SEARCH_FAILURE,
      "Spiral search finished without a confirmed YOLO detection.");
    return;
  }

  const auto waypoint = mission.search_waypoints[mission.next_search_waypoint++];
  sendWaypointGoal(
    waypoint, ExecuteMission::Feedback::STATE_SEARCHING, ExecuteMission::Result::SEARCH_FAILED,
    [this](const GoalHandleNavigate::WrappedResult & result) {
      finishSearchLeg(result);
    });
}

// Search waypoints are best effort: an unreachable one is skipped, and only a run of
// consecutive failures aborts the search.

void NavCoordinator::finishSearchLeg(const GoalHandleNavigate::WrappedResult & result)
{
  if (!active_mission_) {
    return;
  }

  active_goal_handle_.reset();
  if (active_mission_->cancellation_requested) {
    finishCanceledMission();
    return;
  }

  const bool reached = result.code == rclcpp_action::ResultCode::SUCCEEDED && result.result &&
    result.result->error_code == NavigateToWaypoint::Result::SUCCESS;
  if (reached) {
    active_mission_->consecutive_search_leg_failures = 0;
  } else if (++active_mission_->consecutive_search_leg_failures >=
    max_consecutive_search_leg_failures_)
  {
    failMission(
      ExecuteMission::Result::SEARCH_FAILED, ErrorType::SEARCH_FAILURE,
      "Too many consecutive search waypoints failed.");
    return;
  } else {
    RCLCPP_WARN(
      get_logger(), "Search waypoint %zu failed; skipping to the next one.",
      active_mission_->next_search_waypoint);
  }

  sendNextSearchLeg();
}

void NavCoordinator::handleYoloDetections(const vision_msgs::msg::Detection2DArray & detections)
{
  if (!active_mission_ || state_ != urc_state_machine::MissionState::SEARCHING_YOLO) {
    return;
  }

  const auto confirmed = yolo_confirmation_->update(toDetectionCandidates(detections));
  if (!confirmed) {
    return;
  }

  succeedYoloSearch(
    toBoundingBox(*confirmed, detections.header, camera_image_width_, camera_image_height_));
}

void NavCoordinator::succeedYoloSearch(const urc_msgs::msg::DetectionBoundingBox & bounding_box)
{
  
  if (active_goal_handle_) {
    follower_client_->async_cancel_goal(active_goal_handle_);
    active_goal_handle_.reset();
  }

  auto result = std::make_shared<ExecuteMission::Result>();
  result->error_code = ExecuteMission::Result::SUCCESS;
  result->message = "Confirmed YOLO detection of '" + bounding_box.class_name + "'.";
  result->has_bounding_box = true;
  result->bounding_box = bounding_box;
  active_mission_->goal_handle->succeed(result);
  active_mission_.reset();

  RCLCPP_INFO(
    get_logger(), "YOLO target '%s' confirmed (confidence %.2f).",
    bounding_box.class_name.c_str(), bounding_box.confidence);
  transitionTo(urc_state_machine::MissionState::SUCCEEDED, "YOLO target confirmed");
}

}  