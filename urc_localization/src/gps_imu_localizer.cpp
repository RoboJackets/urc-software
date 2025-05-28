#include "gps_imu_localizer.hpp"
#include <sensor_msgs/msg/detail/imu__struct.hpp>
#include <sensor_msgs/msg/detail/nav_sat_fix__struct.hpp>
#include <std_msgs/msg/detail/empty__struct.hpp>

namespace gps_imu_localizer
{

GpsImuLocalizer::GpsImuLocalizer(const rclcpp::NodeOptions &options)
: rclcpp::Node("gps_imu_localizer", options)
{
  declare_parameter("gps_topic", "/gps/data");
  declare_parameter("imu_topic", "/imu/data");
  declare_parameter("set_base_topic", "/set_base");
  declare_parameter("odometry_topic", "/odometry/filtered_global");

  odometry_msg_.header.frame_id = "map";
  odometry_msg_.child_frame_id = "base_link";

  gps_subscriber_ = create_subscription<sensor_msgs::msg::NavSatFix>(
    get_parameter("gps_topic").as_string(), rclcpp::SystemDefaultsQoS(),
    [this](const sensor_msgs::msg::NavSatFix msg) {GpsCallback(msg);});

  imu_subscriber_ = create_subscription<sensor_msgs::msg::Imu>(
    get_parameter("imu_topic").as_string(), rclcpp::SystemDefaultsQoS(),
    std::bind(&GpsImuLocalizer::ImuCallback, this, std::placeholders::_1));

  set_base_subscriber_ = create_subscription<std_msgs::msg::Empty>(
    get_parameter("set_base_topic").as_string(), rclcpp::SystemDefaultsQoS(),
    [this](const std_msgs::msg::Empty msg) {
      base.first = odometry_msg_.pose.pose.position.x;
      base.second = odometry_msg_.pose.pose.position.y;
    }
  );

  odometry_publisher_ = create_publisher<nav_msgs::msg::Odometry>(
    get_parameter("odometry_topic").as_string(), rclcpp::SystemDefaultsQoS());
}

void GpsImuLocalizer::GpsCallback(const sensor_msgs::msg::NavSatFix & msg)
{
  double lat = msg.latitude;
  double lng = msg.longitude;
  int zone;
  bool northp;
  double x, y;

  GeographicLib::UTMUPS::Forward(lat, lng, zone, northp, x, y);
  odometry_msg_.pose.pose.position.x = x - base.first;
  odometry_msg_.pose.pose.position.y = y - base.second;
}

void GpsImuLocalizer::ImuCallback(const sensor_msgs::msg::Imu & msg)
{
  odometry_msg_.header.stamp = msg.header.stamp;
  odometry_msg_.pose.pose.orientation = msg.orientation;

  odometry_publisher_->publish(odometry_msg_);
}

} // namespace gps_imu_localizer

RCLCPP_COMPONENTS_REGISTER_NODE(gps_imu_localizer::GpsImuLocalizer)
