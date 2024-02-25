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

  struct AStarNode
  {
    bool visited = false;
    double x;
    double y;
    geometry_msgs::msg::Pose pose; // optional
    double g_cost;                 // Cost from start to this node
    double h_cost;                 // Heuristic estimate to goal
    AStarNode *parent = nullptr;   // For backtracking the path

    double fCost() const { return g_cost + h_cost; }
  };

  struct AStarNodeComparator
  {
    bool operator()(const AStarNode &a, const AStarNode &b) const
    {
      return a.fCost() > b.fCost();
    }
  };

  class AStar
  {

  public:
    explicit AStar();

    std::vector<AStarNode> createPlan(const geometry_msgs::msg::Pose &start_pose, const geometry_msgs::msg::Pose &goal_pose);

    void setMap(const nav_msgs::msg::OccupancyGrid &costmap);

  private:
    typedef std::priority_queue<AStarNode, std::vector<AStarNode>, AStarNodeComparator> AStarNodeQueue;

    AStarNode getAStarNodeByPose(const geometry_msgs::msg::Pose &pose);

    double heuristic(AStarNode &node, AStarNode &goal);

    double cost(const AStarNode &from, const AStarNode &to);

    std::vector<AStarNode> getNeighbors(const AStarNode &node);

    void reconstruct_path(const AStarNode &goal_node, std::vector<AStarNode> &path);

    nav_msgs::msg::OccupancyGrid costmap_;
    AStarNode start_node_;
    AStarNode goal_node_;
  };
}

#endif
