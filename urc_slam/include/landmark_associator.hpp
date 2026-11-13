#ifndef LANDMARK_ASSOCIATOR_HPP_
#define LANDMARK_ASSOCIATOR_HPP_

#include <cstddef>
#include <optional>
#include <vector>
#include <gtsam/base/Matrix.h>
#include <gtsam/geometry/Point3.h>
#include <gtsam/geometry/Pose3.h>
#include <gtsam/inference/Key.h>
#include <gtsam/nonlinear/ISAM2.h>

#include "jcbb_search.hpp"
#include "rock_landmark_params.hpp"
#include "rock_types.hpp"

namespace urc_slam {

    struct LandmarkCandidate {
        gtsam::Key key = 0;
        gtsam::Point3 position;          // map frame
        bool recently_seen = false;
    };

    // Map-frame state one scan is associated against. `covariance` is the joint
    // marginal of [pose, candidates[0], candidates[1], ...]: a 6x6 pose block in
    // GTSAM's Pose3 tangent order (rotation, then translation), then a 3x3 block
    // per candidate, cross-covariances included.
    struct AssociationState {
        gtsam::Pose3 pose;               // map_T_base
        std::vector<LandmarkCandidate> candidates;
        gtsam::Matrix covariance;
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

            // Result is index-aligned with `observations`. Throws
            // std::invalid_argument if `state.covariance` does not match the
            // candidate count.
            std::vector<ObservationAssociation> associate(
                const std::vector<RockObservation> &observations,
                const AssociationState &state
            ) const;

            // Baseline for comparison only (not used by the pipeline): each
            // observation independently takes the closest individually-gated
            // landmark in the map frame. Fails when the pose error is shared by
            // all observations, which is exactly what JCBB models.
            std::vector<std::optional<std::size_t>> nearestNeighbor(
                const std::vector<RockObservation> &observations,
                const AssociationState &state
            ) const;

        private:
            JcbbProblem buildProblem(
                const std::vector<RockObservation> &observations,
                const AssociationState &state
            ) const;

            PairTerm pairTerm(
                const RockObservation &observation,
                const gtsam::Pose3 &pose,
                const LandmarkCandidate &candidate
            ) const;

            AssociatorParams params_;
            RockMeasurementNoise noise_;
            gtsam::Pose3 base_T_sensor_;
    };

    // Exact joint marginal covariance of `keys` from iSAM2's Bayes tree, at its
    // current linearization point. Blocks follow the order of `keys`, each the
    // variable's tangent dimension (6 for Pose3, 3 for Point3). The keys must
    // be in one connected graph.
    gtsam::Matrix jointCovariance(const gtsam::ISAM2 &isam, const gtsam::KeyVector &keys);

}

#endif
