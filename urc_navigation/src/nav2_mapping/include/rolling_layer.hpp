#ifndef SRC_ROLLING_LAYER_H
#define SRC_ROLLING_LAYER_H

#include <rclcpp/rclcpp.hpp>
#include <nav2_costmap_2d/costmap_2d.hpp>
#include <nav2_costmap_2d/costmap_layer.hpp>
#include <nav2_costmap_2d/layer.hpp>
#include <nav2_costmap_2d/layered_costmap.hpp>
#include <nav_msgs/msg/occupancy_grid.hpp>
#include <map_msgs/msg/occupancy_grid_update.hpp>
#include <pluginlib/class_list_macros.hpp>

namespace rolling_layer
{
class RollingLayer : public nav2_costmap_2d::CostmapLayer
{
public:
  explicit RollingLayer();

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
  virtual void updateBounds(double robot_x, double robot_y, double robot_yaw, double* min_x, double* min_y, double* max_x,
                    double* max_y);

  /**
   * @brief Actually update the underlying costmap, only within the bounds
   *        calculated during UpdateBounds().
   */
  virtual void updateCosts(nav2_costmap_2d::Costmap2D & master_grid, int min_i, int min_j, int max_i, int max_j);

  virtual void reset() {
    return;
  }
  virtual bool isClearable() {
    return false;
  }

private:
  std::string topic;

  void costmapCallback(const nav_msgs::msg::OccupancyGrid& map);

  rclcpp::Subscription<nav_msgs::msg::OccupancyGrid>::SharedPtr costmap_sub_;
};
}  // namespace rolling_layer

#endif  // SRC_ROLLING_LAYER_H
