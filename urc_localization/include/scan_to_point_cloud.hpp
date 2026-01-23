#ifndef SCAN_TO_POINT_CLOUD_HPP
#define SCAN_TO_POINT_CLOUD_HPP

#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/laser_scan.hpp>
#include <sensor_msgs/msg/point_cloud2.hpp>
#include <laser_geometry/laser_geometry.hpp>
#include <tf2_ros/transform_listener.h>
#include <tf2_ros/buffer.h>
#include <memory>

namespace scan_to_point_cloud
{
class ScanToPointCloud : public rclcpp::Node
{
public:
  explicit ScanToPointCloud(const rclcpp::NodeOptions &options);

private:
  void handleScan(const sensor_msgs::msg::LaserScan::SharedPtr msg);

  rclcpp::Subscription<sensor_msgs::msg::LaserScan>::SharedPtr scan_subscription_;
  rclcpp::Publisher<sensor_msgs::msg::PointCloud2>::SharedPtr point_cloud_publisher_;

  std::unique_ptr<tf2_ros::Buffer> tf_buffer_;
  std::shared_ptr<tf2_ros::TransformListener> tf_listener_;
  std::string target_frame_;
};
} // namespace scan_to_point_cloud

#endif // SCAN_TO_POINT_CLOUD_HPP
