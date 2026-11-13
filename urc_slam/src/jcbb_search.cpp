#include "jcbb_search.hpp"

#include <cmath>
#include <Eigen/Cholesky>

namespace urc_slam {

    namespace {

        // Standard normal quantile, Abramowitz & Stegun 26.2.23 (|error| < 4.5e-4).
        // Valid for 0.5 < probability < 1, which is all the gate ever needs.
        double normalQuantile(double probability) {
            const double t = std::sqrt(-2.0 * std::log(1.0 - probability));
            const double numerator = 2.515517 + t * (0.802853 + t * 0.010328);
            const double denominator = 1.0 + t * (1.432788 + t * (0.189269 + t * 0.001308));
            return t - numerator / denominator;
        }

        class JcbbSearch {
            public:
                explicit JcbbSearch(const JcbbProblem &problem)
                    : problem_(problem),
                      assignment_(problem.num_observations, -1),
                      candidate_used_(problem.num_candidates, false) {}

                JcbbResult run() {
                    descend(0);
                    result_.budget_exhausted = nodes_visited_ > problem_.max_search_nodes;
                    return result_;
                }

            private:
                const PairTerm &term(std::size_t observation, std::size_t candidate) const {
                    return problem_.terms[observation * problem_.num_candidates + candidate];
                }

                void descend(std::size_t observation) {
                    if (++nodes_visited_ > problem_.max_search_nodes) {
                        return;
                    }
                    if (observation == problem_.num_observations) {
                        recordLeaf();
                        return;
                    }


                    //for each possible landmark to associate to 
                    for (std::size_t candidate = 0; candidate < problem_.num_candidates; ++candidate) {
                        //have you already been to that canditate or the obverstaion or landmark are not invidually comptabile skip
                        if (candidate_used_[candidate] ||
                            !term(observation, candidate).individually_compatible) {
                            continue;
                        }

                        //the observation can be explained by a landmark, keep track of them
                        pairings_.emplace_back(observation, candidate);
                        

                        //if there is a distance we can calculate, mark candidate as used and goto the next observation
                        if (jointDistanceSq(problem_, pairings_).has_value()) {
                            candidate_used_[candidate] = true;

                            //keep track of association
                            assignment_[observation] = static_cast<int>(candidate);
                            descend(observation + 1);
                            assignment_[observation] = -1;
                            candidate_used_[candidate] = false;
                        }
                        //remove
                        pairings_.pop_back();
                    }

                    // Bound: skipping this observation is only worth exploring if the
                    // remaining observations could still reach the best pairing count.
                    // `>=` (not `>`) keeps equally large hypotheses alive so ties are
                    // seen and can be reported as ambiguity.
                    const std::size_t reachable =
                        pairings_.size() + (problem_.num_observations - observation - 1);
                    if (reachable >= best_count()) {
                        descend(observation + 1);
                    }
                }

                std::size_t best_count() const {
                    return result_.best ? result_.best->num_pairings : 0;
                }

                void recordLeaf() {
                    if (pairings_.empty()) {
                        return;
                    }
                    JcbbHypothesis hypothesis;
                    hypothesis.assignment = assignment_;
                    hypothesis.num_pairings = pairings_.size();
                    hypothesis.joint_distance_sq = *jointDistanceSq(problem_, pairings_);

                    const bool larger = hypothesis.num_pairings > best_count();
                    const bool tighter = hypothesis.num_pairings == best_count() &&
                        hypothesis.joint_distance_sq < result_.best->joint_distance_sq;

                    if (larger || tighter) {
                        // The displaced best becomes runner-up only if it is the same
                        // size; a smaller hypothesis is not a competing explanation.
                        result_.runner_up = tighter ? result_.best : std::nullopt;
                        result_.best = hypothesis;
                    } else if (hypothesis.num_pairings == best_count() &&
                               (!result_.runner_up ||
                                hypothesis.joint_distance_sq < result_.runner_up->joint_distance_sq)) {
                        result_.runner_up = hypothesis;
                    }
                }

