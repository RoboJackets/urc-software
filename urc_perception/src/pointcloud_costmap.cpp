#include "pointcloud_costmap.hpp"

namespace pointcloud_costmap
{
    PointCloudCostmap::PointCloudCostmap(const rclcpp::NodeOptions &options)
        : rclcpp::Node("pointcloud_costmap", options)
    {
        pointcloud_subscriber = create_subscription<sensor_msgs::msg::PointCloud2>(
            "/camera/points", rclcpp::SystemDefaultsQoS(),
            [this](const sensor_msgs::msg::PointCloud2 msg)
            { PointCloudCallback(msg); });

        costmap_publisher = create_publisher<nav_msgs::msg::OccupancyGrid>(
            "/costmap2", rclcpp::SystemDefaultsQoS());

        tf_buffer_ = std::make_unique<tf2_ros::Buffer>(this->get_clock());
        tf_listener_ = std::make_shared<tf2_ros::TransformListener>(*tf_buffer_);

        costmap_ = new nav2_costmap_2d::Costmap2D(50, 50, 0.1, -2.5, -2.5);
        k_neighbors_ = 50;
    }

    void PointCloudCostmap::PointCloudCallback(const sensor_msgs::msg::PointCloud2 &msg)
    {
        pcl::PointCloud<pcl::PointXYZ> cloud;
        pcl::fromROSMsg(msg, cloud);

        // Transform pt cloud to odom frame
        geometry_msgs::msg::TransformStamped transform = lookup_camera_odom();
        sensor_msgs::msg::PointCloud2 transformed_cloud;
        tf2::doTransform(msg, transformed_cloud, transform);

        pcl::PointCloud<pcl::PointXYZ>::Ptr cloudPtr(new pcl::PointCloud<pcl::PointXYZ>);
        pcl::fromROSMsg(transformed_cloud, *cloudPtr);

        // filtering makes it processing to slow
        // pcl::PointCloud<pcl::PointXYZ>::Ptr filtered = filterOutliers(cloudPtr);

        std::vector<double> gradients(cloudPtr->points.size(), 0.0); // init grads to 0
        double minGradient = std::numeric_limits<double>::max();
        double maxGradient = std::numeric_limits<double>::lowest();

        // Compute gradients and find min/max
        updateGradientsMinMax(cloudPtr, gradients, minGradient, maxGradient, k_neighbors_);

        // Code to actually compute costmap
        for (size_t i = 0; i < cloudPtr->points.size(); i++)
        {
            pcl::PointXYZ point = cloudPtr->points[i];
            unsigned int mx, my;
            if (costmap_->worldToMap(point.x, point.y, mx, my))
            {
                double gradient_range = maxGradient - minGradient;
                double normalized_gradient = (gradients[i] - minGradient) / gradient_range;
                unsigned char cost = static_cast<unsigned char>(normalized_gradient * 100);
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
        grid.header.frame_id = "odom";

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
        sor.setMeanK(k_neighbors_);              // Number of neighbors to analyze for each point
        sor.setStddevMulThresh(1.0);   // Standard deviation multiplier
        pcl::PointCloud<pcl::PointXYZ>::Ptr filtered(new pcl::PointCloud<pcl::PointXYZ>);
        sor.filter(*filtered);
        return filtered;
        // return inputCloud;
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

    // returns a transform from the camera link to the odom frame
    geometry_msgs::msg::TransformStamped PointCloudCostmap::lookup_camera_odom(){
        std::string map_frame = "camera_link";
        std::string odom_frame = "odom";
        return tf_buffer_->lookupTransform(map_frame, odom_frame, tf2::TimePointZero);
    }
}

RCLCPP_COMPONENTS_REGISTER_NODE(pointcloud_costmap::PointCloudCostmap)
