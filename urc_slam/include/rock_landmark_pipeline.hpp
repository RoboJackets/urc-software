#ifndef ROCK_LANDMARK_PIPELINE_HPP_
#define ROCK_LANDMARK_PIPELINE_HPP_

#include <cstddef>
#include <vector>

#include "landmark_manager.hpp"
#include "rock_extractor.hpp"
#include "rock_landmark_params.hpp"
#include "rock_types.hpp"

namespace urc_slam {

    // One LiDAR sweep in, landmark graph changes out:
    // RockExtractor -> LandmarkManager (association, then creation).
    // ROS-free; SlamNode only feeds it clouds and applies the result.
    class RockLandmarkPipeline {
        public:
            RockLandmarkPipeline(const RockLandmarkParams &params, LogSink log);

            // `cloud` is in the sensor frame; so are the returned rocks.
            std::vector<RockObservation> extract(const PointCloud3d &cloud) const {
                return extractor_.extract(cloud);
            }

            // `pose_index` must be a keyframe already in `isam`. The returned
            // update must be applied to iSAM2 before the next call.
            LandmarkGraphUpdate associate(
                const std::vector<RockObservation> &observations, std::size_t pose_index,
                const gtsam::ISAM2 &isam);

            std::vector<LandmarkSnapshot> snapshots(const gtsam::ISAM2 &isam) const {
                return manager_.snapshots(isam);
            }

        private:
            RockExtractor extractor_;
            LandmarkManager manager_;
    };

}

#endif
