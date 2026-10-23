#ifndef ASSOCIATION_FIXTURE_HPP_
#define ASSOCIATION_FIXTURE_HPP_

#include <cmath>
#include <vector>
#include <gtsam/inference/Symbol.h>

#include "landmark_associator.hpp"
#include "rock_landmark_params.hpp"
#include "rock_types.hpp"

// Shared synthetic setup for the association tests. Everything is expressed
// directly in the associator's inputs, so no ISAM2 is involved.
namespace fixture {

    // TEST-ONLY noise. The repo defines no rock range/bearing noise
    // (see REVIEW_NOTES.md), so the tests pick values that make the geometry
    // below unambiguous. They are not a recommendation for the real robot.
    inline urc_slam::RockMeasurementNoise testNoise() {
        urc_slam::RockMeasurementNoise noise;
        noise.range_sigma_m = 0.05;
        noise.bearing_sigma_rad = 0.01;
        return noise;
    }

    inline gtsam::Key landmarkKey(std::size_t id) {
        return gtsam::Symbol('l', id).key();
    }

    // Pose at the origin whose only meaningful uncertainty is `sigma_x_m` in x.
    inline urc_slam::BasePoseEstimate poseUncertainInX(double sigma_x_m) {
        urc_slam::BasePoseEstimate pose;
        pose.covariance = gtsam::Matrix6::Zero();
        pose.covariance.diagonal() << 1e-6, 1e-6, 1e-6,    // rotation
                                      sigma_x_m * sigma_x_m, 1e-4, 1e-4;  // translation
        return pose;
    }

    inline urc_slam::LandmarkCandidate landmarkAt(std::size_t id, double x, double y) {
        urc_slam::LandmarkCandidate candidate;
        candidate.key = landmarkKey(id);
        candidate.position = gtsam::Point3(x, y, 0.0);
        candidate.covariance = gtsam::Matrix3::Identity() * 1e-4;
        candidate.recently_seen = true;
        return candidate;
    }

    inline urc_slam::RockObservation observationAt(double x, double y) {
        urc_slam::RockObservation observation;
        observation.range_m = std::hypot(x, y);
        observation.bearing_rad = std::atan2(y, x);
        observation.size_m = 0.4;
        return observation;
    }

}

#endif
