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
            SlamBackend(double keyframe_translation_threshold_m,
                double keyframe_rotation_threshold_rad,
                const gtsam::Vector6 &pose_prior_sigmas,
                const gtsam::Vector3 &velocity_prior_sigmas,
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
            void addImuKeyframe();

            void addLidarFactor(
                std::size_t from_index,
                std::size_t to_index,
                const gtsam::Pose3 &relative_pose
            );

            void addGpsFactor(
                std::size_t index,
                const gtsam::Point3 &position,
                const gtsam::Matrix3 &covariance
            );
            
            // Wheel odometry motion between two existing keyframes.
            // Pose delta is previous-body-to-next-body; velocity delta is
            // next minus previous in the same frame as the graph velocities.
            // `noise` must be 6-dimensional, in Pose3 tangent order
            // (roll, pitch, yaw, x, y, z).
            void addOdometryPoseFactor(
                std::size_t previous_index,
                std::size_t post_index,
                const gtsam::Pose3 &pose_change,
                const gtsam::SharedNoiseModel &noise
            );

            // `noise` must be 3-dimensional (vx, vy, vz).
            void addOdometryVelocityFactor(
                std::size_t previous_index,
                std::size_t post_index,
                const gtsam::Vector3 &velocity_change,
                const gtsam::SharedNoiseModel &noise
            );

            // 6-dimensional, Pose3 tangent order (roll, pitch, yaw, x, y, z).
            const gtsam::SharedNoiseModel &lidarNoise() const { return lidar_noise; }

            // Adds a raw imu sample to the preintegrator
            // Every time an imu measurement arrives, accumulate it into
            //  a compressed IMU measurement between current and next frame
            // Accumulates one IMU sample into the preintegrated measurement
            // since the last keyframe
            void integrateImuMeasurement(
                const gtsam::Vector3 &measured_acc,
                const gtsam::Vector3 &measured_omega,
                double dt
            );
            
            // Returns the backend's best estimate of robot state
            gtsam::NavState latestEstimate() const;
            gtsam::Pose3 poseAt(std::size_t index) const;

            gtsam::Pose3 predictedRelativePose() const;

            // Read-only view for landmark association, which needs pose and
            // landmark marginal covariances that only iSAM2 can provide.
            const gtsam::ISAM2 &isamGraph() const { return isam; }

            // Constrains two existing keyframes by a registration between their
            // clouds, using the same noise as consecutive-keyframe ICP but wrapped
            // in a Huber kernel: a loop closure that is wrong warps the whole
            // trajectory, so it must not be trusted as hard as a sequential one.
            void addLoopClosureFactor(
                std::size_t earlier_index,
                std::size_t current_index,
                const gtsam::Pose3 &relative_pose,
                double huber_kernel_width
            );

            // Merges landmark factors/values (see LandmarkManager) into the
            // graph and optimizes. The referenced pose must already be in iSAM2.
            void addLandmarkUpdate(
                const gtsam::NonlinearFactorGraph &factors,
                const gtsam::Values &values
            );
        
            void optimize();
        private:

            // Factor graph symbols
            gtsam::Symbol poseKey(std::size_t index) const;
            gtsam::Symbol velocityKey(std::size_t index) const;
            gtsam::Symbol biasKey(std::size_t index) const;

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


            gtsam::SharedNoiseModel pose_prior_noise;
            gtsam::SharedNoiseModel velocity_prior_noise;
            gtsam::SharedNoiseModel lidar_noise;
            gtsam::SharedNoiseModel bias_prior_noise;
            gtsam::SharedNoiseModel bias_between_noise;

            boost::shared_ptr<gtsam::PreintegrationParams> imu_params;
            std::unique_ptr<gtsam::PreintegratedImuMeasurements> imu_preintegrator;

            


            std::size_t latest_index = 0;

            double keyframe_translation_threshold_m;
            double keyframe_rotation_threshold_rad;
            gtsam::Pose3 last_estimated_pose;
            gtsam::Vector3 last_estimated_velocity;
            gtsam::imuBias::ConstantBias last_estimated_bias;

    };


}



#endif
