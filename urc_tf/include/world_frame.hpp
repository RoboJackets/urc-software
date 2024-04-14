#ifndef WORLD_FRAME_H
#define WORLD_FRAME_H

#include <geometry_msgs/msg/detail/quaternion__struct.hpp>
#include <geometry_msgs/msg/transform_stamped.hpp>
#include <rclcpp/rclcpp.hpp>
#include <rclcpp/subscription.hpp>
#include <rclcpp_components/register_node_macro.hpp>
#include <sensor_msgs/msg/imu.hpp>
#include <sensor_msgs/msg/nav_sat_fix.hpp>
#include <std_msgs/msg/bool.hpp>
#include <tf2_ros/transform_broadcaster.h>
#include <urc_msgs/msg/waypoint.hpp>

namespace world_frame {
const int gpsOffsetToMetres = 111139;

class WorldFrameBroadcaster : public rclcpp::Node {
public:
  WorldFrameBroadcaster(const rclcpp::NodeOptions &options);

private:
  double baseStationLat;
  double baseStationLng;
  double baseStationAlt;
  int baseStationSet;

  geometry_msgs::msg::Quaternion imu;

  rclcpp::Subscription<sensor_msgs::msg::NavSatFix>::SharedPtr gps_subscriber;
  rclcpp::Subscription<urc_msgs::msg::Waypoint>::SharedPtr waypoint_subscriber;
  rclcpp::Subscription<sensor_msgs::msg::NavSatFix>::SharedPtr base_subscriber;
  rclcpp::Subscription<geometry_msgs::msg::Quaternion>::SharedPtr
      imu_subscriber;

  std::shared_ptr<tf2_ros::TransformBroadcaster> tf_broadcaster_;

  void GPSCallback(const sensor_msgs::msg::NavSatFix &msg);
  void IMUCallback(const geometry_msgs::msg::Quaternion &msg);
  void WaypointCallback(const urc_msgs::msg::Waypoint &msg);
  void BaseFixCallback(const sensor_msgs::msg::NavSatFix &msg);
};
} // namespace world_frame

#endif
