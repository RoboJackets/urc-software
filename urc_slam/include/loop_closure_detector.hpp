#ifndef LOOP_CLOSURE_DETECTOR_HPP_
#define LOOP_CLOSURE_DETECTOR_HPP_

#include <cstddef>
#include <optional>
#include <string>
#include <vector>
#include <gtsam/geometry/Pose3.h>

#include "landmark_manager.hpp"
#include "lidar_frontend.hpp"
#include "loop_closure_params.hpp"
#include "slam_backend.hpp"

namespace urc_slam {

    struct LoopClosure {
        std::size_t earlier_index = 0;
        // Pose of the current keyframe expressed in the earlier keyframe's frame
        // (the measurement of BetweenFactor(x(earlier), x(current))).
        gtsam::Pose3 relative_pose;
        double fitness_score = 0.0;
        // Squared Mahalanobis size of GICP's correction to the graph's estimate.
        double correction_distance_sq = 0.0;
        double huber_kernel_width = 0.0;
    };

    // Looks for a revisit of earlier terrain: picks nearby earlier keyframes
    // (radius scaled by pose uncertainty), registers their clouds with GICP,
    // and accepts the best match only if it fits well AND agrees with what the
    // other sensors already told the graph. Does not modify the graph.
    class LoopClosureDetector {
        public:
            LoopClosureDetector(
                const LoopClosureParams &params, const LidarFrontend &frontend, LogSink log);

            // `clouds[k]` is keyframe k's cloud in its own frame. The current
            // keyframe must already be optimized into `backend`.
            std::optional<LoopClosure> detect(
                std::size_t current_index,
                const std::vector<LidarFrontend::Cloud::ConstPtr> &clouds,
                const SlamBackend &backend);

        private:
            bool shouldAttempt(std::size_t current_index) const;

            std::optional<LoopClosure> evaluateCandidate(
                std::size_t earlier_index,
                std::size_t current_index,
                const std::vector<LidarFrontend::Cloud::ConstPtr> &clouds,
                const SlamBackend &backend) const;

            void log(const std::string &message) const;

            LoopClosureParams params_;
            const LidarFrontend &frontend_;
            LogSink log_;
            std::optional<std::size_t> last_closure_index_;
    };

}

#endif
