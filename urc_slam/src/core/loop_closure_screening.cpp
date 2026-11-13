#include "loop_closure_screening.hpp"

#include <algorithm>
#include <limits>
#include <utility>
#include <Eigen/Cholesky>

#include "jcbb_search.hpp"

namespace urc_slam {

    double searchRadius(double position_sigma_m, const LoopCandidateParams &params) {
        return std::min(params.max_radius_m,
                        params.base_radius_m + params.sigma_scale * position_sigma_m);
    }

    std::vector<std::size_t> findLoopCandidates(
        const KeyframePosition &current,
        const std::vector<KeyframePosition> &earlier,
        double position_sigma_m,
        const LoopCandidateParams &params
    ) {
        const double radius = searchRadius(position_sigma_m, params);

        std::vector<std::pair<double, std::size_t>> in_range;   // (distance, keyframe index)
        for (const KeyframePosition &keyframe : earlier) {
            const bool too_recent = current.index - keyframe.index < params.min_index_gap ||
                                    current.path_length_m - keyframe.path_length_m < params.min_path_gap_m;
            const double distance = (keyframe.position - current.position).norm();
            if (!too_recent && distance <= radius) {
                in_range.emplace_back(distance, keyframe.index);
            }
        }

        const std::size_t count = std::min(params.max_candidates, in_range.size());
        std::partial_sort(in_range.begin(), in_range.begin() + static_cast<std::ptrdiff_t>(count), in_range.end());

        std::vector<std::size_t> candidates;
        for (std::size_t i = 0; i < count; ++i) {
            candidates.push_back(in_range[i].second);
        }
        return candidates;
    }

    GateResult gateCorrection(
        const Eigen::Matrix<double, 6, 1> &correction,
        const Eigen::Matrix<double, 6, 6> &covariance,
        double confidence
    ) {
        GateResult result;
        result.distance_sq = std::numeric_limits<double>::infinity();

        const Eigen::LDLT<Eigen::Matrix<double, 6, 6>> factorization(covariance);
        // isPositive() accepts semi-definite matrices, and LDLT then solves with
        // a pseudo-inverse, so a singular covariance would look like distance 0.
        // Demand strictly positive pivots relative to the largest one.
        const Eigen::Matrix<double, 6, 1> pivots = factorization.vectorD();
        if (factorization.info() != Eigen::Success || !factorization.isPositive() ||
            pivots.minCoeff() <= 1e-12 * pivots.maxCoeff()) {
            return result;
        }
        result.distance_sq = correction.dot(factorization.solve(correction));
        result.plausible = result.distance_sq <= chiSquareQuantile(6, confidence);
        return result;
    }

}
