#include "urc_bt_nodes/actions/search.hpp"
#include "behaviortree_cpp/basic_types.h"
#include <nav_msgs/msg/detail/path__struct.hpp>
#include <rclcpp/logging.hpp>
#include <urc_msgs/action/detail/search_aruco__struct.hpp>
#include <urc_msgs/action/search_aruco.hpp>

namespace behavior::actions
{
bool Search::setGoal(Goal & goal)
{
  uint16_t get_goal = std::stoi(getInput<std::string>("goal_type").value());
  RCLCPP_INFO(node_->get_logger(), "Setting Goal...");
  goal.goal_type = get_goal;
  return true;
}

void Search::onHalt()
{
  RCLCPP_INFO(node_->get_logger(), "Halting...");
}     // namespace behavior::actions

BT::NodeStatus Search::onFeedback(const std::shared_ptr<const Feedback> feedback)
{
  return BT::NodeStatus::RUNNING;
}

BT::NodeStatus Search::onResultReceived(const WrappedResult & wr)
{
  RCLCPP_INFO(
    node_->get_logger(), "Finished following path with error code: %hu.", wr.result->error_code);
  if (wr.result->error_code == 0) {
    return BT::NodeStatus::SUCCESS;
  }

  return BT::NodeStatus::FAILURE;
}

BT::NodeStatus Search::onFailure(BT::ActionNodeErrorCode error)
{
  RCLCPP_ERROR(node_->get_logger(), "%s: Failed with error %s", name().c_str(), toStr(error));
  return BT::NodeStatus::FAILURE;
}
}

#include "behaviortree_ros2/plugins.hpp"
CreateRosNodePlugin(urc_msgs::action::SearchAruco, "Search");
