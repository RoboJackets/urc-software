#ifndef TRAVERSABILITY_ROUTER_HPP_
#define TRAVERSABILITY_ROUTER_HPP_

#include <grid_map_core/grid_map_core.hpp>

#include <cstddef>
#include <optional>
#include <string>
#include <vector>

namespace urc_perception
{

/// How cells of the traversability grid map are classified.
struct TraversabilityCriteria
{
  /// Layer compared against max_cost. Higher values are less traversable.
  std::string cost_layer;

  /// Layer whose NaN cells mark terrain the sensor has not observed.
  std::string validity_layer;

  /// Cells whose cost exceeds this value are blocked.
  double max_cost;

  /// Whether unobserved cells, including everything outside the map, may be driven through.
  bool allow_unknown;
};

/// Waypoint of a routed path, expressed in the traversability map frame.
struct RoutedPoint
{
  grid_map::Position position;

  /// Index of the input waypoint this point reproduces, or empty for detour points.
  std::optional<std::size_t> source_index;
};

struct RoutedPath
{
  std::vector<RoutedPoint> points;

  /// Input waypoints left out because they were blocked or unreachable.
  std::size_t skipped_waypoints = 0;

  /// Number of detours inserted to reconnect around blocked terrain.
  std::size_t detour_count = 0;

  /// True when the trailing part of the input could not be reached safely.
  bool truncated = false;
};

/// Describes why the map cannot be routed through, or an empty string when it can.
std::string validateTraversabilityMap(
  const grid_map::GridMap & map,
  const TraversabilityCriteria & criteria);

/**
 * @brief Routes an ordered waypoint sequence through a traversability grid map.
 *
 * Waypoints are kept in order whenever they and the straight segment leading to them are
 * traversable. When the sequence runs into blocked terrain, the router finds the first later
 * waypoint reachable from the last safe one over traversable cells and inserts the shortest
 * grid detour to it, so the output stays continuous instead of jumping across obstacles.
 */
class TraversabilityRouter
{
public:
  /// @pre validateTraversabilityMap(map, criteria) returns an empty string.
  TraversabilityRouter(grid_map::GridMap map, const TraversabilityCriteria & criteria);

  bool isTraversable(const grid_map::Position & position) const;

  /// Checks every cell the straight segment touches, including both cells beside a corner it
  /// passes exactly through.
  bool isSegmentTraversable(const grid_map::Position & from, const grid_map::Position & to) const;

  /// @param waypoint_spacing [m] Upper bound on the distance between inserted detour points.
  RoutedPath route(
    const std::vector<grid_map::Position> & waypoints,
    double waypoint_spacing) const;

private:
  struct Reconnection
  {
    std::size_t target_index;
    std::vector<grid_map::Position> detour;
  };

  /// Continuous cell coordinates, where cell (i, j) spans [i, i + 1) x [j, j + 1).
  Eigen::Vector2d toCellCoordinates(const grid_map::Position & position) const;
  std::optional<grid_map::Index> cellOf(const grid_map::Position & position) const;

  std::size_t linearIndex(const grid_map::Index & index) const;
  bool isCellTraversable(const grid_map::Index & index) const;

  /// Like isCellTraversable, but applies the unknown-terrain policy outside the map.
  bool isCellOrOutsideTraversable(long row, long col) const;

  std::optional<Reconnection> reconnect(
    const std::vector<grid_map::Position> & waypoints,
    std::size_t from_index,
    std::size_t first_candidate,
    double waypoint_spacing) const;

  /// Thins a chain of adjacent positions to points no farther apart than spacing.
  std::vector<grid_map::Position> simplifyChain(
    const std::vector<grid_map::Position> & chain,
    double spacing) const;

  grid_map::GridMap map_;
  TraversabilityCriteria criteria_;
  std::vector<bool> traversable_cells_;
};

} // namespace urc_perception

#endif // TRAVERSABILITY_ROUTER_HPP_
