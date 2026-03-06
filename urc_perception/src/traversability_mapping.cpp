#include "traversability_mapping.hpp"

#include <ament_index_cpp/get_package_share_directory.hpp>

#include <algorithm>
#include <chrono>
#include <cmath>
#include <limits>
#include <vector>

#include <geometry_msgs/msg/pose.hpp>
#include <grid_map_pcl/GridMapPclLoader.hpp>
#include <pcl/PCLPointCloud2.h>
#include <pcl/filters/filter.h>
#include <pcl_conversions/pcl_conversions.h>
#include <tf2_geometry_msgs/tf2_geometry_msgs.hpp>
#include <tf2_sensor_msgs/tf2_sensor_msgs.hpp>

namespace urc_perception
{

TraversabilityMapping::TraversabilityMapping(const rclcpp::NodeOptions & options)
: Node("traversability_mapping", options), filter_chain_("grid_map::GridMap")
{
  pointcloud_topic_ = this->declare_parameter("pointcloud_topic", pointcloud_topic_);
  output_map_topic_ = this->declare_parameter("output_map_topic", output_map_topic_);
  cache_map_topic_ = this->declare_parameter("cache_map_topic", cache_map_topic_);
  map_frame_ = this->declare_parameter("map_frame", map_frame_);
  odometry_topic_ = this->declare_parameter("odometry_topic", odometry_topic_);
  filter_chain_parameter_name_ =
    this->declare_parameter("filter_chain_parameter_name", filter_chain_parameter_name_);
  filter_radius_ = this->declare_parameter("filter_radius", filter_radius_);
  cache_size_x_ = this->declare_parameter("cache_size_x", cache_size_x_);
  cache_size_y_ = this->declare_parameter("cache_size_y", cache_size_y_);
  resolution_ = this->declare_parameter("resolution", resolution_);
  recenter_rate_hz_ = this->declare_parameter("recenter_rate_hz", recenter_rate_hz_);
  min_filter_radius_ = this->declare_parameter("min_filter_radius", 0.2);

  RCLCPP_INFO(this->get_logger(), "Traversability mapping node has been started.");

  tf_buffer_ = std::make_unique<tf2_ros::Buffer>(this->get_clock());
  tf_listener_ = std::make_shared<tf2_ros::TransformListener>(*tf_buffer_);

  grid_map_publisher_ = create_publisher<grid_map_msgs::msg::GridMap>(output_map_topic_, 10);
  cache_map_publisher_ = create_publisher<grid_map_msgs::msg::GridMap>(cache_map_topic_, 10);

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
  cache_map_.add("elevation", 0.0);
  cache_map_.add("traversability_inflated", 0.0);

  use_filter_chain_ = filter_chain_.configure(
    filter_chain_parameter_name_,
    this->get_node_logging_interface(),
    this->get_node_parameters_interface());

  if (use_filter_chain_) {
    RCLCPP_INFO(this->get_logger(), "Filter chain configured.");
  } else {
    RCLCPP_WARN(
      this->get_logger(),
      "Could not configure the filter chain. Falling back to unfiltered local map.");
  }
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
        this->get_logger(), *this->get_clock(), 2000,
        "Stamped transform unavailable; using latest transform from %s to %s.",
        source_frame.c_str(), target_frame.c_str());
      return transform;
    } catch (const tf2::TransformException & ex2) {
      RCLCPP_WARN_THROTTLE(
        this->get_logger(), *this->get_clock(), 2000,
        "Transform lookup failed from %s to %s. stamped='%s', latest='%s'",
        source_frame.c_str(), target_frame.c_str(), ex1.what(), ex2.what());
      return transform;
    }
  }
}

