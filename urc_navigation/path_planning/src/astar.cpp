#include "astar.hpp"

namespace astar
{

AStar::AStar() {}

Coordinate AStar::getCoordinateByPose(const geometry_msgs::msg::Pose & pose)
{
  int map_x, map_y;
  if (!worldToGrid(pose.position.x, pose.position.y, map_x, map_y)) {
    throw std::runtime_error("Pose is outside costmap bounds");
  }

  return {map_x, map_y};
}

void AStar::setMap(const grid_map_msgs::msg::GridMap & costmap)
{
  costmap_ = costmap;
  grid_map_utils_.setMap(costmap);
}

void AStar::setCostmapLayer(const std::string & layer)
{
  costmap_layer_ = layer;
  grid_map_utils_.setLayer(layer);
}

int AStar::getLayerIndex() const
{
  return grid_map_utils_.getLayerIndex();
}

bool AStar::getMapDimensions(int & width, int & height) const
{
  return grid_map_utils_.getMapDimensions(width, height);
}

bool AStar::worldToGrid(double x, double y, int & map_x, int & map_y) const
{
  return grid_map_utils_.worldToGrid(x, y, map_x, map_y);
}

double AStar::getCellCost(double x, double y) const
{
  float cost;
  if (!grid_map_utils_.tryGetCellCost(x, y, cost)) {
    throw std::runtime_error("Unable to get cell cost");
  }

  return cost;
}

bool AStar::clipGoalToCostmapBoundary(
  const geometry_msgs::msg::Pose & start_pose,
  const geometry_msgs::msg::Pose & goal_pose,
  geometry_msgs::msg::Pose & clipped_goal) const
{
  double resolution = costmap_.info.resolution;
  if (resolution <= 0.0) {
    return false;
  }

  double dx = goal_pose.position.x - start_pose.position.x;
  double dy = goal_pose.position.y - start_pose.position.y;
  double distance = std::sqrt((dx * dx) + (dy * dy));

  clipped_goal = start_pose;
  clipped_goal.orientation = goal_pose.orientation;
  if (distance <= 0.0) {
    return true;
  }

  for (double traveled = resolution; traveled <= distance; traveled += resolution) {
    double t = std::min(1.0, traveled / distance);
    geometry_msgs::msg::Pose candidate = start_pose;
    candidate.position.x = start_pose.position.x + (dx * t);
    candidate.position.y = start_pose.position.y + (dy * t);
    candidate.orientation = goal_pose.orientation;

    int map_x, map_y;
    if (!worldToGrid(candidate.position.x, candidate.position.y, map_x, map_y)) {
      break;
    }

    clipped_goal = candidate;
  }

  return true;
}

void AStar::appendStraightLineSegment(
  const geometry_msgs::msg::Pose & from_pose,
  const geometry_msgs::msg::Pose & to_pose)
{
  double resolution = costmap_.info.resolution;
  if (resolution <= 0.0) {
    return;
  }

  double dx = to_pose.position.x - from_pose.position.x;
  double dy = to_pose.position.y - from_pose.position.y;
  double distance = std::sqrt((dx * dx) + (dy * dy));
  if (distance <= 0.0) {
    return;
  }

  int steps = std::max(1, static_cast<int>(std::ceil(distance / resolution)));
  for (int step = 1; step <= steps; ++step) {
    double t = static_cast<double>(step) / static_cast<double>(steps);
    AStarNode node;
    node.x = from_pose.position.x + (dx * t);
    node.y = from_pose.position.y + (dy * t);
    path_.push_back(node);
  }
}

void AStar::setCostmapLayer(const std::string & layer)
{
  costmap_layer_ = layer;
}

int AStar::getLayerIndex() const
{
  auto it = std::find(costmap_.layers.begin(), costmap_.layers.end(), costmap_layer_);
  if (it == costmap_.layers.end()) {
    return -1;
  }
  return static_cast<int>(std::distance(costmap_.layers.begin(), it));
}

bool AStar::getMapDimensions(int & width, int & height) const
{
  int idx = getLayerIndex();
  if (idx < 0) {
    return false;
  }
  if (costmap_.data.empty() || idx >= static_cast<int>(costmap_.data.size())) {
    return false;
  }

  if (costmap_.data[idx].layout.dim.size() < 2) {
    return false;
  }

  height = costmap_.data[idx].layout.dim[0].size;
  width = costmap_.data[idx].layout.dim[1].size;
  return true;
}

bool AStar::worldToGrid(double x, double y, int & map_x, int & map_y) const
{
  int width, height;
  if (!getMapDimensions(width, height)) {
    return false;
  }

  double resolution = costmap_.info.resolution;
  if (resolution <= 0.0) {
    return false;
  }

  double origin_x = costmap_.info.pose.position.x;
  double origin_y = costmap_.info.pose.position.y;
  double rel_x = x - origin_x;
  double rel_y = y - origin_y;

  map_x = static_cast<int>(rel_x / resolution + width / 2.0);
  map_y = static_cast<int>(rel_y / resolution + height / 2.0);

  if (map_x < 0 || map_x >= width || map_y < 0 || map_y >= height) {
    return false;
  }
  return true;
}

double AStar::getCellCost(double x, double y) const
{
  int idx = getLayerIndex();
  if (idx < 0) {
    throw std::runtime_error("Costmap layer not found");
  }
  if (costmap_.data.empty() || idx >= static_cast<int>(costmap_.data.size())) {
    throw std::runtime_error("Costmap data is invalid");
  }

  int width, height;
  if (!getMapDimensions(width, height)) {
    throw std::runtime_error("Costmap dimensions are invalid");
  }

  int map_x, map_y;
  if (!worldToGrid(x, y, map_x, map_y)) {
    throw std::runtime_error("Point is outside costmap bounds");
  }

  size_t index = static_cast<size_t>(map_y * width + map_x);
  if (index >= costmap_.data[idx].data.size()) {
    throw std::runtime_error("Costmap index is out of range");
  }

  return costmap_.data[idx].data[index];
}

bool AStar::clipGoalToCostmapBoundary(
  const geometry_msgs::msg::Pose & start_pose,
  const geometry_msgs::msg::Pose & goal_pose,
  geometry_msgs::msg::Pose & clipped_goal) const
{
  double resolution = costmap_.info.resolution;
  if (resolution <= 0.0) {
    return false;
  }

  double dx = goal_pose.position.x - start_pose.position.x;
  double dy = goal_pose.position.y - start_pose.position.y;
  double distance = std::sqrt((dx * dx) + (dy * dy));

  clipped_goal = start_pose;
  clipped_goal.orientation = goal_pose.orientation;
  if (distance <= 0.0) {
    return true;
  }

  for (double traveled = resolution; traveled <= distance; traveled += resolution) {
    double t = std::min(1.0, traveled / distance);
    geometry_msgs::msg::Pose candidate = start_pose;
    candidate.position.x = start_pose.position.x + (dx * t);
    candidate.position.y = start_pose.position.y + (dy * t);
    candidate.orientation = goal_pose.orientation;

    int map_x, map_y;
    if (!worldToGrid(candidate.position.x, candidate.position.y, map_x, map_y)) {
      break;
    }

    clipped_goal = candidate;
  }

  return true;
}

void AStar::appendStraightLineSegment(
  const geometry_msgs::msg::Pose & from_pose,
  const geometry_msgs::msg::Pose & to_pose)
{
  double resolution = costmap_.info.resolution;
  if (resolution <= 0.0) {
    return;
  }

  double dx = to_pose.position.x - from_pose.position.x;
  double dy = to_pose.position.y - from_pose.position.y;
  double distance = std::sqrt((dx * dx) + (dy * dy));
  if (distance <= 0.0) {
    return;
  }

  int steps = std::max(1, static_cast<int>(std::ceil(distance / resolution)));
  for (int step = 1; step <= steps; ++step) {
    double t = static_cast<double>(step) / static_cast<double>(steps);
    AStarNode node;
    node.x = from_pose.position.x + (dx * t);
    node.y = from_pose.position.y + (dy * t);
    path_.push_back(node);
  }
}

void AStar::setGoalNode(const geometry_msgs::msg::Pose & goal_pose)
{
  goal_node_.x = goal_pose.position.x;
  goal_node_.y = goal_pose.position.y;
}

void AStar::createPlan(
  const geometry_msgs::msg::Pose & start_pose,
  const geometry_msgs::msg::Pose & goal_pose)
{
  int width, height;
  if (costmap_.info.resolution <= 0.0 || getLayerIndex() < 0 || !getMapDimensions(width, height)) {
    throw std::runtime_error("Costmap is invalid");
  }

  int start_x, start_y;
  int goal_x, goal_y;
  if (!worldToGrid(start_pose.position.x, start_pose.position.y, start_x, start_y)) {
    throw std::runtime_error("Start is outside costmap bounds");
  }

  const geometry_msgs::msg::Pose requested_goal = goal_pose;
  geometry_msgs::msg::Pose planning_goal = goal_pose;
  bool goal_inside_costmap = worldToGrid(goal_pose.position.x, goal_pose.position.y, goal_x, goal_y);
  if (!goal_inside_costmap &&
    !clipGoalToCostmapBoundary(start_pose, goal_pose, planning_goal))
  {
    throw std::runtime_error("Unable to project goal onto costmap boundary");
  }

  closed_set_.clear();
  path_.clear();

  start_pose_ = start_pose;
  goal_pose_ = planning_goal;

  setGoalNode(planning_goal);

  AStarNodeQueue open_set;

  Coordinate start_coord = getCoordinateByPose(start_pose);
  AStarNode * start_node = getNodeRef(start_coord.x, start_coord.y);
  start_node->x = start_pose.position.x;
  start_node->y = start_pose.position.y;
  start_node->g_cost = 0.0;
  start_node->h_cost = estimateCostToGoal(start_pose);
  open_set.push(start_node);

  while (!open_set.empty()) {
    AStarNode * current_node = open_set.top();
    open_set.pop();
    current_node->status = NodeStatus::Visited;

    if (std::fabs(current_node->x - goal_node_.x) < EPSILON &&
      std::fabs(current_node->y - goal_node_.y) < EPSILON)
    {
      reconstructPath(current_node);
      if (!goal_inside_costmap) {
        appendStraightLineSegment(planning_goal, requested_goal);
      }
      return;
    }

    std::vector<AStarNode *> neighbors = getNeighbors(current_node);

    for (auto neighbor : neighbors) {
      if (neighbor->status == NodeStatus::Visited) {
        continue;
      }

      double tentative_g_cost = current_node->g_cost + cost(current_node, neighbor);
      if (tentative_g_cost < neighbor->g_cost) {
        neighbor->status = NodeStatus::Open;
        neighbor->parent = current_node;
        neighbor->g_cost = tentative_g_cost;
        neighbor->h_cost = estimateCostToGoal(neighbor->getPose());

        open_set.push(neighbor);
      }
    }
  }

  throw std::runtime_error("No path found");
}

double AStar::estimateCostToGoal(const geometry_msgs::msg::Pose & pose)
{
  return std::sqrt(
    std::pow(
      goal_pose_.position.x - pose.position.x,
      2) +
    std::pow(goal_pose_.position.y - pose.position.y, 2));
}

double AStar::cost(const AStarNode * from, const AStarNode * to)
{
  double cell_cost = getCellCost(to->x, to->y);
  double distance = std::sqrt(std::pow(to->x - from->x, 2) + std::pow(to->y - from->y, 2));
  return distance * (cell_cost + 1.0);
}

std::vector<AStarNode *> AStar::getNeighbors(const AStarNode * node)
{
  std::vector<AStarNode *> neighbors;

  for (int i = -1; i <= 1; i++) {
    for (int j = -1; j <= 1; j++) {
      if (i == 0 && j == 0) {
        continue;
      }

      double x = node->x + (i * costmap_.info.resolution);
      double y = node->y + (j * costmap_.info.resolution);

      int map_x, map_y;
      if (!worldToGrid(x, y, map_x, map_y)) {
        continue;
      }

      AStarNode * neighbor = getNodeRef(map_x, map_y);
      if (neighbor->status == NodeStatus::None) {
        neighbor->x = x;
        neighbor->y = y;
        neighbor->g_cost = std::numeric_limits<double>::max();
      }
      neighbors.push_back(neighbor);
    }
  }

  return neighbors;
}

void AStar::reconstructPath(const AStarNode * goal_node)
{
  path_.clear();
  const AStarNode * current_node = goal_node;

  while (current_node != nullptr) {
    path_.push_back(*current_node);
    current_node = current_node->parent;
  }

  std::reverse(path_.begin(), path_.end());
}
} // namespace astar
