#include "zero_cmd_vel_node.hpp"

namespace zero_cmd_vel_node {

ZeroCmdVelNode::ZeroCmdVelNode(const rclcpp::NodeOptions &options)
    : rclcpp::Node("zero_cmd_vel_node", options) {
  declare_parameter("zero_cmd_vel_topic", "/cmd_vel_zero");
  drivetrain_cmd_publisher = create_publisher<geometry_msgs::msg::TwistStamped>(
      get_parameter("zero_cmd_vel_topic").as_string(),
      rclcpp::SystemDefaultsQoS());

  timer_ = this->create_wall_timer(
      std::chrono::milliseconds(100),
      std::bind(&ZeroCmdVelNode::publish_zero_cmd_vel, this));
}

void ZeroCmdVelNode::publish_zero_cmd_vel() {
  geometry_msgs::msg::TwistStamped zero_cmd_vel;
  zero_cmd_vel.twist.linear.x = 0.0;
  zero_cmd_vel.twist.angular.z = 0.0;
  drivetrain_cmd_publisher->publish(zero_cmd_vel);

} // namespace zero_cmd_vel_node
} // namespace zero_cmd_vel_node

RCLCPP_COMPONENTS_REGISTER_NODE(zero_cmd_vel_node::ZeroCmdVelNode);
