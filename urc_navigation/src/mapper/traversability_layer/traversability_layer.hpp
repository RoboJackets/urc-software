#ifndef SRC_TRAVERSABILITY_LAYER_H
#define SRC_TRAVERSABILITY_LAYER_H

#include <rclcpp/rclcpp.hpp>
#include <costmap_2d/GenericPluginConfig.h>
#include <costmap_2d/layer.h>
#include <costmap_2d/layered_costmap.h>

#include <grid_map_ros/grid_map_ros.hpp>

#include "gridmap_layer.h"
#include "traversability_layer_config.h"

namespace traversability_layer
{
class TraversabilityLayer : public rclcpp::Node, public gridmap_layer::GridmapLayer
{
public:
  TraversabilityLayer();

  void onInitialize() override;
  void updateCosts(costmap_2d::Costmap2D& master_grid, int min_i, int min_j, int max_i, int max_j) override;
  void updateBounds(double robot_x, double robot_y, double robot_yaw, double* min_x, double* min_y, double* max_x,
                    double* max_y) override;

private:
  double untraversable_probability;
  double slope_threshold;
  double logodd_increment;
  
  double resolution;
  double length_x;
  double length_y;

  double max_occupancy;
  double min_occupancy;

  std::string frame_id;
  std::string costmap_topic;

  double occupied_threshold;

  struct
  {
    std::string map_topic;
    bool enabled;
  } debug;
  
  
  rclcpp::Subscriber<grid_map_msgs::GridMap>::SharedPtr slope_sub_;
  rclcpp::Publisher<nav_msgs::OccupancyGrid>::SharedPtr costmap_pub_;

  costmap_2d::Costmap2D costmap_2d_{};

  void slopeMapCallback(const grid_map_msgs::GridMap& slope_map_msg);

  void matchCostmapDims(const costmap_2d::Costmap2D& master_grid);

  void transferToCostmap();

  void updateStaticWindow();
  void updateRollingWindow();

  void publishCostmap();
};
}  // namespace traversability_layer

#endif  // SRC_TRAVERSABILITY_LAYER_H