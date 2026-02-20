#ifndef COVARIANCES_ON_GPS_HPP
#define COVARIANCES_ON_GPS_HPP

#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/nav_sat_fix.hpp>
#include <memory>

namespace covariances_on_gps
{
class CovariancesOnGps : public rclcpp::Node
{
public:
  explicit CovariancesOnGps(const rclcpp::NodeOptions &options);

private:
  void handleGps(const sensor_msgs::msg::NavSatFix::SharedPtr msg);

  rclcpp::Subscription<sensor_msgs::msg::NavSatFix>::SharedPtr gps_subscription_;
  rclcpp::Publisher<sensor_msgs::msg::NavSatFix>::SharedPtr gps_publisher_;
};
} // namespace covariances_on_gps

#endif // COVARIANCES_ON_GPS_HPP

