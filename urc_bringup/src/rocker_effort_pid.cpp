#include "rocker_effort_pid.hpp"

#include <algorithm>

namespace urc_bringup
{

RockerEffortPid::RockerEffortPid(const rclcpp::NodeOptions & options)
  : rclcpp::Node("rocker_effort_pid", options)
{
  // Parameters
  pitch_topic_       = declare_parameter<std::string>("pitch_topic", "/rocker/pitch_raw");
  command_topic_     = declare_parameter<std::string>("command_topic", "/rocker_effort_controller/commands");

  kp_ = declare_parameter<double>("kp", kp_);
  ki_ = declare_parameter<double>("ki", ki_);
  kd_ = declare_parameter<double>("kd", kd_);
  effort_limit_ = declare_parameter<double>("effort_limit", effort_limit_);
  i_clamp_ = declare_parameter<double>("i_clamp", i_clamp_);
  pitch_target_ = declare_parameter<double>("pitch_target", pitch_target_);

  min_spin_effort_ = declare_parameter<double>("min_spin_effort", min_spin_effort_);

  cmd_pub_ = create_publisher<std_msgs::msg::Float64MultiArray>(command_topic_, 10);

  pitch_sub_ = create_subscription<std_msgs::msg::Float64>(
    pitch_topic_,
    rclcpp::SensorDataQoS(),
    std::bind(&RockerEffortPid::onPitch, this, std::placeholders::_1));

  RCLCPP_INFO(get_logger(),
    "RockerEffortPid: pitch_topic='%s' cmd_topic='%s'",
    pitch_topic_.c_str(), command_topic_.c_str());
  RCLCPP_INFO(get_logger(),
    "PID: kp=%.3f ki=%.3f kd=%.3f, effort_limit=%.1f, i_clamp=%.1f",
    kp_, ki_, kd_, effort_limit_, i_clamp_);
}

void RockerEffortPid::onPitch(const std_msgs::msg::Float64::SharedPtr msg)
{
  const double pitch_meas_raw = msg->data;

  const double error = (pitch_target_ - pitch_meas_raw);

  const rclcpp::Time stamp = now();
  double dt = 0.0;
  if (last_stamp_.nanoseconds() != 0) {
    dt = (stamp - last_stamp_).seconds();
    if (dt < 0.0) dt = 0.0;
  }
  last_stamp_ = stamp;

  double deriv = 0.0;
  if (dt > 1e-6) {
    deriv = (error - last_error_) / dt;
  }

  double integ_next = integ_error_;
  if (dt > 1e-6) {
    integ_next = std::clamp(integ_error_ + error * dt, -i_clamp_, i_clamp_);
  }

  const double u_unsat = kp_ * error + ki_ * integ_next + kd_ * deriv;

  double u = u_unsat;

  const double min_u = min_spin_effort_;  
  if (std::abs(u) > 1e-6 && std::abs(u) < min_u) {
    u = std::copysign(min_u, u);
  }

  double cmd_effort = u;

  cmd_effort = std::clamp(cmd_effort, -effort_limit_, effort_limit_);

  const bool saturated = (std::abs(u_unsat) > effort_limit_ + 1e-9);
  if (!saturated) {
    integ_error_ = integ_next;
  }
  last_error_ = error;

  std_msgs::msg::Float64MultiArray cmd;
  cmd.data.resize(2);
  cmd.data[0] = -cmd_effort;
  cmd.data[1] = -cmd_effort;
  cmd_pub_->publish(cmd);
}

}  // namespace urc_bringup

#include <rclcpp_components/register_node_macro.hpp>
RCLCPP_COMPONENTS_REGISTER_NODE(urc_bringup::RockerEffortPid)
