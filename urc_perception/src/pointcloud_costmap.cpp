#include pointcloud_costmap.hpp

namespace pointcloud_costmap
{
PointCloudCostmap::PointCloudCostmap(const rclcpp::NodeOptions & options) 
: rclcpp::Node("pointcloud_costmap", options)
{
    pointcloud_subscriber = create_subscription<sensor_msgs::msg::PointCloud2>(
        "/camera/depth/color/points", rclcpp::SystemDefaultsQoS(),
        [this](const sensor_msgs::msg::PointCloud2 msg) {PointCloudCallback(msg);});
    
    costmap_publisher = create_publisher<nav2_msgs::msg::OccupancyGrid>(
        "/costmap2", rclcpp::SystemDefaultsQoS());

    costmap_ = new costmap_2d::Costmap2D(100, 100, 0.05, 0, 0);
}

void PointCloudCostmap::PointCloudCallback(const sensor_msgs::msg::PointCloud2 & msg) 
{
    pcl::PointCloud<pcl::PointXYZ> cloud;
    pcl::fromROSMsg(msg, cloud);

    costmap_2d::Costmap2D::mutex_t::scoped_lock lock(*(costmap_->getMutex()));

    for (const auto& point: cloud.points) {
        unsigned int mx, my;
        if(costmap_->worldToMap(point.x, point.y, mx, my)) {
            costmap_->setCost(mx, my, costmap_2d::LETHAL_OBSTACLE);
        }
    }

    nav2_msgs::msg::OccupancyGrid grid;
    costmap_2d::convertCostmapToOccupancyGrid(*costmap_, grid);

    costmap_publisher->publish(grid);

}
}

RCLCPP_COMPONENTS_REGISTER_NODE(pointcloud_costmap::PointCloudCostmap)
