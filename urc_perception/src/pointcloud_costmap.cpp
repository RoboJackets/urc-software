#include "pointcloud_costmap.hpp"

namespace pointcloud_costmap
{
    PointCloudCostmap::PointCloudCostmap(const rclcpp::NodeOptions &options)
        : rclcpp::Node("pointcloud_costmap", options)
    {
        pointcloud_subscriber = create_subscription<sensor_msgs::msg::PointCloud2>(
            "/camera/depth/color/points", rclcpp::SystemDefaultsQoS(),
            [this](const sensor_msgs::msg::PointCloud2 msg)
            { PointCloudCallback(msg); });

        costmap_publisher = create_publisher<nav_msgs::msg::OccupancyGrid>(
            "/costmap2", rclcpp::SystemDefaultsQoS());

        costmap_ = new nav2_costmap_2d::Costmap2D(50, 50, 0.1, -2.5, -2.5);
        callback_count_ = 0;
        k_neighbors_ = 10;
    }

    void PointCloudCostmap::PointCloudCallback(const sensor_msgs::msg::PointCloud2 &msg)
    {

        double xSize = (double)costmap_->getSizeInCellsX();
        double ySize = (double)costmap_->getSizeInCellsY();

        callback_count_++;

        if (callback_count_ % reset_frequency_ == 0)
        {
            costmap_->resetMap(0, 0, xSize, ySize);
        }

        pcl::PointCloud<pcl::PointXYZ> cloud;
        pcl::fromROSMsg(msg, cloud);

        pcl::PointCloud<pcl::PointXYZ>::Ptr cloudPtr(new pcl::PointCloud<pcl::PointXYZ>);
        *cloudPtr = cloud; // Copy the data into the shared pointer

        pcl::PointCloud<pcl::PointXYZ>::Ptr filtered = filterOutliers(cloudPtr);

        std::vector<double> gradients(filtered->points.size(), 0.0); // init grads to 0
        double minGradient = std::numeric_limits<double>::max();
        double maxGradient = std::numeric_limits<double>::lowest();

        // Compute gradients and find min/max
        updateGradientsMinMax(filtered, gradients, minGradient, maxGradient, k_neighbors_);

        // Code to actually compute costmap
        for (size_t i = 0; i < filtered->points.size(); i++)
        {
            pcl::PointXYZ point = filtered->points[i];
            unsigned int mx, my;
            if (costmap_->worldToMap(point.x, point.y, mx, my))
            {
                unsigned char cost = (unsigned char)(gradients[i] * 100);
                costmap_->setCost(mx, my, cost);
            }
        }

        nav_msgs::msg::OccupancyGrid grid = convertCostmapToOccupancyGrid(*costmap_);

        costmap_publisher->publish(grid);
    }

    nav_msgs::msg::OccupancyGrid PointCloudCostmap::convertCostmapToOccupancyGrid(const nav2_costmap_2d::Costmap2D &costmap)
    {
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

        for (unsigned int i = 0; i < grid.info.height; ++i)
        {
            for (unsigned int j = 0; j < grid.info.width; ++j)
            {
                unsigned int index = grid.info.width * i + j;

                unsigned char cost = costmap.getCost(j, i);

                grid.data[index] = cost;
            }
        }

        return grid;
    }

    // Extracted method for filtering outliers from a point cloud
    pcl::PointCloud<pcl::PointXYZ>::Ptr PointCloudCostmap::filterOutliers(const pcl::PointCloud<pcl::PointXYZ>::Ptr &inputCloud)
    {
        pcl::StatisticalOutlierRemoval<pcl::PointXYZ> sor;
        sor.setInputCloud(inputCloud); // Use the input cloud
        sor.setMeanK(50);              // Number of neighbors to analyze for each point
        sor.setStddevMulThresh(1.0);   // Standard deviation multiplier
        pcl::PointCloud<pcl::PointXYZ>::Ptr filtered(new pcl::PointCloud<pcl::PointXYZ>);
        sor.filter(*filtered);
        return filtered;
    }

    // Extracted method for updating gradients, min, and max
    void PointCloudCostmap::updateGradientsMinMax(const pcl::PointCloud<pcl::PointXYZ>::Ptr &filtered,
                                                  std::vector<double> &gradients,
                                                  double &minGradient,
                                                  double &maxGradient,
                                                  int k_neighbors_)
    {
        // efficient KNN lookup
        pcl::search::KdTree<pcl::PointXYZ>::Ptr kdtree(new pcl::search::KdTree<pcl::PointXYZ>);
        kdtree->setInputCloud(filtered);

        std::vector<int> pointIdxNKNSearch(k_neighbors_);
        std::vector<float> pointNKNSquaredDistance(k_neighbors_);

        for (size_t i = 0; i < filtered->points.size(); i++)
        {
            pcl::PointXYZ point = filtered->points[i];
            if (kdtree)
            {
                if (kdtree->nearestKSearch(point, k_neighbors_, pointIdxNKNSearch, pointNKNSquaredDistance) > 0)
                {
                    double &gradient = gradients[i];
                    for (std::size_t j = 0; j < pointIdxNKNSearch.size(); j++)
                    {
                        pcl::PointXYZ &neighbor = filtered->points[pointIdxNKNSearch[j]];
                        double distance = sqrt(pointNKNSquaredDistance[j]);
                        double currentGradient = std::abs((neighbor.z - point.z) / distance);
                        if (currentGradient > gradient)
                        {
                            gradient = currentGradient;
                        }
                    }

                    // Update min and max gradients
                    minGradient = std::min(minGradient, gradient);
                    maxGradient = std::max(maxGradient, gradient);
                }
            }
        }
    }
}

RCLCPP_COMPONENTS_REGISTER_NODE(pointcloud_costmap::PointCloudCostmap)
