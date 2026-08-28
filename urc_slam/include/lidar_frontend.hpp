#ifndef LIDAR_FRONTEND_HPP_
#define LIDAR_FRONTEND_HPP_

#include <limits>

#include <gtsam/geometry/Pose3.h>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>

namespace urc_slam {

    struct LidarRegistrationResult {
        bool converged = false;
        double fitness_score = std::numeric_limits<double>::infinity();
        gtsam::Pose3 relative_pose;
    };

    class LidarFrontend {
        public:
            using Point = pcl::PointXYZ;
            using Cloud = pcl::PointCloud<Point>;

            LidarFrontend(
                double voxel_size_m,
                double minimum_range_m,
                double maximum_range_m,
                double maximum_correspondence_distance_m,
                int maximum_iterations,
                double transformation_epsilon,
                double fitness_epsilon,
                const gtsam::Pose3 &base_T_lidar
            );

            Cloud::Ptr preprocess(
                const Cloud::ConstPtr &cloud
            ) const;

            LidarRegistrationResult registerClouds(
                const Cloud::ConstPtr &previous_cloud,
                const Cloud::ConstPtr &current_cloud,
                const gtsam::Pose3 &initial_base_relative_pose
            ) const;
        private:
            double voxel_size_m_;
            double minimum_range_m_;
            double maximum_range_m_;
            double maximum_correspondence_distance_m_;
            int maximum_iterations_;
            double transformation_epsilon_;
            double fitness_epsilon_;

            // Convert between base link and Lidar frame
            gtsam::Pose3 base_T_lidar_;
    };


} 
#endif