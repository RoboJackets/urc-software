#ifndef PATH_PLANNING_HPP_
#define PATH_PLANNING_HPP_

#include <bits/stdc++.h>
#include <urc_msgs/msg/waypoint.hpp>
#include <urc_msgs/msg/grid_location.hpp>
#include <geometry_msgs/msg/pose.hpp>
#include <nav_msgs/msg/occupancy_grid.hpp>
#include <math.h>
#include <unistd.h>
#include <queue>
#include <set>

namespace astar
{
enum class NodeStatus : uint8_t
{
  None,
  Open,
  Visited
};

struct Coordinate
{
  int x;
  int y;
};

struct AStarNode
{
  NodeStatus status = NodeStatus::None;
  double x;
  double y;
  double g_cost;
  double h_cost;
  AStarNode * parent = nullptr;

  double fCost() const {return g_cost + h_cost;}

  geometry_msgs::msg::Pose getPose() const
  {
    geometry_msgs::msg::Pose pose;
    pose.position.x = x;
    pose.position.y = y;
    return pose;
  }
};

struct AStarNodeComparator
{
  bool operator()(const AStarNode * a, const AStarNode * b) const
  {
    return a->fCost() > b->fCost();
  }
};

class AStar
{

public:
  explicit AStar();

  void createPlan(
    const geometry_msgs::msg::Pose & start_pose,
    const geometry_msgs::msg::Pose & goal_pose);

  void setMap(const nav_msgs::msg::OccupancyGrid & costmap);

  const std::vector<AStarNode> getPath() const {return path_;}

  /**
   * @brief Get the index of the map array from the x and y coordinates using the Cantor pairing function.
   */
  int getMapIndex(int x, int y) const
  {
    return ((x + y) * (x + y + 1)) / 2 + y;
  }

private:
  AStarNode * getNodeRef(int x, int y)
  {
    return &(closed_set_.emplace(getMapIndex(x, y), AStarNode()).first->second);
  }

  typedef std::priority_queue<AStarNode *, std::vector<AStarNode *>,
      AStarNodeComparator> AStarNodeQueue;

  Coordinate getCoordinateByPose(const geometry_msgs::msg::Pose & pose);

  double estimateCostToGoal(const geometry_msgs::msg::Pose & pose);

  double cost(const AStarNode * from, const AStarNode * to);

  std::vector<AStarNode *> getNeighbors(const AStarNode * node);

  void reconstructPath(const AStarNode * goal_node);

  void setGoalNode(const geometry_msgs::msg::Pose & goal_pose);

  nav_msgs::msg::OccupancyGrid costmap_;
  geometry_msgs::msg::Pose start_pose_;
  geometry_msgs::msg::Pose goal_pose_;
  AStarNode goal_node_;

  std::vector<AStarNode> path_;
  std::unordered_map<int, AStarNode> closed_set_;
  const double EPSILON = 1e-6;
};
}

#endif
