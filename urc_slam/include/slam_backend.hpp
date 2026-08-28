#ifndef SLAM_BACKEND_HPP_
#define SLAM_BACKEND_HPP_

#include <memory>
#include <cstddef>
#include <gtsam/geometry/Pose3.h>
#include <gtsam/inference/Symbol.h>
#include <gtsam/nonlinear/ISAM2.h>
#include <gtsam/nonlinear/NonlinearFactorGraph.h>
#include <gtsam/nonlinear/Values.h>
#include <gtsam/linear/NoiseModel.h>
#include <gtsam/navigation/ImuFactor.h>
#include <gtsam/navigation/ImuBias.h>
#include <gtsam/navigation/PreintegrationParams.h>
#include <gtsam/navigation/NavState.h>


namespace urc_slam {

    class SlamBackend {
        public:
            // Constructor
            SlamBackend(double keyframe_translation_threshold_m,
                double keyframe_rotation_threshold_rad,
                const gtsam::Vector6 &pose_prior_sigmas,
                const gtsam::Vector3 &velocity_prior_sigmas,
                const gtsam::Vector6 &odom_sigmas,
                const gtsam::Vector6 &lidar_sigmas,
                const gtsam::Vector6 &bias_prior_sigmas,
                const gtsam::Vector6 &bias_between_sigmas
            );

            // Creates first node in the SLAM factor graph
            void initialize(const gtsam::NavState &initial_navstate,
                            const gtsam::imuBias::ConstantBias &initial_bias);

            // Whether to add a new slam state to the graph
            bool shouldCreateKeyframe(const gtsam::Pose3 &measured_pose) const;
            
            //Adds node to graph
            void addKeyframe(const gtsam::Pose3 &measured_pose);

            void addLidarFactor(
                std::size_t from_index,
                std::size_t to_index,
                const gtsam::Pose3 &relative_pose
            );
            
            // Adds a raw imu sample to the preintegrator
            // Every time an imu measurement arrives, accumulate it into
            //  a compressed IMU measurement between current and next frame
            void integrateImuMeasurement(
                const gtsam::Vector3 &measured_acc,
                const gtsam::Vector3 &measured_omega,
                double dt
            );
            
            // Returns the backend's best estimate of robot state
            gtsam::NavState latestEstimate() const;

            gtsam::Pose3 predictedRelativePose() const;
        private:
            
            // Factor graph symbols
            gtsam::Symbol poseKey(std::size_t index) const;
            gtsam::Symbol velocityKey(std::size_t index) const;
            gtsam::Symbol biasKey(std::size_t index) const;

            // Translation distance
            double translationDistance(
                const gtsam::Pose3 &a,
                const gtsam::Pose3 &b
            ) const;
            
            // Rotation Distance
            double rotationDistance(
                const gtsam::Pose3 &a,
                const gtsam::Pose3 &b
            ) const;

            gtsam::ISAM2 isam;
            gtsam::NonlinearFactorGraph new_factors;
            gtsam::Values new_values;
            gtsam::Values estimate;


            gtsam::SharedNoiseModel pose_prior_noise;
            gtsam::SharedNoiseModel velocity_prior_noise;
            gtsam::SharedNoiseModel odom_noise;
            gtsam::SharedNoiseModel lidar_noise;
            gtsam::SharedNoiseModel bias_prior_noise;
            gtsam::SharedNoiseModel bias_between_noise;

            boost::shared_ptr<gtsam::PreintegrationParams> imu_params;
            std::unique_ptr<gtsam::PreintegratedImuMeasurements> imu_preintegrator;

            


            std::size_t latest_index = 0;

            double keyframe_translation_threshold_m;
            double keyframe_rotation_threshold_rad;
            gtsam::Pose3 last_measured_pose;
            gtsam::Pose3 last_estimated_pose;
            gtsam::Vector3 last_estimated_velocity;
            gtsam::imuBias::ConstantBias last_estimated_bias;

    };


}



#endif
