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

  set_base_subscriber = create_subscription<std_msgs::msg::Bool>(
    "/set_base", rclcpp::SystemDefaultsQoS(),
    [this](const std_msgs::msg::Bool msg) {SetBaseCallback(msg);});
}

void WorldFrameBroadcaster::SetBaseCallback(const std_msgs::msg::Bool & msg)
{
  this->baseStationLat = currentLat;
  this->baseStationLng = currentLng;
  this->baseStationAlt = currentAlt;
}

void WorldFrameBroadcaster::GPSCallback(const sensor_msgs::msg::NavSatFix & msg)
{
  this->currentLat = msg.latitude;
  this->currentLng = msg.longitude;
  this->currentAlt = msg.altitude;

  geometry_msgs::msg::TransformStamped t;
  t.header.stamp = this->get_clock()->now();
  t.header.frame_id = "world";
  t.child_frame_id = "base_link";

  t.transform.translation.x = (currentLat - baseStationLat) * 111139;
  t.transform.translation.y = (currentLng - baseStationLng) * 111139;
  t.transform.translation.z = currentAlt - baseStationAlt;

  // TODO: IMU data
  t.transform.rotation.x = 0.0;
  t.transform.rotation.y = 0.0;
  t.transform.rotation.z = 0.0;
  t.transform.rotation.w = 1.0;

  tf_broadcaster_->sendTransform(t);
}
}

RCLCPP_COMPONENTS_REGISTER_NODE(world_frame::WorldFrameBroadcaster)