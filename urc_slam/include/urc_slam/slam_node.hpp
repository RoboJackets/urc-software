#ifndef URC_SLAM__SLAM_NODE_HPP_
#define URC_SLAM__SLAM_NODE_HPP_

#include <cstddef>
#include <deque>
#include <memory>
#include <optional>
#include <string>
#include <utility>

#include <gtsam/geometry/Pose3.h>
#include <nav_msgs/msg/odometry.hpp>
#include <nav_msgs/msg/path.hpp>
#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/imu.hpp>
#include <sensor_msgs/msg/point_cloud2.hpp>
#include <tf2_ros/buffer.hpp>
#include <tf2_ros/transform_broadcaster.hpp>
#include <tf2_ros/transform_listener.hpp>

#include "urc_slam/gps_keyframe_matcher.hpp"
#include "urc_slam/imu_buffer.hpp"
#include "urc_slam/keyframe_map.hpp"
#include "urc_slam/lidar_frontend.hpp"
#include "urc_slam/slam_backend.hpp"
#include "urc_slam/slam_messages.hpp"
#include "urc_slam/slam_parameters.hpp"

namespace urc_slam
{

// LiDAR-inertial SLAM node publishing map_T_base_link odometry, TF, the
// keyframe path and a downsampled map. All callbacks share state without
// locking and must run on a single-threaded executor.
class SlamNode : public rclcpp::Node
{
public:
  explicit SlamNode(const rclcpp::NodeOptions & options = rclcpp::NodeOptions());

private:
  void imuCallback(const sensor_msgs::msg::Imu::SharedPtr msg);
  void lidarCallback(const sensor_msgs::msg::PointCloud2::SharedPtr msg);
  void odomCallback(const nav_msgs::msg::Odometry::SharedPtr msg);
  void matchBufferedOdometry();
  bool applyWheelOdometryMatches();
  void gpsCallback(const nav_msgs::msg::Odometry::SharedPtr msg);
  void publishMap();

  void initializeAtScan(const sensor_msgs::msg::PointCloud2 & msg);
  std::optional<gtsam::Rot3> settledImuOrientation() const;
  bool integrateImuUntil(const rclcpp::Time & stamp);
  LidarFrontend::Cloud::Ptr preprocessScan(const sensor_msgs::msg::PointCloud2 & msg) const;
  void processScan(const sensor_msgs::msg::PointCloud2 & msg, const rclcpp::Time & stamp);
  void addKeyframe(
    const rclcpp::Time & stamp,
    const LidarFrontend::Cloud::Ptr & cloud,
    const std::optional<gtsam::Pose3> & relative_pose,
    const gtsam::NavState & scan_state
  );
  std::optional<gtsam::Pose3> registerScan(
    const LidarFrontend::Cloud::Ptr & cloud,
    const gtsam::Pose3 & imu_relative_guess
  );
  void commitKeyframe(const rclcpp::Time & stamp, const LidarFrontend::Cloud::Ptr & cloud);
  bool applyGpsMatches();
  void publishState(const gtsam::NavState & state, const rclcpp::Time & stamp);
  void rebuildPath();
  std::optional<gtsam::Pose3> lookupBaseTransform(const std::string & frame_id);
  KeyframeMap::PoseLookup poseLookup() const;

  SlamNodeParameters parameters;
  OdometryFrames output_frames;
  LidarFrontend lidar_frontend;
  SlamBackend backend;
  ImuBuffer imu_buffer;
  GpsKeyframeMatcher gps_matcher;
  KeyframeMap keyframe_map;

  // IMU orientations over the last second, kept only until initialization
  std::deque<std::pair<rclcpp::Time, gtsam::Rot3>> recent_imu_orientations;
  std::string imu_frame_id;
  gtsam::Pose3 base_T_lidar;
  int consecutive_registration_failures = 0;

  std::shared_ptr<tf2_ros::Buffer> tf_buffer;
  std::shared_ptr<tf2_ros::TransformListener> tf_listener;
  std::unique_ptr<tf2_ros::TransformBroadcaster> tf_broadcaster;

  rclcpp::Subscription<sensor_msgs::msg::Imu>::SharedPtr imu_sub;
  rclcpp::Subscription<sensor_msgs::msg::PointCloud2>::SharedPtr lidar_sub;
  rclcpp::Subscription<nav_msgs::msg::Odometry>::SharedPtr gps_sub;
  rclcpp::Subscription<nav_msgs::msg::Odometry>::SharedPtr odom_sub;

  struct MatchedOdometry
  {
    std::size_t keyframe_index;
    nav_msgs::msg::Odometry measurement;
  };
  std::deque<nav_msgs::msg::Odometry> odom_buffer;
  std::deque<MatchedOdometry> matched_odom;
  std::optional<rclcpp::Time> last_accepted_odom_stamp;
  static constexpr std::size_t maximum_odom_buffer_size = 200;
  rclcpp::Publisher<nav_msgs::msg::Odometry>::SharedPtr odometry_pub;
  rclcpp::Publisher<nav_msgs::msg::Path>::SharedPtr path_pub;
  rclcpp::Publisher<sensor_msgs::msg::PointCloud2>::SharedPtr map_pub;
  rclcpp::TimerBase::SharedPtr map_timer;

  nav_msgs::msg::Path path_msg;
};

}  // namespace urc_slam

#endif  // URC_SLAM__SLAM_NODE_HPP_
