#include "costmap_generator.hpp"
#include <math.h>

namespace costmap_generator
{
CostmapGenerator::CostmapGenerator(const rclcpp::NodeOptions & options)
: rclcpp::Node("laserscan_costmap", options)
{
  depth_subscriber = create_subscription<sensor_msgs::msg::Image>(
    "/depth_camera/depth/image_raw", rclcpp::SystemDefaultsQoS(),
    [this](const sensor_msgs::msg::Image msg) {DepthCallback(msg);});

  laser_subscriber = create_subscription<sensor_msgs::msg::LaserScan>(
    "/laserscan", rclcpp::SystemDefaultsQoS(),
    [this](const sensor_msgs::msg::LaserScan msg) {LaserScanCallback(msg);});

  pose_subscriber = create_subscription<geometry_msgs::msg::Pose>(
    "/pose", rclcpp::SystemDefaultsQoS(),
    [this](const geometry_msgs::msg::Pose msg) {PoseCallback(msg);});

  costmap_publisher = create_publisher<nav2_msgs::msg::Costmap>(
    "/costmap", rclcpp::SystemDefaultsQoS());

  RCLCPP_INFO(this->get_logger(), "hello");
  costmap.metadata.resolution = 0.25;       // m/cell
  costmap.metadata.size_x = 100;
  costmap.metadata.size_y = 100;
  costmap.data[100] = 10;
  std::cout << costmap.data[100];
}


void CostmapGenerator::DepthCallback(const sensor_msgs::msg::Image & msg)
{
  nav2_msgs::msg::Costmap costmap_msg;
  costmap_publisher->publish(costmap_msg);
}
void CostmapGenerator::LaserScanCallback(const sensor_msgs::msg::LaserScan & msg)
{
  // Convert laser scan to costmap
  nav2_msgs::msg::Costmap costmap_msg;
  costmap_publisher->publish(costmap_msg);
}
void CostmapGenerator::PoseCallback(const geometry_msgs::msg::Pose & msg)
{
  double x = msg.orientation.x;
  double y = msg.orientation.y;
  double z = msg.orientation.z;
  double w = msg.orientation.w;
  double euler_z = atan2(2.0f * (w * z + x * y), w * w + x * x - y * y - z * z) + M_PI / 4;
  int rotation_id = (int(euler_z / (M_PI / 8))) % 8;
  RCLCPP_INFO(this->get_logger(), "%d", rotation_id);
}
}

RCLCPP_COMPONENTS_REGISTER_NODE(costmap_generator::CostmapGenerator)
