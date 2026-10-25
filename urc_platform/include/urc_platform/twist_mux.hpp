#ifndef TWIST_MUX
#define TWIST_MUX

#include "geometry_msgs/msg/twist_stamped.hpp"
#include "std_msgs/msg/bool.hpp"
#include "std_msgs/msg/string.hpp"
#include <rclcpp/publisher.hpp>
#include <rclcpp/rclcpp.hpp>
#include <rclcpp_components/register_node_macro.hpp>

namespace twist_mux
{
class TwistMux : public rclcpp::Node
{
public:
  explicit TwistMux(const rclcpp::NodeOptions & options);

private:
  rclcpp::Subscription<geometry_msgs::msg::TwistStamped>::SharedPtr
    autonomous_subscriber;
  rclcpp::Subscription<geometry_msgs::msg::TwistStamped>::SharedPtr
    teleop_subscriber;

  rclcpp::Subscription<std_msgs::msg::Bool>::SharedPtr enabled_subscriber;

  rclcpp::Subscription<std_msgs::msg::String>::SharedPtr mode_subscriber;

  std::shared_ptr<rclcpp::Publisher<geometry_msgs::msg::TwistStamped>>
  cmd_publisher;

  bool enabled;
  std::string mode;
};
} // namespace twist_mux

#endif
