#include "astar.hpp"

namespace astar
{

  AStar::AStar() {}

  AStarNode AStar::getAStarNodeByPose(const geometry_msgs::msg::Pose &pose)
  {
    AStarNode node;
    node.x = pose.position.x / costmap_.info.resolution;
    node.y = pose.position.y / costmap_.info.resolution;
    node.pose = pose;

    return node;
  }

  void AStar::setMap(const nav_msgs::msg::OccupancyGrid &costmap)
  {
    costmap_ = costmap;
  }

  std::vector<AStarNode> AStar::createPlan(const geometry_msgs::msg::Pose &start_pose, const geometry_msgs::msg::Pose &goal_pose)
  {
    start_node_ = getAStarNodeByPose(start_pose);
    goal_node_ = getAStarNodeByPose(goal_pose);

    std::vector<AStarNode> waypoint_list;
    AStarNodeQueue open_set;

    AStarNode start_node = start_node_;
    start_node.g_cost = 0.0;
    start_node.h_cost = heuristic(start_node, goal_node_);
    open_set.push(start_node);

    while (!open_set.empty())
    {
      AStarNode current_node = open_set.top();
      open_set.pop();
      current_node.visited = true;

      if (current_node.x == goal_node_.x && current_node.y == goal_node_.y)
      {
        reconstruct_path(current_node, waypoint_list);
        return waypoint_list;
      }

      std::vector<AStarNode> neighbors = getNeighbors(current_node);
      for (auto &neighbor : neighbors)
      {
        if (neighbor.visited)
        {
          continue;
        }

        double tentative_g_cost = current_node.g_cost + cost(current_node, neighbor);
        if (tentative_g_cost < neighbor.g_cost)
        {
          neighbor.parent = &current_node;
          neighbor.g_cost = tentative_g_cost;
          neighbor.h_cost = heuristic(neighbor, goal_node_);
          open_set.push(neighbor);
        }
      }
    }

    throw std::runtime_error("No path found");
  }

  double AStar::heuristic(AStarNode &node, AStarNode &goal)
  {
    return std::sqrt(std::pow(goal.x - node.x, 2) + std::pow(goal.y - node.y, 2));
  }

  double AStar::cost(const AStarNode &from, const AStarNode &to)
  {
    int costmap_index = to.y * costmap_.info.width + to.x;
    double cell_cost = costmap_.data[costmap_index];

    double distance = std::sqrt(std::pow(to.x - from.x, 2) + std::pow(to.y - from.y, 2));
    return cell_cost * distance;
  }

  std::vector<AStarNode> AStar::getNeighbors(const AStarNode &node)
  {
    std::vector<AStarNode> neighbors;

    for (int i = -1; i <= 1; i++)
    {
      for (int j = -1; j <= 1; j++)
      {
        if (i == 0 && j == 0)
        {
          continue;
        }
        double x = node.x + (i * costmap_.info.resolution);
        double y = node.y + (j * costmap_.info.resolution);
        if (x >= 0 && x < costmap_.info.width && y >= 0 && y < costmap_.info.height)
        {
          AStarNode neighbor;
          neighbor.x = x;
          neighbor.y = y;
          neighbors.push_back(neighbor);
        }
      }
    }

    return neighbors;
  }

  void AStar::reconstruct_path(const AStarNode &goal_node, std::vector<AStarNode> &path)
  {
    AStarNode current_node = goal_node;
    while (current_node.parent != nullptr)
    {
      path.push_back(current_node);
      current_node = *current_node.parent;
    }
  }
}
