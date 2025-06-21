#ifndef DISPATCHER_HPP_
#define DISPATCHER_HPP_

#include <rclcpp/rclcpp.hpp>
#include <queue>

#include "urc_msgs/srv/get_goal.hpp"
#include "urc_msgs/srv/add_goal.hpp"
#include "urc_msgs/msg/goal.hpp"

namespace urc_behavior
{
class Dispatcher : public rclcpp::Node
{
public:
  explicit Dispatcher(const rclcpp::NodeOptions & options);
  ~Dispatcher();

private:
  void handleGetGoal(
    const std::shared_ptr<urc_msgs::srv::GetGoal::Request> request,
    const std::shared_ptr<urc_msgs::srv::GetGoal::Response> response);

  void handleAddGoal(
    const std::shared_ptr<urc_msgs::srv::AddGoal::Request> request,
    const std::shared_ptr<urc_msgs::srv::AddGoal::Response> response);

  rclcpp::Service<urc_msgs::srv::GetGoal>::SharedPtr get_goal_service_;
  rclcpp::Service<urc_msgs::srv::AddGoal>::SharedPtr add_goal_service_;

  std::queue<urc_msgs::msg::Goal> goal_queue_;       // Queue to store goals
  std::mutex queue_mutex_;                           // Mutex for thread-safe access to the queue
};
} // namespace urc_behavior

#endif // DISPATCHER_HPP_
