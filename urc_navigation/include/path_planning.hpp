#ifndef PATH_PLANNING_H
#define PATH_PLANNING_H

#include <rclcpp/rclcpp.hpp>
#include <rclcpp_components/register_node_macro.hpp>
#include <bits/stdc++.h>
#include <urc_msgs/msg/waypoint.hpp>
#include <nav2_msgs/msg/costmap.hpp>
#include <math.h>
#include <rclcpp/qos.hpp>
#include <unistd.h>
#include <queue>

namespace path_planning
{

class PathPlanning : public rclcpp::Node
{
public:
  explicit PathPlanning(const rclcpp::NodeOptions & options);

private:
  rclcpp::Publisher<std::vector<urc_msgs::msg::Waypoint>>::SharedPtr path_publisher;  
  rclcpp::Subscription<nav2_msgs::msg::Costmap>::SharedPtr costmap_subscriber;
  rclcpp::Subscription<geometry_msgs::msg::Pose>::SharedPtr grid_pose_subscriber;

  rclcpp::Subscription<urc_msgs::msg::Waypoint>::SharedPtr gps_waypoint_subscriber;
  rclcpp::Subscription<geometry_msgs::msg::Pose>::SharedPtr base_pose_subscriber;

  nav2_msgs::msg::Costmap currentCostmap;
  geometry_msgs::msg::Pose currentPose;
  geometry_msgs::msg::Pose basePose;
  urc_msgs::msg::Waypoint waypoint;


  void CostmapCallback(
    const nav2_msgs::msg::Costmap & msg
  );
  void GridPositionCallback(
    const geometry_msgs::msg::Pose & msg
  );
  void WaypointCallback(
    const urc_msgs::msg::Waypoint & msg
  );
  void BasePoseCallback(
    const geometry_msgs::msg::Pose & msg
  );
  
  void AStar();

};
}

#endif
