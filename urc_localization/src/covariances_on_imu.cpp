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

  // Set covariance diagonals to squared stddevs per field
  constexpr double var_lin_acc = 0.01 * 0.01;     // 1e-4
  constexpr double var_ang_vel = 0.0005 * 0.0005; // 2.5e-7
  constexpr double var_orientation = 0.001 * 0.001; // 1e-6

  auto set_diag_variance = [](std::array<double, 9> &cov, double variance) {
    if (!cov.empty() && cov[0] < 0.0) {
      cov.fill(0.0);
    }
    cov[0] = variance;
    cov[4] = variance;
    cov[8] = variance;
  };

  set_diag_variance(output.linear_acceleration_covariance, var_lin_acc);
  set_diag_variance(output.angular_velocity_covariance, var_ang_vel);
  set_diag_variance(output.orientation_covariance, var_orientation);

  imu_publisher_->publish(output);
}

} // namespace covariances_on_imu

RCLCPP_COMPONENTS_REGISTER_NODE(covariances_on_imu::CovariancesOnImu)
