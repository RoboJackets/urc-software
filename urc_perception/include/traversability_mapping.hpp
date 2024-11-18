#ifndef TRAVERSABILITY_MAPPING_HPP_
#define TRAVERSABILITY_MAPPING_HPP_

#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/point_cloud2.hpp>
#include <grid_map_ros/grid_map_ros.hpp>
#include "tf2_ros/transform_listener.h"
#include "tf2_ros/buffer.h"
#include <grid_map_ros/grid_map_ros.hpp>

namespace urc_perception
{

    class TraversabilityMapping : public rclcpp::Node
    {
    public:
        explicit TraversabilityMapping(const rclcpp::NodeOptions &options);
        ~TraversabilityMapping();

    private:
        void handlePointcloud(const sensor_msgs::msg::PointCloud2::SharedPtr msg);
        void initializeMap();

        rclcpp::Subscription<sensor_msgs::msg::PointCloud2>::SharedPtr lidar_subscriber_;
        rclcpp::Publisher<grid_map_msgs::msg::GridMap>::SharedPtr grid_map_publisher_;

        std::unique_ptr<tf2_ros::Buffer> tf_buffer_;
        std::shared_ptr<tf2_ros::TransformListener> tf_listener_;

        grid_map::GridMap map_;

        double resolution_;
        double min_z_;
        double max_z_;
        unsigned int width_;

        std::string map_frame_;
    };

} // namespace urc_perception

#endif // TRAVERSABILITY_MAPPING_HPP_
