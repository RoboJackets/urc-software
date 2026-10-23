#ifndef ROCK_LANDMARK_PARAMS_HPP_
#define ROCK_LANDMARK_PARAMS_HPP_

#include <cstddef>
#include <limits>
#include <gtsam/geometry/Pose3.h>

namespace urc_slam {

    struct RockExtractorParams {
        // Consecutive beams whose ranges differ by more than this start a new
        // cluster. Too small splits one rock in two; too large merges rock + wall.
        double cluster_range_jump_m = 0.3;
        std::size_t min_points = 3;
        std::size_t max_points = 100;
        // Extent = 2 * largest distance from the cluster centroid.
        double min_extent_m = 0.1;
        double max_extent_m = 1.5;
    };

    // Noise of a rock observation expressed as range/bearing of the EXTRACTED
    // centroid. The repo defines no such value (its lidar_sigmas describe the
    // ICP relative pose), so these start unset and validate() rejects NaN.
    struct RockMeasurementNoise {
        // TODO(AJ): set from repo/measurement
        double range_sigma_m = std::numeric_limits<double>::quiet_NaN();
        // TODO(AJ): set from repo/measurement
        double bearing_sigma_rad = std::numeric_limits<double>::quiet_NaN();
    };

    struct AssociatorParams {
        // Probability mass inside the Mahalanobis gate, for both the
        // individual gate and the joint (JCBB) gate.
        double gate_confidence = 0.99;
        // A landmark last seen more than this many pose indices ago needs
        // min_pairings_for_reassociation jointly compatible pairings.
        std::size_t recently_seen_window_poses = 10;
        std::size_t min_pairings_for_reassociation = 2;
        // Best and runner-up joint hypotheses of equal size closer than this
        // (in joint squared Mahalanobis distance) are declared ambiguous.
        double ambiguity_margin = 2.0;
        // Bounds the exponential worst case of the JCBB tree search.
        std::size_t max_search_nodes = 20000;
    };

    struct RockLandmarkParams {
        RockExtractorParams extractor;
        RockMeasurementNoise noise;
        AssociatorParams associator;
        // Huber threshold in units of whitened residual (sigmas). 1.345 is the
        // textbook 95%-efficiency value for Gaussian noise.
        double huber_kernel_width = 1.345;
        // Same identity placeholder as SlamNode::addKeyframeToMap.
        gtsam::Pose3 base_T_sensor;
    };

    // Throws std::invalid_argument naming the offending parameter.
    void validate(const RockLandmarkParams &params);

}

#endif
