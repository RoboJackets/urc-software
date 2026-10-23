#include "rock_landmark_params.hpp"

#include <cmath>
#include <stdexcept>
#include <string>

namespace urc_slam {

    namespace {

        void requirePositive(double value, const std::string &name) {
            // !(value > 0) also rejects NaN, which is how "unset" noise is caught.
            if (!(value > 0.0)) {
                throw std::invalid_argument(name + " must be set to a positive value");
            }
        }

    }

    void validate(const RockLandmarkParams &params) {
        requirePositive(params.noise.range_sigma_m, "noise.range_sigma_m");
        requirePositive(params.noise.bearing_sigma_rad, "noise.bearing_sigma_rad");
        requirePositive(params.huber_kernel_width, "huber_kernel_width");
        requirePositive(params.extractor.cluster_range_jump_m, "extractor.cluster_range_jump_m");

        if (params.extractor.min_points > params.extractor.max_points ||
            params.extractor.min_extent_m > params.extractor.max_extent_m) {
            throw std::invalid_argument("extractor min bounds exceed max bounds");
        }

        const double confidence = params.associator.gate_confidence;
        if (!(confidence > 0.0 && confidence < 1.0)) {
            throw std::invalid_argument("associator.gate_confidence must be in (0, 1)");
        }
        if (params.associator.min_pairings_for_reassociation < 1) {
            throw std::invalid_argument("associator.min_pairings_for_reassociation must be >= 1");
        }
    }

}
