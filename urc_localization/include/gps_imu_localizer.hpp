#ifndef GPS_IMU_LOCALIZER_H
#define GPS_IMU_LOCALIZER_H

#include "nav_msgs/msg/odometry.hpp"
#include "sensor_msgs/msg/imu.hpp"
#include "sensor_msgs/msg/nav_sat_fix.hpp"
#include "geographic_msgs/msg/geo_point.hpp"
#include "math.h"
#include <geodesy/utm.h>
#include <geodesy/wgs84.h>
#include <memory>
#include <rclcpp/publisher.hpp>
#include <rclcpp/rclcpp.hpp>
#include <rclcpp_components/register_node_macro.hpp>
#include <std_msgs/msg/empty.hpp>
#include <utility>

namespace gps_imu_localizer
{
class GpsImuLocalizer : public rclcpp::Node
{
public:
  explicit GpsImuLocalizer(const rclcpp::NodeOptions &options);

private:
  rclcpp::Subscription<sensor_msgs::msg::NavSatFix>::SharedPtr gps_subscriber_;
  rclcpp::Subscription<sensor_msgs::msg::Imu>::SharedPtr imu_subscriber_;
  rclcpp::Subscription<std_msgs::msg::Empty>::SharedPtr set_base_subscriber_;
  std::shared_ptr<rclcpp::Publisher<nav_msgs::msg::Odometry>>
      odometry_publisher_;

  void GpsCallback(const sensor_msgs::msg::NavSatFix &msg);
  void ImuCallback(const sensor_msgs::msg::Imu &msg);

  std::pair<double, double> base;
  nav_msgs::msg::Odometry odometry_msg_;
};
} // namespace gps_imu_localizer

#endif
