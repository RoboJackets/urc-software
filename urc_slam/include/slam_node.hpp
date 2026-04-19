#ifndef SLAM_NODE_HPP_
#define SLAM_NODE_HPP_

#include <memory>
#include <string>

#include <gtsam/geometry/Pose3.h>
#include <nav_msgs/msg/odometry.hpp>
#include <nav_msgs/msg/path.hpp>
#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/imu.hpp>
#include <sensor_msgs/msg/point_cloud2.hpp>
#include <tf2_ros/transform_broadcaster.h>

#include "slam_backend.hpp"


namespace urc_slam {
    class SlamNode: public rclcpp::Node {
        public:
            explicit SlamNode(
                const rclcpp::NodeOptions &options = rclcpp::NodeOptions()
            );

        private:
            void odomCallback(const nav_msgs::msg::Odometry::SharedPtr msg);
            void imuCallback(const sensor_msgs::msg::Imu::SharedPtr msg);
            void lidarCallback(const sensor_msgs::msg::PointCloud2::SharedPtr msg);

            gtsam::Pose3 poseFromOdom(const nav_msgs::msg::Odometry &msg) const;
            void publishOutputs(const rclcpp::Time &stamp);

            SlamBackend backend;

            rclcpp::Subscription<nav_msgs::msg::Odometry>::SharedPtr odom_sub;
            rclcpp::Subscription<sensor_msgs::msg::Imu>::SharedPtr imu_sub;
            rclcpp::Subscription<sensor_msgs::msg::PointCloud2>::SharedPtr lidar_sub;

            rclcpp::Publisher<nav_msgs::msg::Odometry>::SharedPtr slam_odom_pub;
            rclcpp::Publisher<nav_msgs::msg::Path>::SharedPtr path_pub;

            std::unique_ptr<tf2_ros::TransformBroadcaster> tf_broadcaster;

            nav_msgs::msg::Path path_msg;
            sensor_msgs::msg::Imu last_imu_msg;
            sensor_msgs::msg::PointCloud2::SharedPtr last_lidar_msg;

            std::string odom_topic;
            std::string imu_topic;
            std::string lidar_topic;
            std::string map_frame;
            std::string odom_frame;
            std::string base_link_frame;

    };

}
#endif