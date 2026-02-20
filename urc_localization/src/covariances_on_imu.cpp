#include "covariances_on_imu.hpp"

#include <array>
#include <functional>
#include <sensor_msgs/msg/imu.hpp>
#include "rclcpp_components/register_node_macro.hpp"

namespace covariances_on_imu
{

CovariancesOnImu::CovariancesOnImu(const rclcpp::NodeOptions &options)
    : rclcpp::Node("covariances_on_imu", options)
{
  const auto imu_input_topic = declare_parameter<std::string>("imu_input_topic", "/imu/data_raw");
  const auto imu_output_topic = declare_parameter<std::string>("imu_output_topic", "/imu/fused");

  imu_publisher_ = create_publisher<sensor_msgs::msg::Imu>(
      imu_output_topic,
      rclcpp::SystemDefaultsQoS());

  imu_subscription_ = create_subscription<sensor_msgs::msg::Imu>(
      imu_input_topic,
      rclcpp::SystemDefaultsQoS(),
      std::bind(&CovariancesOnImu::handleImu, this, std::placeholders::_1));
}

void CovariancesOnImu::handleImu(const sensor_msgs::msg::Imu::SharedPtr msg)
{
  if (!imu_publisher_)
  {
    return;
  }

  sensor_msgs::msg::Imu output = *msg;

  output.header.stamp = this->get_clock()->now();
  output.header.frame_id = "imu_link"; // Ensure the frame_id is set to the expected value

  output.orientation_covariance.fill(0.0);
  output.angular_velocity_covariance.fill(0.0);
  output.linear_acceleration_covariance.fill(0.0);

  output.orientation_covariance[0] = 0.0001;  // roll variance
  output.orientation_covariance[4] = 0.0001;  // pitch variance
  output.orientation_covariance[8] = 0.0001;  // yaw variance

  output.angular_velocity_covariance[0] = 0.00001;  // x variance
  output.angular_velocity_covariance[4] = 0.00001;  // y
  output.angular_velocity_covariance[8] = 0.00001;  // z

  output.linear_acceleration_covariance[0] = 1e6;  // x variance
  output.linear_acceleration_covariance[4] = 1e6;  // y
  output.linear_acceleration_covariance[8] = 1e6;  // z
  
  imu_publisher_->publish(output);
}

} // namespace covariances_on_imu

RCLCPP_COMPONENTS_REGISTER_NODE(covariances_on_imu::CovariancesOnImu)
