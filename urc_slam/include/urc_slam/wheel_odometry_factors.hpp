#ifndef URC_SLAM__WHEEL_ODOMETRY_FACTORS_HPP_
#define URC_SLAM__WHEEL_ODOMETRY_FACTORS_HPP_

#include <gtsam/geometry/Pose2.h>
#include <gtsam/geometry/Pose3.h>
#include <gtsam/nonlinear/NonlinearFactor.h>

namespace urc_slam
{

// Wheel odometry measures relative x/y/yaw, not height, roll, or pitch.
class WheelPoseFactor : public gtsam::NoiseModelFactor2<gtsam::Pose3, gtsam::Pose3>
{
public:
  WheelPoseFactor(
    gtsam::Key previous, gtsam::Key current, const gtsam::Pose2 & measurement,
    const gtsam::SharedNoiseModel & noise);

  gtsam::Vector evaluateError(
    const gtsam::Pose3 & previous, const gtsam::Pose3 & current,
    boost::optional<gtsam::Matrix &> previous_jacobian = boost::none,
    boost::optional<gtsam::Matrix &> current_jacobian = boost::none) const override;

private:
  gtsam::Pose2 measurement_;
};

// Graph velocities are in map; measured x/y velocities are in base_link.
class WheelVelocityFactor : public gtsam::NoiseModelFactor2<gtsam::Pose3, gtsam::Vector3>
{
public:
  WheelVelocityFactor(
    gtsam::Key pose, gtsam::Key velocity, const gtsam::Vector2 & measurement,
    const gtsam::SharedNoiseModel & noise);

  gtsam::Vector evaluateError(
    const gtsam::Pose3 & pose, const gtsam::Vector3 & map_velocity,
    boost::optional<gtsam::Matrix &> pose_jacobian = boost::none,
    boost::optional<gtsam::Matrix &> velocity_jacobian = boost::none) const override;

private:
  gtsam::Vector2 measurement_;
};

}  // namespace urc_slam

#endif  // URC_SLAM__WHEEL_ODOMETRY_FACTORS_HPP_
