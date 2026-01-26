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
  spin_effort_topic_ = declare_parameter<std::string>(
    "spin_effort_topic", "/rocker/spin_effort");

  kp_ = declare_parameter<double>("kp", kp_);
  ki_ = declare_parameter<double>("ki", ki_);
  kd_ = declare_parameter<double>("kd", kd_);
  effort_limit_ = declare_parameter<double>("effort_limit", effort_limit_);
  i_clamp_ = declare_parameter<double>("i_clamp", i_clamp_);
  pitch_target_ = declare_parameter<double>("pitch_target", pitch_target_);
  invert_pitch_ = declare_parameter<bool>("invert_pitch", invert_pitch_);

  spin_scale_ = declare_parameter<double>("spin_scale", spin_scale_);
  min_spin_effort_ = declare_parameter<double>("min_spin_effort", min_spin_effort_);
  stiction_vel_epsilon_ = declare_parameter<double>(
    "stiction_vel_epsilon", stiction_vel_epsilon_);

  cmd_pub_ = create_publisher<std_msgs::msg::Float64MultiArray>(command_topic_, 10);

  pitch_sub_ = create_subscription<std_msgs::msg::Float64>(
    pitch_topic_,
    rclcpp::SensorDataQoS(),
    std::bind(&RockerEffortPid::onPitch, this, std::placeholders::_1));

  spin_sub_ = create_subscription<std_msgs::msg::Float64>(
    spin_effort_topic_, 10,
    std::bind(&RockerEffortPid::onSpinEffort, this, std::placeholders::_1));

  RCLCPP_INFO(get_logger(),
    "RockerEffortPid: pitch_topic='%s' cmd_topic='%s' spin_topic='%s'",
    pitch_topic_.c_str(), command_topic_.c_str(), spin_effort_topic_.c_str());
  RCLCPP_INFO(get_logger(),
    "PID: kp=%.3f ki=%.3f kd=%.3f, effort_limit=%.1f, i_clamp=%.1f",
    kp_, ki_, kd_, effort_limit_, i_clamp_);
}

void RockerEffortPid::onSpinEffort(const std_msgs::msg::Float64::SharedPtr msg)
{
  base_spin_effort_.store(std::clamp(msg->data, -effort_limit_, effort_limit_));
}

void RockerEffortPid::onPitch(const std_msgs::msg::Float64::SharedPtr msg)
{
  const double pitch_meas_raw = msg->data;
  const double pitch_meas = invert_pitch_ ? -pitch_meas_raw : pitch_meas_raw;

  // Error should be "target - measured"
  const double error = (pitch_target_ - pitch_meas);

  // Time delta
  const rclcpp::Time stamp = now();
  double dt = 0.0;
  if (last_stamp_.nanoseconds() != 0) {
    dt = (stamp - last_stamp_).seconds();
    if (dt < 0.0) dt = 0.0;
  }
  last_stamp_ = stamp;

  // Derivative of error (safe)
  double deriv = 0.0;
  if (dt > 1e-6) {
    deriv = (error - last_error_) / dt;
  }

  // Candidate integral update (we'll apply only if not saturating)
  double integ_next = integ_error_;
  if (dt > 1e-6) {
    integ_next = std::clamp(integ_error_ + error * dt, -i_clamp_, i_clamp_);
  }

  // PID output (this is the "same-sign" rocker torque command)
  const double u_unsat = kp_ * error + ki_ * integ_next + kd_ * deriv;

  // Optional operator/base spin feedforward
  double base = spin_scale_ * base_spin_effort_.load();
  base = std::clamp(base, -effort_limit_, effort_limit_);

  // Combine and saturate (same sign on both joints)
  double u = u_unsat;

  // Stiction/breakaway for correction too (VERY important in sim + real)
  const double min_u = min_spin_effort_;  // reuse your param; feel free to rename
  if (std::abs(u) > 1e-6 && std::abs(u) < min_u) {
    u = std::copysign(min_u, u);
  }

  double cmd_effort = base + u;

  // Saturate final command
  cmd_effort = std::clamp(cmd_effort, -effort_limit_, effort_limit_);

  // Anti-windup: only accept integral update if we didn't saturate badly
  // (simple method: if u got clamped by effort limit, freeze integral)
  const bool saturated = (std::abs(base + u_unsat) > effort_limit_ + 1e-9);
  if (!saturated) {
    integ_error_ = integ_next;
  }
  last_error_ = error;

  // Same-sign on both
  std_msgs::msg::Float64MultiArray cmd;
  cmd.data.resize(2);
  cmd.data[0] = -cmd_effort;
  cmd.data[1] = -cmd_effort;
  cmd_pub_->publish(cmd);
}

}  // namespace urc_bringup

#include <rclcpp_components/register_node_macro.hpp>
RCLCPP_COMPONENTS_REGISTER_NODE(urc_bringup::RockerEffortPid)
