#include "monkey.hpp"

namespace monkey
{
Monkey::Monkey(const rclcpp::NodeOptions & options)
: rclcpp::Node("monkey", options)
{

  testpub = create_publisher<std_msgs::msg::Bool>(
    "~/banana",
    rclcpp::SystemDefaultsQoS());
    std_msgs::msg::Bool enabled_msg;
    enabled_msg.data = true;
    testpub->publish(enabled_msg);
}

} // namespace monkey

RCLCPP_COMPONENTS_REGISTER_NODE(monkey::Monkey)
