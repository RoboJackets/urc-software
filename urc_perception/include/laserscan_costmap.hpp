#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/laser_scan.hpp"
#include "occupancy_grid.hpp"
#include "nav2_costmap_2d/costmap_2d_ros.hpp"
#include "math.h"

namespace laserscan_costmap
{
class LaserScanCostmap : public rclcpp::Node
{
    public:
        explicit LaserScanCostmap(const rclcpp::NodeOptions & options);
    private:
        scanCallback(const sensor_msgs::msg::LaserScan::SharedPtr msg);
        rclcpp::Subscription<sensor_msgs::msg::LaserScan>::SharedPtr scan_sub_;
        rclcpp::Publisher<occupancy_grid::OccupancyGrid>::SharedPtr costmap_pub_;
};
}