#include "traversability_layer.hpp"

namespace traversability_layer
{
TraversabilityLayer::TraversabilityLayer()
    gridmap_layer::GridmapLayer({ "logodds", "probability" })
{
}

void TraversabilityLayer::onInitialize()
{
  auto node = node_.lock();
  GridmapLayer::onInitialize();

  // Initialize parameters
  untraversable_probability = node->declare_parameter<double>("untraversable_probability");
  slope_threshold = node->declare_parameter<double>("slope_threshold");
  logodd_increment = probability_utils::toLogOdds(untraversable_probability);
  
  resolution = node->declare_parameter<double>("resolution");
  length_x = node->declare_parameter<double>("length_x");
  length_y = node->declare_parameter<double>("length_y");

  max_occupancy = node->declare_parameter<double>("max_occupancy");
  min_occupancy = node->declare_parameter<double>("min_occupancy");

  frame_id = node->declare_parameter<std::string>("untraversable_probability");
  costmap_topic = node->declare_parameter<std::string>("untraversable_probability");

  occupied_threshold = node->declare_parameter<double>("untraversable_probability");

  debug.map_topic = node->declare_parameter<std::string>("debug/map_topic");
  debug.enabled = node->declare_parameter<bool>("debug/enabled");
  

  // Initialize gridmap
  map_.setFrameId(frame_id);
  grid_map::Length dimensions{ length_x, length_y };
  map_.setGeometry(dimensions, resolution);
  map_.get("logodds").setZero();


  // Initialize publisher/subscriber
  slope_sub_ = node->create_subscription<grid_map_msgs::GridMap>(
    "/slope/gridmap", rclcpp::SystemDefaultsQoS(), [this](const grid_map_msgs::GridMap &msg) {
      slopeMapCallback(msg);
    });
  costmap_pub_ = node->create_publisher<nav_msgs::OccupancyGrid>(
    costmap_topic,
    rclcpp::SystemDefaultsQoS());



  matchCostmapDims(*layered_costmap_->getCostmap());
}

void TraversabilityLayer::updateCosts(nav2_costmap_2d::Costmap2D &master_grid, int min_i, int min_j, int max_i, int max_j)
{
  matchCostmapDims(master_grid);
  transferToCostmap();
  if (debug.enabled)
  {
    publishCostmap();
  }
  resetDirty();

  uchar *master_array = master_grid.getCharMap();
  uchar *line_array = costmap_2d_.getCharMap();
  unsigned int span = master_grid.getSizeInCellsX();

  for (int j = min_j; j < max_j; ++j)
  {
    unsigned int it = j * span + min_i;
    for (int i = min_i; i < max_i; ++i)
    {
      unsigned char old_cost = master_array[it];
      if (old_cost == costmap_2d::NO_INFORMATION || old_cost < line_array[it]) {
        master_array[it] = line_array[it];
      }
      ++it;
    }
  }
}

void TraversabilityLayer::updateBounds(double robot_x, double robot_y, double robot_yaw, double *min_x, double *min_y,
                                       double *max_x, double *max_y)
{
  GridmapLayer::updateBounds(robot_x, robot_y, robot_yaw, min_x, min_y, max_x, max_y);
  if (rolling_window_)
  {
    costmap_2d_.updateOrigin(robot_x - costmap_2d_.getSizeInMetersX() / 2,
                             robot_y - costmap_2d_.getSizeInMetersY() / 2);
  }
}

void TraversabilityLayer::slopeMapCallback(const grid_map_msgs::GridMap &slope_map_msg)
{
  current_ = true;
  grid_map::GridMap slope_map;
  grid_map::GridMapRosConverter::fromMessage(slope_map_msg, slope_map);

  for (grid_map::GridMapIterator it(slope_map); !it.isPastEnd(); ++it)
  {
    grid_map::Position pos;
    slope_map.getPosition((*it), pos);
    if (map_.isInside(pos))
    {
      float slope = slope_map.get("slope")((*it)[0], (*it)[1]);
      grid_map::Index map_index;
      map_.getIndex(pos, map_index);
      touch(map_index);
      float *logodd = &map_.at("logodds", map_index);
      if (slope > slope_threshold)
      {
        *logodd = std::min(*logodd + logodd_increment, map.max_occupancy);
      }
      else
      {
        *logodd = std::max(*logodd - logodd_increment, map.min_occupancy);
      }
    }
  }
}

void TraversabilityLayer::matchCostmapDims(const nav2_costmap_2d::Costmap2D &master_grid)
{
  unsigned int cells_x = master_grid.getSizeInCellsX();
  unsigned int cells_y = master_grid.getSizeInCellsY();
  double resolution = master_grid.getResolution();
  bool different_dims = costmap_2d_.getSizeInCellsX() != cells_x || costmap_2d_.getSizeInCellsY() != cells_y ||
                        costmap_2d_.getResolution() != resolution;

  double origin_x = master_grid.getOriginX();
  double origin_y = master_grid.getOriginY();

  if (different_dims)
  {
    costmap_2d_.resizeMap(cells_x, cells_y, resolution, origin_x, origin_y);
  }
  costmap_2d_.updateOrigin(origin_x, origin_y);
}

void TraversabilityLayer::transferToCostmap()
{
  if (rolling_window_)
  {
    updateRollingWindow();
  }
  else
  {
    updateStaticWindow();
  }
  publishCostmap();
}

void TraversabilityLayer::publishCostmap()
{
  nav_msgs::OccupancyGrid msg;

  std::unique_lock<costmap_2d::Costmap2D::mutex_t> lock(*(costmap_2d_.getMutex()));

  double resolution = costmap_2d_.getResolution();

  msg.header.frame_id = frame_id;
  msg.header.stamp = rclcpp::Time::now();
  msg.info.resolution = resolution;

  msg.info.width = costmap_2d_.getSizeInCellsX();
  msg.info.height = costmap_2d_.getSizeInCellsY();

  double wx;
  double wy;
  costmap_2d_.mapToWorld(0, 0, wx, wy);
  msg.info.origin.position.x = wx - resolution / 2;
  msg.info.origin.position.y = wy - resolution / 2;
  msg.info.origin.position.z = 0.0;
  msg.info.origin.orientation.w = 1.0;

  msg.data.resize(msg.info.width * msg.info.height);

  unsigned char *data = costmap_2d_.getCharMap();
  for (size_t i = 0; i < msg.data.size(); i++)
  {
    switch (data[i])
    {
      case nav2_costmap_2d::FREE_SPACE:
        msg.data[i] = 0;
        break;
      case nav2_costmap_2d::LETHAL_OBSTACLE:
        msg.data[i] = 100;
        break;
      default:
        msg.data[i] = -1;
        break;
    }
  }

  costmap_pub_->publish(msg);
}

void TraversabilityLayer::updateStaticWindow()
{
  // Static window, so we can only update dirty cells
  size_t num_cells = map_.getSize().prod();

  unsigned char *char_map = costmap_2d_.getCharMap();

  auto optional_it = getDirtyIterator();

  if (!optional_it)
  {
    return;
  }

  for (auto it = *optional_it; !it.isPastEnd(); ++it)
  {
    const auto &log_odds = map_.get("logodds")((*it)[0], (*it)[1]);
    float probability = probability_utils::fromLogOdds(log_odds);
    size_t linear_index = grid_map::getLinearIndexFromIndex(*it, map_.getSize(), false);

    if (probability > occupied_threshold)
    {
      char_map[num_cells - linear_index - 1] = nav2_costmap_2d::LETHAL_OBSTACLE;
    }
    else
    {
      char_map[num_cells - linear_index - 1] = nav2_costmap_2d::FREE_SPACE;
    }
  }
}

void TraversabilityLayer::updateRollingWindow()
{
  const size_t cells_x = costmap_2d_.getSizeInCellsX();
  const size_t cells_y = costmap_2d_.getSizeInCellsY();

  grid_map::Position costmap_br_corner{ costmap_2d_.getOriginX(), costmap_2d_.getOriginY() };
  grid_map::Position costmap_tl_corner =
      costmap_br_corner + grid_map::Position{ costmap_2d_.getSizeInMetersX(), costmap_2d_.getSizeInMetersY() };
  grid_map::Index start_index;
  map_.getIndex(costmap_tl_corner, start_index);

  grid_map::Index submap_buffer_size{ costmap_2d_.getSizeInCellsX(), costmap_2d_.getSizeInCellsY() };

  uchar *char_map = costmap_2d_.getCharMap();

  size_t x_idx = cells_x - 1;
  size_t y_idx = cells_y - 1;

  // This goes top -> down, left -> right
  // but costmap_2d_ indicies go down -> up, left -> right
  for (grid_map::SubmapIterator it{ map_, start_index, submap_buffer_size }; !it.isPastEnd(); ++it)
  {
    const auto &log_odds = map_.get("logodds")((*it)[0], (*it)[1]);
    float probability = probability_utils::fromLogOdds(log_odds);

    const size_t linear_idx = x_idx + y_idx * cells_x;

    if (probability > occupied_threshold)
    {
      char_map[linear_idx] = nav2_costmap_2d::LETHAL_OBSTACLE;
    }
    else
    {
      char_map[linear_idx] = nav2_costmap_2d::FREE_SPACE;
    }

    if (y_idx == 0)
    {
      y_idx = cells_y - 1;
      x_idx--;
    }
    else
    {
      y_idx--;
    }
  }
}
}  // namespace traversability_layer

// This is the macro allowing a traversability_layer::TraversabilityLayer class
// to be registered in order to be dynamically loadable of base type nav2_costmap_2d::Layer.
PLUGINLIB_EXPORT_CLASS(traversability_layer::TraversabilityLayer, nav2_costmap_2d::Layer)