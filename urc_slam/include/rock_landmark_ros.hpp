#ifndef ROCK_LANDMARK_ROS_HPP_
#define ROCK_LANDMARK_ROS_HPP_

#include <memory>
#include <string>
#include <vector>
#include <builtin_interfaces/msg/time.hpp>
#include <rclcpp/rclcpp.hpp>
#include <visualization_msgs/msg/marker_array.hpp>

#include "landmark_manager.hpp"
#include "urc_slam/lidar_frontend.hpp"
#include "rock_landmark_pipeline.hpp"
#include "rock_types.hpp"

namespace urc_slam {

    // Declares the rock_landmarks.* parameters on `node`. Returns nullptr when
    // rock_landmarks.enabled is false. Throws std::invalid_argument if enabled
    // with unset or inconsistent parameters (notably the measurement noise,
    // which has no default on purpose), so a misconfigured robot fails at
    // startup instead of running on an invented value. `base_T_sensor` is the
    // LiDAR mounting pose in base_link.
    std::unique_ptr<RockLandmarkPipeline> createRockPipeline(
        rclcpp::Node &node, const gtsam::Pose3 &base_T_sensor);

    // Finite points only, copied into the extractor's ROS/PCL-free type.
    PointCloud3d toPointCloud3d(const LidarFrontend::Cloud &cloud);

    // One sphere (sized by the rock radius) and one text label per landmark.
    visualization_msgs::msg::MarkerArray makeLandmarkMarkers(
        const std::vector<LandmarkSnapshot> &landmarks,
        const std::string &frame_id,
        const builtin_interfaces::msg::Time &stamp);

    // Rocks extracted from one sweep, in that sweep's sensor frame: one sphere
    // per rock, sized by its fitted radius. Starts with DELETEALL so rocks from
    // the previous sweep do not linger.
    visualization_msgs::msg::MarkerArray makeDetectionMarkers(
        const std::vector<RockObservation> &observations,
        const std::string &frame_id,
        const builtin_interfaces::msg::Time &stamp);

}

#endif
