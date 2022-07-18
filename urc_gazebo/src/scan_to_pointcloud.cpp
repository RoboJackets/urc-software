#include "scan_to_pointcloud.hpp"

namespace scan_to_pointcloud
{
ScanToPointCloud::ScanToPointCloud(const rclcpp::NodeOptions & options)
: rclcpp::Node("scan_to_pointcloud", options),
  tfBuffer_(this->get_clock()),
  tfListener_(tfBuffer_)
{
  min_dist = declare_parameter<double>("min_dist");
  neighbor_dist = declare_parameter<double>("neighbor_dist");

  _pointcloud_pub = create_publisher<sensor_msgs::msg::PointCloud2>(
    "~/pc2",
    rclcpp::SystemDefaultsQoS());

  _pointcloud_sub = create_subscription<sensor_msgs::msg::LaserScan>(
    "~/scan", rclcpp::SystemDefaultsQoS(), [this](const sensor_msgs::msg::LaserScan msg) {
      scanCallback(msg);
    });
}

void ScanToPointCloud::scanCallback(const sensor_msgs::msg::LaserScan & scanData)
{
  sensor_msgs::msg::LaserScan filteredScan(scanData);

  auto rangeIsValid = [&scanData](float range) {
      return !std::isnan(range) && range > scanData.range_min && range < scanData.range_max;
    };

  for (size_t i = 0; i < scanData.ranges.size(); ++i) {
    double range = scanData.ranges[i];
    if (range > scanData.range_max || range < scanData.range_min) {
      continue;
    }
    // Too close
    if (range < min_dist) {
      range = scanData.range_max + 1;
    }
    // No valid neighbors
    else if ((i == 0 || !rangeIsValid(scanData.ranges[i - 1])) &&
      (i == (scanData.ranges.size() - 1) || !rangeIsValid(scanData.ranges[i + 1])))
    {
      range = scanData.range_max + 1;
    }
    // No close neighbors
    else if ((i == 0 || abs(scanData.ranges[i - 1] - range) > neighbor_dist) &&
      (i == (scanData.ranges.size() - 1) || abs(scanData.ranges[i + 1] - range) > neighbor_dist))
    {
      range = scanData.range_max + 1;
    }
  }

  sensor_msgs::msg::PointCloud2 initial_cloud;
  projection.projectLaser(filteredScan, initial_cloud);
  initial_cloud.header.frame_id = "/lidar";
  sensor_msgs::msg::PointCloud2 transformed_cloud;

  geometry_msgs::msg::TransformStamped transform_stamped;
  try {
    transform_stamped = tfBuffer_.lookupTransform("scan", "lidar", rclcpp::Time(0));
    tf2::doTransform(initial_cloud, transformed_cloud, transform_stamped);
  } catch (tf2::TransformException & ex) {
    RCLCPP_ERROR(this->get_logger(), "Transformation Error:\n%s", ex.what());
    return;
  }

  _pointcloud_pub->publish(transformed_cloud);
}
}  // namespace scan_to_pointcloud

RCLCPP_COMPONENTS_REGISTER_NODE(scan_to_pointcloud::ScanToPointCloud)