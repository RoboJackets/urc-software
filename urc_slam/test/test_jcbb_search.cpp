#include <iostream>

#include "jcbb_search.hpp"
#include "mini_check.hpp"

// GTSAM-free check of the JCBB core. The pose is a pure translation error
// (d innovation / d pose = -I on the translation block), so the whole
// problem reduces to 1D positions along x.
namespace {

    urc_slam::PairTerm term(double observed_x, double landmark_x, double independent_sigma) {
        urc_slam::PairTerm t;
        t.innovation = Eigen::Vector3d(observed_x - landmark_x, 0.0, 0.0);
        t.pose_jacobian.setZero();
        t.pose_jacobian.block<3, 3>(0, 3) = -Eigen::Matrix3d::Identity();
        t.independent_covariance = Eigen::Matrix3d::Identity() * independent_sigma * independent_sigma;
        return t;
    }

    // Individual gate, same test the associator applies to one pairing.
    urc_slam::JcbbProblem problemFor(
        const std::vector<double> &observed, const std::vector<double> &landmarks, double pose_sigma
    ) {
        urc_slam::JcbbProblem problem;
        problem.num_observations = observed.size();
        problem.num_candidates = landmarks.size();
        problem.pose_covariance.setZero();
        problem.pose_covariance.diagonal() << 1e-6, 1e-6, 1e-6, pose_sigma * pose_sigma, 1e-4, 1e-4;
        for (double o : observed) {
            for (double l : landmarks) {
                urc_slam::PairTerm t = term(o, l, 0.05);
                problem.terms.push_back(t);
            }
        }
        for (std::size_t i = 0; i < observed.size(); ++i) {
            for (std::size_t j = 0; j < landmarks.size(); ++j) {
                problem.terms[i * landmarks.size() + j].individually_compatible =
                    urc_slam::jointDistanceSq(problem, {{i, j}}).has_value();
            }
        }
        return problem;
    }

}

int main() {
    // Quantiles against tabulated values (99%): chi2(1)=6.63 is outside the
    // approximation's intended range, so check dof 2, 3, 6.
    CHECK_NEAR(urc_slam::chiSquareQuantile(2, 0.99), 9.210, 0.15);
    CHECK_NEAR(urc_slam::chiSquareQuantile(3, 0.99), 11.345, 0.15);
    CHECK_NEAR(urc_slam::chiSquareQuantile(6, 0.99), 16.812, 0.2);

    // R1=0, R2=1, R3=4 (shifted by 5); observations at 5 and 8; pose sigma 1 m.
    const auto problem = problemFor({5.0, 8.0}, {5.0, 6.0, 9.0}, 1.0);

    // Both nearest-neighbour pairings pass their individual gates...
    CHECK(problem.terms[0 * 3 + 0].individually_compatible);   // obs0 -> R1
    CHECK(problem.terms[1 * 3 + 2].individually_compatible);   // obs1 -> R3
    // ...but together they imply different pose errors (0 m and 1 m).
    CHECK(!urc_slam::jointDistanceSq(problem, {{0, 0}, {1, 2}}).has_value());
    // R2 and R3 imply the same 1 m shift for both observations.
    CHECK(urc_slam::jointDistanceSq(problem, {{0, 1}, {1, 2}}).has_value());

    const auto result = urc_slam::runJcbb(problem);
    CHECK(result.best.has_value());
    CHECK(result.best->num_pairings == 2);
    CHECK(result.best->assignment[0] == 1);   // R2
    CHECK(result.best->assignment[1] == 2);   // R3
    CHECK(!result.isAmbiguous(2.0));

    // One observation midway between two landmarks: a perfect tie.
    const auto tie = urc_slam::runJcbb(problemFor({5.0}, {4.0, 6.0}, 1.0));
    CHECK(tie.best.has_value() && tie.runner_up.has_value());
    CHECK(tie.isAmbiguous(2.0));

    // Search budget is respected.
    auto tiny_budget = problem;
    tiny_budget.max_search_nodes = 1;
    CHECK(urc_slam::runJcbb(tiny_budget).budget_exhausted);

    std::cout << "test_jcbb_search passed" << std::endl;
    return 0;
}
