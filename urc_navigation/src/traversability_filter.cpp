#include "traversability_filter.hpp"

namespace traversability_filter
{
TraversabilityFilter::TraversabilityFilter(const rclcpp::NodeOptions & options)
: rclcpp::Node("traversability_filter", options),
  filter_chain_("grid_map::GridMap")
{
  elevation_map_sub_ = create_subscription<grid_map_msgs::msg::GridMap>(
    "~/elevation_mapping/elevation_map_raw",
    rclcpp::SystemDefaultsQoS(), [this](const grid_map_msgs::msg::GridMap::SharedPtr message) {
        elevationMapCallback(message);
    });

  traversability_map_pub_ = create_publisher<grid_map_msgs::msg::GridMap>(
    "~/slope/gridmap", rclcpp::QoS(1).transient_local());

  // setup filter chain
  if (!filter_chain_.configure("/slope_filter/slope_map_filters",
      this->get_node_logging_interface(),
      this->get_node_parameters_interface()))
  {
    RCLCPP_ERROR_STREAM(this->get_logger(), "Could not configure filter chain!");
    rclcpp::shutdown();
    return;
  }
}

void TraversabilityFilter::elevationMapCallback(const grid_map_msgs::msg::GridMap::SharedPtr message)
{
  // Convert message to map
  grid_map::GridMap input_map;
  grid_map::GridMapRosConverter::fromMessage(*message, input_map);

  // Apply filter chain
  grid_map::GridMap output_map;
  if (!filter_chain_.update(input_map, output_map))
  {
    RCLCPP_ERROR_STREAM(this->get_logger(), "Could not update the grid map filter chain!");
    return;
  }

  auto output_message = grid_map::GridMapRosConverter::toMessage(output_map);
  traversability_map_pub_->publish(std::move(output_message));
}
}

RCLCPP_COMPONENTS_REGISTER_NODE(traversability_filter::TraversabilityFilter)
