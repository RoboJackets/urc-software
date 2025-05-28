#include "gps_imu_localizer.hpp"

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
    [this](const sensor_msgs::msg::Imu msg) {ImuCallback(msg);});

  set_base_subscriber_ = create_subscription<std_msgs::msg::Empty>(
    get_parameter("set_base_topic").as_string(), rclcpp::SystemDefaultsQoS(),
    [this](const std_msgs::msg::Empty::SharedPtr msg) {
      base.first = odometry_msg_.pose.pose.position.x;
      base.second = odometry_msg_.pose.pose.position.y;
    }
  );

  odometry_publisher_ = create_publisher<nav_msgs::msg::Odometry>(
    get_parameter("odometry_topic").as_string(), rclcpp::SystemDefaultsQoS());

  br = std::make_unique<tf2_ros::TransformBroadcaster>(*this);
}

void GpsImuLocalizer::GpsCallback(const sensor_msgs::msg::NavSatFix & msg)
{
  geographic_msgs::msg::GeoPoint geo_point;
  geo_point.latitude = msg.latitude;
  geo_point.longitude = msg.longitude;
  geo_point.altitude = msg.altitude;
  geodesy::UTMPoint utm_point;
  geodesy::fromMsg(geo_point, utm_point);
  odometry_msg_.pose.pose.position.x = utm_point.easting - base.first;
  odometry_msg_.pose.pose.position.y = utm_point.northing - base.second;
}

void GpsImuLocalizer::ImuCallback(const sensor_msgs::msg::Imu & msg)
{
  odometry_msg_.header.stamp = msg.header.stamp;
  odometry_msg_.pose.pose.orientation = msg.orientation;

  odometry_publisher_->publish(odometry_msg_);

  geometry_msgs::msg::TransformStamped t;
  t.header.stamp = msg.header.stamp;
  t.header.frame_id = "map";
  t.child_frame_id = "base_link";
  t.transform.translation.x = odometry_msg_.pose.pose.position.x;
  t.transform.translation.y = odometry_msg_.pose.pose.position.y;
  t.transform.translation.z = 0.0;
  t.transform.rotation = odometry_msg_.pose.pose.orientation;
  br->sendTransform(t);
}

} // namespace gps_imu_localizer

RCLCPP_COMPONENTS_REGISTER_NODE(gps_imu_localizer::GpsImuLocalizer)
