#ifndef LANDMARK_ASSOCIATOR_HPP_
#define LANDMARK_ASSOCIATOR_HPP_

#include <cstddef>
#include <optional>
#include <vector>
#include <gtsam/base/Matrix.h>
#include <gtsam/geometry/Point3.h>
#include <gtsam/geometry/Pose3.h>
#include <gtsam/inference/Key.h>

#include "jcbb_search.hpp"
#include "rock_landmark_params.hpp"
#include "rock_types.hpp"

namespace urc_slam {

    // Current best guess of the pose that took the scan: map_T_base, with the
    // 6x6 covariance in GTSAM's Pose3 tangent order (rotation, then translation).
    struct BasePoseEstimate {
        gtsam::Pose3 pose;
        gtsam::Matrix6 covariance = gtsam::Matrix6::Identity();
    };

    struct LandmarkCandidate {
        gtsam::Key key = 0;
        gtsam::Point3 position;          // map frame
        gtsam::Matrix3 covariance = gtsam::Matrix3::Identity();
        bool recently_seen = false;
    };

    enum class Disposition { kMatched, kNewLandmark, kAmbiguous };

    enum class AmbiguityReason {
        kNone,
        kNoJointlyCompatibleSet,
        kTooFewPairings,
        kEquallyConsistentAlternatives,
        kSearchBudgetExhausted,
    };

    struct ObservationAssociation {
        Disposition disposition = Disposition::kAmbiguous;
        gtsam::Key landmark_key = 0;     // valid only when kMatched
        AmbiguityReason reason = AmbiguityReason::kNone;
    };

    // Decides, for every observation of one scan, whether it is an existing
    // landmark, a new one, or too uncertain to act on. "New" is only ever
    // returned for an observation that no existing landmark could explain, so
    // an uncertain match never spawns a duplicate landmark.
    class LandmarkAssociator {
        public:
            LandmarkAssociator(
                const AssociatorParams &params,
                const RockMeasurementNoise &noise,
                const gtsam::Pose3 &base_T_sensor
            );

            // Result is index-aligned with `observations`.
            std::vector<ObservationAssociation> associate(
                const std::vector<RockObservation> &observations,
                const BasePoseEstimate &pose,
                const std::vector<LandmarkCandidate> &candidates
            ) const;

            // Baseline for comparison only (not used by the pipeline): each
            // observation independently takes the closest individually-gated
            // landmark in the map frame. Fails when the pose error is shared by
            // all observations, which is exactly what JCBB models.
            std::vector<std::optional<std::size_t>> nearestNeighbor(
                const std::vector<RockObservation> &observations,
                const BasePoseEstimate &pose,
                const std::vector<LandmarkCandidate> &candidates
            ) const;

        private:
            JcbbProblem buildProblem(
                const std::vector<RockObservation> &observations,
                const BasePoseEstimate &pose,
                const std::vector<LandmarkCandidate> &candidates
            ) const;

            PairTerm pairTerm(
                const RockObservation &observation,
                const BasePoseEstimate &pose,
                const LandmarkCandidate &candidate
            ) const;

            AssociatorParams params_;
            RockMeasurementNoise noise_;
            gtsam::Pose3 base_T_sensor_;
    };

}

#endif
