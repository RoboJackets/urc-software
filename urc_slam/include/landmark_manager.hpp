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
        double size_m = 0.0;
        std::size_t last_seen_pose_index = 0;
    };

    struct ScanSummary {
        std::size_t matched = 0;
        std::size_t created = 0;
        std::size_t ambiguous = 0;
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

            // Same 'x' pose symbol as SlamBackend::poseKey (private there).
            static gtsam::Symbol poseKey(std::size_t index) { return gtsam::Symbol('x', index); }
            static gtsam::Symbol landmarkKey(std::size_t id) { return gtsam::Symbol('l', id); }

        private:
            std::vector<LandmarkCandidate> gatherCandidates(
                const gtsam::ISAM2 &isam, std::size_t pose_index) const;

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
