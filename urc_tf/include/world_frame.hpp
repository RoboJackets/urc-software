#ifndef WORLD_FRAME_H
#define WORLD_FRAME_H

#include <chrono>

#include <geometry_msgs/msg/transform_stamped.hpp>
#include <std_msgs/msg/bool.hpp>
#include <rclcpp/rclcpp.hpp>
#include <rclcpp_components/register_node_macro.hpp>
#include <rclcpp/subscription.hpp>
#include <tf2_ros/transform_broadcaster.h>
#include <sensor_msgs/msg/nav_sat_fix.hpp>

namespace world_frame
{
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

  rclcpp::Subscription<sensor_msgs::msg::NavSatFix>::SharedPtr gps_subscriber;
  rclcpp::Subscription<std_msgs::msg::Bool>::SharedPtr set_base_subscriber;
  std::shared_ptr<tf2_ros::TransformBroadcaster> tf_broadcaster_;
  void GPSCallback(const sensor_msgs::msg::NavSatFix & msg);
  void SetBaseCallback(const std_msgs::msg::Bool & msg);
};
}

#endif
