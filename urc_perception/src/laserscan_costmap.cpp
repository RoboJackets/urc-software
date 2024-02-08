#include "laserscan_costmap.hpp"

namespace laserscan_costmap
{
    LaserScanCostmap::LaserScanCostmap(const rclcpp::NodeOptions & options)
    : rclcpp::Node("laserscan_costmap", options)
    {
        laser_subscriber = create_subscription<sensor_msgs::msg::LaserScan>(
            "/laserscan", rclcpp::SystemDefaultsQoS(),
            [this](const sensor_msgs::msg::LaserScan msg) {LaserScanCallback(msg);});

    }
    void scanCallback(const sensor_msgs::msg::LaserScan::SharedPtr msg)
    {
        // Convert laser scan to costmap
        auto costmap_msg = convertScanToCostmap(msg);
        costmap_pub_->publish(costmap_msg);
    }


    void LaserScanCallback(const sensor_msgs::msg::LaserScan msg) {
        
    }

  
};