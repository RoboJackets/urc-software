#ifndef PATH_PLANNING_H
#define PATH_PLANNING_H

#include <bits/stdc++.h>
#include <urc_msgs/msg/waypoint.hpp>
#include <nav2_msgs/msg/costmap.hpp>
#include <urc_msgs/msg/grid_location.hpp>
#include <math.h>
#include <unistd.h>
#include <queue>
#include <set>

namespace astar {

  class AStar {

  public:
    explicit AStar(const nav2_msgs::msg::Costmap &costmap,
               const geometry_msgs::msg::Pose &pose,
               const urc_msgs::msg::GridLocation &destination,
               int gridSize);

  private:


    struct GridBlock {
      urc_msgs::msg::GridLocation location; // x, y data
      geometry_msgs::msg::Pose pose; // optional
      double g_cost; // Cost from start to this node
      double h_cost; // Heuristic estimate to goal
      double f_cost; // g_cost + h_cost
      GridBlock* parent; // For backtracking the path
    };

    nav2_msgs::msg::Costmap currentCostmap;
    AStar::GridBlock currentLocation;
    AStar::GridBlock destination;

    int gridSize = 1; //meter

    AStar::GridBlock gridLocationToGridBlock(const urc_msgs::msg::GridLocation &gridLocation);

    AStar::GridBlock getGridBlockByPose(const geometry_msgs::msg::Pose &pose);
    
    void calculate();

    double AStar::heuristic(GridBlock &node, GridBlock &goal);

    double AStar::cost(const AStar::GridBlock & from, 
                            const AStar::GridBlock & to);

    std::vector<AStar::GridBlock> AStar::get_neighbors(
                          const AStar::GridBlock & node,
                          const nav2_msgs::msg::Costmap & costmap);

    void AStar::reconstruct_path(const AStar::GridBlock & goal_node, 
                            std::vector<AStar::GridBlock> & path); 
  }
}

#endif
