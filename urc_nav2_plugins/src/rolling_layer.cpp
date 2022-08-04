#include "rolling_layer.hpp"

namespace rolling_layer
{
RollingLayer::RollingLayer()
{
}

void RollingLayer::onInitialize()
{
  auto node = node_.lock();
  matchSize();
  topic = node->declare_parameter<std::string>("topic");
  costmap_sub_ = node->create_subscription<nav_msgs::msg::OccupancyGrid>(
    topic, rclcpp::SystemDefaultsQoS(), [this](const nav_msgs::msg::OccupancyGrid &msg) {
      costmapCallback(msg);
  });

  current_ = true;
}

void RollingLayer::updateBounds(double robot_x, double robot_y, double robot_yaw, double *min_x, double *min_y,
                                double *max_x, double *max_y)
{
  updateOrigin(robot_x - getSizeInMetersX() / 2, robot_y - getSizeInMetersY() / 2);
  *min_x = getOriginX();
  *max_x = getOriginX() + getSizeInMetersX();
  *min_y = getOriginY();
  *max_y = getOriginY() + getSizeInMetersY();
}

void RollingLayer::updateCosts(nav2_costmap_2d::Costmap2D &master_grid, int min_i, int min_j, int max_i, int max_j)
{
  uint8_t *master_array = master_grid.getCharMap();
  uint8_t *line_array = getCharMap();
  unsigned int span = master_grid.getSizeInCellsX();

  for (int j = min_j; j < max_j; j++)
  {
    const unsigned int base = j * span;
    for (int i = min_i; i < max_i; i++)
    {
      const unsigned int it = base + i;
      master_array[it] = line_array[it];
    }
  }
}

void RollingLayer::costmapCallback(const nav_msgs::msg::OccupancyGrid &map)
{
  double local_origin_x = getOriginX();
  double local_origin_y = getOriginY();
  double resolution = map.info.resolution;
  double global_origin_x = map.info.origin.position.x;
  double global_origin_y = map.info.origin.position.y;

  size_t global_start_index_x = (local_origin_x - global_origin_x) / resolution + 1;
  size_t global_start_index_y = (local_origin_y - global_origin_y) / resolution + 1;

  unsigned char *charmap = getCharMap();

  for (size_t local_index_y = 0; local_index_y < getSizeInCellsY(); local_index_y++)
  {
    size_t global_index_y = global_start_index_y + local_index_y;
    for (size_t local_index_x = 0; local_index_x < getSizeInCellsX(); local_index_x++)
    {
      size_t global_index_x = global_start_index_x + local_index_x;
      char global_data = map.data[global_index_y * map.info.width + global_index_x];
      if (global_data == -1)
      {
        charmap[local_index_y * getSizeInCellsX() + local_index_x] = nav2_costmap_2d::NO_INFORMATION;
      }
      else if (global_data == 100)
      {
        charmap[local_index_y * getSizeInCellsX() + local_index_x] = nav2_costmap_2d::LETHAL_OBSTACLE;
      }
      else
      {
        charmap[local_index_y * getSizeInCellsX() + local_index_x] = nav2_costmap_2d::FREE_SPACE;
      }
    }
  }
}
}  // namespace rolling_layer

// This is the macro allowing a rolling_layer::RollingLayer class
// to be registered in order to be dynamically loadable of base type nav2_costmap_2d::Layer.
PLUGINLIB_EXPORT_CLASS(rolling_layer::RollingLayer, nav2_costmap_2d::Layer)