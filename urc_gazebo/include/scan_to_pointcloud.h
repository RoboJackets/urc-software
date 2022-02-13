#ifndef SCAN_TO_POINTCLOUD
#define SCAN_TO_POINTCLOUD

#include <laser_geometry/laser_geometry.h>
#include <parameter_assertions/assertions.h>
#include <pcl/point_types.h>
#include <pcl_ros/point_cloud.h>
#include <pcl_ros/transforms.h>
#include <sensor_msgs/LaserScan.h>

#include <Quaternion.h>
#include <Transform.h>


#include <rclcpp/rclcpp.hpp>
#include <rclcpp_components/register_node_marco.hpp>

namespace scan_to_pointcloud
{
class ScanToPointCloud : public rclcpp::Node
{
public:
  explicit ScanToPointCloud(const rclcpp::NodeOptions &options);

private:
  rclcpp::Publisher<pcl::PointCloud<pcl::PointXYZ>> _pointcloud_pub;
  rclcpp::Subscription<sensor_msgs::LaserScan::ConstPtr> _pointcloud_sub;

  laser_geometry::LaserProjection projection;
  double min_dist;
  double neighbor_dist;
  double offset;

  void scanCallback(const sensor_msgs::LaserScan::ConstPtr &msg);
  void spinnerUpdate();
};
}



#endif