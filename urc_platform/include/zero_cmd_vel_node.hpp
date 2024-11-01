#ifndef JOYSTICK_DRIVER_H
#define JOYSTICK_DRIVER_H

#include <geometry_msgs/msg/twist_stamped.hpp>
#include <rclcpp/publisher.hpp>
#include <rclcpp/rclcpp.hpp>
#include <rclcpp_components/register_node_macro.hpp>

namespace zero_cmd_vel_node {
class ZeroCmdVelNode : public rclcpp::Node {
public:
  explicit ZeroCmdVelNode(const rclcpp::NodeOptions &options);

private:
  void publish_zero_cmd_vel();
  std::shared_ptr<rclcpp::Publisher<geometry_msgs::msg::TwistStamped>>
      drivetrain_cmd_publisher;
  rclcpp::TimerBase::SharedPtr timer_;
};
} // namespace zero_cmd_vel_node

#endif
