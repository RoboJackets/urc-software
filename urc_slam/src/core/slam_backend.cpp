#include "urc_slam/slam_backend.hpp"
#include "urc_slam/wheel_odometry_factors.hpp"

#include <algorithm>
#include <cmath>
#include <stdexcept>

#include <gtsam/navigation/GPSFactor.h>
#include <gtsam/nonlinear/ISAM2Params.h>
#include <gtsam/slam/BetweenFactor.h>
#include <gtsam/slam/PriorFactor.h>

namespace urc_slam
{

namespace
{
// Huber threshold in whitened units (standard deviations)
constexpr double kHuberThreshold = 1.345;
// Lower bound on the bias random-walk window to keep its noise model invertible
constexpr double kMinimumBiasWindowS = 1e-3;

gtsam::SharedNoiseModel diagonalNoise(const gtsam::Vector & sigmas)
{
  return gtsam::noiseModel::Diagonal::Sigmas(sigmas);
}

gtsam::SharedNoiseModel robustNoise(const gtsam::SharedNoiseModel & noise)
{
  return gtsam::noiseModel::Robust::Create(
    gtsam::noiseModel::mEstimator::Huber::Create(kHuberThreshold), noise);
}

gtsam::Vector6 rotationTranslationSigmas(double rotation_sigma, double translation_sigma)
{
  gtsam::Vector6 sigmas;
  sigmas << gtsam::Vector3::Constant(rotation_sigma),
    gtsam::Vector3::Constant(translation_sigma);
  return sigmas;
}

gtsam::Vector6 biasSigmas(double accelerometer_sigma, double gyroscope_sigma)
{
  gtsam::Vector6 sigmas;
  sigmas << gtsam::Vector3::Constant(accelerometer_sigma),
    gtsam::Vector3::Constant(gyroscope_sigma);
  return sigmas;
}
}  // namespace

SlamBackend::SlamBackend(const SlamBackendParameters & parameters)
: parameters(parameters),
  isam(gtsam::ISAM2Params()),
  pose_prior_noise(diagonalNoise(rotationTranslationSigmas(
      parameters.pose_prior_rotation_sigma_rad,
      parameters.pose_prior_translation_sigma_m))),
  velocity_prior_noise(diagonalNoise(
      gtsam::Vector3::Constant(parameters.velocity_prior_sigma_mps))),
  bias_prior_noise(diagonalNoise(biasSigmas(
      parameters.accelerometer_bias_prior_sigma_mps2,
      parameters.gyroscope_bias_prior_sigma_radps))),
  // Gaussian, not robust: the frontend already rejects bad alignments, and a
  // robust loss here lets a wrong IMU factor override an accepted LiDAR match
  lidar_noise(diagonalNoise(rotationTranslationSigmas(
      parameters.lidar_rotation_sigma_rad,
      parameters.lidar_translation_sigma_m)))
{
  imu_params = gtsam::PreintegrationParams::MakeSharedU(parameters.gravity_mps2);
  imu_params->accelerometerCovariance =
    gtsam::I_3x3 * std::pow(parameters.accelerometer_noise_sigma, 2);
  imu_params->gyroscopeCovariance =
    gtsam::I_3x3 * std::pow(parameters.gyroscope_noise_sigma, 2);
  imu_params->integrationCovariance =
    gtsam::I_3x3 * std::pow(parameters.integration_noise_sigma, 2);
}

void SlamBackend::initialize(
  const gtsam::NavState & initial_state,
  const gtsam::imuBias::ConstantBias & initial_bias,
  const gtsam::Pose3 & base_T_imu
)
{
  if (isInitialized()) {
    throw std::logic_error("SlamBackend::initialize called twice");
  }

  imu_params->body_P_sensor = base_T_imu;

  new_factors.add(
    gtsam::PriorFactor<gtsam::Pose3>(
      poseKey(0), initial_state.pose(), pose_prior_noise));
  new_factors.add(
    gtsam::PriorFactor<gtsam::Vector3>(
      velocityKey(0), initial_state.v(), velocity_prior_noise));
  new_factors.add(
    gtsam::PriorFactor<gtsam::imuBias::ConstantBias>(
      biasKey(0), initial_bias, bias_prior_noise));

  new_values.insert(poseKey(0), initial_state.pose());
  new_values.insert(velocityKey(0), initial_state.v());
  new_values.insert(biasKey(0), initial_bias);

  latest_index = 0;
  imu_preintegrator = std::make_unique<gtsam::PreintegratedImuMeasurements>(
    imu_params, initial_bias);
  optimize();
}

bool SlamBackend::isInitialized() const
{
  return imu_preintegrator != nullptr;
}

bool SlamBackend::shouldCreateKeyframe(
  const gtsam::Pose3 & predicted_pose,
  double seconds_since_keyframe
) const
{
  const gtsam::Pose3 motion = last_estimated_pose.between(predicted_pose);
  return motion.translation().norm() >= parameters.keyframe_translation_threshold_m ||
         gtsam::Rot3::Logmap(motion.rotation()).norm() >=
         parameters.keyframe_rotation_threshold_rad ||
         seconds_since_keyframe >= parameters.keyframe_maximum_interval_s;
}

void SlamBackend::integrateImuMeasurement(
  const gtsam::Vector3 & measured_acc,
  const gtsam::Vector3 & measured_omega,
  double dt
)
{
  imu_preintegrator->integrateMeasurement(measured_acc, measured_omega, dt);
}

gtsam::NavState SlamBackend::predictedState() const
{
  return imu_preintegrator->predict(
    gtsam::NavState(last_estimated_pose, last_estimated_velocity),
    last_estimated_bias);
}

gtsam::Pose3 SlamBackend::predictedRelativePose() const
{
  return last_estimated_pose.between(predictedState().pose());
}

std::size_t SlamBackend::addImuKeyframe()
{
  const std::size_t previous_index = latest_index;
  const std::size_t new_index = previous_index + 1;
  const gtsam::NavState predicted_state = predictedState();

  new_factors.add(
    gtsam::ImuFactor(
      poseKey(previous_index),
      velocityKey(previous_index),
      poseKey(new_index),
      velocityKey(new_index),
      biasKey(previous_index),
      *imu_preintegrator));

  // Bias random walk: sigma grows with the square root of the window length
  const double window_s = std::max(imu_preintegrator->deltaTij(), kMinimumBiasWindowS);
  new_factors.add(
    gtsam::BetweenFactor<gtsam::imuBias::ConstantBias>(
      biasKey(previous_index),
      biasKey(new_index),
      gtsam::imuBias::ConstantBias(),
      diagonalNoise(
        std::sqrt(window_s) * biasSigmas(
          parameters.accelerometer_bias_random_walk_sigma,
          parameters.gyroscope_bias_random_walk_sigma))));

  new_values.insert(poseKey(new_index), predicted_state.pose());
  new_values.insert(velocityKey(new_index), predicted_state.v());
  new_values.insert(biasKey(new_index), last_estimated_bias);

  latest_index = new_index;
  return new_index;
}

void SlamBackend::addLidarFactor(
  std::size_t from_index,
  std::size_t to_index,
  const gtsam::Pose3 & relative_pose
)
{
  new_factors.add(
    gtsam::BetweenFactor<gtsam::Pose3>(
      poseKey(from_index), poseKey(to_index), relative_pose, lidar_noise));
}

void SlamBackend::addGpsFactor(
  std::size_t index,
  const gtsam::Point3 & position,
  const gtsam::Matrix3 & covariance
)
{
  new_factors.add(
    gtsam::GPSFactor(
      poseKey(index),
      position,
      robustNoise(gtsam::noiseModel::Gaussian::Covariance(covariance))));
}

void SlamBackend::addWheelOdometryFactors(
  std::size_t previous_index, std::size_t current_index,
  const gtsam::Pose2 & relative_pose, const gtsam::Vector2 & body_velocity,
  const gtsam::Vector2 & velocity_sigmas)
{
  const auto pose_noise = diagonalNoise(
    gtsam::Vector3(
      parameters.wheel_translation_sigma_m, parameters.wheel_translation_sigma_m,
      parameters.wheel_yaw_sigma_rad));
  new_factors.emplace_shared<WheelPoseFactor>(
    poseKey(previous_index), poseKey(current_index), relative_pose, pose_noise);
  new_factors.emplace_shared<WheelVelocityFactor>(
    poseKey(current_index), velocityKey(current_index), body_velocity, diagonalNoise(
      velocity_sigmas));
}

void SlamBackend::addLandmarkUpdate(
  const gtsam::NonlinearFactorGraph & factors,
  const gtsam::Values & values)
{
  new_factors.push_back(factors);
  new_values.insert(values);
}

void SlamBackend::addLoopClosureFactor(
  std::size_t earlier_index, std::size_t current_index,
  const gtsam::Pose3 & relative_pose, double huber_kernel_width)
{
  new_factors.add(
    gtsam::BetweenFactor<gtsam::Pose3>(
      poseKey(earlier_index), poseKey(current_index), relative_pose,
      gtsam::noiseModel::Robust::Create(
        gtsam::noiseModel::mEstimator::Huber::Create(huber_kernel_width), lidar_noise)));
}

void SlamBackend::optimize()
{
  const bool added_keyframe = new_values.exists(poseKey(latest_index));

  isam.update(new_factors, new_values);
  new_factors.resize(0);
  new_values.clear();
  estimate = isam.calculateEstimate();

  last_estimated_pose = estimate.at<gtsam::Pose3>(poseKey(latest_index));
  last_estimated_velocity = estimate.at<gtsam::Vector3>(velocityKey(latest_index));
  last_estimated_bias = estimate.at<gtsam::imuBias::ConstantBias>(biasKey(latest_index));
  last_pose_covariance = isam.marginalCovariance(poseKey(latest_index));
  last_velocity_covariance = isam.marginalCovariance(velocityKey(latest_index));

  if (added_keyframe) {
    imu_preintegrator->resetIntegrationAndSetBias(last_estimated_bias);
  }
}

std::size_t SlamBackend::latestIndex() const
{
  return latest_index;
}

gtsam::NavState SlamBackend::latestEstimate() const
{
  return gtsam::NavState(last_estimated_pose, last_estimated_velocity);
}

gtsam::Pose3 SlamBackend::poseAt(std::size_t index) const
{
  return estimate.at<gtsam::Pose3>(poseKey(index));
}

gtsam::Vector3 SlamBackend::velocityAt(std::size_t index) const
{
  return estimate.at<gtsam::Vector3>(velocityKey(index));
}

const gtsam::Matrix6 & SlamBackend::latestPoseCovariance() const
{
  return last_pose_covariance;
}

const gtsam::Matrix3 & SlamBackend::latestVelocityCovariance() const
{
  return last_velocity_covariance;
}

const gtsam::ISAM2 & SlamBackend::isamGraph() const
{
  return isam;
}

gtsam::Symbol SlamBackend::poseKey(std::size_t index) const
{
  return gtsam::Symbol('x', index);
}

gtsam::Symbol SlamBackend::velocityKey(std::size_t index) const
{
  return gtsam::Symbol('v', index);
}

gtsam::Symbol SlamBackend::biasKey(std::size_t index) const
{
  return gtsam::Symbol('b', index);
}

}  // namespace urc_slam
