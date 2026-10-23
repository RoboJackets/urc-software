#include "rock_landmark_pipeline.hpp"

#include <utility>

namespace urc_slam {

    RockLandmarkPipeline::RockLandmarkPipeline(const RockLandmarkParams &params, LogSink log)
        : extractor_(params.extractor), manager_(params, std::move(log)) {}

    LandmarkGraphUpdate RockLandmarkPipeline::processSweep(
        const PointCloud3d &cloud, std::size_t pose_index, const gtsam::ISAM2 &isam
    ) {
        return manager_.processScan(extractor_.extract(cloud), pose_index, isam);
    }

}