void TraversabilityMapping::filterSphere(
  pcl::PointCloud<pcl::PointXYZ>::Ptr cloud,
  float min_radius,
  float max_radius)
{
  const double min_r2 = static_cast<double>(min_radius) * static_cast<double>(min_radius);
  const double max_r2 = static_cast<double>(max_radius) * static_cast<double>(max_radius);

  pcl::PointCloud<pcl::PointXYZ>::Ptr filtered_cloud(new pcl::PointCloud<pcl::PointXYZ>());
  filtered_cloud->points.reserve(cloud->points.size());

  for (const auto & point : cloud->points) {
    if (!std::isfinite(point.x) || !std::isfinite(point.y) || !std::isfinite(point.z)) {
      continue;
    }

    const double d2 =
      static_cast<double>(point.x) * point.x +
      static_cast<double>(point.y) * point.y +
      static_cast<double>(point.z) * point.z;

    if (d2 >= min_r2 && d2 <= max_r2) {
      filtered_cloud->points.push_back(point);
    }
  }

  filtered_cloud->width = static_cast<uint32_t>(filtered_cloud->points.size());
  filtered_cloud->height = 1;
  filtered_cloud->is_dense = true;

  *cloud = std::move(*filtered_cloud);
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
    const auto start = region.getStartIndex();
    const auto size = region.getSize();
    const auto map_size = cache_map_.getSize();

    for (int r = 0; r < size(0); ++r) {
      for (int c = 0; c < size(1); ++c) {
        grid_map::Index idx(start(0) + r, start(1) + c);
        idx(0) = (idx(0) + map_size(0)) % map_size(0);
        idx(1) = (idx(1) + map_size(1)) % map_size(1);

        cache_map_.at("elevation", idx) = 0.0;
        cache_map_.at("traversability_inflated", idx) = 0.0;
      }
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

  auto msg1 = grid_map::GridMapRosConverter::toMessage(cache_map_);

  grid_map_publisher_->publish(std::move(msg1));
}

void TraversabilityMapping::handlePointcloud(const sensor_msgs::msg::PointCloud2::SharedPtr msg)
{
  if (!cache_initialized_) {
    return;
  }

  pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_sensor(new pcl::PointCloud<pcl::PointXYZ>);
  pcl::fromROSMsg(*msg, *cloud_sensor);

  filterSphere(cloud_sensor, min_filter_radius_, filter_radius_);

  sensor_msgs::msg::PointCloud2 cloud_sensor_filtered_msg;
  pcl::toROSMsg(*cloud_sensor, cloud_sensor_filtered_msg);
  cloud_sensor_filtered_msg.header = msg->header;

  bool tf_ok = false;
  const auto sensor_to_map = lookupTransformSafe(
    map_frame_,
    msg->header.frame_id,
    msg->header.stamp,
    tf2::durationFromSec(0.05),
    tf_ok);

  if (!tf_ok) {
    return;
  }

  sensor_msgs::msg::PointCloud2 cloud_global_msg;
  tf2::doTransform(cloud_sensor_filtered_msg, cloud_global_msg, sensor_to_map);

  pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_global(new pcl::PointCloud<pcl::PointXYZ>);
  pcl::fromROSMsg(cloud_global_msg, *cloud_global);

  if (cloud_global->empty()) {
    return;
  }

  const std::string file_path =
    ament_index_cpp::get_package_share_directory("urc_perception") +
    "/config/pcl_grid_map_params.yaml";

  grid_map::GridMapPclLoader grid_map_loader(this->get_logger());
  grid_map_loader.setInputCloud(cloud_global);
  grid_map_loader.loadParameters(file_path);

  grid_map_loader.preProcessInputCloud();
  grid_map_loader.initializeGridMapGeometryFromInputCloud();
  grid_map_loader.addLayerFromInputCloud("elevation");
  grid_map_loader.addLayerFromInputCloud("traversability_inflated");

  grid_map::GridMap local_map = grid_map_loader.getGridMap();
  local_map.setFrameId(map_frame_);

  grid_map::GridMap filtered_local_map;
  if (use_filter_chain_) {
    if (!filter_chain_.update(local_map, filtered_local_map)) {
      RCLCPP_ERROR(this->get_logger(), "Could not update the grid map filter chain.");
      return;
    }
  } else {
    filtered_local_map = local_map;
  }

  for (grid_map::GridMapIterator it(filtered_local_map); !it.isPastEnd(); ++it) {
    const grid_map::Index src_index = *it;

    if (!filtered_local_map.isValid(src_index, "elevation") ||
        !filtered_local_map.isValid(src_index, "traversability_inflated"))
    {
      continue;
    }

    grid_map::Position world_position;
    filtered_local_map.getPosition(src_index, world_position);

    grid_map::Index cache_index;
    if (!cache_map_.getIndex(world_position, cache_index)) {
      continue;
    }

    const float src_elevation = filtered_local_map.at("elevation", src_index);
    const float src_trav = filtered_local_map.at("traversability_inflated", src_index);

    cache_map_.at("elevation", cache_index) =
      std::max(cache_map_.at("elevation", cache_index), src_elevation);

    cache_map_.at("traversability_inflated", cache_index) = src_trav;
  }

  publishCacheMap();
}

}  // namespace urc_perception

#include <rclcpp_components/register_node_macro.hpp>
RCLCPP_COMPONENTS_REGISTER_NODE(urc_perception::TraversabilityMapping)
