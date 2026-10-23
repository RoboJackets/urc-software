#ifndef ROCK_EXTRACTOR_HPP_
#define ROCK_EXTRACTOR_HPP_

#include <vector>

#include "rock_extractor_params.hpp"
#include "rock_types.hpp"

namespace urc_slam {

    // Finds rocks in one 3D sweep: ground removal -> Euclidean clustering ->
    // size filtering -> sphere fit for the centre. Stateless between sweeps.
    class RockExtractor {
        public:
            explicit RockExtractor(const RockExtractorParams &params);

            // `cloud` is in the sensor frame with +z roughly up; see
            // attitudeIsUsable().
            std::vector<RockObservation> extract(const PointCloud3d &cloud) const;

            // Hook, not yet implemented: reject sweeps taken while the vehicle is
            // pitched or rolled far enough that the sensor z axis no longer points
            // roughly up, which breaks the grid ground model in removeGround().
            // A better fix than rejecting is rotating the cloud into a
            // gravity-aligned frame using IMU roll/pitch (e.g. /imu/fused) before
            // extract(). Currently always accepts.
            // TODO(AJ): implement with a roll/pitch tolerance once IMU attitude
            // is plumbed to the landmark pipeline.
            bool attitudeIsUsable(double roll_rad, double pitch_rad) const;

        private:
            RockExtractorParams params_;
    };

}

#endif
