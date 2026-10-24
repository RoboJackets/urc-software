#ifndef LOOP_CLOSURE_SCREENING_HPP_
#define LOOP_CLOSURE_SCREENING_HPP_

#include <cstddef>
#include <vector>
#include <Eigen/Core>

#include "loop_closure_params.hpp"

namespace urc_slam {

    struct KeyframePosition {
        std::size_t index = 0;
        Eigen::Vector3d position = Eigen::Vector3d::Zero();   // map frame
        // Distance travelled along the keyframe chain from keyframe 0.
        double path_length_m = 0.0;
    };

    double searchRadius(double position_sigma_m, const LoopCandidateParams &params);

    // Indices (KeyframePosition::index) of earlier keyframes worth registering
    // against `current`, nearest first, at most params.max_candidates.
    // `earlier` must not contain `current`. O(N) in the number of keyframes.
    std::vector<std::size_t> findLoopCandidates(
        const KeyframePosition &current,
        const std::vector<KeyframePosition> &earlier,
        double position_sigma_m,
        const LoopCandidateParams &params);

    struct GateResult {
        bool plausible = false;
        double distance_sq = 0.0;
    };

    // Is `correction` (a 6-vector in GTSAM Pose3 tangent order: rotation, then
    // translation) a believable size given `covariance`? Chi-square test at
    // `confidence` with 6 degrees of freedom. A covariance that is not
    // positive definite is never plausible.
    GateResult gateCorrection(
        const Eigen::Matrix<double, 6, 1> &correction,
        const Eigen::Matrix<double, 6, 6> &covariance,
        double confidence);

}

#endif
