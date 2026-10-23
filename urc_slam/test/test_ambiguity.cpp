#include <iostream>

#include "association_fixture.hpp"
#include "mini_check.hpp"

int main() {
    using namespace fixture;
    using urc_slam::Disposition;

    const urc_slam::LandmarkAssociator associator(
        urc_slam::AssociatorParams{}, testNoise(), gtsam::Pose3());
    const urc_slam::BasePoseEstimate pose = poseUncertainInX(1.0);

    // One observation exactly halfway between two landmarks: both pairings
    // have the same innovation magnitude and the same covariance, so nothing
    // in the data prefers one. The associator must add nothing, and in
    // particular must not fall back to creating a third landmark.
    const auto symmetric = associator.associate(
        {observationAt(5.0, 0.0)}, pose, {landmarkAt(1, 4.0, 0.0), landmarkAt(2, 6.0, 0.0)});
    CHECK(symmetric.size() == 1);
    CHECK(symmetric[0].disposition == Disposition::kAmbiguous);
    CHECK(symmetric[0].reason == urc_slam::AmbiguityReason::kEquallyConsistentAlternatives);

    // An observation far outside every gate cannot be any known landmark, so
    // it is safe to create a new one, even in the same scan as an ambiguous one.
    const auto mixed = associator.associate(
        {observationAt(5.0, 0.0), observationAt(5.0, 15.0)}, pose,
        {landmarkAt(1, 4.0, 0.0), landmarkAt(2, 6.0, 0.0)});
    CHECK(mixed[0].disposition == Disposition::kAmbiguous);
    CHECK(mixed[1].disposition == Disposition::kNewLandmark);

    // A stale landmark (not seen recently) matched by a single pairing is
    // below min_pairings_for_reassociation = 2, so it is not re-associated.
    urc_slam::LandmarkCandidate stale = landmarkAt(1, 5.5, 0.0);
    stale.recently_seen = false;
    const auto lone_stale = associator.associate({observationAt(5.0, 0.0)}, pose, {stale});
    CHECK(lone_stale[0].disposition == Disposition::kAmbiguous);
    CHECK(lone_stale[0].reason == urc_slam::AmbiguityReason::kTooFewPairings);

    std::cout << "test_ambiguity passed" << std::endl;
    return 0;
}
