#include "astar.hpp"

namespace astar
{

  AStar::AStar(const nav2_msgs::msg::Costmap &costmap,
               const geometry_msgs::msg::Pose &initialPose,
               const geometry_msgs::msg::Pose &destinationPose,
               int gridSize)
  {

    this->currentCostmap = costmap;
    this->currentLocation = this->getGridBlockByPose(initialPose);
    this->destination = this->getGridBlockByPose(destinationPose);
    this->gridSize = gridSize;
  }

  AStar::GridBlock AStar::getGridBlockByPose(const geometry_msgs::msg::Pose &pose)
  {
    AStar::GridBlock gridBlock;
    gridBlock.location.x = (int)pose.position.x / this->gridSize;
    gridBlock.location.y = (int)pose.position.y / this->gridSize;
    gridBlock.pose = pose;
    return gridBlock;
  }

  void AStar::calculate()
  {

    std::set<AStar::GridBlock> visited_set;
    std::vector<AStar::GridBlock> waypoint_list;
    GridBlockQueue open_set;

    AStar::GridBlock start_node = this->currentLocation;
    start_node.g_cost = 0.0;
    start_node.h_cost = heuristic(start_node, this->destination);
    start_node.f_cost = start_node.g_cost + start_node.h_cost;
    start_node.parent = nullptr;
    open_set.push(start_node);

    while (!open_set.empty())
    {
      AStar::GridBlock current_node = open_set.top();
      open_set.pop();

      if (current_node.location.x == this->destination.location.x && current_node.location.y == this->destination.location.y)
      {
        reconstruct_path(current_node, waypoint_list);
        break;
      }

      visited_set.insert(current_node);

      std::vector<AStar::GridBlock> neighbors = get_neighbors(current_node, this->currentCostmap);
      for (auto &neighbor : neighbors)
      {
        if (visited_set.find(neighbor) != visited_set.end())
        {
          continue;
        }

        double tentative_g_cost = current_node.g_cost + cost(current_node, neighbor);
        if (tentative_g_cost < neighbor.g_cost)
        {
          neighbor.parent = &current_node;
          neighbor.g_cost = tentative_g_cost;
          neighbor.h_cost = heuristic(neighbor, this->destination);
          neighbor.f_cost = neighbor.g_cost + neighbor.h_cost;
          open_set.push(neighbor);
        }
      }
    }
  }

  double AStar::heuristic(GridBlock &node, GridBlock &goal)
  {
    return std::sqrt(std::pow(goal.location.x - node.location.x, 2) + std::pow(goal.location.y - node.location.y, 2));
  }

  double AStar::cost(const AStar::GridBlock &from, const AStar::GridBlock &to)
  {

    int costmap_index = to.location.y * currentCostmap.metadata.size_x + to.location.x;
    double cell_cost = currentCostmap.data[costmap_index];

    double distance = std::sqrt(std::pow(to.location.x - from.location.x, 2) + std::pow(to.location.y - from.location.y, 2));
    return cell_cost * distance;
  }

  std::vector<AStar::GridBlock> AStar::get_neighbors(
      const AStar::GridBlock &node,
      const nav2_msgs::msg::Costmap &costmap)
  {

    std::vector<AStar::GridBlock> neighbors;

    for (int i = -1; i <= 1; i++)
    {
      for (int j = -1; j <= 1; j++)
      {
        if (i == 0 && j == 0)
        {
          continue;
        }
        int x = node.location.x + i;
        int y = node.location.y + j;
        if (x >= 0 && x < costmap.metadata.size_x && y >= 0 && y < costmap.metadata.size_y)
        {
          AStar::GridBlock neighbor;
          neighbor.location.x = x;
          neighbor.location.y = y;
          neighbors.push_back(neighbor);
        }
      }
    }
  }

  void AStar::reconstruct_path(const AStar::GridBlock &goal_node, std::vector<AStar::GridBlock> &path)
  {
    AStar::GridBlock current_node = goal_node;
    while (current_node.parent != nullptr)
    {
      path.push_back(current_node);
      current_node = *current_node.parent;
    }
  }
}
