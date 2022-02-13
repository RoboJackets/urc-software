#include "../include/scan_to_pointcloud.h"

ScanToPointCloud::ScanToPointCloud(const rclcpp::NodeOptions &options)
: rclcpp::Node("scan_to_pointcloud", options)
{
  get_parameter("min_dist", min_dist);
  get_parameter("neighbor_dist", neighbor_dist);
  get_parameter("offset", offset);

  _pointcloud_pub = create_publisher<pcl::PointCloud<pcl::PointXYZ>>
  ("/pc2", rclcpp::SystemDefaultsQoS());

  _pointcloud_sub = create_subscription<sensor_msgs::LaserScan::ConstPtr>
  ("/scan", rclcpp::SystemDefaultsQoS(), std::bind(&ScanToPointCloud::scanCallback, this, std::placeholders::_1));
  
}

void ScanToPointCloud::scanCallback(const sensor_msgs::LaserScan::ConstPtr &msg)
{
  sensor_msgs::LaserScan scanData = *msg;

  auto rangeIsValid = [&scanData](float range) {
    return !std::isnan(range) && range > scanData.range_min && range < scanData.range_max;
  };

  for (size_t i = 0; i < scanData.ranges.size(); ++i)
  {
    float &range = scanData.ranges[i];
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
  sensor_msgs::PointCloud2 cloud;
  projection.projectLaser(scanData, cloud);
  cloud.header.frame_id = "/lidar";

  pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_for_pub(new pcl::PointCloud<pcl::PointXYZ>());

  fromROSMsg(cloud, *cloud_for_pub); //change
  tf2::Quaternion quaternion_mag;
  quaternion_mag.setRPY(0, 0, offset);

  tf2::Transform trans;
  trans.setRotation(quaternion_mag);
  pcl_ros::transformPointCloud(*cloud_for_pub, *cloud_for_pub, trans); //see if changes needed
  _pointcloud_pub.publish(*cloud_for_pub);
}

int main(int argc, char **argv)
{
  rclcpp::init(argc, argc, "scan_to_pointcloud");
  rclcpp::spin(std::make_shared<scan_to_pointcloud::ScanToPointCloud>());
  rclcpp::shutdown();
  
  return 0;
}

RCLCPP_COMPONENTS_REGISTER_NODE(scan_to_pointcloud::ScanToPointCloud)