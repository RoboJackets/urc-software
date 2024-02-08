#include "costmap_generator.hpp"

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

        costmap_publisher = create_publisher<nav2_msgs::msg::Costmap>(
            "/costmap", rclcpp::SystemDefaultsQoS());

        RCLCPP_INFO(this->get_logger(), "hello");
        costmap.metadata.resolution = 0.25; // m/cell
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
    void CostmapGenerator::LaserScanCallback(const sensor_msgs::msg::LaserScan & msg) {
        // Convert laser scan to costmap
        nav2_msgs::msg::Costmap costmap_msg;
        costmap_publisher->publish(costmap_msg);
    }
};

RCLCPP_COMPONENTS_REGISTER_NODE(costmap_generator::CostmapGenerator)