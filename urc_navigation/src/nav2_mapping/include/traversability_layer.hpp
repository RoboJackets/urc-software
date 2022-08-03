#ifndef SRC_TRAVERSABILITY_LAYER_H
#define SRC_TRAVERSABILITY_LAYER_H

#include "gridmap_layer/gridmap_layer.hpp"

#include <rclcpp/rclcpp.hpp>
#include <nav2_costmap_2d/layer.hpp>
#include <nav2_costmap_2d/layered_costmap.hpp>
#include <pluginlib/class_list_macros.hpp>
#include <grid_map_ros/grid_map_ros.hpp>
#include <grid_map_ros/GridMapRosConverter.hpp>
#include <urc_util/probability_utils.hpp>

namespace traversability_layer
{
class TraversabilityLayer : public gridmap_layer::GridmapLayer
{
public:
  explicit TraversabilityLayer();

  virtual void onInitialize();
  virtual void updateCosts(nav2_costmap_2d::Costmap2D& master_grid, int min_i, int min_j, int max_i, int max_j) override;
  virtual void updateBounds(double robot_x, double robot_y, double robot_yaw, double* min_x, double* min_y, double* max_x,
                    double* max_y);

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

  nav2_costmap_2d::Costmap2D costmap_2d_{};

  void slopeMapCallback(const grid_map_msgs::GridMap& slope_map_msg);

  void matchCostmapDims(const nav2_costmap_2d::Costmap2D& master_grid);

  void transferToCostmap();

  void updateStaticWindow();
  void updateRollingWindow();

  void publishCostmap();
};
}  // namespace traversability_layer

#endif  // SRC_TRAVERSABILITY_LAYER_H