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

    costmap_ = new nav2_costmap_2d::Costmap2D(10, 10, 0.25, 0, 0);
    callback_count_ = 0;
}

void PointCloudCostmap::PointCloudCallback(const sensor_msgs::msg::PointCloud2 & msg) 
{

    double xSize = (double) costmap_->getSizeInCellsX();
    double ySize = (double) costmap_->getSizeInCellsY();
    double resolution = costmap_->getResolution();
    // double max_distance = sqrt(pow(xSize * resolution, 2) + pow(ySize * resolution, 2));

    callback_count_++;

    if(callback_count_ % reset_frequency_ == 0) {
        costmap_->resetMap(0, 0, xSize, ySize);
    }
    
    pcl::PointCloud<pcl::PointXYZ> cloud;
    pcl::fromROSMsg(msg, cloud);

    for (const auto& point: cloud.points) {
        unsigned int mx, my;
        if(costmap_->worldToMap(point.x, point.y, mx, my)) {
            // create a dynamic costmap
            // double distance = sqrt(pow(point.x , 2) + pow(point.y, 2));

            // TODO: Implement a max and min height for the costmap
            /*
                For future reference, camera has a 60deg vertical field of view
                The ideal depth range is ~3m, so the max/min height should be +-3m*tan(30deg)
                = +-3m*0.577 = +-1.731m
            */
            
            unsigned char cost;
            double height = point.z;

            double max_height = 2;
            double min_height = -2;

            if (height > max_height) {
                cost = 254;
            } else if (height < min_height) {
                cost = 0;
            } else {
                cost = static_cast<unsigned char>(
                    height-min_height / (max_height-min_height) * 254
                );
            }

            costmap_->setCost(mx, my, cost);

            // Inflate the costmap around obstacles
            double min_inflation_cost = 50;
            int inflation_radius = 1;
            for (int dx = -inflation_radius; dx <= inflation_radius; dx++) {
                for (int dy = -inflation_radius; dy <= inflation_radius; dy++) {
                    double inflation_distance = sqrt(dx*dx + dy*dy);
                    double normalized_distance = inflation_distance / inflation_radius;

                    unsigned char inflated_cost = static_cast<unsigned char>(
                        (1-normalized_distance) * (254 - min_inflation_cost) + min_inflation_cost
                    );

                    unsigned char curr_cost = costmap_->getCost(mx+dx, my+dy);
                    costmap_->setCost(mx+dx, my+dy, std::max(curr_cost, inflated_cost));
                }
            }  
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

            grid.data[index] = cost;

        }
    }

    return grid;
}
}

RCLCPP_COMPONENTS_REGISTER_NODE(pointcloud_costmap::PointCloudCostmap)
