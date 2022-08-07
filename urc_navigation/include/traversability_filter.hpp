#ifndef SRC_TRAVERSABILITY_FILTER_H
#define SRC_TRAVERSABILITY_FILTER_H

#include <rclcpp/rclcpp.hpp>
#include <rclcpp_components/register_node_macro.hpp>
#include <filters/filter_chain.hpp>
#include <grid_map_ros/grid_map_ros.hpp>

namespace traversability_filter
{
class TraversabilityFilter : public rclcpp::Node
{
public:
  explicit TraversabilityFilter(const rclcpp::NodeOptions & options);

private:

  rclcpp::Subscription<grid_map_msgs::msg::GridMap>::SharedPtr elevation_map_sub_;
  rclcpp::Publisher<grid_map_msgs::msg::GridMap>::SharedPtr traversability_map_pub_;
  filters::FilterChain<grid_map::GridMap> filter_chain_;

  void elevationMapCallback(const grid_map_msgs::msg::GridMap::SharedPtr message);
};
}

#endif