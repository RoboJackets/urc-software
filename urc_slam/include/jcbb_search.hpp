#ifndef JCBB_SEARCH_HPP_
#define JCBB_SEARCH_HPP_

#include <cstddef>
#include <optional>
#include <utility>
#include <vector>
#include <Eigen/Core>

namespace urc_slam {

    // Upper-tail chi-square quantile: the value that a chi-square variable with
    // `dof` degrees of freedom stays below with probability `probability`.
    // Wilson-Hilferty approximation (error well under 1% for dof >= 2).
    double chiSquareQuantile(std::size_t dof, double probability);

    // Everything JCBB needs to know about pairing observation i with candidate j.
    // Observations and candidates are identified by index only, so the search
    // knows nothing about GTSAM, keys, or frames.
    struct PairTerm {
        bool individually_compatible = false;
        // Observed minus predicted rock centre (3D, sensor frame).
        Eigen::Vector3d innovation = Eigen::Vector3d::Zero();
        // d(predicted observation)/d(pose) and d(predicted observation)/d(landmark).
        // Together with the joint state covariance they couple the innovations
        // of different pairings through the shared pose and correlated landmarks.
        Eigen::Matrix<double, 3, 6> pose_jacobian = Eigen::Matrix<double, 3, 6>::Zero();
        Eigen::Matrix3d landmark_jacobian = Eigen::Matrix3d::Zero();
        // Measurement noise, independent between pairings.
        Eigen::Matrix3d measurement_covariance = Eigen::Matrix3d::Identity();
    };

    struct JcbbProblem {
        std::size_t num_observations = 0;
        std::size_t num_candidates = 0;
        // Joint covariance of [pose (6), candidate 0 (3), candidate 1 (3), ...],
        // so it is (6 + 3 * num_candidates) square, cross terms included.
        Eigen::MatrixXd state_covariance;
        // Row-major [observation * num_candidates + candidate].
        std::vector<PairTerm> terms;
        double gate_confidence = 0.99;
        double ambiguity_margin = 2.0;
        std::size_t max_search_nodes = 20000;
    };

    struct JcbbHypothesis {
        // assignment[i] = candidate index for observation i, or -1 for "none".
        std::vector<int> assignment;
        std::size_t num_pairings = 0;
        // Joint squared Mahalanobis distance of all pairings.
        double joint_distance_sq = 0.0;
    };

    struct JcbbResult {
        std::optional<JcbbHypothesis> best;
        // Best hypothesis with the same pairing count as `best` but a different
        // assignment, if any exists.
        std::optional<JcbbHypothesis> runner_up;
        bool budget_exhausted = false;

        bool isAmbiguous(double margin) const {
            return runner_up.has_value() && best.has_value() &&
                   runner_up->joint_distance_sq - best->joint_distance_sq < margin;
        }
    };

    // Joint Compatibility Branch and Bound (Neira & Tardos, IEEE T-RA 2001).
    // Finds the largest jointly compatible set of pairings; among equally large
    // sets prefers the smallest joint Mahalanobis distance.
    JcbbResult runJcbb(const JcbbProblem &problem);

    // Joint squared Mahalanobis distance of the given (observation, candidate)
    // pairings, or nullopt if they are not jointly compatible at the problem's
    // gate confidence. Exposed so tests can inspect individual hypotheses.
    std::optional<double> jointDistanceSq(
        const JcbbProblem &problem,
        const std::vector<std::pair<std::size_t, std::size_t>> &pairings
    );

}

#endif
