// #include "laserscan_costmap.hpp"

// namespace laserscan_costmap
// {
//     LaserScanCostmapNode::LaserScanCostmapNode(const rclcpp::NodeOptions & oprions) : rclcpp::Node('laserscan_costmap', option)
//     {
//         scan_sub_ = this->create_subscription<sensor_msgs::msg::LaserScan>(
//             "/scan", 10, std::bind(&LaserScanCostmapNode::scanCallback, this, std::placeholders::_1));
//         costmap_pub_ = this->create_publisher<occupancy_grid::OccupancyGrid>("/costmap", 10);
//     }

//     void scanCallback(const sensor_msgs::msg::LaserScan::SharedPtr msg)
//     {
//         // Convert laser scan to costmap
//         auto costmap_msg = convertScanToCostmap(msg);
//         costmap_pub_->publish(costmap_msg);
//     }

    
// }