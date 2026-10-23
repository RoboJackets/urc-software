#include <iostream>

#include "association_fixture.hpp"
#include "mini_check.hpp"

// The worked example from the design: mapped rocks R1=(0,0), R2=(1,0),
// R3=(4,0). The robot really sees R2 and R3, but its pose estimate is off by
// -1 m in x, so the observations land at (0,0) and (3,0).
//
// Every x is shifted by +5 m here so no observation sits exactly on the sensor
// origin (range 0 has an undefined bearing); the geometry is unchanged.
int main() {
    using namespace fixture;

    const std::vector<urc_slam::LandmarkCandidate> landmarks{
        landmarkAt(1, 5.0, 0.0), landmarkAt(2, 6.0, 0.0), landmarkAt(3, 9.0, 0.0)};
    const std::vector<urc_slam::RockObservation> observations{
        observationAt(5.0, 0.0), observationAt(8.0, 0.0)};

    // sigma 1.0 m in x encodes "the pose may be off by about a metre", which is
    // what makes a common 1 m shift plausible for BOTH observations at once.
    const urc_slam::BasePoseEstimate pose = poseUncertainInX(1.0);

    const urc_slam::LandmarkAssociator associator(
        urc_slam::AssociatorParams{}, testNoise(), gtsam::Pose3());

    // Per-rock nearest neighbour trusts each pairing on its own: {R1, R3}.
    const auto nearest = associator.nearestNeighbor(observations, pose, landmarks);
    CHECK(nearest[0].has_value() && *nearest[0] == 0);   // R1
    CHECK(nearest[1].has_value() && *nearest[1] == 2);   // R3

    // JCBB asks whether the pairings agree on ONE pose error. {R1, R3} implies
    // shifts of 0 m and 1 m for the same pose, which is inconsistent; {R2, R3}
    // implies 1 m and 1 m, which is.
    const auto joint = associator.associate(observations, pose, landmarks);
    CHECK(joint[0].disposition == urc_slam::Disposition::kMatched);
    CHECK(joint[1].disposition == urc_slam::Disposition::kMatched);
    CHECK(joint[0].landmark_key == landmarkKey(2));      // R2
    CHECK(joint[1].landmark_key == landmarkKey(3));      // R3

    std::cout << "test_jcbb_vs_nearest_neighbor passed" << std::endl;
    return 0;
}
