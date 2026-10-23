#include <iostream>
#include <vector>
#include <gtsam/nonlinear/ISAM2.h>
#include <gtsam/slam/BetweenFactor.h>
#include <gtsam/slam/PriorFactor.h>

#include "association_fixture.hpp"
#include "landmark_manager.hpp"
#include "mini_check.hpp"

namespace {

    using gtsam::Pose3;
    using urc_slam::LandmarkManager;

    constexpr std::size_t kSquareSides = 4;

    // One side of the square: drive forward 10 m, then turn left 90 degrees.
    Pose3 trueSide() {
        return Pose3(gtsam::Rot3::Yaw(M_PI / 2.0), gtsam::Point3(10.0, 0.0, 0.0));
    }

    // What a drifting odometer reports for the same side: a small extra turn
    // and 1% scale error per side, so error accumulates around the loop.
    Pose3 driftingSide() {
        return Pose3(gtsam::Rot3::Yaw(M_PI / 2.0 + 0.01), gtsam::Point3(10.1, 0.0, 0.0));
    }

    std::vector<urc_slam::RockObservation> observeFrom(
        const Pose3 &true_pose, const std::vector<gtsam::Point3> &rocks
    ) {
        std::vector<urc_slam::RockObservation> observations;
        for (const gtsam::Point3 &rock : rocks) {
            const gtsam::Point3 local = true_pose.transformTo(rock);
            observations.push_back(fixture::observationAt(local.x(), local.y(), local.z()));
        }
        return observations;
    }

    void apply(gtsam::ISAM2 &isam, const urc_slam::LandmarkGraphUpdate &update) {
        isam.update(update.factors, update.values);
    }

}

int main() {
    urc_slam::RockLandmarkParams params;
    params.noise = fixture::testNoise();
    // Make the first-seen landmarks count as "not seen recently" by the end of
    // the loop, so the real loop-closure rule (>= 2 pairings) is what is tested.
    params.associator.recently_seen_window_poses = 2;
    LandmarkManager manager(params);

    const std::vector<gtsam::Point3> rocks{gtsam::Point3(3.0, 2.0, 0.0), gtsam::Point3(6.0, -2.0, 0.0)};

    const auto prior_noise = gtsam::noiseModel::Diagonal::Sigmas(gtsam::Vector6::Constant(1e-3));
    gtsam::Vector6 odometry_sigmas;
    odometry_sigmas << 0.03, 0.03, 0.03, 0.2, 0.2, 0.2;
    const auto odometry_noise = gtsam::noiseModel::Diagonal::Sigmas(odometry_sigmas);

    gtsam::ISAM2 isam;
    {
        gtsam::NonlinearFactorGraph factors;
        gtsam::Values values;
        factors.add(gtsam::PriorFactor<Pose3>(LandmarkManager::poseKey(0), Pose3(), prior_noise));
        values.insert(LandmarkManager::poseKey(0), Pose3());
        isam.update(factors, values);
    }

    // Start of the loop: both rocks are new, so two landmarks are created.
    const auto first = manager.processScan(observeFrom(Pose3(), rocks), 0, isam);
    CHECK(first.summary.created == 2);
    CHECK(first.summary.matched == 0);
    apply(isam, first);

    Pose3 true_pose;
    Pose3 dead_reckoned;
    for (std::size_t side = 1; side <= kSquareSides; ++side) {
        true_pose = true_pose.compose(trueSide());
        dead_reckoned = dead_reckoned.compose(driftingSide());

        gtsam::NonlinearFactorGraph factors;
        gtsam::Values values;
        factors.add(gtsam::BetweenFactor<Pose3>(
            LandmarkManager::poseKey(side - 1), LandmarkManager::poseKey(side),
            driftingSide(), odometry_noise));
        values.insert(LandmarkManager::poseKey(side), dead_reckoned);
        isam.update(factors, values);
    }

    // Back at the start: the true pose is the origin again, but odometry thinks otherwise.
    const Pose3 origin;
    const Pose3 before = isam.calculateEstimate<Pose3>(LandmarkManager::poseKey(kSquareSides));
    const double error_before = (before.translation() - origin.translation()).norm();
    CHECK(error_before > 0.3);   // the scenario really does drift

    const auto closure = manager.processScan(observeFrom(true_pose, rocks), kSquareSides, isam);
    CHECK(closure.summary.matched == 2);
    CHECK(closure.summary.created == 0);
    CHECK(closure.summary.ambiguous == 0);
    apply(isam, closure);

    const Pose3 after = isam.calculateEstimate<Pose3>(LandmarkManager::poseKey(kSquareSides));
    const double error_after = (after.translation() - origin.translation()).norm();
    std::cout << "final position error: odometry only " << error_before
              << " m, with landmark re-observation " << error_after << " m" << std::endl;
    CHECK(error_after < 0.5 * error_before);
    CHECK(manager.landmarks().size() == 2);

    std::cout << "test_loop_closure_graph passed" << std::endl;
    return 0;
}
