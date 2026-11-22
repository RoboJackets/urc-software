#ifndef URC_NAV_COMMON__GRID_MAP_UTILS_HPP_
#define URC_NAV_COMMON__GRID_MAP_UTILS_HPP_

#include <string>

#include <grid_map_core/GridMap.hpp>
#include <grid_map_msgs/msg/grid_map.hpp>

namespace grid_map_utils
{
// Reads a GridMap message through grid_map itself, so lookups honor its index
// convention (indices grow toward -x and -y) and its circular buffer offset.
class GridMapUtils
{
public:
  // Returns false and keeps no map if the message cannot be converted
  bool setMap(const grid_map_msgs::msg::GridMap & grid_map);
  void setLayer(const std::string & layer_name);

  bool hasLayer() const;
  double resolution() const;

  // Index of the cell containing (x, y). It identifies one cell for as long as
  // the current map is held, but is not a row/column offset from any origin.
  bool worldToGrid(double x, double y, int & map_x, int & map_y) const;

  // NaN cost means the cell has not been observed
  bool tryGetCellCost(double x, double y, float & cost) const;

private:
  grid_map::GridMap grid_map_;
  std::string layer_name_;
};
}  // namespace grid_map_utils

#endif  // URC_NAV_COMMON__GRID_MAP_UTILS_HPP_
