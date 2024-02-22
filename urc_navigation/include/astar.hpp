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

  class AStar
  {

  public:
    explicit AStar(const nav_msgs::msg::OccupancyGrid &costmap,
                   const geometry_msgs::msg::Pose &initialPose,
                   const geometry_msgs::msg::Pose &destinationPose,
                   int gridSize);

    struct GridBlock
    {
      urc_msgs::msg::GridLocation location; // x, y data
      geometry_msgs::msg::Pose pose;        // optional
      double g_cost;                        // Cost from start to this node
      double h_cost;                        // Heuristic estimate to goal
      double f_cost;                        // g_cost + h_cost
      GridBlock *parent;                    // For backtracking the path

      bool operator<(const GridBlock &other) const
      {
        return location.x < other.location.x;
      }
    };

    std::vector<AStar::GridBlock> calculate();

  private:
    struct GridBlockComparator
    {
      bool operator()(const GridBlock &a, const GridBlock &b) const
      {
        return a.f_cost > b.f_cost;
      }
    };

    typedef std::priority_queue<GridBlock, std::vector<GridBlock>, GridBlockComparator> GridBlockQueue;

    nav_msgs::msg::OccupancyGrid currentCostmap;
    GridBlock currentLocation;
    GridBlock destination;

    int gridSize = 1; // meter

    GridBlock getGridBlockByPose(const geometry_msgs::msg::Pose &pose);

    double heuristic(GridBlock &node, GridBlock &goal);

    double cost(const GridBlock &from, const GridBlock &to);

    std::vector<GridBlock> get_neighbors(
        const GridBlock &node,
        const nav_msgs::msg::OccupancyGrid &costmap);

    void reconstruct_path(const GridBlock &goal_node, std::vector<GridBlock> &path);
  };
}

#endif
