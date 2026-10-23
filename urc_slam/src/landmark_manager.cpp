#include "landmark_manager.hpp"

#include <algorithm>
#include <gtsam/geometry/Unit3.h>
#include <gtsam/linear/NoiseModel.h>
#include <gtsam/sam/BearingRangeFactor.h>

namespace urc_slam {

    namespace {

        using RockFactor = gtsam::BearingRangeFactor<gtsam::Pose3, gtsam::Point3>;

        const char *describe(AmbiguityReason reason) {
            switch (reason) {
                case AmbiguityReason::kNoJointlyCompatibleSet: return "no jointly compatible pairing";
                case AmbiguityReason::kTooFewPairings: return "too few pairings to re-associate a stale landmark";
                case AmbiguityReason::kEquallyConsistentAlternatives: return "equally consistent alternative assignments";
                case AmbiguityReason::kSearchBudgetExhausted: return "JCBB search budget exhausted";
                case AmbiguityReason::kNone: break;
            }
            return "unknown";
        }

    }

    LandmarkManager::LandmarkManager(const RockLandmarkParams &params, LogSink log)
        : params_((validate(params), params)),
          associator_(params.associator, params.noise, params.base_T_sensor),
          log_(std::move(log)) {}

    void LandmarkManager::log(const std::string &message) const {
        if (log_) {
            log_(message);
        }
    }

    std::vector<LandmarkCandidate> LandmarkManager::gatherCandidates(
        const gtsam::ISAM2 &isam, std::size_t pose_index
    ) const {
        std::vector<LandmarkCandidate> candidates;
        candidates.reserve(landmarks_.size());
        for (const LandmarkRecord &record : landmarks_) {
            // Created by a previous scan whose update has not been applied yet.
            if (!isam.valueExists(record.key)) {
                continue;
            }
            LandmarkCandidate candidate;
            candidate.key = record.key;
            candidate.position = isam.calculateEstimate<gtsam::Point3>(record.key);
            candidate.covariance = isam.marginalCovariance(record.key);
            candidate.recently_seen =
                pose_index - record.last_seen_pose_index <= params_.associator.recently_seen_window_poses;
            candidates.push_back(candidate);
        }
        return candidates;
    }

    gtsam::Point3 LandmarkManager::initialLandmarkPosition(
        const RockObservation &observation, const gtsam::Pose3 &pose
    ) const {
        // Composition of the current pose estimate with the range-bearing
        // measurement (scan plane, so z = 0 in the sensor frame).
        const Eigen::Vector2d p = observation.sensorPoint();
        return pose.transformFrom(params_.base_T_sensor.transformFrom(gtsam::Point3(p.x(), p.y(), 0.0)));
    }

    gtsam::NonlinearFactor::shared_ptr LandmarkManager::makeFactor(
        const RockObservation &observation,
        std::size_t pose_index,
        const gtsam::Symbol &landmark
    ) const {
        // The factor measures from the BASE pose key, so express the scan point
        // in the base frame before splitting into bearing and range.
        const Eigen::Vector2d p = observation.sensorPoint();
        const gtsam::Point3 in_base = params_.base_T_sensor.transformFrom(gtsam::Point3(p.x(), p.y(), 0.0));

        // Unit3 has a 2-D tangent space with an arbitrary basis, so both bearing
        // axes share one sigma (the elevation is measured as ~0 by a planar scan).
        const gtsam::Vector3 sigmas(
            params_.noise.bearing_sigma_rad,
            params_.noise.bearing_sigma_rad,
            params_.noise.range_sigma_m
        );
        // Huber: down-weights residuals beyond the kernel width instead of
        // letting one wrong association pull the whole trajectory.
        const gtsam::SharedNoiseModel noise = gtsam::noiseModel::Robust::Create(
            gtsam::noiseModel::mEstimator::Huber::Create(params_.huber_kernel_width),
            gtsam::noiseModel::Diagonal::Sigmas(sigmas)
        );
        return boost::make_shared<RockFactor>(
            poseKey(pose_index), landmark, gtsam::Unit3(in_base), in_base.norm(), noise);
    }

    LandmarkGraphUpdate LandmarkManager::processScan(
        const std::vector<RockObservation> &observations,
        std::size_t pose_index,
        const gtsam::ISAM2 &isam
    ) {
        LandmarkGraphUpdate update;
        if (observations.empty()) {
            return update;
        }

        const gtsam::Pose3 pose = isam.calculateEstimate<gtsam::Pose3>(poseKey(pose_index));
        const BasePoseEstimate pose_estimate{pose, isam.marginalCovariance(poseKey(pose_index))};

        // Associate FIRST, create SECOND, so one rock cannot become two nodes.
        const std::vector<ObservationAssociation> associations =
            associator_.associate(observations, pose_estimate, gatherCandidates(isam, pose_index));

        for (std::size_t i = 0; i < observations.size(); ++i) {
            const ObservationAssociation &association = associations[i];
            switch (association.disposition) {
                case Disposition::kMatched: {
                    update.factors.push_back(makeFactor(
                        observations[i], pose_index, gtsam::Symbol(association.landmark_key)));
                    auto record = std::find_if(landmarks_.begin(), landmarks_.end(),
                        [&](const LandmarkRecord &r) { return r.key.key() == association.landmark_key; });
                    record->last_seen_pose_index = pose_index;
                    ++update.summary.matched;
                    break;
                }
                case Disposition::kNewLandmark: {
                    const gtsam::Symbol key = landmarkKey(landmarks_.size());
                    update.values.insert(key, initialLandmarkPosition(observations[i], pose));
                    update.factors.push_back(makeFactor(observations[i], pose_index, key));
                    landmarks_.push_back({key, observations[i].size_m, pose_index});
                    ++update.summary.created;
                    break;
                }
                case Disposition::kAmbiguous:
                    log(std::string("rock observation ") + std::to_string(i) + " left unassociated: " +
                        describe(association.reason));
                    ++update.summary.ambiguous;
                    break;
            }
        }
        return update;
    }

}
