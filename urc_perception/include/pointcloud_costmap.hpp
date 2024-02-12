#ifndef POINTCLOUD_COSTMAP_H
#define POINTCLOUD_COSTMAP_H

#include <rclcpp/rclcpp.hpp>
#include <rclcpp_components/register_node_macro.hpp>
#include <sensor_msgs/msg/image.hpp>
#include <sensor_msgs/msg/point_cloud2.hpp>
#include <costmap_2d/costmap_2d_ros.hpp>
#include <bits/stdc++.h>
#include <nav2_msgs/msg/occupancy_grid.hpp>
#include <pcl_conversions/pcl_conversions.h>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>

namespace pointcloud_costmap
{
class PointCloudCostmap : public rclcpp::Node
{
    public:
        explicit PointCloudCostmap(const rclcpp::NodeOptions & options);
    private:
        void PointCloudCallback(const sensor_msgs::msg::PointCloud2 & msg);
        rclcpp::Subscription<sensor_msgs::msg::PointCloud2>::SharedPtr pointcloud_subscriber;
        rclcpp::Publisher<costmap_2d::OccupancyGrid>::SharedPtr costmap_publisher;

        costmap_2d::Costmap2D* costmap_;
}


}

#endif