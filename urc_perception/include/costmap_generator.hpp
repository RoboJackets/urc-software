#ifndef COSTMAP_GENERATOR_H
#define COSTMAP_GENERATOR_H

#include <rclcpp/rclcpp.hpp>
#include <rclcpp_components/register_node_macro.hpp>
#include <sensor_msgs/msg/laser_scan.hpp>
#include <nav2_costmap_2d/costmap_2d_ros.hpp>
#include <sensor_msgs/msg/image.hpp>
#include <nav2_msgs/msg/costmap.hpp>
#include <math.h>
#include <stdlib.h>

namespace costmap_generator
{
class CostmapGenerator : public rclcpp::Node
{
public:
    explicit CostmapGenerator(const rclcpp::NodeOptions & options);
private:
    void DepthCallback(const sensor_msgs::msg::Image & msg);
    void LaserScanCallback(const sensor_msgs::msg::LaserScan & msg);
    void PoseCallback(const geometry_msgs::msg::Pose & msg);

    rclcpp::Subscription<geometry_msgs::msg::Pose>::SharedPtr pose_subscriber;
    rclcpp::Subscription<sensor_msgs::msg::LaserScan>::SharedPtr laser_subscriber;
    rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr depth_subscriber;
    rclcpp::Publisher<nav2_msgs::msg::Costmap>::SharedPtr costmap_publisher;

    // Private Variables
    nav2_msgs::msg::Costmap costmap;
    int direction = 0;
    int robotGridX;
    int robotGridY;
    double minCost;
    double maxCost;
    int delay;
};
}

#endif