#include "heartbeat_publisher.hpp"

namespace heartbeat_publisher
{
HeartbeatPublisher::HeartbeatPublisher(const rclcpp::NodeOptions & options)
: rclcpp::Node("heartbeat_publisher", options)
{
  heartbeatInterval = declare_parameter<int>("heartbeatInterval");
  heartbeat_publisher = create_publisher<std_msgs::msg::Header>(
    "/heartbeat",
    rclcpp::SystemDefaultsQoS());
  timer_ = 
    create_wall_timer(
    std::chrono::milliseconds(heartbeatInterval),
    std::bind(&HeartbeatPublisher::timerCallback, this));
}

void HeartbeatPublisher::timerCallback()
{
  auto message = std_msgs::msg::Header();
  message.stamp = now();
  heartbeat_publisher->publish(message);
}

}

RCLCPP_COMPONENTS_REGISTER_NODE(heartbeat_publisher::HeartbeatPublisher)
