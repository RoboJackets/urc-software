#include "octomap_to_gridmap.hpp"

namespace octomap_to_gridmap
{
OctomapToGridmap::OctomapToGridmap(const rclcpp::NodeOptions & options)
: rclcpp::Node("octomap_to_gridmap", options)
{
  octomap_sub_ = create_subscription<octomap_msgs::msg::Octomap>(
    "~/octomap_full"
    rclcpp::SystemDefaultsQoS(), [this](const octomap_msgs::msg::Octomap message) {
        octomapCallback(message);
    });

  gridmap_pub_ = create_publisher<grid_map_msgs::msg::GridMap>(
    "~/slope/gridmap", rclcpp::QoS(1).transient_local());

}

void OctomapToGridmap::octomapCallback(const octomap_msgs::msg::Octomap::SharedPtr message)
{
  octomap_msgs::msg::Octomap cloud = *message;


  grid_map::GridMap output_map = grid_map::GridMap({"elevation"});
  map_.setBasicLayers({"elevation"});


  octomap::OcTree * octomap = nullptr;
  octomap::AbstractOcTree * tree = octomap_msgs::msgToMap(message->map);

  id_map::Position3 min_bound;
  grid_map::Position3 max_bound;
  octomap->getMetricMin(min_bound(0), min_bound(1), min_bound(2));
  octomap->getMetricMax(max_bound(0), max_bound(1), max_bound(2));
  if (!std::isnan(minX_)) {
    min_bound(0) = minX_;
  }
  if (!std::isnan(maxX_)) {
    max_bound(0) = maxX_;
  }
  if (!std::isnan(minY_)) {
    min_bound(1) = minY_;
  }
  if (!std::isnan(maxY_)) {
    max_bound(1) = maxY_;
  }
  if (!std::isnan(minZ_)) {
    min_bound(2) = minZ_;
  }
  if (!std::isnan(maxZ_)) {
    max_bound(2) = maxZ_;
  }
  bool res = grid_map::GridMapOctomapConverter::fromOctomap(
    *octomap, "elevation", map_, &min_bound,
    &max_bound);
  if (!res) {
    RCLCPP_ERROR(this->get_logger(), "Failed to call convert Octomap.");
    return;
  }
  map_.setFrameId(response->map.header.frame_id);


  auto output_message = grid_map::GridMapRosConverter::toMessage(output_map);
  gridmap_pub_->publish(std::move(output_message));
}
}

RCLCPP_COMPONENTS_REGISTER_NODE(pointcloud_to_gridmap::PointcloudToGridmap)
