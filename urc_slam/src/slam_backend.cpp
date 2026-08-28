#include "slam_backend.hpp"

#include <cmath>
#include <stdexcept>
#include <gtsam/inference/Symbol.h>
#include <gtsam/nonlinear/ISAM2Params.h>
#include <gtsam/slam/BetweenFactor.h>
#include <gtsam/slam/PriorFactor.h>
#include <gtsam/navigation/ImuBias.h>
#include <gtsam/navigation/ImuFactor.h>
#include <gtsam/navigation/PreintegrationParams.h>

namespace urc_slam {
    
    // Constructor
    SlamBackend::SlamBackend(
        double keyframe_translation_threshold_m,
        double keyframe_rotation_threshold_rad,
        const gtsam::Vector6 &pose_prior_sigmas,
        const gtsam::Vector3 &velocity_prior_sigmas,
        const gtsam::Vector6 &odom_sigmas,
        const gtsam::Vector6 &lidar_sigmas,
        const gtsam::Vector6 &bias_prior_sigmas,
        const gtsam::Vector6 &bias_between_sigmas
    ):
        // ISAM factor graph
        isam(gtsam::ISAM2(gtsam::ISAM2Params())),
        // Prior for first measurement, wheel odom noise, lidar noise
        pose_prior_noise(gtsam::noiseModel::Diagonal::Sigmas(pose_prior_sigmas)),
        velocity_prior_noise(gtsam::noiseModel::Diagonal::Sigmas(velocity_prior_sigmas)),
        odom_noise(gtsam::noiseModel::Diagonal::Sigmas(odom_sigmas)),
        lidar_noise(gtsam::noiseModel::Diagonal::Sigmas(lidar_sigmas)),
        // Bias noises
        bias_prior_noise(gtsam::noiseModel::Diagonal::Sigmas(bias_prior_sigmas)),
        bias_between_noise(gtsam::noiseModel::Diagonal::Sigmas(bias_between_sigmas)),
        // Latest index
        latest_index(0),
        // for shouldCreateKeyframe
        keyframe_translation_threshold_m(
            keyframe_translation_threshold_m
        ),
        keyframe_rotation_threshold_rad(
            keyframe_rotation_threshold_rad
        )
    {
        // IMU covariance and gravity params
        imu_params = gtsam::PreintegrationParams::MakeSharedU(9.81);
        imu_params->accelerometerCovariance = gtsam::I_3x3 * std::pow(0.1, 2);
        imu_params->gyroscopeCovariance = gtsam::I_3x3 * std::pow(0.01, 2);
        imu_params->integrationCovariance = gtsam::I_3x3 * 1e-8;
        
    }


    void SlamBackend::initialize(
        const gtsam::NavState &initial_navstate,
        const gtsam::imuBias::ConstantBias &initial_bias
    ) {
        // Add prior factor with initial navstate and prior noise
        new_factors.add(
            gtsam::PriorFactor<gtsam::Pose3>(
                poseKey(0),
                initial_navstate.pose(),
                pose_prior_noise
            )
        );

        new_factors.add(
            gtsam::PriorFactor<gtsam::Vector3>(
                velocityKey(0),
                initial_navstate.v(),
                velocity_prior_noise
            )
        );
        // Add initial bias to the graph
        new_factors.add(
            gtsam::PriorFactor<
                gtsam::imuBias::ConstantBias>(
                    biasKey(0),
                    initial_bias,
                    bias_prior_noise
                )
        );

        // Add prior values to graph
        new_values.insert(poseKey(0), initial_navstate.pose());
        new_values.insert(velocityKey(0), initial_navstate.v());
        new_values.insert(biasKey(0), initial_bias);

        isam.update(new_factors, new_values);
        estimate = isam.calculateEstimate();

        // Empty out the new factors and new values
        new_factors.resize(0);
        new_values.clear();


        latest_index = 0;
        last_measured_pose = initial_navstate.pose();

        last_estimated_pose = estimate.at<gtsam::Pose3>(poseKey(0));
        last_estimated_velocity = estimate.at<gtsam::Vector3>(velocityKey(0));
        last_estimated_bias = estimate.at<gtsam::imuBias::ConstantBias>(biasKey(0));

        imu_preintegrator = std::make_unique<gtsam::PreintegratedImuMeasurements>(
            imu_params,
            last_estimated_bias
        );

    }

