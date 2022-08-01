#ifndef SRC_ROLLING_LAYER_H
#define SRC_ROLLING_LAYER_H

#include <rclcpp/rclcpp.hpp>
#include <nav2_costmap_2d/layer.hpp>
#include <nav2_costmap_2d/layered_costmap.hpp>
#include <nav2_msgs/occupancy_grid.hpp>
#include <map_msgs/OccupancyGridUpdate.h>
#include <pluginlib/class_list_macros.h>

namespace rolling_layer
{
class RollingLayer : public rclcpp::Node, public nav2_costmap_2d::Layer
{
public:
  RollingLayer();
  void onInitialize() override;
  void updateBounds(double robot_x, double robot_y, double robot_yaw, double* min_x, double* min_y, double* max_x,
                    double* max_y) override;
  void updateCosts(costmap_2d::Costmap2D& master_grid, int min_i, int min_j, int max_i, int max_j) override;

private:
  std::string topic;

  void costmapCallback(const nav_msgs::OccupancyGridConstPtr& map);

  rclcpp::Subscriber<nav_msgs::OccupancyGridConstPtr> costmap_sub_;
};
}  // namespace rolling_layer

#endif  // SRC_ROLLING_LAYER_H
