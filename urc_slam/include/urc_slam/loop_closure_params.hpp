#ifndef LOOP_CLOSURE_PARAMS_HPP_
#define LOOP_CLOSURE_PARAMS_HPP_

#include <cstddef>

namespace urc_slam {

    struct LoopCandidateParams {
        // Search radius = base_radius_m + sigma_scale * (largest 1-sigma
        // position uncertainty of the current pose), capped at max_radius_m.
        // A drifted pose can only match places it may really be near.
        double base_radius_m = 3.0;
        double sigma_scale = 3.0;
        double max_radius_m = 25.0;
        // Earlier keyframes this recent (by index) or this close along the
        // travelled path are already tied to the current one by odometry; they
        // match trivially and say nothing about a revisit.
        std::size_t min_index_gap = 20;
        double min_path_gap_m = 20.0;
        // GICP is slow, so only the nearest few candidates are registered.
        std::size_t max_candidates = 3;
    };

    struct LoopClosureParams {
        LoopCandidateParams candidates;
        // Mean squared inlier distance after alignment, in m^2. Defaults to
        // the odometry gate, lidar_frontend.maximum_fitness_score_m2.
        double max_fitness_score = 0.5;
        // Probability mass of the chi-square (6 dof) test on the correction
        // GICP applies to the graph's own relative-pose estimate.
        double gate_confidence = 0.99;
        double huber_kernel_width = 1.345;
        // Attempt cadence, to bound GICP work in the LiDAR callback.
        std::size_t attempt_every_n_keyframes = 1;
        // After an accepted closure, wait this many keyframes before the next try.
        std::size_t cooldown_keyframes = 10;
    };

}

#endif
