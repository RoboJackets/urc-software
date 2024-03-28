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
#include <pcl/filters/statistical_outlier_removal.h>
#include <pcl/search/kdtree.h>
#include <tf2_ros/transform_listener.h>
#include <tf2_sensor_msgs/tf2_sensor_msgs.h>
#include <tf2_ros/buffer.h>

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
        pcl::PointCloud<pcl::PointXYZ>::Ptr filterOutliers(const pcl::PointCloud<pcl::PointXYZ>::Ptr& inputCloud);
        void updateGradientsMinMax(const pcl::PointCloud<pcl::PointXYZ>::Ptr& filtered, std::vector<double>& gradients, double& minGradient, double& maxGradient, int k_neighbors);

        nav2_costmap_2d::Costmap2D* costmap_;
        int callback_count_;
        int k_neighbors_;
        const int reset_frequency_ = 1;
        std::shared_ptr<tf2_ros::TransformListener> tf_listener_;
        std::shared_ptr<tf2_ros::Buffer> tf_buffer_;
};


}

#endif