#ifndef URC_SLAM__SLAM_PARAMETERS_HPP_
#define URC_SLAM__SLAM_PARAMETERS_HPP_

#include <string>

#include <rclcpp/node.hpp>

#include "urc_slam/lidar_frontend.hpp"
#include "urc_slam/slam_backend.hpp"

namespace urc_slam
{

struct SlamTopics
{
  std::string imu;
  std::string lidar;
  std::string gps;
  std::string odometry;
  std::string path;
  std::string map;
};

struct SlamFrames
{
  std::string map;
  std::string base_link;
  bool publish_tf;
};

struct SlamNodeParameters
{
  SlamTopics topics;
  SlamFrames frames;
  LidarFrontendParameters lidar_frontend;
  SlamBackendParameters backend;

  int registration_submap_keyframes;
  int registration_maximum_consecutive_failures;
  double imu_maximum_gap_s;
  double gps_time_tolerance_s;
  double map_voxel_size_m;
  double map_publish_period_s;
};

// Declares every slam_node parameter and validates it; throws
// std::invalid_argument naming the offending parameter
SlamNodeParameters declareSlamParameters(rclcpp::Node & node);

}  // namespace urc_slam

#endif  // URC_SLAM__SLAM_PARAMETERS_HPP_
