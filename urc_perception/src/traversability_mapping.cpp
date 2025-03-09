#include "traversability_mapping.hpp"

#include <ament_index_cpp/get_package_share_directory.hpp>

#include <pcl_conversions/pcl_conversions.h>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/filters/filter.h>
#include <pcl/PCLPointCloud2.h>

#include <tf2_sensor_msgs/tf2_sensor_msgs.hpp>
#include <tf2_geometry_msgs/tf2_geometry_msgs.hpp>
#include <geometry_msgs/msg/pose.hpp>

#include <grid_map_pcl/GridMapPclLoader.hpp>

namespace urc_perception
{

    TraversabilityMapping::TraversabilityMapping(const rclcpp::NodeOptions &options)
        : Node("traversability_mapping", options), filter_chain_("grid_map::GridMap")
    {
        if (!readParameters())
        {
            RCLCPP_ERROR(this->get_logger(), "Could not read parameters. Shutting down node.");
            return;
        }

        RCLCPP_INFO(this->get_logger(), "Traversability mapping node has been started.");

        tf_buffer_ = std::make_unique<tf2_ros::Buffer>(this->get_clock());
        tf_listener_ = std::make_shared<tf2_ros::TransformListener>(*tf_buffer_);

        grid_map_publisher_ = create_publisher<grid_map_msgs::msg::GridMap>(output_map_topic_, 10);
        pointcloud_subscriber_ = create_subscription<sensor_msgs::msg::PointCloud2>(
            pointcloud_topic_, 10, std::bind(&TraversabilityMapping::handlePointcloud, this, std::placeholders::_1));

        if (filter_chain_.configure(
                filter_chain_parameter_name_, this->get_node_logging_interface(),
                this->get_node_parameters_interface()))
        {
            RCLCPP_INFO(this->get_logger(), "Filter chain configured.");
        }
        else
        {
            RCLCPP_ERROR(this->get_logger(), "Could not configure the filter chain!");
            return;
        }
    }

    TraversabilityMapping::~TraversabilityMapping() = default;

    void TraversabilityMapping::handlePointcloud(const sensor_msgs::msg::PointCloud2::SharedPtr msg)
    {
        // Convert the transformed point cloud to a PCL point cloud
        pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);
        pcl::fromROSMsg(*msg, *cloud);

        std::string filePath = ament_index_cpp::get_package_share_directory("urc_perception") + "/config/pcl_grid_map_params.yaml";

        // Construct a GridMapPclLoader object and set the input cloud
        grid_map::GridMapPclLoader gridMapPclLoader(this->get_logger());
        gridMapPclLoader.setInputCloud(cloud);
        gridMapPclLoader.loadParameters(filePath);

        gridMapPclLoader.preProcessInputCloud();
        gridMapPclLoader.initializeGridMapGeometryFromInputCloud();
        gridMapPclLoader.addLayerFromInputCloud(std::string("elevation"));

        grid_map::GridMap map = gridMapPclLoader.getGridMap();
        map.setFrameId(msg->header.frame_id);

        grid_map::GridMap filtered_map;
        if (!filter_chain_.update(map, filtered_map))
        {
            RCLCPP_ERROR(this->get_logger(), "Could not update the grid map filter chain!");
            return;
        }

        std::unique_ptr<grid_map_msgs::msg::GridMap> outputMessage;
        outputMessage = grid_map::GridMapRosConverter::toMessage(filtered_map);
        grid_map_publisher_->publish(std::move(outputMessage));
    }

    bool TraversabilityMapping::readParameters()
    {
        this->declare_parameter("pointcloud_topic", std::string("pointcloud"));
        this->declare_parameter("output_map_topic", std::string("costmap"));
        this->declare_parameter("filter_chain_parameter_name", std::string("filters"));

        if (!this->get_parameter("pointcloud_topic", pointcloud_topic_))
        {
            RCLCPP_ERROR(this->get_logger(), "Could not read parameter pointcloud_topic.");
            return false;
        }

        this->get_parameter("output_map_topic", output_map_topic_);
        this->get_parameter("filter_chain_parameter_name", filter_chain_parameter_name_);

        return true;
    }
} // namespace urc_perception

#include <rclcpp_components/register_node_macro.hpp>
RCLCPP_COMPONENTS_REGISTER_NODE(urc_perception::TraversabilityMapping)
