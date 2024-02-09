#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/image.hpp"
#include "sensor_msgs/msg/laser_scan.hpp"
#include "nav2_costmap_2d/costmap_2d_ros.hpp"
#include "math.h"
#include <rclcpp_components/register_node_macro.hpp>


namespace depth_laserscan
{
class DepthLaserScan : public rclcpp::Node
{
public:
  explicit DepthLaserScan(const rclcpp::NodeOptions & options);

private:
  void depthCallback(const sensor_msgs::msg::Image::SharedPtr msg);
  rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr depth_sub_;
  rclcpp::Publisher<sensor_msgs::msg::LaserScan>::SharedPtr scan_pub_;
  sensor_msgs::msg::LaserScan convertDepthToLaserScan(const sensor_msgs::msg::Image::SharedPtr msg);
};
}
