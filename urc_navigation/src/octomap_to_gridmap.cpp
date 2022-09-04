#include "octomap_to_gridmap.hpp"

namespace octomap_to_gridmap
{
  OctomapToGridmap::OctomapToGridmap(const rclcpp::NodeOptions &options)
      : rclcpp::Node("octomap_to_gridmap", options),
        map_(grid_map::GridMap({"elevation"}))
  {
    minX_ = declare_parameter<float>("min_x", NAN);
    maxX_ = declare_parameter<float>("max_x", NAN);
    minY_ = declare_parameter<float>("min_y", NAN);
    maxY_ = declare_parameter<float>("max_y", NAN);
    minZ_ = declare_parameter<float>("min_z", NAN);
    maxZ_ = declare_parameter<float>("max_z", NAN);

    octomap_client_ = create_client<octomap_msgs::srv::GetOctomap>(
        "~/octomap_full");

    gridmap_pub_ = create_publisher<grid_map_msgs::msg::GridMap>(
        "~/slope/gridmap", rclcpp::QoS(1).transient_local());
  }

  void OctomapToGridmap::getGridmap()
  {
    auto request = std::make_shared<octomap_msgs::srv::GetOctomap::Request>();
    auto result_future = octomap_client_->async_send_request(request);
    if (rclcpp::spin_until_future_complete(this->get_node_base_interface(), result_future) !=
        rclcpp::FutureReturnCode::SUCCESS)
    {
      RCLCPP_ERROR_STREAM(this->get_logger(), "Failed to call service: ~/octomap_full");
      return;
    }
    auto response = result_future.get();

    grid_map::GridMap output_map = grid_map::GridMap({"elevation"});
    map_.setBasicLayers({"elevation"});

    octomap::OcTree *octomap = nullptr;
    octomap::AbstractOcTree *tree = octomap_msgs::msgToMap(response->map);
    if (tree)
    {
      octomap = dynamic_cast<octomap::OcTree *>(tree);
    }
    else
    {
      RCLCPP_ERROR(this->get_logger(), "Failed to call convert Octomap.");
      return;
    }

    grid_map::Position3 min_bound;
    grid_map::Position3 max_bound;
    octomap->getMetricMin(min_bound(0), min_bound(1), min_bound(2));
    octomap->getMetricMax(max_bound(0), max_bound(1), max_bound(2));
    if (!std::isnan(minX_))
    {
      min_bound(0) = minX_;
    }
    if (!std::isnan(maxX_))
    {
      max_bound(0) = maxX_;
    }
    if (!std::isnan(minY_))
    {
      min_bound(1) = minY_;
    }
    if (!std::isnan(maxY_))
    {
      max_bound(1) = maxY_;
    }
    if (!std::isnan(minZ_))
    {
      min_bound(2) = minZ_;
    }
    if (!std::isnan(maxZ_))
    {
      max_bound(2) = maxZ_;
    }
    bool res = grid_map::GridMapOctomapConverter::fromOctomap(
        *octomap, "elevation", map_, &min_bound,
        &max_bound);
    if (!res)
    {
      RCLCPP_ERROR(this->get_logger(), "Failed to call convert Octomap.");
      return;
    }
    map_.setFrameId(response->map.header.frame_id);

    auto output_message = grid_map::GridMapRosConverter::toMessage(output_map);
    gridmap_pub_->publish(std::move(output_message));
  }
}

RCLCPP_COMPONENTS_REGISTER_NODE(octomap_to_gridmap::OctomapToGridmap)
