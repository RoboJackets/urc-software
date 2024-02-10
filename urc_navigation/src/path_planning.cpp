#include "path_planning.hpp"

namespace path_planning
{
PathPlanning::PathPlanning(const rclcpp::NodeOptions & options)
: rclcpp::Node("path_planning", options)
{
  path_publisher = create_publisher<std::vector<urc_msgs::msg::Waypoint>>(
    "/path", rclcpp::SystemDefaultsQoS()
  );

  costmap_subscriber = create_subscription<nav2_msgs::msg::Costmap>(
    "/costmap", rclcpp::SystemDefaultsQoS(),
    [this](const nav2_msgs::msg::Costmap msg) {CostmapCallback(msg);});
  grid_pose_subscriber = create_subscription<geometry_msgs::msg::Pose>(
    "/pose/costmap", rclcpp::SystemDefaultsQoS(),
    [this](const geometry_msgs::msg::Pose msg) {GridPositionCallback(msg);});

  gps_waypoint_subscriber = create_subscription<urc_msgs::msg::Waypoint>(
    "/waypoint", rclcpp::SystemDefaultsQoS(),
    [this](const urc_msgs::msg::Waypoint msg) {WaypointCallback(msg);});
  base_pose_subscriber = create_subscription<geometry_msgs::msg::Pose>(
    "/base_pose", rclcpp::SystemDefaultsQoS(),
    [this](const geometry_msgs::msg::Pose msg) {BasePoseCallback(msg);});

  this->currentCostmap.metadata.size_x = 0;
  this->currentPose.position.x = MAXFLOAT;
  this->basePose.position.x = MAXFLOAT;
  this->waypoint.latitude = MAXFLOAT;
}

void PathPlanning::CostmapCallback(const nav2_msgs::msg::Costmap & msg) {
    this->currentCostmap = msg;
    AStar();
}
void PathPlanning::GridPositionCallback(const geometry_msgs::msg::Pose & msg) {
    this->currentPose = msg;
    AStar();
}
void PathPlanning::WaypointCallback(const urc_msgs::msg::Waypoint & msg) {
    this->waypoint = msg;
    AStar();
}
void PathPlanning::BasePoseCallback(const geometry_msgs::msg::Pose & msg) {
    this->basePose = msg;
    AStar();
}

void PathPlanning::AStar() {
    if (this->currentCostmap.metadata.size_x == 0) {
        RCLCPP_INFO(this->get_logger(), "Costmap data not received");
        return;
    } else if (this->currentPose.position.x == MAXFLOAT) {
        RCLCPP_INFO(this->get_logger(), "Current pose data not received");
        return;
    } else if (this->basePose.position.x == MAXFLOAT) {
        RCLCPP_INFO(this->get_logger(), "Base pose data not received");
        return;
    } else if (this->waypoint.latitude == MAXFLOAT) {
        RCLCPP_INFO(this->get_logger(), "Waypoint data not received");
        return;
    } 
    
    // By now, all data must have been received

    double waypointLatitude = this->waypoint.latitude;
    double waypointLongitude

    std::vector<urc_msgs::msg::Waypoint> waypoint_list;
    std::priority_queue<urc_msgs::msg::Waypoint> pq;



}
}

RCLCPP_COMPONENTS_REGISTER_NODE(path_planning::PathPlanning)
