#ifndef SLAM_BACKEND_HPP_
#define SLAM_BACKEND_HPP_

#include <cstddef>
#include <gtsam/geometry/Pose3.h>
#include <gtsam/inference/Symbol.h>
#include <gtsam/nonlinear/ISAM2.h>
#include <gtsam/nonlinear/NonlinearFactorGraph.h>
#include <gtsam/nonlinear/Values.h>
#include <gtsam/noiseModel/Diagonal.h>


namespace urc_slam {

    class SlamBackend {
        public:
            SlamBackend(double keyframe_translation_threshold_m,
                double keyframe_rotation_threshold_rad,
                const gtsam::Vector6 &prior_sigmas,
                const gtsam::Vector6 &odom_sigmas,
                const gtsam::Vector6 &lidar_sigmas);

            void initialize(const gtsam::Pose3 &initial_pose);
            
            bool shouldCreateKeyframe(const gtsam::Pose3 &measured_pose) const;
            
            void addKeyframe(const gtsam::Pose3 &measured_pose);

            void addLidarFactor(
                std::size_t from_index,
                std::size_t to_index,
                const gtsam::Pose3 &relative_pose
            );

            gtsam::Pose3 latestEstimate() const;
        private:
            gtsam::Symbol poseKey(std::size_t index) const;

            double translationDistance(
                const gtsam::Pose3 &a,
                const gtsam::Pose3 &b
            ) const;

            double rotationDistance(
                const gtsam::Pose3 &a,
                const gtsam::Pose3 &b
            ) const;

            gtsam::ISAM2 isam;
            gtsam::NonlinearFactorGraph new_factors;
            gtsam::Values new_values;
            gtsam::Values estimate;

            gtsam::SharedNoiseModel prior_noise;
            gtsam::SharedNoiseModel odom_noise;
            gtsam::SharedNoiseModel lidar_noise;

            std::size_t latest_index = 0;

            double keyframe_translation_threshold_m;
            double keyframe_rotation_threshold_rad;

            gtsam::Pose3 last_measured_pose;
            gtsam::Pose3 last_estimated_pose;

    };


}



#endif
