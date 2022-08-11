#ifndef POINTCLOUD_TO_GRIDMAP_H
#define POINTCLOUD_TO_GRIDMAP_H

#include <rclcpp/rclcpp.hpp>
#include <rclcpp_components/register_node_macro.hpp>
#include <sensor_msgs/msg/point_cloud2.hpp>
#include <grid_map_ros/grid_map_ros.hpp>
#include <grid_map_msgs/msg/grid_map.hpp>

namespace pointcloud_to_gridmap
{
class PointcloudToGridmap : public rclcpp::Node
{
public:
  explicit PointcloudToGridmap(const rclcpp::NodeOptions & options);

private:

  rclcpp::Subscription<sensor_msgs::msg::PointCloud2 >::SharedPtr pointcloud_sub_;
  rclcpp::Publisher<grid_map_msgs::msg::GridMap>::SharedPtr gridmap_pub_;

  void pointcloudCallback(const sensor_msgs::msg::Pointcloud2::SharedPtr message);
};
}


#endif