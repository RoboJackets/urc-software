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

    costmap_ = new nav2_costmap_2d::Costmap2D(100, 100, 0.1, -5, -5);
    callback_count_ = 0;
}

void PointCloudCostmap::PointCloudCallback(const sensor_msgs::msg::PointCloud2 & msg) 
{

    double xSize = (double) costmap_->getSizeInCellsX();
    double ySize = (double) costmap_->getSizeInCellsY();
    

    callback_count_++;

    if(callback_count_ % reset_frequency_ == 0) {
        costmap_->resetMap(0, 0, xSize, ySize);
        // Reinitialized max_heights to minimum possible heights for every callback
        max_heights_.resize(costmap_->getSizeInCellsX(), std::vector<double>(costmap_->getSizeInCellsY(), std::numeric_limits<double>::lowest()));
    }

    
    
    pcl::PointCloud<pcl::PointXYZ> cloud;
    pcl::fromROSMsg(msg, cloud);

    pcl::PointCloud<pcl::PointXYZ>::Ptr cloudPtr(new pcl::PointCloud<pcl::PointXYZ>);
    *cloudPtr = cloud; // Copy the data into the shared pointer

    // Filter out outlies from the point cloud
    pcl::StatisticalOutlierRemoval<pcl::PointXYZ> sor;
    sor.setInputCloud(cloudPtr); // Use the shared pointer here
    sor.setMeanK(50); // Number of neighbors to analyze for each point
    sor.setStddevMulThresh(1.0); // Standard deviation multiplier
    pcl::PointCloud<pcl::PointXYZ>::Ptr filtered(new pcl::PointCloud<pcl::PointXYZ>);
    sor.filter(*filtered);

    for (const auto& point: filtered->points) {
        unsigned int mx, my;
        if(costmap_->worldToMap(point.x, point.y, mx, my)) {
            // TODO: Implement a max and min height for the costmap
            /*
                For future reference, camera has a 60deg vertical field of view
                The ideal depth range is ~3m, so the max/min height should be +-3m*tan(30deg)
                = +-3m*0.577 = +-1.731m
            */
            
            unsigned char cost;
            

            if(point.z > max_heights_[mx][my]) {
                max_heights_[mx][my] = point.z;
            }

            double height = max_heights_[mx][my];

            double max_height = 1.731;
            double min_height = 0;

            // Implement a dynamic cost function
            if (height > max_height) {
                cost = 254;
            } else if (height < min_height) {
                cost = 0;
            } else {
                double height_range = max_height - min_height;
                double normalized_height = (height - min_height) / height_range;
                cost = static_cast<unsigned char>(normalized_height * 254); // Scale to max cost value
            }

            costmap_->setCost(mx, my, cost);

            // Inflate the costmap around obstacles
            // double min_inflation_cost = 50;
            // int inflation_radius = 1;
            // for (int dx = -inflation_radius; dx <= inflation_radius; dx++) {
            //     for (int dy = -inflation_radius; dy <= inflation_radius; dy++) {
            //         // Prevent out of bounds
            //         if (dx < -static_cast<int>(mx) || mx+dx >= xSize || dy < -static_cast<int>(my) || my+dy >= ySize) {
            //             continue;
            //         }
                    
            //         double inflation_distance = sqrt(dx*dx + dy*dy);
            //         double normalized_distance = inflation_distance / inflation_radius;

            //         unsigned char inflated_cost = static_cast<unsigned char>(
            //             (1-normalized_distance) * (254 - min_inflation_cost) + min_inflation_cost
            //         );
                    
            //         unsigned char curr_cost = costmap_->getCost(mx+dx, my+dy);
            //         costmap_->setCost(mx+dx, my+dy, std::max(curr_cost, inflated_cost));
            //     }
            // }  
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
