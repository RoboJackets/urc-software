#include "traversability_router.hpp"

#include <algorithm>
#include <cmath>
#include <functional>
#include <limits>
#include <queue>
#include <string>
#include <utility>
#include <vector>

namespace urc_perception
{
namespace
{
constexpr double kInfiniteDistance = std::numeric_limits<double>::infinity();
constexpr std::size_t kNoParent = std::numeric_limits<std::size_t>::max();
} // namespace

std::string validateTraversabilityMap(
  const grid_map::GridMap & map,
  const TraversabilityCriteria & criteria)
{
  if (map.getSize()(0) <= 0 || map.getSize()(1) <= 0 || !(map.getResolution() > 0.0)) {
    return "map has no cells";
  }

  if (map.getFrameId().empty()) {
    return "map has no frame id";
  }

  for (const std::string & layer : {criteria.cost_layer, criteria.validity_layer}) {
    if (!map.exists(layer)) {
      return "map has no layer '" + layer + "'";
    }
  }

  return {};
}

TraversabilityRouter::TraversabilityRouter(
  grid_map::GridMap map,
  const TraversabilityCriteria & criteria)
: map_(std::move(map)), criteria_(criteria)
{
  // Neighbor arithmetic on indices is only spatial once the circular buffer is unwrapped.
  map_.convertToDefaultStartIndex();

  const grid_map::Size size = map_.getSize();
  traversable_cells_.assign(static_cast<std::size_t>(size(0) * size(1)), false);

  for (grid_map::GridMapIterator iterator(map_); !iterator.isPastEnd(); ++iterator) {
    const float validity = map_.at(criteria_.validity_layer, *iterator);
    const float cost = map_.at(criteria_.cost_layer, *iterator);

    // Inflation spreads cost into cells that were never observed, so cost alone can block a cell.
    const bool too_costly = std::isfinite(cost) && cost > criteria_.max_cost;
    const bool observed = std::isfinite(validity) && std::isfinite(cost);
    traversable_cells_[linearIndex(*iterator)] = !too_costly &&
      (observed || criteria_.allow_unknown);
  }
}

std::size_t TraversabilityRouter::linearIndex(const grid_map::Index & index) const
{
  return static_cast<std::size_t>(index(0) * map_.getSize()(1) + index(1));
}

bool TraversabilityRouter::isCellTraversable(const grid_map::Index & index) const
{
  return traversable_cells_[linearIndex(index)];
}

Eigen::Vector2d TraversabilityRouter::toCellCoordinates(const grid_map::Position & position) const
{
  // Index (0, 0) sits at the map's +x/+y corner, and indices grow toward -x and -y.
  const grid_map::Position corner = map_.getPosition() + 0.5 * map_.getLength().matrix();
  return (corner - position) / map_.getResolution();
}

std::optional<grid_map::Index> TraversabilityRouter::cellOf(const grid_map::Position & position) const
{
  const Eigen::Vector2d cell = toCellCoordinates(position);
  const long row = static_cast<long>(std::floor(cell.x()));
  const long col = static_cast<long>(std::floor(cell.y()));
  if (row < 0 || row >= map_.getSize()(0) || col < 0 || col >= map_.getSize()(1)) {
    return std::nullopt;
  }
  return grid_map::Index(static_cast<int>(row), static_cast<int>(col));
}

bool TraversabilityRouter::isCellOrOutsideTraversable(long row, long col) const
{
  if (row < 0 || row >= map_.getSize()(0) || col < 0 || col >= map_.getSize()(1)) {
    return criteria_.allow_unknown;
  }
  return isCellTraversable(grid_map::Index(static_cast<int>(row), static_cast<int>(col)));
}

bool TraversabilityRouter::isTraversable(const grid_map::Position & position) const
{
  const std::optional<grid_map::Index> cell = cellOf(position);
  return cell ? isCellTraversable(*cell) : criteria_.allow_unknown;
}

bool TraversabilityRouter::isSegmentTraversable(
  const grid_map::Position & from,
  const grid_map::Position & to) const
{
  const Eigen::Vector2d start = toCellCoordinates(from);
  const Eigen::Vector2d end = toCellCoordinates(to);
  const Eigen::Vector2d delta = end - start;

  long row = static_cast<long>(std::floor(start.x()));
  long col = static_cast<long>(std::floor(start.y()));
  const long end_row = static_cast<long>(std::floor(end.x()));
  const long end_col = static_cast<long>(std::floor(end.y()));

  const long row_step = delta.x() > 0.0 ? 1 : -1;
  const long col_step = delta.y() > 0.0 ? 1 : -1;
  const double row_crossing_interval =
    delta.x() != 0.0 ? 1.0 / std::abs(delta.x()) : kInfiniteDistance;
  const double col_crossing_interval =
    delta.y() != 0.0 ? 1.0 / std::abs(delta.y()) : kInfiniteDistance;
  double next_row_crossing = delta.x() > 0.0 ?
    (static_cast<double>(row + 1) - start.x()) * row_crossing_interval :
    delta.x() < 0.0 ? (start.x() - static_cast<double>(row)) * row_crossing_interval :
    kInfiniteDistance;
  double next_col_crossing = delta.y() > 0.0 ?
    (static_cast<double>(col + 1) - start.y()) * col_crossing_interval :
    delta.y() < 0.0 ? (start.y() - static_cast<double>(col)) * col_crossing_interval :
    kInfiniteDistance;

  const long max_steps = std::abs(end_row - row) + std::abs(end_col - col);
  for (long taken = 0; ; ++taken) {
    if (!isCellOrOutsideTraversable(row, col)) {
      return false;
    }
    if (row == end_row && col == end_col) {
      return true;
    }
    if (taken >= max_steps) {
      return isCellOrOutsideTraversable(end_row, end_col);
    }

    if (next_row_crossing < next_col_crossing) {
      row += row_step;
      next_row_crossing += row_crossing_interval;
    } else if (next_col_crossing < next_row_crossing) {
      col += col_step;
      next_col_crossing += col_crossing_interval;
    } else {
      if (!isCellOrOutsideTraversable(row + row_step, col) ||
        !isCellOrOutsideTraversable(row, col + col_step))
      {
        return false;
      }
      row += row_step;
      col += col_step;
      next_row_crossing += row_crossing_interval;
      next_col_crossing += col_crossing_interval;
      ++taken;
    }
  }
}

RoutedPath TraversabilityRouter::route(
  const std::vector<grid_map::Position> & waypoints,
  double waypoint_spacing) const
{
  RoutedPath routed;

  std::size_t next = 0;
  while (next < waypoints.size() && !isTraversable(waypoints[next])) {
    ++next;
  }
  routed.skipped_waypoints = next;

  if (next == waypoints.size()) {
    routed.truncated = !waypoints.empty();
    return routed;
  }

  routed.points.push_back({waypoints[next], next});
  std::size_t last = next++;

  while (next < waypoints.size()) {
    if (isTraversable(waypoints[next]) && isSegmentTraversable(waypoints[last], waypoints[next])) {
      routed.points.push_back({waypoints[next], next});
      last = next++;
      continue;
    }

    const std::optional<Reconnection> reconnection =
      reconnect(waypoints, last, next, waypoint_spacing);
    if (!reconnection) {
      routed.skipped_waypoints += waypoints.size() - next;
      routed.truncated = true;
      break;
    }

    for (const grid_map::Position & position : reconnection->detour) {
      routed.points.push_back({position, std::nullopt});
    }
    routed.points.push_back({waypoints[reconnection->target_index], reconnection->target_index});

    routed.skipped_waypoints += reconnection->target_index - next;
    ++routed.detour_count;
    last = reconnection->target_index;
    next = last + 1;
  }

  return routed;
}

std::optional<TraversabilityRouter::Reconnection> TraversabilityRouter::reconnect(
  const std::vector<grid_map::Position> & waypoints,
  std::size_t from_index,
  std::size_t first_candidate,
  double waypoint_spacing) const
{
  const std::optional<grid_map::Index> source = cellOf(waypoints[from_index]);
  if (!source) {
    return std::nullopt;
  }

  const grid_map::Size size = map_.getSize();
  const std::size_t cell_count = traversable_cells_.size();
  std::vector<double> distance(cell_count, kInfiniteDistance);
  std::vector<std::size_t> parent(cell_count, kNoParent);

  using QueueEntry = std::pair<double, std::size_t>;
  std::priority_queue<QueueEntry, std::vector<QueueEntry>, std::greater<QueueEntry>> open;

  const std::size_t source_cell = linearIndex(*source);
  distance[source_cell] = 0.0;
  open.push({0.0, source_cell});

  const double resolution = map_.getResolution();
  while (!open.empty()) {
    const auto [current_distance, current] = open.top();
    open.pop();
    if (current_distance > distance[current]) {
      continue;
    }

    const grid_map::Index index(
      static_cast<int>(current / static_cast<std::size_t>(size(1))),
      static_cast<int>(current % static_cast<std::size_t>(size(1))));

    for (int row_step = -1; row_step <= 1; ++row_step) {
      for (int col_step = -1; col_step <= 1; ++col_step) {
        if (row_step == 0 && col_step == 0) {
          continue;
        }

        const grid_map::Index neighbor(index(0) + row_step, index(1) + col_step);
        if (neighbor(0) < 0 || neighbor(0) >= size(0) || neighbor(1) < 0 ||
          neighbor(1) >= size(1) || !isCellTraversable(neighbor))
        {
          continue;
        }

        const bool diagonal = row_step != 0 && col_step != 0;
        if (diagonal && (!isCellTraversable(grid_map::Index(index(0) + row_step, index(1))) ||
          !isCellTraversable(grid_map::Index(index(0), index(1) + col_step))))
        {
          continue;
        }

        const double candidate_distance =
          current_distance + resolution * (diagonal ? M_SQRT2 : 1.0);
        const std::size_t neighbor_cell = linearIndex(neighbor);
        if (candidate_distance < distance[neighbor_cell]) {
          distance[neighbor_cell] = candidate_distance;
          parent[neighbor_cell] = current;
          open.push({candidate_distance, neighbor_cell});
        }
      }
    }
  }

  for (std::size_t candidate = first_candidate; candidate < waypoints.size(); ++candidate) {
    const std::optional<grid_map::Index> target = cellOf(waypoints[candidate]);
    if (!target || !isCellTraversable(*target)) {
      continue;
    }

    std::size_t cell = linearIndex(*target);
    if (distance[cell] == kInfiniteDistance) {
      continue;
    }

    std::vector<grid_map::Position> cell_centers;
    for (cell = parent[cell]; cell != kNoParent && cell != source_cell; cell = parent[cell]) {
      grid_map::Position center;
      map_.getPosition(
        grid_map::Index(
          static_cast<int>(cell / static_cast<std::size_t>(size(1))),
          static_cast<int>(cell % static_cast<std::size_t>(size(1)))),
        center);
      cell_centers.push_back(center);
    }

    std::vector<grid_map::Position> chain;
    chain.reserve(cell_centers.size() + 2);
    chain.push_back(waypoints[from_index]);
    chain.insert(chain.end(), cell_centers.rbegin(), cell_centers.rend());
    chain.push_back(waypoints[candidate]);

    return Reconnection{candidate, simplifyChain(chain, waypoint_spacing)};
  }

  return std::nullopt;
}

std::vector<grid_map::Position> TraversabilityRouter::simplifyChain(
  const std::vector<grid_map::Position> & chain,
  double spacing) const
{
  std::vector<grid_map::Position> kept;

  std::size_t anchor = 0;
  while (anchor + 1 < chain.size()) {
    std::size_t reach = anchor + 1;
    for (std::size_t candidate = anchor + 2; candidate < chain.size(); ++candidate) {
      if ((chain[candidate] - chain[anchor]).norm() > spacing ||
        !isSegmentTraversable(chain[anchor], chain[candidate]))
      {
        break;
      }
      reach = candidate;
    }

    if (reach + 1 < chain.size()) {
      kept.push_back(chain[reach]);
    }
    anchor = reach;
  }

  return kept;
}

} // namespace urc_perception
