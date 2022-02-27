#include "scan_to_pointcloud.h"

namespace scan_to_pointcloud
{
ScanToPointCloud::ScanToPointCloud(const rclcpp::NodeOptions &options)
: rclcpp::Node("scan_to_pointcloud", options)
{
  get_parameter("min_dist", min_dist);
  get_parameter("neighbor_dist", neighbor_dist);
  get_parameter("offset", offset);

  _pointcloud_pub = create_publisher<sensor_msgs::msg::PointCloud2>
  ("~/pc2", 
  rclcpp::SystemDefaultsQoS());

  _pointcloud_sub = create_subscription<sensor_msgs::msg::LaserScan>
  ("~/scan", 
  rclcpp::SystemDefaultsQoS(),
  [this](const sensor_msgs::msg::LaserScan msg){scanCallback(msg);});
}

void ScanToPointCloud::scanCallback(const sensor_msgs::msg::LaserScan &scanData)
{
  sensor_msgs::msg::LaserScan filteredScan(scanData);

  auto rangeIsValid = [&scanData](float range) {
    return !std::isnan(range) && range > scanData.range_min && range < scanData.range_max;
  };

  for (size_t i = 0; i < scanData.ranges.size(); ++i)
  {
    double range = scanData.ranges[i];
    if (range > scanData.range_max || range < scanData.range_min)
      continue;
    // Too close
    if (range < min_dist)
    {
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

  sensor_msgs::msg::PointCloud2 cloud;
  projection.projectLaser(filteredScan, cloud);
  cloud.header.frame_id = "/lidar";

  _pointcloud_pub->publish(cloud);
}
}

/*
int main(int argc, char **argv)
{
  rclcpp::init(argc, argc, "scan_to_pointcloud");
  rclcpp::spin(std::make_shared<scan_to_pointcloud::ScanToPointCloud>());
  rclcpp::shutdown();
  
  return 0;
}
*/

RCLCPP_COMPONENTS_REGISTER_NODE(scan_to_pointcloud::ScanToPointCloud)