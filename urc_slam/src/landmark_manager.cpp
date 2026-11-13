#include "landmark_manager.hpp"

#include <algorithm>
#include <cmath>
#include <optional>
#include <Eigen/Eigenvalues>
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

        // Rocks are modelled as spheres, so two distinct rocks cannot have
        // centres closer than the sum of their radii; `min_separation_m` is a
        // floor for small or poorly fitted radii. Linear in the map size, which
        // stays in the hundreds; positions move with every optimization, so a
        // spatial index would need rebuilding each scan anyway.
        std::optional<std::size_t> collidingLandmark(
            const gtsam::Point3 &position, double radius_m,
            const std::vector<LandmarkSnapshot> &mapped, double min_separation_m
        ) {
            const auto collision = std::find_if(mapped.begin(), mapped.end(),
                [&](const LandmarkSnapshot &rock) {
                    const double required = std::max(min_separation_m, radius_m + rock.radius_m);
                    return (rock.position - position).norm() < required;
                });
            if (collision == mapped.end()) {
                return std::nullopt;
            }
            return collision->id;
        }

        // 1-sigma position error along the pose's least certain direction.
        // GTSAM's Pose3 tangent order is (rotation, translation), so position
        // is the trailing 3x3 block; its eigenvalues do not depend on whether
        // it is expressed in the body or the map frame.
        double largestPositionSigma(const gtsam::Matrix &pose_covariance) {
            const Eigen::Matrix3d position = pose_covariance.bottomRightCorner<3, 3>();
            const Eigen::SelfAdjointEigenSolver<Eigen::Matrix3d> solver(position, Eigen::EigenvaluesOnly);
            return std::sqrt(std::max(solver.eigenvalues().maxCoeff(), 0.0));
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

    double LandmarkManager::candidateRadius(const gtsam::ISAM2 &isam, std::size_t pose_index) const {
        const AssociatorParams &associator = params_.associator;
        const double sigma_m = largestPositionSigma(isam.marginalCovariance(poseKey(pose_index)));
        return std::min(associator.candidate_radius_m + associator.candidate_pose_sigma_scale * sigma_m,
                        associator.max_candidate_radius_m);
    }

    std::vector<LandmarkCandidate> LandmarkManager::gatherCandidates(
        const std::vector<LandmarkSnapshot> &mapped, std::size_t pose_index,
        const gtsam::Point3 &robot_position, double radius_m
    ) const {
        std::vector<LandmarkCandidate> candidates;
        candidates.reserve(mapped.size());

        for (const LandmarkSnapshot &landmark : mapped) {
            // Beyond the radius the Mahalanobis gate would reject the rock
            // anyway, so it is not worth the joint covariance cost.
            if ((landmark.position - robot_position).norm() > radius_m) {
                continue;
            }
            LandmarkCandidate candidate;
            candidate.key = landmarkKey(landmark.id);
            candidate.position = landmark.position;
            candidate.recently_seen =
                pose_index - landmark.last_seen_pose_index <= params_.associator.recently_seen_window_poses;
            candidates.push_back(candidate);
        }
        return candidates;
    }

    AssociationState LandmarkManager::associationState(
        const gtsam::ISAM2 &isam, std::size_t pose_index,
        const std::vector<LandmarkSnapshot> &mapped, double candidate_radius_m
    ) const {
        AssociationState state;
        state.pose = isam.calculateEstimate<gtsam::Pose3>(poseKey(pose_index));
        state.candidates = gatherCandidates(mapped, pose_index, state.pose.translation(), candidate_radius_m);
        gtsam::KeyVector state_keys{poseKey(pose_index)};
        for (const LandmarkCandidate &candidate : state.candidates) {
            state_keys.push_back(candidate.key);
        }
        state.covariance = jointCovariance(isam, state_keys);
        return state;
    }

    gtsam::Point3 LandmarkManager::initialLandmarkPosition(
        const RockObservation &observation, const gtsam::Pose3 &pose
    ) const {
        // Current pose estimate composed with the measured rock centre.
        return pose.transformFrom(params_.base_T_sensor.transformFrom(observation.sensor_point));
    }

    gtsam::NonlinearFactor::shared_ptr LandmarkManager::makeFactor(
        const RockObservation &observation,
        std::size_t pose_index,
        const gtsam::Symbol &landmark
    ) const {
        // The factor measures from the BASE pose key, so express the scan point
        // in the base frame before splitting into bearing and range.
        const gtsam::Point3 in_base = params_.base_T_sensor.transformFrom(observation.sensor_point);

        // Unit3 has a 2-D tangent space with an arbitrary basis, so both bearing
        // axes (azimuth and elevation) share one sigma.
        const gtsam::Vector3 sigmas(
            params_.noise.bearing_sigma_rad,
            params_.noise.bearing_sigma_rad,
            params_.noise.range_sigma_m
        );
        // Huber: down-weights residuals beyond the kernel width instead of
        // letting one wrong association pull the whole trajectory.

        //This noise here should include the empirical covariance for rock detection/error in rock position/as well as the hubert model(or both)
        const gtsam::SharedNoiseModel noise = gtsam::noiseModel::Robust::Create(
            gtsam::noiseModel::mEstimator::Huber::Create(params_.huber_kernel_width),
            gtsam::noiseModel::Diagonal::Sigmas(sigmas)
        );
        return boost::make_shared<RockFactor>(
            poseKey(pose_index), landmark, gtsam::Unit3(in_base), in_base.norm(), noise);
    }


    //gates... how much should the robot have moved before it thinks about if its been here before
    bool LandmarkManager::isNewViewpoint(
        const LandmarkRecord &record, std::size_t pose_index, const gtsam::ISAM2 &isam
    ) const {
        // Far apart in keyframes, the two sightings' errors are independent
        // (this is what closes loops), whatever the viewpoint.

        //what are the last_factor_pose_index and the recently_seen_window_poses
        if (pose_index - record.last_factor_pose_index > params_.associator.recently_seen_window_poses) {
            return true;
        }

        // Current estimates for both poses, so later corrections are respected.
        const gtsam::Point3 landmark = isam.calculateEstimate<gtsam::Point3>(record.key);

        //how much did it move from last time
        const gtsam::Point3 previous =
            isam.calculateEstimate<gtsam::Pose3>(poseKey(record.last_factor_pose_index)).translation();

        //where is it now
        const gtsam::Point3 current = isam.calculateEstimate<gtsam::Pose3>(poseKey(pose_index)).translation();

        //take the difference then
                const gtsam::Vector3 previous_sight = landmark - previous;

        //take the difference now
        const gtsam::Vector3 current_sight = landmark - current;

        //how much did it change
        const double view_change_rad =
            std::atan2(previous_sight.cross(current_sight).norm(), previous_sight.dot(current_sight));
            //does it match the gate
        return view_change_rad >= params_.min_factor_view_change_rad ||
               (current - previous).norm() >= params_.min_factor_travel_m;
    }


    
    void LandmarkManager::recordMatch(
        const RockObservation &observation, std::size_t pose_index,
        gtsam::Key landmark, const gtsam::ISAM2 &isam, LandmarkGraphUpdate &update
    ) {

        //get a record from each landmark record
        auto record = std::find_if(landmarks_.begin(), landmarks_.end(),
            [&](const LandmarkRecord &r) { return r.key.key() == landmark; });

        //update metadata
        record->last_seen_pose_index = pose_index;
        ++record->radius_samples;

        //difference between observation and radius and divide by radius sample(used to keep a running average) --> this seems like too much work
        record->radius_m += (observation.radius_m - record->radius_m) / static_cast<double>(record->radius_samples);

        //if it is at a new point of view
        if (!isNewViewpoint(*record, pose_index, isam)) {
            ++update.summary.redundant;
            return;
        }
        update.factors.push_back(makeFactor(observation, pose_index, gtsam::Symbol(landmark)));
        record->last_factor_pose_index = pose_index;
        ++update.summary.matched;
    }



    LandmarkSnapshot LandmarkManager::createLandmark(
        const RockObservation &observation, std::size_t pose_index,
        const gtsam::Point3 &position, LandmarkGraphUpdate &update
    ) {

        //why is the id ahhh that is a great idea. 
        const std::size_t id = landmarks_.size();
        const gtsam::Symbol key = landmarkKey(id);

        //add the new landmark
        update.values.insert(key, position);

        //make the factor
        update.factors.push_back(makeFactor(observation, pose_index, key));

        //save the landmark for data ssociation
        landmarks_.push_back({key, observation.radius_m, 1, pose_index, pose_index});
        ++update.summary.created;

        //return important info
        return {id, position, observation.radius_m, pose_index};
    }

    std::vector<LandmarkSnapshot> LandmarkManager::snapshots(const gtsam::ISAM2 &isam) const {
        std::vector<LandmarkSnapshot> result;
        result.reserve(landmarks_.size());
        for (std::size_t id = 0; id < landmarks_.size(); ++id) {
            const LandmarkRecord &record = landmarks_[id];
            // Skip landmarks whose creating update has not reached iSAM2 yet.
            if (!isam.valueExists(record.key)) {
                continue;
            }
            result.push_back({id, isam.calculateEstimate<gtsam::Point3>(record.key),
                              record.radius_m, record.last_seen_pose_index});
        }
        return result;
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

        // Every mapped landmark, not only association candidates, so the
        // collision gate also sees rocks outside the candidate radius.
        // Landmarks created below are appended so one scan cannot place two
        // landmarks on the same rock.
        std::vector<LandmarkSnapshot> mapped = snapshots(isam);
        update.summary.candidate_radius_m = candidateRadius(isam, pose_index);
        const AssociationState state =
            associationState(isam, pose_index, mapped, update.summary.candidate_radius_m);

        // Associate FIRST, create SECOND, so one rock cannot become two nodes.
        const std::vector<ObservationAssociation> associations =
            associator_.associate(observations, state);

        for (std::size_t i = 0; i < observations.size(); ++i) {
            const RockObservation &observation = observations[i];
            const ObservationAssociation &association = associations[i];
            switch (association.disposition) {
                case Disposition::kMatched:
                    recordMatch(observation, pose_index, association.landmark_key, isam, update);
                    break;
                case Disposition::kNewLandmark: {
                    const gtsam::Point3 position = initialLandmarkPosition(observation, state.pose);
                    const std::optional<std::size_t> collision = collidingLandmark(
                        position, observation.radius_m, mapped, params_.min_landmark_separation_m);
                    if (collision) {
                        log("rock observation " + std::to_string(i) +
                            " not added: overlaps landmark " + std::to_string(*collision));
                        ++update.summary.colliding;
                        break;
                    }
                    mapped.push_back(createLandmark(observation, pose_index, position, update));
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
