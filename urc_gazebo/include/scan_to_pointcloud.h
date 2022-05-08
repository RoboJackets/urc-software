#ifndef SCAN_TO_POINTCLOUD_H_
#define SCAN_TO_POINTCLOUD_H_

#include <rclcpp/rclcpp.hpp>
#include <rclcpp/time.hpp>
#include <rclcpp/clock.hpp>
#include <laser_geometry/laser_geometry.hpp>
#include <sensor_msgs/msg/laser_scan.hpp>
#include <sensor_msgs/msg/point_cloud2.hpp>
#include <tf2_ros/transform_listener.h>
#include <tf2_ros/buffer.h>
#include <tf2/LinearMath/Transform.h>
#include <rclcpp_components/register_node_macro.hpp>

namespace scan_to_pointcloud
{
  class ScanToPointCloud: public rclcpp::Node
  {
public:
    explicit ScanToPointCloud(const rclcpp::NodeOptions & options);

private:
    rclcpp::Publisher < sensor_msgs::msg::PointCloud2 > ::SharedPtr _pointcloud_pub;
    rclcpp::Subscription < sensor_msgs::msg::LaserScan > ::SharedPtr _pointcloud_sub;

    laser_geometry::LaserProjection projection;
    double min_dist;
    double neighbor_dist;

    tf2_ros::Buffer tfBuffer_;
    tf2_ros::TransformListener tfListener_;

    void scanCallback(const sensor_msgs::msg::LaserScan & scanData);
  };
}  // namespace scan_to_pointcloud

#endif
