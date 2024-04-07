#include "world_frame.hpp"

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

  set_base_subscriber = create_subscription<std_msgs::msg::Bool>(
    "/set_base", rclcpp::SystemDefaultsQoS(),
    [this](const std_msgs::msg::Bool msg) {SetBaseCallback(msg);});

  imu_subscriber = create_subscription<sensor_msgs::msg::Imu>(
    "/imu/data", rclcpp::SystemDefaultsQoS(),
    [this](const sensor_msgs::msg::Imu msg) {IMUCallback(msg);});

  baseStationLat = -1000;
  baseStationLng = -1000;
  baseStationAlt = -1000;
}

void WorldFrameBroadcaster::SetBaseCallback(const std_msgs::msg::Bool & msg)
{
  this->baseStationLat = currentLat;
  this->baseStationLng = currentLng;
  this->baseStationAlt = currentAlt;
}

void WorldFrameBroadcaster::IMUCallback(const sensor_msgs::msg::Imu & msg)
{
  this->imu_x = msg.orientation.x;
  this->imu_y = msg.orientation.y;
  this->imu_z = msg.orientation.z;
  this->imu_w = msg.orientation.w;
}

void WorldFrameBroadcaster::GPSCallback(const sensor_msgs::msg::NavSatFix & msg)
{
  this->currentLat = msg.latitude;
  this->currentLng = msg.longitude;
  this->currentAlt = msg.altitude;

  if (baseStationLat < -200 || baseStationLng < -200) {
    return;
  }
  geometry_msgs::msg::TransformStamped t;
  t.header.stamp = this->get_clock()->now();
  t.header.frame_id = "odom";
  t.child_frame_id = "base_link";

  t.transform.translation.x = (currentLat - baseStationLat) * 111139;
  t.transform.translation.y = (currentLng - baseStationLng) * 111139;
  t.transform.translation.z = currentAlt - baseStationAlt;

  t.transform.rotation.x = this->imu_x;
  t.transform.rotation.y = this->imu_y;
  t.transform.rotation.z = this->imu_z;
  t.transform.rotation.w = this->imu_w;

  tf_broadcaster_->sendTransform(t);
}

void WorldFrameBroadcaster::WaypointCallback(const urc_msgs::msg::Waypoint & msg)
{
  this->waypointLat = msg.latitude;
  this->waypointLng = msg.longitude;

  if (baseStationLat < -200 || baseStationLng < -200) {
    return;
  }
  geometry_msgs::msg::TransformStamped t;
  t.header.stamp = this->get_clock()->now();
  t.header.frame_id = "world";
  t.child_frame_id = "waypoint";

  t.transform.translation.x = (waypointLat - baseStationLat) * 111139;
  t.transform.translation.y = (waypointLng - baseStationLng) * 111139;
  t.transform.translation.z = 0; // waypoint doesn't work

  t.transform.rotation.x = 0.0;
  t.transform.rotation.y = 0.0;
  t.transform.rotation.z = 0.0;
  t.transform.rotation.w = 1.0; // waypoint doesn't have any rotation data

  tf_broadcaster_->sendTransform(t);
}
}

RCLCPP_COMPONENTS_REGISTER_NODE(world_frame::WorldFrameBroadcaster)
