#include "urc_nav_common/grid_map_utils.hpp"

#include <utility>

#include <grid_map_ros/GridMapRosConverter.hpp>

namespace grid_map_utils
{
bool GridMapUtils::setMap(const grid_map_msgs::msg::GridMap & grid_map)
{
  grid_map::GridMap converted;
  if (!grid_map::GridMapRosConverter::fromMessage(grid_map, converted)) {
    grid_map_ = grid_map::GridMap();
    return false;
  }
  grid_map_ = std::move(converted);
  return true;
}

void GridMapUtils::setLayer(const std::string & layer_name)
{
  layer_name_ = layer_name;
}

bool GridMapUtils::hasLayer() const
{
  return grid_map_.exists(layer_name_);
}

double GridMapUtils::resolution() const
{
  return grid_map_.getResolution();
}

bool GridMapUtils::worldToGrid(double x, double y, int & map_x, int & map_y) const
{
  grid_map::Index index;
  if (!grid_map_.getIndex(grid_map::Position(x, y), index)) {
    return false;
  }
  map_x = index(0);
  map_y = index(1);
  return true;
}

bool GridMapUtils::tryGetCellCost(double x, double y, float & cost) const
{
  const grid_map::Position position(x, y);
  if (!hasLayer() || !grid_map_.isInside(position)) {
    return false;
  }
  cost = grid_map_.atPosition(layer_name_, position);
  return true;
}
}  // namespace grid_map_utils
