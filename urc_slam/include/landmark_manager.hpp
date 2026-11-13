#ifndef LANDMARK_MANAGER_HPP_
#define LANDMARK_MANAGER_HPP_

#include <cstddef>
#include <functional>
#include <string>
#include <vector>
#include <gtsam/inference/Symbol.h>
#include <gtsam/nonlinear/ISAM2.h>
#include <gtsam/nonlinear/NonlinearFactorGraph.h>
#include <gtsam/nonlinear/Values.h>

#include "landmark_associator.hpp"
#include "rock_landmark_params.hpp"
#include "rock_types.hpp"

namespace urc_slam {

    // Metadata only; the landmark's position lives in iSAM2 under `key`.
    struct LandmarkRecord {
        gtsam::Symbol key;
        // Mean fitted radius over every matched sighting, so the collision
        // gate does not hinge on the one fit that created the landmark.
        double radius_m = 0.0;
        std::size_t radius_samples = 1;
        std::size_t last_seen_pose_index = 0;
        // Pose that added this landmark's most recent factor.
        std::size_t last_factor_pose_index = 0;
    };

    // A landmark's current optimized state, for visualization and logging.
    struct LandmarkSnapshot {
        std::size_t id = 0;
        gtsam::Point3 position;   // map frame
        double radius_m = 0.0;
        std::size_t last_seen_pose_index = 0;
    };

    struct ScanSummary {
        std::size_t matched = 0;
        std::size_t created = 0;
        std::size_t ambiguous = 0;
        // New-landmark observations dropped for overlapping a mapped rock.
        std::size_t colliding = 0;
        // Matched sightings that added no factor (viewpoint barely changed).
        std::size_t redundant = 0;
        // Association search radius used for this scan (grows with pose
        // uncertainty); 0 when the scan had no observations.
        double candidate_radius_m = 0.0;
    };

    // New factors/values for the caller to merge into its pending iSAM2 update.
    struct LandmarkGraphUpdate {
        gtsam::NonlinearFactorGraph factors;
        gtsam::Values values;
        ScanSummary summary;
    };

    using LogSink = std::function<void(const std::string &)>;

    // Owns landmark bookkeeping and turns association results into graph
    // changes. Does not own or modify the iSAM2 instance.
    class LandmarkManager {
        public:
            explicit LandmarkManager(const RockLandmarkParams &params, LogSink log = {});

            // `pose_index` must already be in `isam` (its pose and covariance are
            // read from it), and the previous call's update must already have
            // been applied, or those landmarks are invisible to association.
            LandmarkGraphUpdate processScan(
                const std::vector<RockObservation> &observations,
                std::size_t pose_index,
                const gtsam::ISAM2 &isam
            );

            const std::vector<LandmarkRecord> &landmarks() const { return landmarks_; }

            // Current optimized position of every landmark already in `isam`.
            std::vector<LandmarkSnapshot> snapshots(const gtsam::ISAM2 &isam) const;

            // Same 'x' pose symbol as SlamBackend::poseKey (private there).
            static gtsam::Symbol poseKey(std::size_t index) { return gtsam::Symbol('x', index); }
            static gtsam::Symbol landmarkKey(std::size_t id) { return gtsam::Symbol('l', id); }

        private:
            // candidate_radius_m grown by the pose's position uncertainty,
            // capped at max_candidate_radius_m.
            double candidateRadius(const gtsam::ISAM2 &isam, std::size_t pose_index) const;

            // Landmarks of `mapped` within `radius_m` of the robot.
            std::vector<LandmarkCandidate> gatherCandidates(
                const std::vector<LandmarkSnapshot> &mapped,
                std::size_t pose_index,
                const gtsam::Point3 &robot_position,
                double radius_m) const;

            AssociationState associationState(
                const gtsam::ISAM2 &isam,
                std::size_t pose_index,
                const std::vector<LandmarkSnapshot> &mapped,
                double candidate_radius_m) const;

            // Adds a factor only for a sighting from a new viewpoint.
            void recordMatch(
                const RockObservation &observation,
                std::size_t pose_index,
                gtsam::Key landmark,
                const gtsam::ISAM2 &isam,
                LandmarkGraphUpdate &update);

            bool isNewViewpoint(
                const LandmarkRecord &record, std::size_t pose_index, const gtsam::ISAM2 &isam) const;

            // Adds the landmark node and its first factor to `update`.
            LandmarkSnapshot createLandmark(
                const RockObservation &observation,
                std::size_t pose_index,
                const gtsam::Point3 &position,
                LandmarkGraphUpdate &update);

            gtsam::NonlinearFactor::shared_ptr makeFactor(
                const RockObservation &observation,
                std::size_t pose_index,
                const gtsam::Symbol &landmark) const;

            gtsam::Point3 initialLandmarkPosition(
                const RockObservation &observation, const gtsam::Pose3 &pose) const;

            void log(const std::string &message) const;

            RockLandmarkParams params_;
            LandmarkAssociator associator_;
            LogSink log_;
            std::vector<LandmarkRecord> landmarks_;
    };

}

#endif
