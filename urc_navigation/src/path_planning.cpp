#include "path_planning.hpp"

namespace path_planning
{
PathPlanning::PathPlanning(const rclcpp::NodeOptions & options)
: rclcpp::Node("path_planning", options)
{
  path_publisher = create_publisher<std::vector<urc_msgs::msg::GridLocation>>(
    "/path", rclcpp::SystemDefaultsQoS()
  );

  costmap_subscriber = create_subscription<nav2_msgs::msg::Costmap>(
    "/costmap", rclcpp::SystemDefaultsQoS(),
    [this](const nav2_msgs::msg::Costmap msg) {CostmapCallback(msg);});
  grid_pose_subscriber = create_subscription<geometry_msgs::msg::Pose>(
    "/pose/costmap", rclcpp::SystemDefaultsQoS(),
    [this](const geometry_msgs::msg::Pose msg) {GridPositionCallback(msg);});
  grid_waypoint_subscriber = create_subscription<urc_msgs::msg::GridLocation>(
    "/waypoint", rclcpp::SystemDefaultsQoS(),
    [this](const urc_msgs::msg::GridLocation msg) {WaypointCallback(msg);});

  this->currentCostmap.metadata.size_x = 0;
  this->currentPose.position.x = MAXFLOAT;
  this->waypoint.x = 100;;
}

void PathPlanning::CostmapCallback(const nav2_msgs::msg::Costmap & msg) {
    this->currentCostmap = msg;
    AStar();
}
void PathPlanning::GridPositionCallback(const geometry_msgs::msg::Pose & msg) {
    this->currentPose = msg;
    AStar();
}
void PathPlanning::WaypointCallback(const urc_msgs::msg::GridLocation & msg) {
    this->waypoint = msg;
    AStar();
}

void PathPlanning::AStar() {
    if (this->currentCostmap.metadata.size_x == 0) {
        RCLCPP_INFO(this->get_logger(), "Costmap data not received");
        return;
    } else if (this->currentPose.position.x == MAXFLOAT) {
        RCLCPP_INFO(this->get_logger(), "Current pose data not received");
        return;
    } else if (this->waypoint.x == 100) {
        RCLCPP_INFO(this->get_logger(), "Waypoint data not received");
        return;
    } 
    
    // By now, all data must have been received
    int currentX = (int)currentPose.position.x;
    int currentY = (int)currentPose.position.y;
    int goalX = waypoint.x;
    int goalY = waypoint.y;
    
    std::set<urc_msgs::msg::GridLocation> visited_set;
    std::vector<urc_msgs::msg::GridLocation> waypoint_list;
    std::priority_queue<urc_msgs::msg::GridLocation> pq;

    while (!visited_set.empty()) {
        
    }



}
}

RCLCPP_COMPONENTS_REGISTER_NODE(path_planning::PathPlanning)
