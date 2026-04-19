#include "slam_backend.hpp"

#include <cmath>
#include <utility>

#include <gtsam/inference/Symbol.h>
#include <gtsam/nonlinear/ISAM2Params.h>
#include <gtsam/slam/BetweenFactor.h>
#include <gtsam/slam/PriorFactor.h>

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
        latest_index(0),
        keyframe_translation_threshold_m(keyframe_translation_threshold_m),
        keyframe_rotation_threshold_rad(keyframe_rotation_threshold_rad)
    {

    }

    void SlamBackend::initialize(const gtsam::Pose3 &initial_pose) {
        new_factors.add(
            gtsam::PriorFactor<gtsam::Pose3>(poseKey(0), initial_pose, prior_noise)
        );
        new_values.insert(poseKey(0), initial_pose);

        isam.update(new_factors, new_values);
        estimate = isam.calculateEstimate();
        
        new_factors.resize(0);
        new_values.clear();

        latest_index = 0;
        last_measured_pose = initial_pose;
        last_estimated_pose = estimate.at<gtsam::Pose3>(poseKey(0));

    }

    bool SlamBackend::shouldCreateKeyframe(const gtsam::Pose3 &measured_pose) const {
        return translationDistance(last_measured_pose, measured_pose) >= keyframe_translation_threshold_m 
        || rotationDistance(last_measured_pose, measured_pose) >= keyframe_rotation_threshold_rad;
    }

    void SlamBackend::addKeyframe(const gtsam::Pose3 &measured_pose) {
        const std::size_t new_index = latest_index + 1;
        const gtsam::Pose3 delta = last_measured_pose.between(measured_pose);
        const gtsam::Pose3 predicted_pose = last_estimated_pose.compose(delta);

        new_factors.add(
            gtsam::BetweenFactor<gtsam::Pose3>(
                poseKey(latest_index),
                poseKey(new_index),
                delta,
                odom_noise
            )
        );

        new_values.insert(poseKey(new_index), predicted_pose);

        isam.update(new_factors, new_values);
        estimate = isam.calculateEstimate();

        new_factors.resize(0);
        new_values.clear();

        latest_index = new_index;
        last_measured_pose = measured_pose;
        // Figure ts syntax out later
        last_estimated_pose = estimate.at<gtsam::Pose3>(poseKey(latest_index));
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

        last_estimated_pose = estimate.at<gtsam::Pose3>(poseKey(latest_index));
    }

    gtsam::Pose3 SlamBackend::latestEstimate() const {
        return estimate.at<gtsam::Pose3>(poseKey(latest_index));
    }

    gtsam::Symbol SlamBackend::poseKey(std::size_t index) const {
        return gtsam::Symbol('x', index);
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
