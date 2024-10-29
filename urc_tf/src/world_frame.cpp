#include "world_frame.hpp"
#include <rclcpp/logging.hpp>

namespace world_frame
{
WorldFrameBroadcaster::WorldFrameBroadcaster(const rclcpp::NodeOptions & options)
: Node("world_frame", options)
{
  tf_broadcaster_ = std::make_shared<tf2_ros::TransformBroadcaster>(this);

  gps_subscriber = create_subscription<sensor_msgs::msg::NavSatFix>(
    "/fix", rclcpp::SystemDefaultsQoS(),
    [this](const sensor_msgs::msg::NavSatFix msg) {GPSCallback(msg);});

  waypoint_subscriber = create_subscription<urc_msgs::msg::Waypoint>(
    "/waypoint", rclcpp::SystemDefaultsQoS(),
    [this](const urc_msgs::msg::Waypoint msg) {WaypointCallback(msg);});

  base_subscriber = create_subscription<sensor_msgs::msg::NavSatFix>(
    "/base_fix", rclcpp::SystemDefaultsQoS(),
    [this](const sensor_msgs::msg::NavSatFix msg) {BaseFixCallback(msg);});

  imu_subscriber = create_subscription<sensor_msgs::msg::Imu>(
    "/imu/data", rclcpp::SystemDefaultsQoS(),
    [this](const sensor_msgs::msg::Imu msg) {IMUCallback(msg);});

  baseStationSet = 0;
}

void WorldFrameBroadcaster::BaseFixCallback(
  const sensor_msgs::msg::NavSatFix & msg)
{
  this->baseStationLat = msg.latitude;
  this->baseStationLng = msg.longitude;
  this->baseStationAlt = msg.altitude;
  this->baseStationSet = 1;
}

void WorldFrameBroadcaster::IMUCallback(const sensor_msgs::msg::Imu & msg)
{
  this->imu = msg;
}

void WorldFrameBroadcaster::GPSCallback(
  const sensor_msgs::msg::NavSatFix & msg)
{
  if (!baseStationSet) {
    // RCLCPP_ERROR(this->get_logger(), "Base Station Not Set!");
    return;
  }
  geometry_msgs::msg::TransformStamped t;
  t.header.stamp = this->get_clock()->now();
  t.header.frame_id = "odom";
  t.child_frame_id = "base_link";

  t.transform.translation.x =
    (msg.latitude - baseStationLat) * gpsOffsetToMetres;
  t.transform.translation.y =
    (msg.longitude - baseStationLng) * gpsOffsetToMetres;
  t.transform.translation.z = msg.altitude - baseStationAlt;
  t.transform.rotation = this->imu.orientation;

  tf_broadcaster_->sendTransform(t);
}

void WorldFrameBroadcaster::WaypointCallback(
  const urc_msgs::msg::Waypoint & msg)
{
  if (baseStationLat < -200 || baseStationLng < -200) {
    return;
  }
  geometry_msgs::msg::TransformStamped t;
  t.header.stamp = this->get_clock()->now();
  t.header.frame_id = "odom";
  t.child_frame_id = "waypoint";

  t.transform.translation.x =
    (msg.latitude - baseStationLat) * gpsOffsetToMetres;
  t.transform.translation.y =
    (msg.longitude - baseStationLng) * gpsOffsetToMetres;
  t.transform.translation.z = 0;

  t.transform.rotation.x = 0.0;
  t.transform.rotation.y = 0.0;
  t.transform.rotation.z = 0.0;
  t.transform.rotation.w = 1.0; // waypoint doesn't have any rotation data

  tf_broadcaster_->sendTransform(t);
}
} // namespace world_frame

RCLCPP_COMPONENTS_REGISTER_NODE(world_frame::WorldFrameBroadcaster)