    bool SlamBackend::shouldCreateKeyframe(const gtsam::Pose3 &measured_pose) const {
        // Check if current measurements exceed thresholds
        return translationDistance(
                last_measured_pose,
                measured_pose
            ) >= keyframe_translation_threshold_m
            || 
            rotationDistance(
                last_measured_pose,
                measured_pose
            ) >= keyframe_rotation_threshold_rad;
    }

    gtsam::Pose3 SlamBackend::predictedRelativePose() const {
        const gtsam::NavState previous_state(
            last_estimated_pose,
            last_estimated_velocity
        );

        const gtsam::NavState predicted_state = imu_preintegrator->predict(
            previous_state,
            last_estimated_bias
        );

        return last_estimated_pose.between(
            predicted_state.pose()
        );
    }

    void SlamBackend::addKeyframe(const gtsam::Pose3 &measured_pose) {

        const std::size_t previous_index = latest_index;
        const std::size_t new_index = previous_index + 1;

        // Reconstruct previous state for IMU prediction
        const gtsam::NavState previous_state(
            last_estimated_pose,
            last_estimated_velocity
        );

        const gtsam::NavState predicted_state = 
            imu_preintegrator->predict(
                previous_state,
                last_estimated_bias
            );
        
        // Preintegrated IMU constraint on pose and velocity
        new_factors.add(
            gtsam::ImuFactor(
                poseKey(previous_index),
                velocityKey(previous_index),
                poseKey(new_index),
                velocityKey(new_index),
                biasKey(previous_index),
                *imu_preintegrator
            )
        );

        // Model IMU bias as slowly changing between keyframes
        new_factors.add(
            gtsam::BetweenFactor<gtsam::imuBias::ConstantBias>(
                biasKey(previous_index),
                biasKey(new_index),
                gtsam::imuBias::ConstantBias(),
                bias_between_noise
            )
        );

        // Predicted pose and velocity
        new_values.insert(
            poseKey(new_index),
            predicted_state.pose()
        );

        new_values.insert(
            velocityKey(new_index),
            predicted_state.v()
        );

        new_values.insert(
            biasKey(new_index),
            last_estimated_bias
        );

        

        latest_index = new_index;
        last_measured_pose = measured_pose;

        
        imu_preintegrator->resetIntegrationAndSetBias(
            last_estimated_bias
        );

    }

    void SlamBackend::addLidarFactor(
        std::size_t from_index,
        std::size_t to_index,
        const gtsam::Pose3 &relative_pose
    ) {
        // Constrain keyframe motion using ICP
        new_factors.add(
            gtsam::BetweenFactor<gtsam::Pose3>(
                poseKey(from_index),
                poseKey(to_index),
                relative_pose,
                lidar_noise
            )
        );

        isam.update(new_factors, new_values);
        estimate = isam.calculateEstimate();

        new_factors.resize(0);
        new_values.clear();

        last_estimated_pose = estimate.at<gtsam::Pose3>(
            poseKey(latest_index)
        );

        last_estimated_velocity = estimate.at<gtsam::Vector3>(
            velocityKey(latest_index)
        );

        last_estimated_bias =
            estimate.at<gtsam::imuBias::ConstantBias>(
                biasKey(latest_index)
        );
    }

    // Integrate IMU measurement
    void SlamBackend::integrateImuMeasurement(
        const gtsam::Vector3 &measured_acc,
        const gtsam::Vector3 &measured_omega,
        double dt
    ) {
        imu_preintegrator->integrateMeasurement(
            measured_acc,
            measured_omega,
            dt
        );
    }

    
    gtsam::NavState SlamBackend::latestEstimate() const {
        const gtsam::Pose3 pose = estimate.at<gtsam::Pose3>(
            poseKey(latest_index)
        );

        const gtsam::Vector3 velocity = estimate.at<gtsam::Vector3>(
            velocityKey(latest_index)
        );

        return gtsam::NavState(pose,velocity);
    }

    gtsam::Symbol SlamBackend::poseKey(std::size_t index) const {
        return gtsam::Symbol('x', index);
    }

    gtsam::Symbol SlamBackend::velocityKey(std::size_t index) const {
        return gtsam::Symbol('v', index);
    }

    gtsam::Symbol SlamBackend::biasKey(std::size_t index) const {
        return gtsam::Symbol('b', index);
    }

    double SlamBackend::translationDistance(const gtsam::Pose3 &a, 
        const gtsam::Pose3 &b
    ) const {
        return (a.translation() - b.translation()).norm();
    }

    double SlamBackend::rotationDistance(
        const gtsam::Pose3 &a,
        const gtsam::Pose3 &b
    ) const {
        return a.rotation().between(b.rotation()).rpy().norm();
    }
}