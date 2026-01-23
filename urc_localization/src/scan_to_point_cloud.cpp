#include "scan_to_point_cloud.hpp"

#include <array>
#include <functional>
#include "rclcpp_components/register_node_macro.hpp"
#include <sensor_msgs/msg/laser_scan.hpp>
#include <sensor_msgs/msg/point_cloud2.hpp>
#include <laser_geometry/laser_geometry.hpp>
#include <tf2/exceptions.h>


namespace scan_to_point_cloud
{

ScanToPointCloud::ScanToPointCloud(const rclcpp::NodeOptions &options)
    : rclcpp::Node("scan_to_point_cloud", options)
{
  const auto scan_input_topic = declare_parameter<std::string>("scan_input_topic", "/scan");
  const auto point_cloud_output_topic = declare_parameter<std::string>("point_cloud_output_topic", "/point_cloud");
  target_frame_ = declare_parameter<std::string>("target_frame", "base_link");

  tf_buffer_ = std::make_unique<tf2_ros::Buffer>(this->get_clock());
  tf_listener_ = std::make_shared<tf2_ros::TransformListener>(*tf_buffer_);

  point_cloud_publisher_ = create_publisher<sensor_msgs::msg::PointCloud2>(
      point_cloud_output_topic,
      rclcpp::SystemDefaultsQoS());

  scan_subscription_ = create_subscription<sensor_msgs::msg::LaserScan>(
      scan_input_topic,
      rclcpp::SystemDefaultsQoS(),
      std::bind(&ScanToPointCloud::handleScan, this, std::placeholders::_1));
}

void ScanToPointCloud::handleScan(const sensor_msgs::msg::LaserScan::SharedPtr msg)
{
  if (!point_cloud_publisher_)
  {
    return;
  }

  laser_geometry::LaserProjection projector;
  sensor_msgs::msg::PointCloud2 cloud;

  try
  {
    // Transform scan to target frame and project to PointCloud2.
    projector.transformLaserScanToPointCloud(
        target_frame_, *msg, cloud, *tf_buffer_);
  }
  catch (const tf2::TransformException &ex)
  {
    RCLCPP_WARN_THROTTLE(
        get_logger(), *get_clock(), 2000,
        "TF transform failed for LaserScan to %s: %s",
        target_frame_.c_str(), ex.what());
    // Fallback: publish in the scan's frame without TF transform
    projector.projectLaser(*msg, cloud);
  }

  point_cloud_publisher_->publish(cloud);
  
}

} // namespace scan_to_point_cloud  
RCLCPP_COMPONENTS_REGISTER_NODE(scan_to_point_cloud::ScanToPointCloud)
