#include "covariances_on_gps.hpp"

#include <array>
#include <functional>
#include <sensor_msgs/msg/nav_sat_fix.hpp>
#include "rclcpp_components/register_node_macro.hpp"

namespace covariances_on_gps
{

CovariancesOnGps::CovariancesOnGps(const rclcpp::NodeOptions &options)
    : rclcpp::Node("covariances_on_gps", options)
{
  const auto gps_input_topic = declare_parameter<std::string>("gps_input_topic", "/gps");
  const auto gps_output_topic = declare_parameter<std::string>("gps_output_topic", "/gps/covariances");

  gps_publisher_ = create_publisher<sensor_msgs::msg::NavSatFix>(
      gps_output_topic,
      rclcpp::SystemDefaultsQoS());

  gps_subscription_ = create_subscription<sensor_msgs::msg::NavSatFix>(
      gps_input_topic,
      rclcpp::SystemDefaultsQoS(),
      std::bind(&CovariancesOnGps::handleGps, this, std::placeholders::_1));
}

void CovariancesOnGps::handleGps(const sensor_msgs::msg::NavSatFix::SharedPtr msg)
{
  if (!gps_publisher_)
  {
    return;
  }

  sensor_msgs::msg::NavSatFix output = *msg;

  output.header.stamp = this->get_clock()->now();
  output.header.frame_id = "gps_link";

  output.position_covariance.fill(0.0); 

  output.position_covariance[0] = 0.15 * 0.15;  // x variance (m^2)
  output.position_covariance[4] = 0.3 * 0.3;  // y variance (m^2)
  output.position_covariance[8] = 2 * 2;  // z variance (m^2)
  output.position_covariance_type = sensor_msgs::msg::NavSatFix::COVARIANCE_TYPE_DIAGONAL_KNOWN;

  gps_publisher_->publish(output);
}

} // namespace covariances_on_gps

RCLCPP_COMPONENTS_REGISTER_NODE(covariances_on_gps::CovariancesOnGps)
