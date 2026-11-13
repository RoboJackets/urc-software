#include "loop_closure_detector.hpp"

#include <algorithm>
#include <cmath>
#include <utility>
#include <Eigen/Eigenvalues>
#include <gtsam/inference/Symbol.h>

#include "loop_closure_screening.hpp"

namespace urc_slam {

    namespace {

        // Same 'x' pose symbol convention as SlamBackend::poseKey (private there).
        gtsam::Symbol poseKey(std::size_t index) {
            return gtsam::Symbol('x', index);
        }

        // Largest 1-sigma position uncertainty of a pose, from the translation
        // block of its 6x6 covariance (GTSAM order: rotation, then translation).
        double largestPositionSigma(const gtsam::Matrix6 &pose_covariance) {
            const Eigen::SelfAdjointEigenSolver<Eigen::Matrix3d> solver(pose_covariance.block<3, 3>(3, 3));
            return std::sqrt(std::max(0.0, solver.eigenvalues().maxCoeff()));
        }

        std::vector<KeyframePosition> keyframePositions(std::size_t count, const SlamBackend &backend) {
            std::vector<KeyframePosition> positions;
            positions.reserve(count);
            double path_length_m = 0.0;
            for (std::size_t index = 0; index < count; ++index) {
                KeyframePosition keyframe;
                keyframe.index = index;
                keyframe.position = backend.poseAt(index).translation();
                if (!positions.empty()) {
                    path_length_m += (keyframe.position - positions.back().position).norm();
                }
                keyframe.path_length_m = path_length_m;
                positions.push_back(keyframe);
            }
            return positions;
        }

    }

    LoopClosureDetector::LoopClosureDetector(
        const LoopClosureParams &params, const LidarFrontend &frontend, LogSink log
    )
        : params_(params), frontend_(frontend), log_(std::move(log)) {}

    void LoopClosureDetector::log(const std::string &message) const {
        if (log_) {
            log_(message);
        }
    }

    bool LoopClosureDetector::shouldAttempt(std::size_t current_index) const {
        if (params_.attempt_every_n_keyframes > 1 &&
            current_index % params_.attempt_every_n_keyframes != 0) {
            return false;
        }
        return !last_closure_index_ ||
               current_index - *last_closure_index_ > params_.cooldown_keyframes;
    }

    std::optional<LoopClosure> LoopClosureDetector::evaluateCandidate(
        std::size_t earlier_index,
        std::size_t current_index,
        const std::vector<LidarFrontend::Cloud::ConstPtr> &clouds,
        const SlamBackend &backend
    ) const {
        // Starting guess for GICP: the graph's own belief about how the two
        // keyframes sit relative to each other (earlier^-1 * current).
        const gtsam::Pose3 earlier_pose = backend.poseAt(earlier_index);
        const gtsam::Pose3 guess = earlier_pose.between(backend.poseAt(current_index));

        const LidarRegistrationResult registration =
            frontend_.registerClouds(clouds[earlier_index], clouds[current_index], {guess});
        if (!registration.converged || registration.fitness_score_m2 > params_.max_fitness_score) {
            log("loop candidate " + std::to_string(earlier_index) + " rejected: " +
                (registration.converged ? "fitness " + std::to_string(registration.fitness_score_m2)
                                        : std::string("GICP did not converge")));
            return std::nullopt;
        }

        // How far GICP moved the answer from the graph's belief, as a 6-vector
        // in the tangent space at the guess (GTSAM right-perturbation).
        const gtsam::Vector6 correction = gtsam::Pose3::Logmap(guess.between(registration.relative_pose));

        // Uncertainty of that relative pose, same perturbation convention:
        //   cov(earlier^-1 * current) ~= cov_current + Ad * cov_earlier * Ad^T
        // with Ad the adjoint of (current^-1 * earlier). APPROXIMATION: the two
        // poses' errors are treated as independent. For nearby, correlated
        // keyframes the true covariance is smaller, so this gate is too LOOSE.
        const gtsam::ISAM2 &isam = backend.isamGraph();
        const gtsam::Matrix6 adjoint = guess.inverse().AdjointMap();
        const gtsam::Matrix6 relative_covariance =
            isam.marginalCovariance(poseKey(current_index)) +
            adjoint * isam.marginalCovariance(poseKey(earlier_index)) * adjoint.transpose();

        const GateResult gate = gateCorrection(correction, relative_covariance, params_.gate_confidence);
        if (!gate.plausible) {
            log("loop candidate " + std::to_string(earlier_index) +
                " rejected: disagrees with graph (d^2 " + std::to_string(gate.distance_sq) + ")");
            return std::nullopt;
        }

        LoopClosure closure;
        closure.earlier_index = earlier_index;
        closure.relative_pose = registration.relative_pose;
        closure.fitness_score = registration.fitness_score_m2;
        closure.correction_distance_sq = gate.distance_sq;
        closure.huber_kernel_width = params_.huber_kernel_width;
        return closure;
    }

    std::optional<LoopClosure> LoopClosureDetector::detect(
        std::size_t current_index,
        const std::vector<LidarFrontend::Cloud::ConstPtr> &clouds,
        const SlamBackend &backend
    ) {
        if (!shouldAttempt(current_index) || current_index == 0) {
            return std::nullopt;
        }

        const std::vector<KeyframePosition> keyframes = keyframePositions(current_index + 1, backend);
        const KeyframePosition current = keyframes.back();
        const std::vector<KeyframePosition> earlier(keyframes.begin(), keyframes.end() - 1);

        const double position_sigma_m = largestPositionSigma(
            backend.isamGraph().marginalCovariance(poseKey(current_index)));

        std::optional<LoopClosure> best;
        for (std::size_t candidate : findLoopCandidates(current, earlier, position_sigma_m, params_.candidates)) {
            const std::optional<LoopClosure> closure =
                evaluateCandidate(candidate, current_index, clouds, backend);
            if (closure && (!best || closure->fitness_score < best->fitness_score)) {
                best = closure;
            }
        }

        if (best) {
            last_closure_index_ = current_index;
        }
        return best;
    }

}
