#ifndef SRC_TRAVERSABILITY_LAYER_H
#define SRC_TRAVERSABILITY_LAYER_H

#include "gridmap_layer.hpp"
#include <rclcpp/rclcpp.hpp>
#include <rclcpp/time.hpp>
#include <nav2_costmap_2d/layer.hpp>
#include <nav2_costmap_2d/layered_costmap.hpp>
#include <nav_msgs/msg/occupancy_grid.hpp>
#include <pluginlib/class_list_macros.hpp>
#include <urc_util/probability_utils.hpp>

namespace traversability_layer
{
class TraversabilityLayer : public gridmap_layer::GridmapLayer
{
public:
  explicit TraversabilityLayer();

  // Essentially a constructor
  virtual void onInitialize();

  /**
   * @brief This is called by the LayeredCostmap to poll this plugin as to how
   *        much of the costmap it needs to update. Each layer can increase
   *        the size of this bounds.
   *
   * For more details, see "Layered Costmaps for Context-Sensitive Navigation",
   * by Lu et. Al, IROS 2014.
   */
  virtual void updateCosts(nav2_costmap_2d::Costmap2D& master_grid, int min_i, int min_j, int max_i, int max_j);

  /**
   * @brief Actually update the underlying costmap, only within the bounds
   *        calculated during UpdateBounds().
   */
  virtual void updateBounds(double robot_x, double robot_y, double robot_yaw, double* min_x, double* min_y, double* max_x,
                    double* max_y);

  virtual void reset() {
    return;
  }
  virtual bool isClearable() {
    return false;
  }

private:
  double untraversable_probability;
  double slope_threshold;
  double logodd_increment;
  
  double resolution;
  int length_x;
  int length_y;

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
  
  
  rclcpp::Subscription<grid_map_msgs::msg::GridMap>::SharedPtr slope_sub_;
  rclcpp::Publisher<nav_msgs::msg::OccupancyGrid>::SharedPtr costmap_pub_;

  nav2_costmap_2d::Costmap2D costmap_2d_{};

  void slopeMapCallback(const grid_map_msgs::msg::GridMap& slope_map_msg);

  void matchCostmapDims(const nav2_costmap_2d::Costmap2D& master_grid);

  void transferToCostmap();

  void updateStaticWindow();
  void updateRollingWindow();

  void publishCostmap();
};
}  // namespace traversability_layer

#endif  // SRC_TRAVERSABILITY_LAYER_H