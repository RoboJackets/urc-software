#include "monkey.hpp"

namespace monkey
{
Monkey::Monkey(const rclcpp::NodeOptions & options)
: rclcpp::Node("monkey", options)
{

  testpub = create_publisher<std_msgs::msg::Float64>(
    "~/banana",
    rclcpp::SystemDefaultsQoS());
    
    while(rclcpp::ok()) {
    std_msgs::msg::Float64 testmessage;
    testmessage.data = testnum;
    testpub->publish(testmessage);
    }
}

} // namespace monkey

RCLCPP_COMPONENTS_REGISTER_NODE(monkey::Monkey)
