#ifndef URC_SLAM__SLAM_BACKEND_HPP_
#define URC_SLAM__SLAM_BACKEND_HPP_

#include <cstddef>
#include <memory>

#include <gtsam/geometry/Pose2.h>
#include <gtsam/geometry/Pose3.h>
#include <gtsam/inference/Symbol.h>
#include <gtsam/linear/NoiseModel.h>
#include <gtsam/navigation/ImuBias.h>
#include <gtsam/navigation/ImuFactor.h>
#include <gtsam/navigation/NavState.h>
#include <gtsam/navigation/PreintegrationParams.h>
#include <gtsam/nonlinear/ISAM2.h>
#include <gtsam/nonlinear/NonlinearFactorGraph.h>
#include <gtsam/nonlinear/Values.h>

namespace urc_slam
{

struct SlamBackendParameters
{
  double keyframe_translation_threshold_m;
  double keyframe_rotation_threshold_rad;
  double keyframe_maximum_interval_s;

  double pose_prior_rotation_sigma_rad;
  double pose_prior_translation_sigma_m;
  double velocity_prior_sigma_mps;
  double accelerometer_bias_prior_sigma_mps2;
  double gyroscope_bias_prior_sigma_radps;

  double wheel_translation_sigma_m;
  double wheel_yaw_sigma_rad;

  double lidar_rotation_sigma_rad;
  double lidar_translation_sigma_m;

  // Continuous-time IMU noise densities
  double accelerometer_noise_sigma;
  double gyroscope_noise_sigma;
  double integration_noise_sigma;
  double accelerometer_bias_random_walk_sigma;
  double gyroscope_bias_random_walk_sigma;
  double gravity_mps2;
};

// Keyframe factor graph over pose (map_T_base), map-frame velocity and IMU
// bias, solved incrementally with iSAM2. Factors are staged by the add
// methods and only reach the solver in optimize().
class SlamBackend
{
public:
  explicit SlamBackend(const SlamBackendParameters & parameters);

  // Adds priors for keyframe 0. base_T_imu is the IMU mounting pose in base_link.
  void initialize(
    const gtsam::NavState & initial_state,
    const gtsam::imuBias::ConstantBias & initial_bias,
    const gtsam::Pose3 & base_T_imu
  );
  bool isInitialized() const;

  bool shouldCreateKeyframe(
    const gtsam::Pose3 & predicted_pose,
    double seconds_since_keyframe
  ) const;

  // Accumulates one IMU sample into the preintegrated measurement
  // since the last keyframe
  void integrateImuMeasurement(
    const gtsam::Vector3 & measured_acc,
    const gtsam::Vector3 & measured_omega,
    double dt
  );

  // Latest keyframe state propagated through the preintegrated IMU window
  gtsam::NavState predictedState() const;
  // predictedState() expressed relative to the latest keyframe pose
  gtsam::Pose3 predictedRelativePose() const;

  // Stages a new keyframe constrained to the previous one by the IMU
  // window and returns its index
  std::size_t addImuKeyframe();

  void addLidarFactor(
    std::size_t from_index,
    std::size_t to_index,
    const gtsam::Pose3 & relative_pose
  );

  void addGpsFactor(
    std::size_t index,
    const gtsam::Point3 & position,
    const gtsam::Matrix3 & covariance
  );

  // Stages planar motion and body-frame velocity constraints; optimize() commits them.
  void addWheelOdometryFactors(
    std::size_t previous_index, std::size_t current_index,
    const gtsam::Pose2 & relative_pose, const gtsam::Vector2 & body_velocity,
    const gtsam::Vector2 & velocity_sigmas);

  // Stages rock landmark factors and new landmark values
  void addLandmarkUpdate(
    const gtsam::NonlinearFactorGraph & factors,
    const gtsam::Values & values);

  // Stages a revisit constraint between two existing keyframes, Huber-robust
  // with the given kernel width in whitened units
  void addLoopClosureFactor(
    std::size_t earlier_index, std::size_t current_index,
    const gtsam::Pose3 & relative_pose, double huber_kernel_width);

  void optimize();

  std::size_t latestIndex() const;
  gtsam::NavState latestEstimate() const;
  gtsam::Pose3 poseAt(std::size_t index) const;
  gtsam::Vector3 velocityAt(std::size_t index) const;
  // Marginal covariance of the latest pose in its tangent space, ordered
  // [rotation (rad), translation (m)] and expressed in base_link
  const gtsam::Matrix6 & latestPoseCovariance() const;
  // Marginal covariance of the latest map-frame velocity
  const gtsam::Matrix3 & latestVelocityCovariance() const;
  // Read access for components that query marginals of pose and landmark keys
  const gtsam::ISAM2 & isamGraph() const;

private:
  gtsam::Symbol poseKey(std::size_t index) const;
  gtsam::Symbol velocityKey(std::size_t index) const;
  gtsam::Symbol biasKey(std::size_t index) const;

  SlamBackendParameters parameters;

  gtsam::ISAM2 isam;
  gtsam::NonlinearFactorGraph new_factors;
  gtsam::Values new_values;
  gtsam::Values estimate;

  gtsam::SharedNoiseModel pose_prior_noise;
  gtsam::SharedNoiseModel velocity_prior_noise;
  gtsam::SharedNoiseModel bias_prior_noise;
  gtsam::SharedNoiseModel lidar_noise;

  boost::shared_ptr<gtsam::PreintegrationParams> imu_params;
  std::unique_ptr<gtsam::PreintegratedImuMeasurements> imu_preintegrator;

  std::size_t latest_index = 0;
  gtsam::Pose3 last_estimated_pose;
  gtsam::Vector3 last_estimated_velocity = gtsam::Vector3::Zero();
  gtsam::imuBias::ConstantBias last_estimated_bias;
  gtsam::Matrix6 last_pose_covariance = gtsam::Matrix6::Zero();
  gtsam::Matrix3 last_velocity_covariance = gtsam::Matrix3::Zero();
};

}  // namespace urc_slam

#endif  // URC_SLAM__SLAM_BACKEND_HPP_
