#include <cmath>
#include <iostream>

#include "loop_closure_screening.hpp"
#include "mini_check.hpp"

namespace {

    // A 10 m radius circle, one keyframe per metre of path.
    std::vector<urc_slam::KeyframePosition> circle(std::size_t count) {
        std::vector<urc_slam::KeyframePosition> keyframes;
        const double radius = 10.0;
        for (std::size_t i = 0; i < count; ++i) {
            const double angle = static_cast<double>(i) / radius;
            urc_slam::KeyframePosition k;
            k.index = i;
            k.position = Eigen::Vector3d(radius * std::cos(angle), radius * std::sin(angle), 0.0);
            k.path_length_m = static_cast<double>(i);
            keyframes.push_back(k);
        }
        return keyframes;
    }

}

int main() {
    const urc_slam::LoopCandidateParams params;   // base 3 m, 3 sigma, cap 25 m, gaps 20 / 20 m

    // Radius grows with uncertainty and is capped.
    CHECK_NEAR(urc_slam::searchRadius(0.0, params), 3.0, 1e-9);
    CHECK_NEAR(urc_slam::searchRadius(2.0, params), 9.0, 1e-9);
    CHECK_NEAR(urc_slam::searchRadius(100.0, params), 25.0, 1e-9);

    // Walk the circle (circumference ~63 m) and arrive near the start.
    const auto all = circle(64);
    const urc_slam::KeyframePosition current = all.back();
    const std::vector<urc_slam::KeyframePosition> earlier(all.begin(), all.end() - 1);

    // The revisited start of the loop is found; the trail right behind the
    // robot (inside the index and path gap) is not.
    const auto found = urc_slam::findLoopCandidates(current, earlier, 0.0, params);
    CHECK(!found.empty() && found.size() <= params.max_candidates);
    for (std::size_t index : found) {
        CHECK(current.index - index >= params.min_index_gap);
        CHECK(index <= 5);
    }

    // Pose uncertainty too small for the displacement: nothing is in range.
    auto displaced = current;
    displaced.position += Eigen::Vector3d(20.0, 0.0, 0.0);
    CHECK(urc_slam::findLoopCandidates(displaced, earlier, 0.0, params).empty());
    // Same displacement, but the graph says it could be off by ~7 m: in range.
    CHECK(!urc_slam::findLoopCandidates(displaced, earlier, 7.0, params).empty());

    // Gate: a 1 m translation passes when sigma is 1 m, fails when sigma is 5 cm.
    Eigen::Matrix<double, 6, 1> correction = Eigen::Matrix<double, 6, 1>::Zero();
    correction(3) = 1.0;
    const Eigen::Matrix<double, 6, 6> loose = Eigen::Matrix<double, 6, 6>::Identity();
    CHECK(urc_slam::gateCorrection(correction, loose, 0.99).plausible);
    CHECK_NEAR(urc_slam::gateCorrection(correction, loose, 0.99).distance_sq, 1.0, 1e-9);
    const Eigen::Matrix<double, 6, 6> tight = Eigen::Matrix<double, 6, 6>::Identity() * 0.05 * 0.05;
    CHECK(!urc_slam::gateCorrection(correction, tight, 0.99).plausible);
    // A singular covariance is never plausible.
    CHECK(!urc_slam::gateCorrection(correction, Eigen::Matrix<double, 6, 6>::Zero(), 0.99).plausible);

    std::cout << "test_loop_closure_screening passed" << std::endl;
    return 0;
}
