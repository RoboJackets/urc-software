#include "traversability_mapping.hpp"

#include <pcl_conversions/pcl_conversions.h>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/filters/filter.h>
#include <pcl/PCLPointCloud2.h>

#include <tf2_sensor_msgs/tf2_sensor_msgs.hpp>
#include <tf2_geometry_msgs/tf2_geometry_msgs.hpp>
#include <geometry_msgs/msg/pose.hpp>

namespace urc_perception
{

    TraversabilityMapping::TraversabilityMapping(const rclcpp::NodeOptions &options)
        : Node("traversability_mapping", options)
    {
        RCLCPP_INFO(this->get_logger(), "Traversability mapping node has been started.");

        tf_buffer_ = std::make_unique<tf2_ros::Buffer>(this->get_clock());
        tf_listener_ = std::make_shared<tf2_ros::TransformListener>(*tf_buffer_);
    }

    TraversabilityMapping::~TraversabilityMapping() = default;

    void TraversabilityMapping::handlePointcloud(const sensor_msgs::msg::PointCloud2::SharedPtr msg)
    {
        // This function should be called whenever a new point cloud message is received.
        // The point cloud message is transformed to the map frame and then processed.
        // The resulting traversability map should be published.
    }

    void TraversabilityMapping::initializeMap()
    {
        // Initialize the map_ object.
    }

} // namespace urc_perception

#include <rclcpp_components/register_node_macro.hpp>
RCLCPP_COMPONENTS_REGISTER_NODE(urc_perception::TraversabilityMapping)
