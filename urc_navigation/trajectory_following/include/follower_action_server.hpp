#ifndef FOLLOWER_ACTION_SERVER_HPP_
#define FOLLOWER_ACTION_SERVER_HPP_

#include <rclcpp/rclcpp.hpp>
#include <rclcpp_action/rclcpp_action.hpp>
#include <geometry_msgs/msg/point_stamped.hpp>

#include "pure_pursuit.hpp"

namespace follower_action_server
{
class FollowerActionServer : public rclcpp::Node
{
public:
  explicit FollowerActionServer(const rclcpp::NodeOptions & options);

  ~FollowerActionServer();

private:
  rclcpp::Publisher<geometry_msgs::msg::PointStamped>::SharedPtr carrot_pub_;
};
} // namespace follower_action_server

#endif // FOLLOWER_ACTION_SERVER_HPP_
