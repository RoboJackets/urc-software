#include "urc_controllers/rocker_tf_broadcaster.hpp"

#include <algorithm>
#include <cmath>
#include <iterator>
#include <stdexcept>

namespace urc_controllers
{

RockerTfBroadcaster::RockerTfBroadcaster(const rclcpp::NodeOptions & options)
: rclcpp::Node("rocker_pitch_publisher", options)
{
  left_joint_name_ = declare_parameter<std::string>("left_joint_name", "L_Rocker_Joint");
  right_joint_name_ = declare_parameter<std::string>("right_joint_name", "R_Rocker_Joint");
  joint_state_topic_ = declare_parameter<std::string>("joint_state_topic", "/joint_states");
  invert_sign_ = declare_parameter<bool>("invert_sign", true);

  pitch_topic_ = declare_parameter<std::string>("pitch_topic", "/rocker/pitch_raw");
  if (left_joint_name_.empty() || right_joint_name_.empty() ||
    left_joint_name_ == right_joint_name_ || joint_state_topic_.empty() || pitch_topic_.empty())
  {
    throw std::invalid_argument("Rocker joints must be distinct and topics must be nonempty");
  }
  pitch_pub_ = create_publisher<std_msgs::msg::Float64>(pitch_topic_, 10);

  js_sub_ = create_subscription<sensor_msgs::msg::JointState>(
    joint_state_topic_,
    rclcpp::SensorDataQoS(),
    std::bind(&RockerTfBroadcaster::onJointState, this, std::placeholders::_1));

  RCLCPP_INFO(
    get_logger(),
    "Publishing %s from joints '%s','%s' (invert_sign=%s)",
    pitch_topic_.c_str(), left_joint_name_.c_str(), right_joint_name_.c_str(),
    invert_sign_ ? "true" : "false");
}

void RockerTfBroadcaster::onJointState(const sensor_msgs::msg::JointState::SharedPtr msg)
{
  const auto left = std::find(msg->name.begin(), msg->name.end(), left_joint_name_);
  const auto right = std::find(msg->name.begin(), msg->name.end(), right_joint_name_);
  if (left == msg->name.end() || right == msg->name.end()) {
    RCLCPP_WARN_THROTTLE(
      get_logger(), *get_clock(), 5000,
      "Waiting for joints '%s' and '%s' in JointState...",
      left_joint_name_.c_str(), right_joint_name_.c_str());
    return;
  }
  const auto left_index = static_cast<size_t>(std::distance(msg->name.begin(), left));
  const auto right_index = static_cast<size_t>(std::distance(msg->name.begin(), right));
  if (left_index >= msg->position.size() || right_index >= msg->position.size()) {
    return;
  }
  const double left_angle = msg->position[left_index];
  const double right_angle = msg->position[right_index];
  if (!std::isfinite(left_angle) || !std::isfinite(right_angle)) {
    return;
  }

  double avg = 0.5 * (left_angle + right_angle);
  if (invert_sign_) {avg = -avg;}

  std_msgs::msg::Float64 out;
  out.data = avg;
  pitch_pub_->publish(out);
}

}  // namespace urc_controllers

#include "rclcpp_components/register_node_macro.hpp"
RCLCPP_COMPONENTS_REGISTER_NODE(urc_controllers::RockerTfBroadcaster)
