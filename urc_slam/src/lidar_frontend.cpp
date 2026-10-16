#include "lidar_frontend.hpp"

#include <cmath>
#include <Eigen/Core>
#include <pcl/common/point_tests.h>
#include <pcl/filters/voxel_grid.h>
#include <pcl/registration/gicp.h>

namespace urc_slam {
    LidarFrontend::LidarFrontend(
        double voxel_size_m,
        double minimum_range_m,
        double maximum_range_m,
        double maximum_correspondence_distance_m,
        int maximum_iterations,
        double transformation_epsilon,
        double fitness_epsilon,
        const gtsam::Pose3 &base_T_lidar
    ) 
    : voxel_size_m_(voxel_size_m),
    minimum_range_m_(minimum_range_m),
    maximum_range_m_(maximum_range_m),
    maximum_correspondence_distance_m_(
        maximum_correspondence_distance_m
    ),
    maximum_iterations_(maximum_iterations),
    transformation_epsilon_(transformation_epsilon),
    fitness_epsilon_(fitness_epsilon),
    base_T_lidar_(base_T_lidar)
{

}

LidarFrontend::Cloud::Ptr LidarFrontend::preprocess(const Cloud::ConstPtr &cloud) const {
    Cloud::Ptr range_filtered(new Cloud);

    range_filtered->reserve(cloud->size());

    const double minimum_range_squared = minimum_range_m_ * minimum_range_m_;
    const double maximum_range_squared = maximum_range_m_ * maximum_range_m_;

    // Remove invalid points and points outside range
    for (const Point &point : cloud->points) {
        if (!pcl::isFinite(point)) {
            continue;
        }

        const double range_squared = point.x * point.x + point.y * point.y + point.z * point.z;

        if (range_squared < minimum_range_squared || range_squared > maximum_range_squared) {
            continue;
        }

        range_filtered->push_back(point);
    }
    Cloud::Ptr downsampled(new Cloud);

    pcl::VoxelGrid<Point> voxel_filter;
    voxel_filter.setInputCloud(range_filtered);
    voxel_filter.setLeafSize(voxel_size_m_, voxel_size_m_, voxel_size_m_);
    voxel_filter.filter(*downsampled);
    return downsampled;
}

LidarRegistrationResult LidarFrontend::registerClouds(
    const Cloud::ConstPtr &previous_cloud,
    const Cloud::ConstPtr &current_cloud,
    const gtsam::Pose3 &initial_base_relative_pose
) const {
    LidarRegistrationResult result;
    if (!previous_cloud || !current_cloud || previous_cloud->empty() ||
        current_cloud->empty()) {
        return result;
    }

    // Convert imu prediction from base_link to lidar frame
    const gtsam::Pose3 initial_lidar_relative_pose = 
        base_T_lidar_.inverse().compose(initial_base_relative_pose).compose(base_T_lidar_);
    
    const Eigen::Matrix4f initial_guess = initial_lidar_relative_pose.matrix().cast<float>();

    pcl::GeneralizedIterativeClosestPoint<Point, Point> gicp;

    gicp.setInputSource(current_cloud);
    gicp.setInputTarget(previous_cloud);
    gicp.setMaxCorrespondenceDistance(maximum_correspondence_distance_m_);
    gicp.setMaximumIterations(maximum_iterations_); 
    gicp.setTransformationEpsilon(transformation_epsilon_);
    gicp.setEuclideanFitnessEpsilon(fitness_epsilon_);

    Cloud aligned_cloud;

    gicp.align(aligned_cloud, initial_guess);

    result.converged = gicp.hasConverged();
    result.fitness_score = gicp.getFitnessScore();

    if (!result.converged) {
        return result;
    }

    const Eigen::Matrix4f lidar_transform = gicp.getFinalTransformation();
    const gtsam::Matrix3 rotation_matrix = lidar_transform.block<3, 3>(0, 0).cast<double>();
    const gtsam::Vector3 translation_vector = lidar_transform.block<3, 1>(0, 3).cast<double>();

    const gtsam::Pose3 lidar_relative_pose(
        gtsam::Rot3(rotation_matrix),
        translation_vector
    );

    // Convert lidar relative pose back to base_link frame
    result.relative_pose = base_T_lidar_.compose(lidar_relative_pose).compose(base_T_lidar_.inverse());
    return result;


}

} 