#ifndef SLAM_NODE_HPP_
#define SLAM_NODE_HPP_

#include <memory>
#include <string>
#include <optional>
#include <nav_msgs/msg/odometry.hpp>
#include <nav_msgs/msg/path.hpp>
#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/imu.hpp>
#include <sensor_msgs/msg/point_cloud2.hpp>
#include <tf2_ros/transform_broadcaster.h>

#include "slam_backend.hpp"
#include "lidar_frontend.hpp"

namespace urc_slam {
    class SlamNode : public rclcpp::Node {
        public:
            explicit SlamNode(
                const rclcpp::NodeOptions &options = rclcpp::NodeOptions()
            );

        private:
            LidarFrontend lidar_frontend;
            LidarFrontend::Cloud::Ptr previous_keyframe_cloud;
            double maximum_fitness_score;


            void imuCallback(const sensor_msgs::msg::Imu::SharedPtr msg);
            void lidarCallback(const sensor_msgs::msg::PointCloud2::SharedPtr msg);
            void publishOutputs(const rclcpp::Time &stamp);

            SlamBackend backend;
            bool imu_integrated_since_keyframe = false;
            std::optional<rclcpp::Time> previous_imu_stamp;
            std::size_t latest_keyframe_index = 0;


            rclcpp::Subscription<sensor_msgs::msg::Imu>::SharedPtr imu_sub;
            rclcpp::Subscription<sensor_msgs::msg::PointCloud2>::SharedPtr lidar_sub;

            rclcpp::Publisher<nav_msgs::msg::Odometry>::SharedPtr slam_odom_pub;
            rclcpp::Publisher<nav_msgs::msg::Path>::SharedPtr path_pub;

            std::unique_ptr<tf2_ros::TransformBroadcaster> tf_broadcaster;

            nav_msgs::msg::Path path_msg;


            std::string slam_odom_topic;
            std::string imu_topic;
            std::string lidar_topic;
            std::string map_frame;
            std::string base_link_frame;


            LidarFrontend::Cloud::Ptr accumulated_map;
            double map_voxel_size_m;
            rclcpp::Publisher<sensor_msgs::msg::PointCloud2>::SharedPtr map_pub;
            void addKeyframeToMap(const LidarFrontend::Cloud::ConstPtr &cloud, const rclcpp::Time &stamp);
    };

}
#endif