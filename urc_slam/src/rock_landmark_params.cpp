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
        requirePositive(params.associator.candidate_radius_m, "associator.candidate_radius_m");
        if (params.associator.candidate_radius_m <
            params.extractor.max_range_m + params.extractor.max_radius_m) {
            throw std::invalid_argument(
                "associator.candidate_radius_m must be >= extractor.max_range_m + extractor.max_radius_m");
        }
        if (!(params.associator.candidate_pose_sigma_scale >= 0.0)) {
            throw std::invalid_argument("associator.candidate_pose_sigma_scale must be >= 0");
        }
        if (!(params.associator.max_candidate_radius_m >= params.associator.candidate_radius_m)) {
            throw std::invalid_argument(
                "associator.max_candidate_radius_m must be >= associator.candidate_radius_m");
        }
        requirePositive(params.min_landmark_separation_m, "min_landmark_separation_m");
        if (!(params.min_factor_view_change_rad >= 0.0) || !(params.min_factor_travel_m >= 0.0)) {
            throw std::invalid_argument("min_factor_view_change_rad and min_factor_travel_m must be >= 0");
        }
        requirePositive(params.extractor.cluster_tolerance_m, "extractor.cluster_tolerance_m");
        requirePositive(params.extractor.ground_cell_size_m, "extractor.ground_cell_size_m");
        if (!(params.extractor.ground_max_slope >= 0.0)) {
            throw std::invalid_argument("extractor.ground_max_slope must be >= 0");
        }
        const RockExtractorParams &extractor = params.extractor;
        if (!(extractor.window_edge_margin_m >= 0.0) ||
            !(2.0 * extractor.window_edge_margin_m < extractor.max_range_m - extractor.min_range_m)) {
            throw std::invalid_argument(
                "extractor.window_edge_margin_m must be >= 0 and below half the range window");
        }
        if (!(std::abs(params.extractor.max_elevation_rad) < M_PI_2)) {
            throw std::invalid_argument("extractor.max_elevation_rad must be in (-pi/2, pi/2)");
        }

        if (params.extractor.min_points > params.extractor.max_points ||
            params.extractor.min_radius_m > params.extractor.max_radius_m ||
            params.extractor.min_range_m > params.extractor.max_range_m) {
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
