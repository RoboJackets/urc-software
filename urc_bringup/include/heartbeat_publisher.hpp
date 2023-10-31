#ifndef HEARTBEAT_PUBLISHER
#define HEARTBEAT_PUBLISHER

#include <chrono>

#include <rclcpp/rclcpp.hpp>
#include <rclcpp_components/register_node_macro.hpp>
#include <std_msgs/msg/header.hpp>

namespace heartbeat_publisher
{

class HeartbeatPublisher : public rclcpp::Node
{
public:
  explicit HeartbeatPublisher(const rclcpp::NodeOptions & options);

private:
  rclcpp::Publisher<std_msgs::msg::Header>::SharedPtr heartbeat_publisher;
  rclcpp::TimerBase::SharedPtr timer_;
  int heartbeatInterval;

  void timerCallback();
};

}

#endif
