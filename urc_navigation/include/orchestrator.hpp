#ifndef ORCHESTRATOR_H
#define ORCHESTRATOR_H

#include <rclcpp/rclcpp.hpp>
#include <rclcpp_components/register_node_macro.hpp>
#include <bits/stdc++.h>
#include <image_transport/image_transport.hpp>
#include <urc_msgs/msg/waypoint.hpp>
#include <urc_msgs/msg/navigation_status.hpp>
#include <sensor_msgs/msg/nav_sat_fix.hpp>
#include <geometry_msgs/msg/twist_stamped.hpp>
#include <geometry_msgs/msg/pose.hpp>
#include <sensor_msgs/msg/imu.hpp>
#include <std_msgs/msg/bool.hpp>
#include <nav_msgs/msg/odometry.hpp>
#include <math.h>
#include <rclcpp/qos.hpp>
#include <unistd.h>

namespace orchestrator
{

class Orchestrator : public rclcpp::Node
{
public:
  explicit Orchestrator(const rclcpp::NodeOptions & options);

private:
  rclcpp::Publisher<urc_msgs::msg::NavigationStatus>::SharedPtr current_state_publisher;
  rclcpp::Publisher<geometry_msgs::msg::TwistStamped>::SharedPtr cmd_vel_publisher;

  rclcpp::Publisher<geometry_msgs::msg::Pose>::SharedPtr metric_offset_pose_publisher;
  rclcpp::Publisher<geometry_msgs::msg::Pose>::SharedPtr costmap_offset_pose_publisher;

  rclcpp::Subscription<sensor_msgs::msg::Imu>::SharedPtr imu_subscriber;
  rclcpp::Subscription<std_msgs::msg::Bool>::SharedPtr set_base_subscriber;
  rclcpp::Subscription<sensor_msgs::msg::NavSatFix>::SharedPtr gps_subscriber;
  rclcpp::Subscription<urc_msgs::msg::Waypoint>::SharedPtr waypoint_subscriber;

  bool purePursuitEnabled;
  double maxDelta;
  double actualLatitude;
  double actualLongitude;
  double baseLatitude;
  double baseLongitude;
  double waypointLatitude;
  double waypointLongitude;
  double initialYaw;
  double currentYaw;
  rclcpp::Time gpsTimestamp;
  geometry_msgs::msg::Pose current_metric_pose;
  geometry_msgs::msg::Pose current_costmap_pose;


  void PublishMetricPose(double gpsOffsetX, double gpsOffsetY);
  void PublishCostmapPose(double gpsOffsetX, double gpsOffsetY);
  void IMUCallback(
    const sensor_msgs::msg::Imu & msg
  );
  void SetBaseCallback(
    const std_msgs::msg::Bool & msg
  );
  void GPSCallback(
    const sensor_msgs::msg::NavSatFix & msg
  );
  void WaypointCallback(
    const urc_msgs::msg::Waypoint & msg
  );
  void OffsetPublishing(
    sensor_msgs::msg::NavSatFix basePosition,
    sensor_msgs::msg::NavSatFix currentPosition
  );
  void DetermineState();
  void PurePursuit(double deltaX, double deltaY);

};
}

#endif
