#include "urc_slam/wheel_odometry_factors.hpp"

#include <gtsam/base/numericalDerivative.h>
#include <gtsam/geometry/Rot2.h>

namespace urc_slam
{

WheelPoseFactor::WheelPoseFactor(
  gtsam::Key previous, gtsam::Key current, const gtsam::Pose2 & measurement,
  const gtsam::SharedNoiseModel & noise)
: NoiseModelFactor2(noise, previous, current), measurement_(measurement)
{
}

gtsam::Vector WheelPoseFactor::evaluateError(
  const gtsam::Pose3 & previous, const gtsam::Pose3 & current,
  boost::optional<gtsam::Matrix &> previous_jacobian,
  boost::optional<gtsam::Matrix &> current_jacobian) const
{
  const auto residual = [this](const gtsam::Pose3 & from, const gtsam::Pose3 & to) {
      const auto relative = from.between(to);
      return gtsam::Vector3(
        relative.x() - measurement_.x(), relative.y() - measurement_.y(),
        measurement_.rotation().between(gtsam::Rot2(relative.rotation().yaw())).theta());
    };
  if (previous_jacobian) {
    *previous_jacobian = gtsam::numericalDerivative21<
      gtsam::Vector3, gtsam::Pose3, gtsam::Pose3>(residual, previous, current);
  }
  if (current_jacobian) {
    *current_jacobian = gtsam::numericalDerivative22<
      gtsam::Vector3, gtsam::Pose3, gtsam::Pose3>(residual, previous, current);
  }
  return residual(previous, current);
}

WheelVelocityFactor::WheelVelocityFactor(
  gtsam::Key pose, gtsam::Key velocity, const gtsam::Vector2 & measurement,
  const gtsam::SharedNoiseModel & noise)
: NoiseModelFactor2(noise, pose, velocity), measurement_(measurement)
{
}

gtsam::Vector WheelVelocityFactor::evaluateError(
  const gtsam::Pose3 & pose, const gtsam::Vector3 & map_velocity,
  boost::optional<gtsam::Matrix &> pose_jacobian,
  boost::optional<gtsam::Matrix &> velocity_jacobian) const
{
  gtsam::Matrix33 rotation_jacobian;
  gtsam::Matrix33 map_velocity_jacobian;
  const gtsam::Vector3 body_velocity = pose.rotation().unrotate(
    map_velocity, rotation_jacobian, map_velocity_jacobian);
  if (pose_jacobian) {
    *pose_jacobian = gtsam::Matrix::Zero(2, 6);
    pose_jacobian->leftCols<3>() = rotation_jacobian.topRows<2>();
  }
  if (velocity_jacobian) {
    *velocity_jacobian = map_velocity_jacobian.topRows<2>();
  }
  return gtsam::Vector2(body_velocity.x(), body_velocity.y()) - measurement_;
}

}  // namespace urc_slam
