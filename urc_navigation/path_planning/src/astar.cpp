#include "astar.hpp"

namespace astar
{

AStar::AStar() {}

Coordinate AStar::getCoordinateByPose(const geometry_msgs::msg::Pose & pose)
{
  int x = pose.position.x / costmap_.info.resolution;
  int y = pose.position.y / costmap_.info.resolution;

  return {x, y};
}

void AStar::setMap(const nav_msgs::msg::OccupancyGrid & costmap)
{
  costmap_ = costmap;
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
  if (costmap_.data.empty() || costmap_.info.width == 0 || costmap_.info.height == 0 ||
    costmap_.info.resolution == 0.0)
  {
    throw std::runtime_error("Costmap is invalid");
  }

  AStarNodeQueue open_set;

  start_pose_ = start_pose;
  goal_pose_ = goal_pose;

  setGoalNode(goal_pose);

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
  Coordinate to_coord = getCoordinateByPose(to->getPose());
  int costmap_index = to_coord.y * costmap_.info.width + to_coord.x;


  double cell_cost = 0.0;

  // Check cell cost if index is within the costmap
  if (costmap_index >= 0 && costmap_index < costmap_.data.size()) {
    cell_cost = costmap_.data[costmap_index];
  }

  double distance = std::sqrt(std::pow(to->x - from->x, 2) + std::pow(to->y - from->y, 2));
  return distance * cell_cost;
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

      geometry_msgs::msg::Pose pose;
      pose.position.x = x;
      pose.position.y = y;

      if (x >= 0 && x < costmap_.info.width && y >= 0 && y < costmap_.info.height) {
        Coordinate coord = getCoordinateByPose(pose);
        AStarNode * neighbor = getNodeRef(coord.x, coord.y);
        if (neighbor->status == NodeStatus::None) {
          neighbor->x = x;
          neighbor->y = y;
          neighbor->g_cost = std::numeric_limits<double>::max();
        }
        neighbors.push_back(neighbor);
      }
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
