#include "rocker_tf_broadcaster.hpp"

#include <algorithm>
#include <std_msgs/msg/float64.hpp>

namespace urc_bringup
{

RockerTfBroadcaster::RockerTfBroadcaster(const rclcpp::NodeOptions & options)
  : rclcpp::Node("rocker_pitch_publisher", options)
{
  left_joint_name_   = declare_parameter<std::string>("left_joint_name", "L_Rocker_Joint");
  right_joint_name_  = declare_parameter<std::string>("right_joint_name", "R_Rocker_Joint");
  joint_state_topic_ = declare_parameter<std::string>("joint_state_topic", "/joint_states");
  invert_sign_       = declare_parameter<bool>("invert_sign", true);

  pitch_pub_ = create_publisher<std_msgs::msg::Float64>("/rocker/pitch_raw", rclcpp::SystemDefaultsQoS());

  js_sub_ = create_subscription<sensor_msgs::msg::JointState>(
    joint_state_topic_,
    rclcpp::SensorDataQoS(),
    std::bind(&RockerTfBroadcaster::onJointState, this, std::placeholders::_1));

  RCLCPP_INFO(get_logger(),
    "Publishing /rocker/pitch_raw from joints '%s','%s' (invert_sign=%s)",
    left_joint_name_.c_str(), right_joint_name_.c_str(),
    invert_sign_ ? "true" : "false");
}

void RockerTfBroadcaster::onJointState(const sensor_msgs::msg::JointState::SharedPtr msg)
{
  if (msg->name.empty()) return;

  if (left_index_ < 0 || right_index_ < 0) {
    for (size_t i = 0; i < msg->name.size(); ++i) {
      if (msg->name[i] == left_joint_name_)  left_index_  = static_cast<int>(i);
      if (msg->name[i] == right_joint_name_) right_index_ = static_cast<int>(i);
    }
    if (left_index_ < 0 || right_index_ < 0) {
      RCLCPP_WARN_THROTTLE(get_logger(), *get_clock(), 5000,
        "Waiting for joints '%s' and '%s' in JointState...",
        left_joint_name_.c_str(), right_joint_name_.c_str());
      return;
    }
  }

  if (static_cast<size_t>(left_index_) >= msg->position.size() ||
      static_cast<size_t>(right_index_) >= msg->position.size()) {
    return;
  }

  const double left_angle  = msg->position[left_index_];
  const double right_angle = msg->position[right_index_];

  double avg = 0.5 * (left_angle + right_angle);
  if (invert_sign_) avg = -avg;

  std_msgs::msg::Float64 out;
  out.data = avg;                 // <-- RAW rocker pitch
  pitch_pub_->publish(out);
}

}  // namespace urc_bringup

#include "rclcpp_components/register_node_macro.hpp"
RCLCPP_COMPONENTS_REGISTER_NODE(urc_bringup::RockerTfBroadcaster)