#ifndef OCTOMAP_TO_GRIDMAP_H
#define OCTOMAP_TO_GRIDMAP_H

#include <rclcpp/rclcpp.hpp>
#include <rclcpp_components/register_node_macro.hpp>
#include <sensor_msgs/msg/point_cloud2.hpp>
#include <grid_map_ros/grid_map_ros.hpp>

#include <grid_map_msgs/msg/grid_map.hpp>
#include <octomap_msgs/msg/octomap.hpp>

namespace octomap_to_gridmap
{
class OctomapToGridmap : public rclcpp::Node
{
public:
  explicit OctomapToGridmap(const rclcpp::NodeOptions & options);

private:

  rclcpp::Subscription<octomap_msgs::msg::Octomap>::SharedPtr octomap_sub_;
  rclcpp::Publisher<grid_map_msgs::msg::GridMap>::SharedPtr gridmap_pub_;

  void octomapCallback(const octomap_msgs::msg::Octomap::SharedPtr message);
};
}


#endif