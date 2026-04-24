#include "slam_backend.hpp"

#include <cmath>
#include <utility>

#include <gtsam/inference/Symbol.h>
#include <gtsam/navigation/CombinedImuFactor.h>
#include <gtsam/nonlinear/ISAM2Params.h>
#include <gtsam/noiseModel/Isotropic.h>
#include <gtsam/slam/BetweenFactor.h>
#include <gtsam/slam/PriorFactor.h>
#include <gtsam/navigation/ImuBias.h>
#include <gtsam/navigation/PreintegrationCombinedParams.h>

namespace urc_slam {

    SlamBackend::SlamBackend(
        double keyframe_translation_threshold_m,
        double keyframe_rotation_threshold_rad,
        const gtsam::Vector6 &prior_sigmas,
        const gtsam::Vector6 &odom_sigmas,
        const gtsam::Vector6 &lidar_sigmas)
        : isam(gtsam::ISAM2(gtsam::ISAM2Params())),
        prior_noise(gtsam::noiseModel::Diagonal::Sigmas(prior_sigmas)),
        odom_noise(gtsam::noiseModel::Diagonal::Sigmas(odom_sigmas)),
        lidar_noise(gtsam::noiseModel::Diagonal::Sigmas(lidar_sigmas)),
        velocity_prior_noise(gtsam::noiseModel::Isotropic::Sigma(3, 1.0)),
        bias_prior_noise(gtsam::noiseModel::Isotropic::Sigma(6, 1e-3)),
        latest_index(0),
        keyframe_translation_threshold_m(keyframe_translation_threshold_m),
        keyframe_rotation_threshold_rad(keyframe_rotation_threshold_rad)
    {
        imu_params = gtsam::PreintegrationCombinedParams::MakeSharedU(9.81);
        imu_params->accelerometerCovariance = gtsam::I_3x3 * std::pow(0.1, 2);
        imu_params->gyroscopeCovariance = gtsam::I_3x3 * std::pow(0.01, 2);
        imu_params->integrationCovariance = gtsam::I_3x3 * 1e-8;
        imu_params->biasAccCovariance = gtsam::I_3x3 * std::pow(0.0001, 2);
        imu_params->biasOmegaCovariance = gtsam::I_3x3 * std::pow(0.0001, 2);
        imu_params->biasAccOmegaInt = gtsam::I_6x6 * 1e-5;
    }

    void SlamBackend::initialize(const gtsam::Pose3 &initial_pose) {
        const gtsam::Vector3 initial_velocity(0.0, 0.0, 0.0);
        const gtsam::imuBias::ConstantBias initial_bias;

        new_factors.add(
            gtsam::PriorFactor<gtsam::Pose3>(poseKey(0), initial_pose, prior_noise)
        );
        new_factors.add(
            gtsam::PriorFactor<gtsam::Vector3>(velocityKey(0), initial_velocity, velocity_prior_noise)
        );
        new_factors.add(
            gtsam::PriorFactor<gtsam::imuBias::ConstantBias>(biasKey(0), initial_bias, bias_prior_noise)
        );
        new_values.insert(poseKey(0), initial_pose);
        new_values.insert(velocityKey(0), initial_velocity);
        new_values.insert(biasKey(0), initial_bias);

        isam.update(new_factors, new_values);
        estimate = isam.calculateEstimate();
        
        new_factors.resize(0);
        new_values.clear();

        latest_index = 0;
        last_measured_pose = initial_pose;
        last_estimated_navstate = gtsam::NavState(
            estimate.at<gtsam::Pose3>(poseKey(0)),
            estimate.at<gtsam::Vector3>(velocityKey(0))
        );
        last_estimated_bias = estimate.at<gtsam::imuBias::ConstantBias>(biasKey(0));
        imu_preintegrator = std::make_unique<gtsam::PreintegratedCombinedMeasurements>(
            imu_params, last_estimated_bias
        );

    }

    bool SlamBackend::shouldCreateKeyframe(const gtsam::Pose3 &measured_pose) const {
        return translationDistance(last_measured_pose, measured_pose) >= keyframe_translation_threshold_m 
        || rotationDistance(last_measured_pose, measured_pose) >= keyframe_rotation_threshold_rad;
    }

    void SlamBackend::addKeyframe(const gtsam::Pose3 &measured_pose) {
        const std::size_t new_index = latest_index + 1;
        const gtsam::Pose3 delta = last_measured_pose.between(measured_pose);
        const gtsam::Pose3 predicted_pose = last_estimated_navstate.pose().compose(delta);

        new_factors.add(
            gtsam::BetweenFactor<gtsam::Pose3>(
                poseKey(latest_index),
                poseKey(new_index),
                delta,
                odom_noise
            )
        );
        new_factors.add(
            gtsam::CombinedImuFactor(
                poseKey(latest_index),
                velocityKey(latest_index),
                poseKey(new_index),
                velocityKey(new_index),
                biasKey(latest_index),
                biasKey(new_index),
                *imu_preintegrator
            )
        );

        new_values.insert(poseKey(new_index), predicted_pose);
        new_values.insert(velocityKey(new_index), last_estimated_navstate.v());
        new_values.insert(biasKey(new_index), last_estimated_bias);
        isam.update(new_factors, new_values);
        estimate = isam.calculateEstimate();

        new_factors.resize(0);
        new_values.clear();

        latest_index = new_index;
        last_measured_pose = measured_pose;
        last_estimated_navstate = gtsam::NavState(
            estimate.at<gtsam::Pose3>(poseKey(latest_index)),
            estimate.at<gtsam::Vector3>(velocityKey(latest_index))
        );
        last_estimated_bias = estimate.at<gtsam::imuBias::ConstantBias>(biasKey(latest_index));
        imu_preintegrator = std::make_unique<gtsam::PreintegratedCombinedMeasurements>(
            imu_params, last_estimated_bias
        );
    }

    void SlamBackend::addLidarFactor(
        std::size_t from_index,
        std::size_t to_index,
        const gtsam::Pose3 &relative_pose
    ) {
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

        last_estimated_navstate = gtsam::NavState(
            estimate.at<gtsam::Pose3>(poseKey(latest_index)),
            estimate.at<gtsam::Vector3>(velocityKey(latest_index))
        );
        last_estimated_bias = estimate.at<gtsam::imuBias::ConstantBias>(biasKey(latest_index));
    }


    void SlamBackend::integrateImuMeasurement(
        const gtsam::Vector3 &measured_acc,
        const gtsam::Vector3 &measured_omega,
        double dt
    ) {
        imu_preintegrator->integrateMeasurement(measured_acc, measured_omega, dt);
    }

    gtsam::Pose3 SlamBackend::latestEstimate() const {
        return estimate.at<gtsam::Pose3>(poseKey(latest_index));
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

    double SlamBackend::translationDistance(
        const gtsam::Pose3 &a,
        const gtsam::Pose3 &b
    ) const {
        return a.translation().distance(b.translation());
    }

    double SlamBackend::rotationDistance(
        const gtsam::Pose3 &a,
        const gtsam::Pose3 &b
    ) const {
        return a.rotation().between(b.rotation()).rpy().norm();
    }

} // namespace urc_slam
