#ifndef ROCK_EXTRACTOR_HPP_
#define ROCK_EXTRACTOR_HPP_

#include <vector>

#include "rock_landmark_params.hpp"
#include "rock_types.hpp"

namespace urc_slam {

    // Turns one planar scan into rock-sized clusters. Stateless between scans.
    class RockExtractor {
        public:
            explicit RockExtractor(const RockExtractorParams &params);

            std::vector<RockObservation> extract(const PlanarScan &scan) const;

            // Hook, not yet implemented: reject scans taken while the vehicle is
            // pitched or rolled enough that the scan plane hits the slope itself.
            // Such a scan returns a ground arc whose clusters look like rocks.
            // Intended inputs are IMU roll/pitch (e.g. from /imu/fused) and a
            // tolerance parameter; the caller would skip extract() when this
            // returns false. Currently always accepts.
            // TODO(AJ): implement with a roll/pitch tolerance once the IMU
            // attitude is plumbed to the landmark pipeline.
            bool scanPlaneIsUsable(double roll_rad, double pitch_rad) const;

        private:
            RockExtractorParams params_;
    };

}

#endif
