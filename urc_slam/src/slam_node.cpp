#include "urc_slam/slam_node.hpp"

#include <chrono>
#include <cmath>
#include <functional>

#include <gtsam/geometry/Rot3.h>
#include <gtsam/navigation/ImuBias.h>
#include <gtsam/navigation/NavState.h>
#include <pcl_conversions/pcl_conversions.h>
#include <tf2/exceptions.hpp>
#include <tf2/time.hpp>

namespace urc_slam
{

namespace
{
// About 20 s of IMU history at 100 Hz, enough to bridge a LiDAR dropout
constexpr std::size_t kImuBufferCapacity = 2000;
// Deep enough that 100 Hz IMU samples queue up while GICP blocks the executor
constexpr std::size_t kImuSubscriptionDepth = 200;
constexpr std::size_t kGpsBufferCapacity = 200;
constexpr double kUnitQuaternionTolerance = 1e-3;
constexpr int kWarningThrottleMs = 1000;
// The starting orientation is taken only once the rover has settled, e.g. after
// dropping in at spawn, so a transient tilt is not mistaken for gravity
constexpr double kSettledWindowS = 1.0;
constexpr double kSettledMaximumRotationRad = 0.05;

std::optional<gtsam::Rot3> toValidRotation(const sensor_msgs::msg::Imu & msg)
{
  // A negative first covariance element means the driver provides no orientation
  if (msg.orientation_covariance[0] < 0.0) {
    return std::nullopt;
  }
  const gtsam::Quaternion orientation(
    msg.orientation.w, msg.orientation.x, msg.orientation.y, msg.orientation.z);
  if (std::abs(orientation.norm() - 1.0) >= kUnitQuaternionTolerance) {
    return std::nullopt;
  }
  return gtsam::Rot3(orientation.normalized());
}

GpsMeasurement toGpsMeasurement(const nav_msgs::msg::Odometry & msg)
{
  const auto & position = msg.pose.pose.position;
  gtsam::Matrix3 covariance;
  for (int row = 0; row < 3; ++row) {
    for (int col = 0; col < 3; ++col) {
      covariance(row, col) = msg.pose.covariance[row * 6 + col];
    }
  }
  return {
    rclcpp::Time(msg.header.stamp),
    gtsam::Point3(position.x, position.y, position.z),
    covariance
  };
}
}  // namespace

SlamNode::SlamNode(const rclcpp::NodeOptions & options)
: rclcpp::Node("slam_node", options),
  parameters(declareSlamParameters(*this)),
  output_frames{parameters.frames.map, parameters.frames.base_link},
  lidar_frontend(parameters.lidar_frontend),
  backend(parameters.backend),
  imu_buffer(kImuBufferCapacity),
  gps_matcher(parameters.gps_time_tolerance_s, kGpsBufferCapacity),
  keyframe_map(parameters.map_voxel_size_m, parameters.lidar_frontend.voxel_size_m)
{
  // Identity initialization disabled: the backend is now initialized at the
  // first keyframe from the IMU's roll and pitch, so gravity does not leak
  // into the IMU prediction when the rover starts tilted.
  // backend.initialize(
  //     gtsam::NavState(
  //         gtsam::Pose3(),
  //         gtsam::Vector3::Zero()
  //     ),
  //     gtsam::imuBias::ConstantBias()
  // );

  tf_buffer = std::make_shared<tf2_ros::Buffer>(get_clock());
  tf_listener = std::make_shared<tf2_ros::TransformListener>(*tf_buffer, this);
  tf_broadcaster = std::make_unique<tf2_ros::TransformBroadcaster>(*this);

  imu_sub = create_subscription<sensor_msgs::msg::Imu>(
    parameters.topics.imu,
    rclcpp::SensorDataQoS().keep_last(kImuSubscriptionDepth),
    std::bind(&SlamNode::imuCallback, this, std::placeholders::_1));
  lidar_sub = create_subscription<sensor_msgs::msg::PointCloud2>(
    parameters.topics.lidar,
    rclcpp::SensorDataQoS(),
    std::bind(&SlamNode::lidarCallback, this, std::placeholders::_1));
  gps_sub = create_subscription<nav_msgs::msg::Odometry>(
    parameters.topics.gps,
    rclcpp::SensorDataQoS(),
    std::bind(&SlamNode::gpsCallback, this, std::placeholders::_1));

  odometry_pub = create_publisher<nav_msgs::msg::Odometry>(parameters.topics.odometry, 10);
  path_pub = create_publisher<nav_msgs::msg::Path>(parameters.topics.path, 10);
  map_pub = create_publisher<sensor_msgs::msg::PointCloud2>(
    parameters.topics.map, rclcpp::QoS(1).reliable().transient_local());
  map_timer = create_wall_timer(
    std::chrono::duration<double>(parameters.map_publish_period_s),
    std::bind(&SlamNode::publishMap, this));

  path_msg.header.frame_id = parameters.frames.map;
}

void SlamNode::imuCallback(const sensor_msgs::msg::Imu::SharedPtr msg)
{
  imu_buffer.push(
    {
      rclcpp::Time(msg->header.stamp),
      gtsam::Vector3(
        msg->linear_acceleration.x, msg->linear_acceleration.y, msg->linear_acceleration.z),
      gtsam::Vector3(
        msg->angular_velocity.x, msg->angular_velocity.y, msg->angular_velocity.z)
    });

  imu_frame_id = msg->header.frame_id;
  if (backend.isInitialized()) {
    return;
  }
  if (const auto orientation = toValidRotation(*msg)) {
    const rclcpp::Time stamp(msg->header.stamp);
    recent_imu_orientations.push_back({stamp, *orientation});
    while ((stamp - recent_imu_orientations.front().first).seconds() > kSettledWindowS) {
      recent_imu_orientations.pop_front();
    }
  }
}

std::optional<gtsam::Rot3> SlamNode::settledImuOrientation() const
{
  if (recent_imu_orientations.size() < 2) {
    return std::nullopt;
  }
  const auto & [newest_stamp, newest] = recent_imu_orientations.back();
  const double span_s = (newest_stamp - recent_imu_orientations.front().first).seconds();
  if (span_s < 0.9 * kSettledWindowS) {
    return std::nullopt;
  }
  for (const auto & [stamp, orientation] : recent_imu_orientations) {
    if (gtsam::Rot3::Logmap(newest.between(orientation)).norm() > kSettledMaximumRotationRad) {
      return std::nullopt;
    }
  }
  return newest;
}

void SlamNode::lidarCallback(const sensor_msgs::msg::PointCloud2::SharedPtr msg)
{
  const rclcpp::Time stamp(msg->header.stamp);
  if (!backend.isInitialized()) {
    initializeAtScan(*msg);
    return;
  }
  if (!integrateImuUntil(stamp)) {
    return;
  }
  processScan(*msg, stamp);
}

void SlamNode::gpsCallback(const nav_msgs::msg::Odometry::SharedPtr msg)
{
  if (msg->header.frame_id != parameters.frames.map) {
    RCLCPP_WARN_THROTTLE(
      get_logger(), *get_clock(), kWarningThrottleMs,
      "Ignoring GPS odometry in frame '%s'; expected '%s'",
      msg->header.frame_id.c_str(), parameters.frames.map.c_str());
    return;
  }
  const GpsAddResult result = gps_matcher.add(toGpsMeasurement(*msg));
  if (result == GpsAddResult::Invalid) {
    RCLCPP_WARN_THROTTLE(
      get_logger(), *get_clock(), kWarningThrottleMs,
      "Rejected GPS fix with a non-finite position or invalid covariance");
  }
  if (result != GpsAddResult::Accepted) {
    return;
  }
  if (applyGpsMatches()) {
    path_pub->publish(path_msg);
  }
}

void SlamNode::publishMap()
{
  if (keyframe_map.size() == 0 || !keyframe_map.update(poseLookup())) {
    return;
  }
  sensor_msgs::msg::PointCloud2 map_msg;
  pcl::toROSMsg(keyframe_map.mapCloud(), map_msg);
  map_msg.header.stamp = keyframe_map.stamps().back();
  map_msg.header.frame_id = parameters.frames.map;
  map_pub->publish(map_msg);
}

void SlamNode::initializeAtScan(const sensor_msgs::msg::PointCloud2 & msg)
{
  const std::optional<gtsam::Rot3> imu_orientation = settledImuOrientation();
  if (!imu_orientation) {
    RCLCPP_WARN_THROTTLE(
      get_logger(), *get_clock(), kWarningThrottleMs,
      "Waiting for a settled IMU orientation to initialize SLAM");
    return;
  }
  const auto lidar_extrinsic = lookupBaseTransform(msg.header.frame_id);
  const auto imu_extrinsic = lookupBaseTransform(imu_frame_id);
  if (!lidar_extrinsic || !imu_extrinsic) {
    return;
  }
  base_T_lidar = *lidar_extrinsic;

  const LidarFrontend::Cloud::Ptr cloud = preprocessScan(msg);
  if (cloud->empty()) {
    RCLCPP_WARN_THROTTLE(
      get_logger(), *get_clock(), kWarningThrottleMs,
      "First LiDAR scan is empty after filtering; waiting for another");
    return;
  }

  // Gravity fixes roll and pitch only; yaw stays zero so the map x-axis is
  // the starting heading
  const gtsam::Rot3 measured_map_R_base =
    imu_orientation->compose(imu_extrinsic->rotation().inverse());
  const gtsam::Rot3 initial_rotation = gtsam::Rot3::Ypr(
    0.0, measured_map_R_base.pitch(), measured_map_R_base.roll());

  const rclcpp::Time stamp(msg.header.stamp);
  backend.initialize(
    gtsam::NavState(
      gtsam::Pose3(initial_rotation, gtsam::Point3::Zero()),
      gtsam::Vector3::Zero()),
    gtsam::imuBias::ConstantBias(),
    *imu_extrinsic);
  imu_buffer.startWindowAt(stamp);
  commitKeyframe(stamp, cloud);

  RCLCPP_INFO(
    get_logger(), "SLAM initialized (roll %.3f rad, pitch %.3f rad)",
    initial_rotation.roll(), initial_rotation.pitch());
}

bool SlamNode::integrateImuUntil(const rclcpp::Time & stamp)
{
  const ImuWindow window = imu_buffer.takeUntil(stamp);
  if (window.status == ImuWindowStatus::WaitingForData) {
    RCLCPP_WARN_THROTTLE(
      get_logger(), *get_clock(), kWarningThrottleMs,
      "Waiting for IMU data to reach the LiDAR scan stamp");
    return false;
  }
  if (window.status == ImuWindowStatus::StaleStamp) {
    RCLCPP_WARN_THROTTLE(
      get_logger(), *get_clock(), kWarningThrottleMs,
      "Skipping LiDAR scan that is not newer than the last processed scan");
    return false;
  }
  if (window.largest_gap_s > parameters.imu_maximum_gap_s) {
    RCLCPP_WARN_THROTTLE(
      get_logger(), *get_clock(), kWarningThrottleMs,
      "IMU gap of %.3f s; integrating it with the next sample held constant",
      window.largest_gap_s);
  }

  for (const ImuMeasurement & measurement : window.measurements) {
    if (measurement.dt > 0.0) {
      backend.integrateImuMeasurement(
        measurement.acceleration, measurement.angular_velocity, measurement.dt);
    }
  }
  return true;
}

LidarFrontend::Cloud::Ptr SlamNode::preprocessScan(
  const sensor_msgs::msg::PointCloud2 & msg
) const
{
  LidarFrontend::Cloud sensor_cloud;
  pcl::fromROSMsg(msg, sensor_cloud);
  return lidar_frontend.preprocess(sensor_cloud, base_T_lidar);
}

// Every scan is registered against the local submap so that published odometry
// is LiDAR-corrected; only scans passing the keyframe gate enter the factor graph
void SlamNode::processScan(
  const sensor_msgs::msg::PointCloud2 & msg,
  const rclcpp::Time & stamp
)
{
  const gtsam::NavState predicted_state = backend.predictedState();
  const LidarFrontend::Cloud::Ptr cloud = preprocessScan(msg);
  if (cloud->empty()) {
    RCLCPP_WARN_THROTTLE(
      get_logger(), *get_clock(), kWarningThrottleMs,
      "Discarding empty LiDAR cloud");
    publishState(predicted_state, stamp);
    return;
  }

  const auto relative_pose = registerScan(cloud, backend.predictedRelativePose());
  consecutive_registration_failures = relative_pose ? 0 : consecutive_registration_failures + 1;
  const gtsam::NavState scan_state = relative_pose ?
    gtsam::NavState(backend.latestEstimate().pose().compose(*relative_pose), predicted_state.v()) :
    predicted_state;

  const double seconds_since_keyframe = (stamp - keyframe_map.stamps().back()).seconds();
  if (!backend.shouldCreateKeyframe(scan_state.pose(), seconds_since_keyframe)) {
    publishState(scan_state, stamp);
    return;
  }
  addKeyframe(stamp, cloud, relative_pose, scan_state);
}

void SlamNode::addKeyframe(
  const rclcpp::Time & stamp,
  const LidarFrontend::Cloud::Ptr & cloud,
  const std::optional<gtsam::Pose3> & relative_pose,
  const gtsam::NavState & scan_state
)
{
  const bool imu_only_keyframe_due =
    consecutive_registration_failures >= parameters.registration_maximum_consecutive_failures;
  if (!relative_pose && !imu_only_keyframe_due) {
    publishState(scan_state, stamp);
    return;
  }

  const std::size_t previous_index = backend.latestIndex();
  const std::size_t index = backend.addImuKeyframe();
  if (relative_pose) {
    backend.addLidarFactor(previous_index, index, *relative_pose);
  } else {
    RCLCPP_WARN(
      get_logger(),
      "%d consecutive LiDAR registration failures; adding an IMU-only keyframe",
      consecutive_registration_failures);
    consecutive_registration_failures = 0;
  }

  backend.optimize();
  if (relative_pose) {
    // Large disagreement means the IMU factor is overriding the LiDAR measurement
    const gtsam::Pose3 optimized_motion =
      backend.poseAt(previous_index).between(backend.poseAt(index));
    RCLCPP_DEBUG(
      get_logger(), "Keyframe %zu: LiDAR moved %.3f m, optimizer moved %.3f m (difference %.3f m)",
      index, relative_pose->translation().norm(), optimized_motion.translation().norm(),
      (optimized_motion.translation() - relative_pose->translation()).norm());
  }
  commitKeyframe(stamp, cloud);
}

std::optional<gtsam::Pose3> SlamNode::registerScan(
  const LidarFrontend::Cloud::Ptr & cloud,
  const gtsam::Pose3 & imu_relative_guess
)
{
  const LidarFrontend::Cloud::Ptr submap = keyframe_map.buildLocalSubmap(
    static_cast<std::size_t>(parameters.registration_submap_keyframes), poseLookup());

  // Identity is the fallback guess for when IMU drift makes the prediction unusable
  const auto registration_start = std::chrono::steady_clock::now();
  const LidarRegistrationResult result = lidar_frontend.registerClouds(
    submap, cloud, {imu_relative_guess, gtsam::Pose3()});
  const double registration_ms = std::chrono::duration<double, std::milli>(
    std::chrono::steady_clock::now() - registration_start).count();

  if (result.accepted) {
    RCLCPP_DEBUG(
      get_logger(),
      "LiDAR registration accepted in %.0f ms (%zu source, %zu target points, "
      "fitness %.3f m^2, inliers %.2f)",
      registration_ms, cloud->size(), submap->size(),
      result.fitness_score_m2, result.inlier_fraction);
    return result.relative_pose;
  }

  RCLCPP_WARN_THROTTLE(
    get_logger(), *get_clock(), kWarningThrottleMs,
    "LiDAR registration rejected after %.0f ms (converged: %s, fitness %.3f m^2, "
    "inliers %.2f, IMU guess %.2f m / %.3f rad)",
    registration_ms,
    result.converged ? "yes" : "no",
    result.fitness_score_m2,
    result.inlier_fraction,
    imu_relative_guess.translation().norm(),
    gtsam::Rot3::Logmap(imu_relative_guess.rotation()).norm());
  return std::nullopt;
}

void SlamNode::commitKeyframe(const rclcpp::Time & stamp, const LidarFrontend::Cloud::Ptr & cloud)
{
  const gtsam::NavState state = backend.latestEstimate();
  keyframe_map.addKeyframe(stamp, cloud, state.pose());
  path_msg.poses.push_back(toPoseStampedMsg(state.pose(), stamp, parameters.frames.map));

  applyGpsMatches();
  publishState(backend.latestEstimate(), stamp);
  path_msg.header.stamp = stamp;
  path_pub->publish(path_msg);
}

bool SlamNode::applyGpsMatches()
{
  const std::vector<GpsKeyframeMatch> matches = gps_matcher.takeMatches(keyframe_map.stamps());
  if (matches.empty()) {
    return false;
  }
  for (const GpsKeyframeMatch & match : matches) {
    // Shift the fix to the keyframe's time using the keyframe's estimated
    // velocity, so the matching tolerance does not become position error
    const double keyframe_minus_fix_s =
      (keyframe_map.stamps()[match.keyframe_index] - match.measurement.stamp).seconds();
    const gtsam::Point3 position_at_keyframe = match.measurement.position +
      keyframe_minus_fix_s * backend.velocityAt(match.keyframe_index);
    backend.addGpsFactor(
      match.keyframe_index, position_at_keyframe, match.measurement.covariance);
  }
  backend.optimize();
  keyframe_map.markPosesChanged();
  rebuildPath();
  return true;
}

void SlamNode::publishState(const gtsam::NavState & state, const rclcpp::Time & stamp)
{
  odometry_pub->publish(
    toOdometryMsg(
      state,
      backend.latestPoseCovariance(),
      backend.latestVelocityCovariance(),
      stamp,
      output_frames));
  if (parameters.frames.publish_tf) {
    tf_broadcaster->sendTransform(toTransformMsg(state.pose(), stamp, output_frames));
  }
}

void SlamNode::rebuildPath()
{
  const std::vector<rclcpp::Time> & stamps = keyframe_map.stamps();
  path_msg.poses.clear();
  path_msg.poses.reserve(stamps.size());
  for (std::size_t index = 0; index < stamps.size(); ++index) {
    path_msg.poses.push_back(
      toPoseStampedMsg(backend.poseAt(index), stamps[index], parameters.frames.map));
  }
  path_msg.header.stamp = stamps.back();
}

std::optional<gtsam::Pose3> SlamNode::lookupBaseTransform(const std::string & frame_id)
{
  if (frame_id.empty() || frame_id == parameters.frames.base_link) {
    return gtsam::Pose3();
  }
  try {
    return toPose3(
      tf_buffer->lookupTransform(
        parameters.frames.base_link, frame_id, tf2::TimePointZero).transform);
  } catch (const tf2::TransformException & exception) {
    RCLCPP_WARN_THROTTLE(
      get_logger(), *get_clock(), kWarningThrottleMs,
      "Waiting for transform %s -> %s: %s",
      parameters.frames.base_link.c_str(), frame_id.c_str(), exception.what());
    return std::nullopt;
  }
}

KeyframeMap::PoseLookup SlamNode::poseLookup() const
{
  return [this](std::size_t index) {return backend.poseAt(index);};
}

}  // namespace urc_slam

#include <rclcpp_components/register_node_macro.hpp>
RCLCPP_COMPONENTS_REGISTER_NODE(urc_slam::SlamNode)
