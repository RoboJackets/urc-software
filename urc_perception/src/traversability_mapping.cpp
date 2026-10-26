#include "urc_perception/traversability_mapping.hpp"

#include <ament_index_cpp/get_package_share_directory.hpp>

#include <cmath>
#include <limits>
#include <stdexcept>
#include <vector>

#include <grid_map_core/iterators/GridMapIterator.hpp>
#include <grid_map_core/iterators/SubmapIterator.hpp>
#include <pcl_conversions/pcl_conversions.h>
#include <rcutils/logging.h>
#include <tf2_sensor_msgs/tf2_sensor_msgs.hpp>

namespace urc_perception
{
namespace
{
constexpr char kElevationLayer[] = "elevation";
constexpr char kCostLayer[] = "traversability_inflated";
constexpr float kUnknown = std::numeric_limits<float>::quiet_NaN();
}  // namespace

TraversabilityMapping::TraversabilityMapping(const rclcpp::NodeOptions & options)
: Node("traversability_mapping", options),
  filter_chain_("grid_map::GridMap"),
  grid_map_loader_(get_logger().get_child("pcl_loader"))
{
  // The loader logs progress and sparse-cell warnings on every update
  if (rcutils_logging_set_logger_level(
      get_logger().get_child("pcl_loader").get_name(),
      RCUTILS_LOG_SEVERITY_ERROR) != RCUTILS_RET_OK)
  {
    RCLCPP_WARN(get_logger(), "Could not lower the grid_map_pcl loader log level");
  }

  pointcloud_topic_ = declare_parameter("pointcloud_topic", pointcloud_topic_);
  output_map_topic_ = declare_parameter("output_map_topic", output_map_topic_);
  map_frame_ = declare_parameter("map_frame", map_frame_);
  odometry_topic_ = declare_parameter("odometry_topic", odometry_topic_);
  filter_chain_parameter_name_ =
    declare_parameter("filter_chain_parameter_name", filter_chain_parameter_name_);
  cache_size_x_ = declare_parameter("cache_size_x", cache_size_x_);
  cache_size_y_ = declare_parameter("cache_size_y", cache_size_y_);
  resolution_ = declare_parameter("resolution", resolution_);
  crop_margin_m_ = declare_parameter("crop_margin_m", crop_margin_m_);
  if (cache_size_x_ <= 0.0 || cache_size_y_ <= 0.0 || resolution_ <= 0.0 ||
    crop_margin_m_ < 0.0)
  {
    throw std::invalid_argument(
            "cache_size_x, cache_size_y and resolution must be positive; "
            "crop_margin_m must be non-negative");
  }

  grid_map_loader_.loadParameters(
    ament_index_cpp::get_package_share_directory("urc_perception") +
    "/config/pcl_grid_map_params.yaml");

  if (!filter_chain_.configure(
      filter_chain_parameter_name_, get_node_logging_interface(), get_node_parameters_interface()))
  {
    throw std::runtime_error("Could not configure the traversability filter chain");
  }

  tf_buffer_ = std::make_unique<tf2_ros::Buffer>(get_clock());
  tf_listener_ = std::make_shared<tf2_ros::TransformListener>(*tf_buffer_);

  grid_map_publisher_ = create_publisher<grid_map_msgs::msg::GridMap>(output_map_topic_, 10);

  pointcloud_subscriber_ = create_subscription<sensor_msgs::msg::PointCloud2>(
    pointcloud_topic_,
    rclcpp::SensorDataQoS().keep_last(1),
    std::bind(&TraversabilityMapping::handlePointcloud, this, std::placeholders::_1));

  odometry_subscriber_ = create_subscription<nav_msgs::msg::Odometry>(
    odometry_topic_,
    rclcpp::SensorDataQoS().keep_last(1),
    std::bind(&TraversabilityMapping::handleOdometry, this, std::placeholders::_1));

  cache_map_.setFrameId(map_frame_);
  cache_map_.setGeometry(grid_map::Length(cache_size_x_, cache_size_y_), resolution_);
  cache_map_.add(kElevationLayer, kUnknown);
  cache_map_.add(kCostLayer, kUnknown);

  // Start with a cache centered at the map origin so mapping works before odometry arrives.
  recenterCache(0.0, 0.0);

  RCLCPP_INFO(get_logger(), "Traversability mapping node has been started.");
}

TraversabilityMapping::~TraversabilityMapping() = default;

geometry_msgs::msg::TransformStamped TraversabilityMapping::lookupTransformSafe(
  const std::string & target_frame,
  const std::string & source_frame,
  const rclcpp::Time & stamp,
  const tf2::Duration & timeout,
  bool & success)
{
  geometry_msgs::msg::TransformStamped transform;
  success = false;

  try {
    transform = tf_buffer_->lookupTransform(target_frame, source_frame, stamp, timeout);
    success = true;
    return transform;
  } catch (const tf2::TransformException & ex1) {
    try {
      transform = tf_buffer_->lookupTransform(target_frame, source_frame, rclcpp::Time(0), timeout);
      success = true;
      RCLCPP_WARN_THROTTLE(
        get_logger(), *get_clock(), 2000,
        "Stamped transform unavailable; using latest transform from %s to %s.",
        source_frame.c_str(), target_frame.c_str());
      return transform;
    } catch (const tf2::TransformException & ex2) {
      RCLCPP_WARN_THROTTLE(
        get_logger(), *get_clock(), 2000,
        "Transform lookup failed from %s to %s. stamped='%s', latest='%s'",
        source_frame.c_str(), target_frame.c_str(), ex1.what(), ex2.what());
      return transform;
    }
  }
}

// Keeps only points that can affect the cache, so work stays bounded by the
// window rather than growing with the whole input map
TraversabilityMapping::Cloud::Ptr TraversabilityMapping::cropToCache(const Cloud & cloud) const
{
  const grid_map::Position center = cache_map_.getPosition();
  const double half_x = cache_size_x_ / 2.0 + crop_margin_m_;
  const double half_y = cache_size_y_ / 2.0 + crop_margin_m_;

  Cloud::Ptr cropped(new Cloud);
  cropped->reserve(cloud.size());
  for (const auto & point : cloud.points) {
    if (std::isfinite(point.z) &&
      std::abs(point.x - center.x()) <= half_x &&
      std::abs(point.y - center.y()) <= half_y)
    {
      cropped->push_back(point);
    }
  }
  return cropped;
}

bool TraversabilityMapping::buildLocalMap(const Cloud::Ptr & cloud, grid_map::GridMap & local_map)
{
  grid_map_loader_.setInputCloud(cloud);
  grid_map_loader_.preProcessInputCloud();
  grid_map_loader_.initializeGridMapGeometryFromInputCloud();
  grid_map_loader_.addLayerFromInputCloud(kElevationLayer);

  grid_map::GridMap elevation_map = grid_map_loader_.getGridMap();
  elevation_map.setFrameId(map_frame_);
  if (!filter_chain_.update(elevation_map, local_map)) {
    RCLCPP_ERROR_THROTTLE(
      get_logger(), *get_clock(), 2000, "Could not update the grid map filter chain.");
    return false;
  }
  return true;
}

void TraversabilityMapping::mergeIntoCache(const grid_map::GridMap & local_map)
{
  for (grid_map::GridMapIterator it(local_map); !it.isPastEnd(); ++it) {
    const grid_map::Index local_index = *it;
    if (!local_map.isValid(local_index, kCostLayer)) {
      continue;
    }

    grid_map::Position position;
    local_map.getPosition(local_index, position);
    grid_map::Index cache_index;
    if (!cache_map_.getIndex(position, cache_index)) {
      continue;
    }

    cache_map_.at(kCostLayer, cache_index) = local_map.at(kCostLayer, local_index);
    const float elevation = local_map.at(kElevationLayer, local_index);
    if (std::isfinite(elevation)) {
      cache_map_.at(kElevationLayer, cache_index) = elevation;
    }
  }
}

void TraversabilityMapping::recenterCache(double center_x_world, double center_y_world)
{
  const double snapped_x = std::round(center_x_world / resolution_) * resolution_;
  const double snapped_y = std::round(center_y_world / resolution_) * resolution_;
  const grid_map::Position cache_center(snapped_x, snapped_y);

  if (!cache_initialized_) {
    cache_map_.setPosition(cache_center);
    cache_initialized_ = true;
    return;
  }

  std::vector<grid_map::BufferRegion> regions;
  cache_map_.move(cache_center, regions);

  for (const auto & region : regions) {
    for (grid_map::SubmapIterator it(cache_map_, region); !it.isPastEnd(); ++it) {
      cache_map_.at(kElevationLayer, *it) = kUnknown;
      cache_map_.at(kCostLayer, *it) = kUnknown;
    }
  }
}

void TraversabilityMapping::handleOdometry(const nav_msgs::msg::Odometry::SharedPtr msg)
{
  recenterCache(msg->pose.pose.position.x, msg->pose.pose.position.y);
  publishCacheMap();
}

void TraversabilityMapping::publishCacheMap()
{
  if (!cache_initialized_) {
    return;
  }
  grid_map_publisher_->publish(grid_map::GridMapRosConverter::toMessage(cache_map_));
}

void TraversabilityMapping::handlePointcloud(const sensor_msgs::msg::PointCloud2::SharedPtr msg)
{
  if (!cache_initialized_) {
    return;
  }

  bool tf_ok = false;
  const auto cloud_to_map = lookupTransformSafe(
    map_frame_, msg->header.frame_id, msg->header.stamp, tf2::durationFromSec(0.05), tf_ok);
  if (!tf_ok) {
    return;
  }

  sensor_msgs::msg::PointCloud2 cloud_map_msg;
  tf2::doTransform(*msg, cloud_map_msg, cloud_to_map);
  Cloud cloud_map;
  pcl::fromROSMsg(cloud_map_msg, cloud_map);

  const Cloud::Ptr cropped = cropToCache(cloud_map);
  if (cropped->empty()) {
    return;
  }

  grid_map::GridMap local_map;
  if (!buildLocalMap(cropped, local_map)) {
    return;
  }
  mergeIntoCache(local_map);
  publishCacheMap();
}

}  // namespace urc_perception

#include <rclcpp_components/register_node_macro.hpp>
RCLCPP_COMPONENTS_REGISTER_NODE(urc_perception::TraversabilityMapping)
