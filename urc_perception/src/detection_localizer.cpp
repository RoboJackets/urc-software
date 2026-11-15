#include "urc_perception/detection_localizer.hpp"

#include <cstdint>
#include <cstdlib>
#include <stdexcept>

#include <cv_bridge/cv_bridge.h>
#include <rclcpp_components/register_node_macro.hpp>
#include <sensor_msgs/image_encodings.hpp>
#include <tf2/exceptions.h>
#include <tf2_geometry_msgs/tf2_geometry_msgs.hpp>

namespace urc_perception
{

namespace
{

constexpr double kMillimetersToMeters = 0.001;
constexpr int kWarnThrottleMs = 2000;
constexpr int kInfoThrottleMs = 1000;

PixelBox toPixelBox(const urc_msgs::msg::DetectionBoundingBox & detection)
{
  return {
    static_cast<int>(detection.x_min), static_cast<int>(detection.y_min),
    static_cast<int>(detection.x_max), static_cast<int>(detection.y_max)};
}

}  // namespace

DetectionLocalizer::DetectionLocalizer(const rclcpp::NodeOptions & options)
: rclcpp::Node("detection_localizer", options),
  target_frame_(declare_parameter<std::string>("target_frame", "map")),
  max_depth_stamp_gap_(rclcpp::Duration::from_seconds(
      declare_parameter<double>("max_depth_stamp_gap_s", 0.05))),
  transform_timeout_(tf2::durationFromSec(
      declare_parameter<double>("transform_timeout_s", 0.05))),
  box_core_fraction_(declare_parameter<double>("box_core_fraction", 0.5)),
  depth_buffer_size_(0)
{
  const int depth_buffer_size = declare_parameter<int>("depth_buffer_size", 10);
  if (box_core_fraction_ <= 0.0 || box_core_fraction_ > 1.0) {
    throw std::invalid_argument("box_core_fraction must be in (0, 1]");
  }
  if (depth_buffer_size <= 0) {
    throw std::invalid_argument("depth_buffer_size must be positive");
  }
  depth_buffer_size_ = static_cast<size_t>(depth_buffer_size);

  tf_buffer_ = std::make_shared<tf2_ros::Buffer>(get_clock());
  tf_listener_ = std::make_shared<tf2_ros::TransformListener>(*tf_buffer_);

  camera_info_sub_ = create_subscription<sensor_msgs::msg::CameraInfo>(
    declare_parameter<std::string>("camera_info_topic", "/camera/camera_info"),
    rclcpp::SensorDataQoS(),
    [this](const sensor_msgs::msg::CameraInfo::ConstSharedPtr & msg) {onCameraInfo(msg);});
  depth_sub_ = create_subscription<Image>(
    declare_parameter<std::string>("depth_topic", "/camera/depth_image"),
    rclcpp::SensorDataQoS(),
    [this](const Image::ConstSharedPtr & msg) {onDepth(msg);});
  detection_sub_ = create_subscription<Detection>(
    declare_parameter<std::string>("detections_topic", "/yolo/detections"), 10,
    [this](const Detection::ConstSharedPtr & msg) {onDetection(msg);});
  point_pub_ = create_publisher<geometry_msgs::msg::PointStamped>(
    declare_parameter<std::string>("output_topic", "/yolo/object_point"), 10);
}

void DetectionLocalizer::onCameraInfo(const sensor_msgs::msg::CameraInfo::ConstSharedPtr & msg)
{
  if (msg->k[0] <= 0.0 || msg->k[4] <= 0.0) {
    return;
  }
  intrinsics_ = PinholeIntrinsics{msg->k[0], msg->k[4], msg->k[2], msg->k[5]};
}

void DetectionLocalizer::onDepth(const Image::ConstSharedPtr & msg)
{
  depth_frames_.push_back(msg);
  if (depth_frames_.size() > depth_buffer_size_) {
    depth_frames_.pop_front();
  }
}

void DetectionLocalizer::onDetection(const Detection::ConstSharedPtr & detection)
{
  if (!intrinsics_) {
    RCLCPP_WARN_THROTTLE(get_logger(), *get_clock(), kWarnThrottleMs, "Waiting for camera info");
    return;
  }
  const auto depth_msg = depthFrameNear(rclcpp::Time(detection->header.stamp));
  if (!depth_msg) {
    RCLCPP_WARN_THROTTLE(
      get_logger(), *get_clock(), kWarnThrottleMs, "No depth frame near detection stamp");
    return;
  }
  const auto depth_m = boxDepth(depth_msg, *detection);
  if (!depth_m) {
    return;
  }

  const cv::Point3d point = deprojectBoxCenter(*intrinsics_, toPixelBox(*detection), *depth_m);
  geometry_msgs::msg::PointStamped camera_point;
  camera_point.header = detection->header;  // camera_optical_frame at the image stamp
  camera_point.point.x = point.x;
  camera_point.point.y = point.y;
  camera_point.point.z = point.z;

  const auto target_point = toTargetFrame(camera_point);
  if (!target_point) {
    return;
  }
  point_pub_->publish(*target_point);
  RCLCPP_INFO_THROTTLE(
    get_logger(), *get_clock(), kInfoThrottleMs, "%s at (%.2f, %.2f, %.2f) in %s",
    detection->class_name.c_str(), target_point->point.x, target_point->point.y,
    target_point->point.z, target_frame_.c_str());
}

sensor_msgs::msg::Image::ConstSharedPtr DetectionLocalizer::depthFrameNear(
  const rclcpp::Time & stamp) const
{
  Image::ConstSharedPtr nearest;
  int64_t nearest_gap = max_depth_stamp_gap_.nanoseconds();
  for (const auto & frame : depth_frames_) {
    const int64_t abs_gap = std::abs((rclcpp::Time(frame->header.stamp) - stamp).nanoseconds());
    if (abs_gap <= nearest_gap) {
      nearest = frame;
      nearest_gap = abs_gap;
    }
  }
  return nearest;
}

std::optional<double> DetectionLocalizer::boxDepth(
  const Image::ConstSharedPtr & depth_msg, const Detection & detection)
{
  if (depth_msg->width != detection.image_width || depth_msg->height != detection.image_height) {
    RCLCPP_WARN_THROTTLE(
      get_logger(), *get_clock(), kWarnThrottleMs,
      "Depth image %ux%u does not match detection image %ux%u; is depth aligned to colour?",
      depth_msg->width, depth_msg->height, detection.image_width, detection.image_height);
    return std::nullopt;
  }

  const cv_bridge::CvImageConstPtr depth = cv_bridge::toCvShare(depth_msg);
  cv::Mat depth_m;
  if (depth_msg->encoding == sensor_msgs::image_encodings::TYPE_16UC1) {
    depth->image.convertTo(depth_m, CV_32FC1, kMillimetersToMeters);
  } else if (depth_msg->encoding == sensor_msgs::image_encodings::TYPE_32FC1) {
    depth_m = depth->image;
  } else {
    RCLCPP_WARN_THROTTLE(
      get_logger(), *get_clock(), kWarnThrottleMs, "Unsupported depth encoding '%s'",
      depth_msg->encoding.c_str());
    return std::nullopt;
  }
  return medianCoreDepth(depth_m, toPixelBox(detection), box_core_fraction_);
}

std::optional<geometry_msgs::msg::PointStamped> DetectionLocalizer::toTargetFrame(
  const geometry_msgs::msg::PointStamped & camera_point)
{
  // Bounded wait: SLAM's map->base_link can trail the image stamp slightly.
  try {
    return tf_buffer_->transform(camera_point, target_frame_, transform_timeout_);
  } catch (const tf2::TransformException & error) {
    RCLCPP_WARN_THROTTLE(
      get_logger(), *get_clock(), kWarnThrottleMs, "No transform %s -> %s: %s",
      camera_point.header.frame_id.c_str(), target_frame_.c_str(), error.what());
    return std::nullopt;
  }
}

}  // namespace urc_perception

RCLCPP_COMPONENTS_REGISTER_NODE(urc_perception::DetectionLocalizer)
