#include "pointcloud_to_gridmap.hpp"

namespace pointcloud_to_gridmap
{
TraversabilityFilter::TraversabilityFilter(const rclcpp::NodeOptions & options)
: rclcpp::Node("pointcloud_to_gridmap", options)
{
  pointcloud_sub_ = create_subscription<sensor_msgs::msg::PointCloud2>(
    "~/pc2"
    rclcpp::SystemDefaultsQoS(), [this](const sensor_msgs::msg::Pointcloud2 message) {
        pointcloudCallback(message);
    });

  gridmap_pub_ = create_publisher<grid_map_msgs::msg::GridMap>(
    "~/slope/gridmap", rclcpp::QoS(1).transient_local());

}

void PointcloudToGridmap::pointcloudCallback(const sensor_msgs::msg::Pointcloud2::SharedPtr message)
{
  sensor_msgs::msg::Pointcloud2 cloud = *message


  

  auto output_message = grid_map::GridMapRosConverter::toMessage(output_map);
  gridmap_pub_->publish(std::move(output_message));
}
}

RCLCPP_COMPONENTS_REGISTER_NODE(pointcloud_to_gridmap::PointcloudToGridmap)
