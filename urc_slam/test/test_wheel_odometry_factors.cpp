#include <cmath>

#include <gtsam/base/numericalDerivative.h>
#include <gtsam/inference/Symbol.h>
#include <gtsam/nonlinear/LevenbergMarquardtOptimizer.h>
#include <gtsam/slam/PriorFactor.h>

#include "mini_check.hpp"
#include "urc_slam/wheel_odometry_factors.hpp"

namespace
{

void checkRelativePose()
{
  const double right_angle = std::acos(-1.0) / 2.0;
  const gtsam::Pose3 previous(gtsam::Rot3::Yaw(right_angle), gtsam::Point3(3.0, 4.0, 0.0));
  const gtsam::Pose3 current(gtsam::Rot3::Yaw(2.0 * right_angle), gtsam::Point3(3.0, 6.0, 0.0));
  const gtsam::Pose2 measurement = gtsam::Pose2(3.0, 4.0, right_angle).between(
    gtsam::Pose2(3.0, 6.0, 2.0 * right_angle));
  CHECK_NEAR(measurement.x(), 2.0, 1e-9);
  CHECK_NEAR(measurement.y(), 0.0, 1e-9);
  CHECK_NEAR(measurement.theta(), right_angle, 1e-9);

  urc_slam::WheelPoseFactor factor(
    0, 1, measurement, gtsam::noiseModel::Isotropic::Sigma(3, 1.0));
  CHECK(factor.evaluateError(previous, current).norm() < 1e-9);
  const gtsam::Pose3 no_turn(previous.rotation(), current.translation());
  CHECK_NEAR(std::abs(factor.evaluateError(previous, no_turn)[2]), right_angle, 1e-9);
  const gtsam::Pose3 elevated(current.rotation(), gtsam::Point3(3.0, 6.0, 5.0));
  CHECK(factor.evaluateError(previous, elevated).norm() < 1e-9);

  gtsam::Matrix first_jacobian, second_jacobian;
  factor.evaluateError(previous, current, first_jacobian, second_jacobian);
  CHECK(first_jacobian.rows() == 3 && first_jacobian.cols() == 6);
  CHECK(second_jacobian.rows() == 3 && second_jacobian.cols() == 6);
  CHECK(first_jacobian.allFinite() && second_jacobian.allFinite());
}

void checkBodyVelocity()
{
  const gtsam::Pose3 pose(gtsam::Rot3::Ypr(1.3, 0.2, -0.1), gtsam::Point3(4.0, 2.0, 3.0));
  const gtsam::Vector2 measurement(2.0, -0.4);
  const gtsam::Vector3 map_velocity = pose.rotation().rotate(gtsam::Vector3(2.0, -0.4, 0.7));
  urc_slam::WheelVelocityFactor factor(
    0, 1, measurement, gtsam::noiseModel::Isotropic::Sigma(2, 1.0));
  gtsam::Matrix pose_jacobian, velocity_jacobian;
  CHECK(factor.evaluateError(pose, map_velocity, pose_jacobian, velocity_jacobian).norm() < 1e-9);
  CHECK(factor.evaluateError(gtsam::Pose3(), map_velocity).norm() > 0.5);

  const auto error = [&factor](const gtsam::Pose3 & p, const gtsam::Vector3 & v) {
      return gtsam::Vector2(factor.evaluateError(p, v));
    };
  CHECK(
    pose_jacobian.isApprox(
      (gtsam::numericalDerivative21<
        gtsam::Vector2, gtsam::Pose3, gtsam::Vector3>(error, pose, map_velocity)), 1e-6));
  CHECK(
    velocity_jacobian.isApprox(
      (gtsam::numericalDerivative22<
        gtsam::Vector2, gtsam::Pose3, gtsam::Vector3>(error, pose, map_velocity)), 1e-6));
}

void checkTurningVelocityOptimization()
{
  gtsam::NonlinearFactorGraph graph;
  gtsam::Values initial;
  const auto pose_noise = gtsam::noiseModel::Isotropic::Sigma(6, 1e-4);
  const auto velocity_noise = gtsam::noiseModel::Isotropic::Sigma(3, 10.0);
  const auto wheel_noise = gtsam::noiseModel::Isotropic::Sigma(2, 1e-3);
  const double right_angle = std::acos(-1.0) / 2.0;
  for (std::size_t index = 0; index < 4; ++index) {
    const gtsam::Symbol pose_key('x', index), velocity_key('v', index);
    const gtsam::Pose3 pose(gtsam::Rot3::Yaw(index * right_angle), gtsam::Point3());
    graph.add(gtsam::PriorFactor<gtsam::Pose3>(pose_key, pose, pose_noise));
    graph.add(
      gtsam::PriorFactor<gtsam::Vector3>(
        velocity_key, gtsam::Vector3::Zero(), velocity_noise));
    graph.emplace_shared<urc_slam::WheelVelocityFactor>(
      pose_key, velocity_key, gtsam::Vector2(2.0, 0.0), wheel_noise);
    initial.insert(pose_key, pose);
    initial.insert(velocity_key, gtsam::Vector3(0.0, 0.0, 0.0));
  }
  const auto result = gtsam::LevenbergMarquardtOptimizer(graph, initial).optimize();
  for (std::size_t index = 0; index < 4; ++index) {
    const auto velocity = result.at<gtsam::Vector3>(gtsam::Symbol('v', index));
    CHECK_NEAR(velocity.x(), 2.0 * std::cos(index * right_angle), 1e-5);
    CHECK_NEAR(velocity.y(), 2.0 * std::sin(index * right_angle), 1e-5);
  }
}

}  // namespace

int main()
{
  checkRelativePose();
  checkBodyVelocity();
  checkTurningVelocityOptimization();
  return 0;
}
