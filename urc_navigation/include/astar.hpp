#ifndef PATH_PLANNING_HPP_
#define PATH_PLANNING_HPP_

#include <bits/stdc++.h>
#include <urc_msgs/msg/waypoint.hpp>
#include <nav2_msgs/msg/costmap.hpp>
#include <urc_msgs/msg/grid_location.hpp>
#include <math.h>
#include <unistd.h>
#include <queue>
#include <set>

namespace astar
{

  class AStar
  {

  public:
    explicit AStar(const nav2_msgs::msg::Costmap &costmap,
                   const geometry_msgs::msg::Pose &pose,
                   const urc_msgs::msg::GridLocation &destination,
                   int gridSize);

  private:
    struct GridBlock
    {
      urc_msgs::msg::GridLocation location; // x, y data
      geometry_msgs::msg::Pose pose;        // optional
      double g_cost;                        // Cost from start to this node
      double h_cost;                        // Heuristic estimate to goal
      double f_cost;                        // g_cost + h_cost
      GridBlock *parent;                    // For backtracking the path
    };

    nav2_msgs::msg::Costmap currentCostmap;
    GridBlock currentLocation;
    GridBlock destination;

    int gridSize = 1; // meter

    GridBlock getGridBlockByPose(const geometry_msgs::msg::Pose &pose);

    void calculate();

    double heuristic(GridBlock &node, GridBlock &goal);

    double cost(const GridBlock &from, const GridBlock &to);

    std::vector<GridBlock> get_neighbors(
        const GridBlock &node,
        const nav2_msgs::msg::Costmap &costmap);

    void reconstruct_path(const GridBlock &goal_node, std::vector<GridBlock> &path);
  };
}

#endif
