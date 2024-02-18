#ifndef PATH_PLANNING_H
#define PATH_PLANNING_H

#include <rclcpp/rclcpp.hpp>
#include <rclcpp_components/register_node_macro.hpp>
#include <bits/stdc++.h>
#include <urc_msgs/msg/waypoint.hpp>
#include <nav2_msgs/msg/costmap.hpp>
#include <urc_msgs/msg/grid_location.hpp>
#include <math.h>
#include <rclcpp/qos.hpp>
#include <unistd.h>
#include <queue>
#include <set>

namespace path_planning
{

class PathPlanning : public rclcpp::Node
{
public:
  explicit PathPlanning(const rclcpp::NodeOptions & options);

private:
  rclcpp::Publisher<std::vector<urc_msgs::msg::GridLocation>>::SharedPtr path_publisher;  
  rclcpp::Subscription<nav2_msgs::msg::Costmap>::SharedPtr costmap_subscriber;
  rclcpp::Subscription<geometry_msgs::msg::Pose>::SharedPtr grid_pose_subscriber;
  rclcpp::Subscription<urc_msgs::msg::GridLocation>::SharedPtr grid_waypoint_subscriber;

  nav2_msgs::msg::Costmap currentCostmap;
  geometry_msgs::msg::Pose currentPose;
  urc_msgs::msg::GridLocation waypoint;


  void CostmapCallback(
    const nav2_msgs::msg::Costmap & msg
  );
  void GridPositionCallback(
    const geometry_msgs::msg::Pose & msg
  );
  void WaypointCallback(
    const urc_msgs::msg::GridLocation & msg
  );

  struct GridBlock {
    urc_msgs::msg::GridLocation location;
    double g_cost; // Cost from start to this node
    double h_cost; // Heuristic estimate to goal
    double f_cost; // g_cost + h_cost
    GridBlock* parent; // For backtracking the path
  };
  
  void AStar();

  double PathPlanning::heuristic(int x1, int y1, int x2, int y2);
  double PathPlanning::cost(const PathPlanning::GridBlock & from, 
                          const PathPlanning::GridBlock & to);
  std::vector<urc_msgs::msg::GridLocation> PathPlanning::get_neighbors(
                         const PathPlanning::GridBlock & node,
                         const nav2_msgs::msg::Costmap & costmap);
  void PathPlanning::reconstruct_path(const Node & goal_node, 
                          std::vector<urc_msgs::msg::GridLocation> & path); 
}

#endif
