#include "follower_action_server.hpp"

namespace follower_action_server
{
FollowerActionServer::FollowerActionServer(const rclcpp::NodeOptions & options)
: Node("follower_action_server", options)
{
  RCLCPP_INFO(this->get_logger(), "Follower node has been started.");
}

FollowerActionServer::~FollowerActionServer()
{
  RCLCPP_INFO(this->get_logger(), "Follower action server has been stopped.");
}

} // namespace follower_node
