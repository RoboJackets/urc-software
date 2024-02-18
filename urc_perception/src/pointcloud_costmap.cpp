#include "pointcloud_costmap.hpp"

namespace pointcloud_costmap
{
PointCloudCostmap::PointCloudCostmap(const rclcpp::NodeOptions & options) 
: rclcpp::Node("pointcloud_costmap", options)
{
    pointcloud_subscriber = create_subscription<sensor_msgs::msg::PointCloud2>(
        "/camera/depth/color/points", rclcpp::SystemDefaultsQoS(),
        [this](const sensor_msgs::msg::PointCloud2 msg) {PointCloudCallback(msg);});
    
    costmap_publisher = create_publisher<nav_msgs::msg::OccupancyGrid>(
        "/costmap2", rclcpp::SystemDefaultsQoS());

    costmap_ = new nav2_costmap_2d::Costmap2D(100, 100, 1, 0, 0);
}

void PointCloudCostmap::PointCloudCallback(const sensor_msgs::msg::PointCloud2 & msg) 
{
    pcl::PointCloud<pcl::PointXYZ> cloud;
    pcl::fromROSMsg(msg, cloud);

    // std::scoped_lock lock(*(costmap_->getMutex()));

    for (const auto& point: cloud.points) {
        unsigned int mx, my;
        if(costmap_->worldToMap(point.x, point.y, mx, my)) {
            double max_height = 2.0;
            double min_height = 0.0;

            unsigned char cost = 0;
            
            if(point.z > max_height) {
                cost = 254;
            } else if(point.z < min_height) {
                cost = 0;
            } else {
                cost = 254 * (point.z - min_height) / (max_height - min_height);
            }

            costmap_->setCost(mx, my, cost);
        }
    }

    nav_msgs::msg::OccupancyGrid grid = convertCostmapToOccupancyGrid(*costmap_);

    costmap_publisher->publish(grid);
}

nav_msgs::msg::OccupancyGrid PointCloudCostmap::convertCostmapToOccupancyGrid(const nav2_costmap_2d::Costmap2D & costmap) {
    nav_msgs::msg::OccupancyGrid grid;

    grid.header.stamp = rclcpp::Clock().now();
    grid.header.frame_id = "map";

    grid.info.resolution = costmap.getResolution();
    grid.info.width = costmap.getSizeInCellsX();
    grid.info.height = costmap.getSizeInCellsY();
    grid.info.origin.position.x = costmap.getOriginX();
    grid.info.origin.position.y = costmap.getOriginY();
    grid.info.origin.position.z = 0.0;
    grid.info.origin.orientation.w = 1.0;

    grid.data.resize(grid.info.width * grid.info.height);

    for (unsigned int i=0; i<grid.info.height; ++i) {
        for (unsigned int j=0; j<grid.info.width; ++j) {
            unsigned int index = grid.info.width * i + j;

            unsigned char cost = costmap.getCost(j, i);

            grid.data[index] = cost * 100 / 255;

        }
    }

    return grid;
}
}

RCLCPP_COMPONENTS_REGISTER_NODE(pointcloud_costmap::PointCloudCostmap)
