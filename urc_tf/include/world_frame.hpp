#ifndef WORLD_FRAME_H
#define WORLD_FRAME_H

#include <chrono>

#include <geometry_msgs/msg/transform_stamped.hpp>
#include <std_msgs/msg/bool.hpp>
#include <urc_msgs/msg/waypoint.hpp>
#include <rclcpp/rclcpp.hpp>
#include <rclcpp_components/register_node_macro.hpp>
#include <rclcpp/subscription.hpp>
#include <tf2_ros/transform_broadcaster.h>
#include <sensor_msgs/msg/nav_sat_fix.hpp>
#include <sensor_msgs/msg/imu.hpp>

namespace world_frame
{
const int gpsOffsetToMetres = 111139;

class WorldFrameBroadcaster : public rclcpp::Node
{
public:
  WorldFrameBroadcaster(const rclcpp::NodeOptions & options);

private:
  double baseStationLat;
  double baseStationLng;
  double baseStationAlt;

  double currentLat;
  double currentLng;
  double currentAlt;

  double waypointLat;
  double waypointLng;

  double imu_x;
  double imu_y;
  double imu_z;
  double imu_w;

  rclcpp::Subscription<sensor_msgs::msg::NavSatFix>::SharedPtr gps_subscriber;
  rclcpp::Subscription<urc_msgs::msg::Waypoint>::SharedPtr waypoint_subscriber;
  rclcpp::Subscription<std_msgs::msg::Bool>::SharedPtr set_base_subscriber;
  rclcpp::Subscription<sensor_msgs::msg::Imu>::SharedPtr imu_subscriber;

  std::shared_ptr<tf2_ros::TransformBroadcaster> tf_broadcaster_;

  void GPSCallback(const sensor_msgs::msg::NavSatFix & msg);
  void IMUCallback(const sensor_msgs::msg::Imu & msg);
  void WaypointCallback(const urc_msgs::msg::Waypoint & msg);
  void SetBaseCallback(const std_msgs::msg::Bool & msg);
};
}

#endif