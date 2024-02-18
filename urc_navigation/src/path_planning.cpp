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

    // Data Structures
    int currentX = (int)currentPose.position.x;
    int currentY = (int)currentPose.position.y;
    int goalX = waypoint.x;
    int goalY = waypoint.y;

    std::set<path_planning::PathPlanning::GridBlock> visited_set;
    std::vector<path_planning::PathPlanning::GridBlock> waypoint_list;
    std::priority_queue<path_planning::PathPlanning::GridBlock> open_set; // Min-heap


    // Start Node
    GridBlock start_node;
    start_node.location.x = currentX;
    start_node.location.y = currentY;
    start_node.g_cost = 0.0;
    start_node.h_cost = heuristic(currentX, currentY, goalX, goalY); 
    start_node.f_cost = start_node.g_cost + start_node.h_cost;
    start_node.parent = nullptr;
    open_set.push(start_node);

    // A-star Main Loop
    while (!open_set.empty()) {
         
    }

}

double PathPlanning::heuristic(int x1, int y1, int x2, int y2) {
    return std::abs(x1 - x2) + std::abs(y1 - y2);
}

double PathPlanning::cost(const PathPlanning::GridBlock & from, 
                          const PathPlanning::GridBlock & to) {

    int costmap_index = to.location.y * currentCostmap.metadata.size_x + to.location.x;
    double cell_cost = currentCostmap.data[costmap_index];

    double distance = std::sqrt(std::pow(to.location.x - from.location.x, 2) + std::pow(to.location.y - from.location.y, 2));
    return cell_cost * distance; 
}
}

RCLCPP_COMPONENTS_REGISTER_NODE(path_planning::PathPlanning)
