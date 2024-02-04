#include "depth_laserscan.hpp"

namespace depth_laserscan
{
    DepthLaserScan::DepthLaserScan(const rclcpp::NodeOptions & options) : rclcpp::Node("depth_laserscan", options)
    {
        depth_sub_ = this->create_subscription<sensor_msgs::msg::Image>(
            "/depth_camera/depth/image_raw", 10, std::bind(&DepthLaserScan::depthCallback, this, std::placeholders::_1));
        scan_pub_ = this->create_publisher<sensor_msgs::msg::LaserScan>("/laserscan", 10);
    }

    void DepthLaserScan::depthCallback(const sensor_msgs::msg::Image::SharedPtr msg)
    {
        // Convert depth image to laser scan
        auto scan_msg = this->convertDepthToLaserScan(msg);
        scan_pub_->publish(scan_msg);
    }

    sensor_msgs::msg::LaserScan convertDepthToLaserScan(const sensor_msgs::msg::Image::SharedPtr msg)
    {
        // Convert depth image to laser scan
        sensor_msgs::msg::LaserScan scan_msg;
        
        // Set basic parameters
        scan_msg.header = msg->header;
        scan_msg.angle_min = -M_PI / 2;
        scan_msg.angle_max = M_PI / 2;
        scan_msg.angle_increment = M_PI / 180;
        scan_msg.time_increment = 0.0;
        scan_msg.range_min = 0.0;
        scan_msg.range_max = 10.0;

        auto depth_image = reinterpret_cast<const uint16_t*>(msg->data.data());

        int num_scan_points = (scan_msg.angle_max - scan_msg.angle_min) / scan_msg.angle_increment;

        scan_msg.ranges.resize(num_scan_points);

        for(int i = 0; i< num_scan_points; i++) {
            scan_msg.ranges[i] = depth_image[i];
        }

        return scan_msg;
    }
}

RCLCPP_COMPONENTS_REGISTER_NODE(depth_laserscan::DepthLaserScan)