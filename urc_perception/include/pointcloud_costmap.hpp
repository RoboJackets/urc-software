#ifndef POINTCLOUD_COSTMAP_H
#define POINTCLOUD_COSTMAP_H

#include <rclcpp/rclcpp.hpp>
#include <rclcpp_components/register_node_macro.hpp>
#include <sensor_msgs/msg/image.hpp>
#include <sensor_msgs/msg/point_cloud2.hpp>
#include <nav2_costmap_2d/costmap_2d.hpp>
#include <bits/stdc++.h>
#include <nav_msgs/msg/occupancy_grid.hpp>
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
        nav_msgs::msg::OccupancyGrid convertCostmapToOccupancyGrid(const nav2_costmap_2d::Costmap2D & costmap);
        rclcpp::Subscription<sensor_msgs::msg::PointCloud2>::SharedPtr pointcloud_subscriber;
        rclcpp::Publisher<nav_msgs::msg::OccupancyGrid>::SharedPtr costmap_publisher;

        nav2_costmap_2d::Costmap2D* costmap_;
        int callback_count_;
        const int reset_frequency_ = 1;
};


}

#endif