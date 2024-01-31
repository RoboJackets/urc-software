#ifndef ARUCO_DETECTOR_H
#define ARUCO_DETECTOR_H

#include <rclcpp/rclcpp.hpp>
#include <rclcpp_components/register_node_macro.hpp>
#include <bits/stdc++.h>
#include <image_transport/image_transport.hpp>
#include <urc_msgs/msg/waypoint.hpp>
#include <urc_msgs/msg/navigation_status.hpp>
#include <sensor_msgs/msg/nav_sat_fix.hpp>
#include <math.h>

namespace waypoint_state_machine
{

class WaypointStateMachine : public rclcpp::Node
{
public:
  explicit WaypointStateMachine(const rclcpp::NodeOptions & options);

private:
  rclcpp::Publisher<urc_msgs::msg::NavigationStatus>::SharedPtr current_state_publisher;
  rclcpp::Subscription<urc_msgs::msg::Waypoint>::SharedPtr waypoint_subscriber;
  rclcpp::Subscription<sensor_msgs::msg::NavSatFix>::SharedPtr gps_subscriber;

  double maxDelta;
  double waypointLatitude;
  double waypointLongitude;
  double actualLatitude;
  double actualLongitude;

  void WaypointCallback(
    const urc_msgs::msg::Waypoint & msg
  );
  void GPSCallback(
    const sensor_msgs::msg::NavSatFix & msg
  );
  void DetermineState();
    
};
}

#endif
