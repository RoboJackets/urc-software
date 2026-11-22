#include "urc_slam/slam_parameters.hpp"

#include <stdexcept>

namespace urc_slam
{

namespace
{
double declarePositive(rclcpp::Node & node, const std::string & name, double default_value)
{
  const double value = node.declare_parameter<double>(name, default_value);
  if (!(value > 0.0)) {
    throw std::invalid_argument("Parameter '" + name + "' must be positive");
  }
  return value;
}

int declarePositiveInt(rclcpp::Node & node, const std::string & name, int default_value)
{
  const int value = static_cast<int>(node.declare_parameter<int>(name, default_value));
  if (value <= 0) {
    throw std::invalid_argument("Parameter '" + name + "' must be positive");
  }
  return value;
}

double declareFraction(rclcpp::Node & node, const std::string & name, double default_value)
{
  const double value = node.declare_parameter<double>(name, default_value);
  if (value < 0.0 || value > 1.0) {
    throw std::invalid_argument("Parameter '" + name + "' must be in [0, 1]");
  }
  return value;
}

std::string declareNonEmpty(
  rclcpp::Node & node,
  const std::string & name,
  const std::string & default_value
)
{
  const std::string value = node.declare_parameter<std::string>(name, default_value);
  if (value.empty()) {
    throw std::invalid_argument("Parameter '" + name + "' must not be empty");
  }
  return value;
}

LidarFrontendParameters declareLidarFrontend(rclcpp::Node & node)
{
  LidarFrontendParameters p;
  p.voxel_size_m = declarePositive(node, "lidar_frontend.voxel_size_m", 0.2);
  p.minimum_range_m = declarePositive(node, "lidar_frontend.minimum_range_m", 1.0);
  p.maximum_range_m = declarePositive(node, "lidar_frontend.maximum_range_m", 80.0);
  p.maximum_correspondence_distance_m =
    declarePositive(node, "lidar_frontend.maximum_correspondence_distance_m", 2.0);
  p.maximum_iterations = declarePositiveInt(node, "lidar_frontend.maximum_iterations", 64);
  p.transformation_epsilon =
    declarePositive(node, "lidar_frontend.transformation_epsilon", 1e-6);
  p.maximum_fitness_score_m2 =
    declarePositive(node, "lidar_frontend.maximum_fitness_score_m2", 0.5);
  p.minimum_inlier_fraction =
    declareFraction(node, "lidar_frontend.minimum_inlier_fraction", 0.8);
  if (p.minimum_range_m >= p.maximum_range_m) {
    throw std::invalid_argument(
            "Parameter 'lidar_frontend.minimum_range_m' must be below maximum_range_m");
  }
  return p;
}

SlamBackendParameters declareBackend(rclcpp::Node & node)
{
  SlamBackendParameters p;
  p.keyframe_translation_threshold_m =
    declarePositive(node, "keyframe.translation_threshold_m", 0.5);
  p.keyframe_rotation_threshold_rad =
    declarePositive(node, "keyframe.rotation_threshold_rad", 0.174533);
  p.keyframe_maximum_interval_s =
    declarePositive(node, "keyframe.maximum_interval_s", 2.0);

  p.pose_prior_rotation_sigma_rad =
    declarePositive(node, "prior.pose_rotation_sigma_rad", 0.1);
  p.pose_prior_translation_sigma_m =
    declarePositive(node, "prior.pose_translation_sigma_m", 0.1);
  p.velocity_prior_sigma_mps = declarePositive(node, "prior.velocity_sigma_mps", 1.0);
  p.accelerometer_bias_prior_sigma_mps2 =
    declarePositive(node, "prior.accelerometer_bias_sigma_mps2", 0.1);
  p.gyroscope_bias_prior_sigma_radps =
    declarePositive(node, "prior.gyroscope_bias_sigma_radps", 0.01);

  p.lidar_rotation_sigma_rad =
    declarePositive(node, "lidar_factor.rotation_sigma_rad", 0.05);
  p.lidar_translation_sigma_m =
    declarePositive(node, "lidar_factor.translation_sigma_m", 0.1);

  p.accelerometer_noise_sigma = declarePositive(node, "imu.accelerometer_noise_sigma", 0.25);
  p.gyroscope_noise_sigma = declarePositive(node, "imu.gyroscope_noise_sigma", 0.03);
  p.integration_noise_sigma = declarePositive(node, "imu.integration_noise_sigma", 1e-4);
  p.accelerometer_bias_random_walk_sigma =
    declarePositive(node, "imu.accelerometer_bias_random_walk_sigma", 1e-4);
  p.gyroscope_bias_random_walk_sigma =
    declarePositive(node, "imu.gyroscope_bias_random_walk_sigma", 1e-4);
  p.gravity_mps2 = declarePositive(node, "imu.gravity_mps2", 9.8);
  return p;
}
}  // namespace

SlamNodeParameters declareSlamParameters(rclcpp::Node & node)
{
  SlamNodeParameters p;
  p.topics.imu = declareNonEmpty(node, "imu_topic", "/imu/data");
  p.topics.lidar = declareNonEmpty(node, "lidar_topic", "/points");
  p.topics.gps = declareNonEmpty(node, "gps_topic", "/slam/gps_odometry");
  p.topics.odometry = declareNonEmpty(node, "slam_odom_topic", "/slam/odometry");
  p.topics.path = declareNonEmpty(node, "path_topic", "/slam/path");
  p.topics.map = declareNonEmpty(node, "map_topic", "/slam/map_points");

  p.frames.map = declareNonEmpty(node, "map_frame", "map");
  p.frames.base_link = declareNonEmpty(node, "base_link_frame", "base_link");
  p.frames.publish_tf = node.declare_parameter<bool>("publish_tf", true);

  p.lidar_frontend = declareLidarFrontend(node);
  p.backend = declareBackend(node);

  p.registration_submap_keyframes =
    declarePositiveInt(node, "registration.submap_keyframes", 3);
  p.registration_maximum_consecutive_failures =
    declarePositiveInt(node, "registration.maximum_consecutive_failures", 3);
  p.imu_maximum_gap_s = declarePositive(node, "imu.maximum_gap_s", 0.1);
  p.gps_time_tolerance_s = declarePositive(node, "gps.time_tolerance_s", 0.25);
  p.map_voxel_size_m = declarePositive(node, "map.voxel_size_m", 0.2);
  p.map_publish_period_s = declarePositive(node, "map.publish_period_s", 1.0);
  return p;
}

}  // namespace urc_slam
