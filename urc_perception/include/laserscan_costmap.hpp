#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/laser_scan.hpp"
#include "occupancy_grid.hpp"
#include "nav2_costmap_2d/costmap_2d_ros.hpp"
#include "sensor_msgs/msg/image.hpp"
#include "nav2_msgs/msg/costmap.hpp"
#include "math.h"

namespace laserscan_costmap
{
class LaserScanCostmap : public rclcpp::Node
{
    public:
        explicit LaserScanCostmap(const rclcpp::NodeOptions & options);
    private:
        void LaserScanCallback(const sensor_msgs::msg::LaserScan::SharedPtr msg);
        rclcpp::Subscription<sensor_msgs::msg::LaserScan>::SharedPtr laser_subscriber;
        rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr depth_subcriber;
        rclcpp::Publisher<nav2_msgs::msg::Costmap>::SharedPtr costmap_pub_;
};
}