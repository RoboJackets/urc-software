#ifndef SCAN_TO_POINTCLOUD_H_
#define SCAN_TO_POINTCLOUD_H_

#include <rclcpp/rclcpp.hpp>
#include <laser_geometry/laser_geometry.hpp>
#include <sensor_msgs/msg/laser_scan.hpp>
#include <sensor_msgs/msg/point_cloud2.hpp>
#include <rclcpp_components/register_node_macro.hpp>

namespace scan_to_pointcloud
{
class ScanToPointCloud : public rclcpp::Node
{
public:
  explicit ScanToPointCloud(const rclcpp::NodeOptions &options);

private:
  rclcpp::Publisher<sensor_msgs::msg::PointCloud2>::SharedPtr _pointcloud_pub;
  rclcpp::Subscription<sensor_msgs::msg::LaserScan>::SharedPtr _pointcloud_sub;

  laser_geometry::LaserProjection projection;
  double min_dist;
  double neighbor_dist;
  double offset;

  void scanCallback(const sensor_msgs::msg::LaserScan &scanData);
};
}

#endif