                const JcbbProblem &problem_;
                std::vector<int> assignment_;
                std::vector<bool> candidate_used_;
                std::vector<std::pair<std::size_t, std::size_t>> pairings_;
                std::size_t nodes_visited_ = 0;
                JcbbResult result_;
        };

    }

    double chiSquareQuantile(std::size_t dof, double probability) {
        const double k = static_cast<double>(dof);
        const double scale = 2.0 / (9.0 * k);
        const double cube_root = 1.0 - scale + normalQuantile(probability) * std::sqrt(scale);
        return k * cube_root * cube_root * cube_root;
    }

    std::optional<double> jointDistanceSq(
        const JcbbProblem &problem,
        const std::vector<std::pair<std::size_t, std::size_t>> &pairings
    ) {
        const Eigen::Index n = static_cast<Eigen::Index>(pairings.size());
        Eigen::VectorXd innovation(3 * n);
        Eigen::MatrixXd covariance(3 * n, 3 * n);

        // State layout: pose (6), then 3 per candidate; see JcbbProblem.
        constexpr Eigen::Index kPoseDim = 6;
        constexpr Eigen::Index kLandmarkDim = 3;
        const Eigen::MatrixXd &sigma = problem.state_covariance;

        for (Eigen::Index a = 0; a < n; ++a) {
            const PairTerm &term_a =
                problem.terms[pairings[a].first * problem.num_candidates + pairings[a].second];
            const Eigen::Index landmark_a = kPoseDim + kLandmarkDim * static_cast<Eigen::Index>(pairings[a].second);
            innovation.segment<3>(3 * a) = term_a.innovation;

            for (Eigen::Index b = 0; b < n; ++b) {
                const PairTerm &term_b =
                    problem.terms[pairings[b].first * problem.num_candidates + pairings[b].second];
                const Eigen::Index landmark_b = kPoseDim + kLandmarkDim * static_cast<Eigen::Index>(pairings[b].second);
                // J_a * Sigma * J_b^T, each J touching only the pose and its own
                // landmark. Every pairing shares the pose, and landmarks are
                // correlated with it and with each other, so these off-diagonal
                // blocks are what distinguish joint from individual compatibility.
                covariance.block<3, 3>(3 * a, 3 * b) =
                    term_a.pose_jacobian * sigma.block<kPoseDim, kPoseDim>(0, 0) *
                        term_b.pose_jacobian.transpose() +
                    term_a.pose_jacobian * sigma.block<kPoseDim, kLandmarkDim>(0, landmark_b) *
                        term_b.landmark_jacobian.transpose() +
                    term_a.landmark_jacobian * sigma.block<kLandmarkDim, kPoseDim>(landmark_a, 0) *
                        term_b.pose_jacobian.transpose() +
                    term_a.landmark_jacobian * sigma.block<kLandmarkDim, kLandmarkDim>(landmark_a, landmark_b) *
                        term_b.landmark_jacobian.transpose();
            }
            covariance.block<3, 3>(3 * a, 3 * a) += term_a.measurement_covariance;
        }

        const Eigen::LDLT<Eigen::MatrixXd> factorization(covariance);
        // isPositive() accepts semi-definite matrices and LDLT then solves with a
        // pseudo-inverse; require strictly positive pivots so a singular joint
        // covariance cannot masquerade as a perfect match.
        const Eigen::VectorXd pivots = factorization.vectorD();
        if (factorization.info() != Eigen::Success || !factorization.isPositive() ||
            pivots.minCoeff() <= 1e-12 * pivots.maxCoeff()) {
            return std::nullopt;
        }
        const double distance_sq = innovation.dot(factorization.solve(innovation));
        const double gate = chiSquareQuantile(3 * pairings.size(), problem.gate_confidence);
        if (distance_sq > gate) {
            return std::nullopt;
        }
        return distance_sq;
    }

    JcbbResult runJcbb(const JcbbProblem &problem) {
        return JcbbSearch(problem).run();
    }

}
