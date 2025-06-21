#include "urc_bt_nodes/call_follow_path.hpp"
#include "behaviortree_cpp/basic_types.h"
#include <cstdint>
#include <nav_msgs/msg/detail/path__struct.hpp>
#include <rclcpp/logging.hpp>

namespace behavior::actions
{

bool FollowPath::setGoal(Goal & goal)
{
  std::uint16_t goal_type = getInput<std::uint16_t>("goal_type").value();
  RCLCPP_INFO(logger(), "Setting Goal...");
  goal.goal_type = goal_type;
  goal.path = getInput<nav_msgs::msg::Path>("path").value();
  return true;
}

void FollowPath::onHalt()
{
  RCLCPP_INFO(logger(), "Halting...");
}

BT::NodeStatus FollowPath::onFeedback(const std::shared_ptr<const Feedback> feedback)
{
  if (feedback->distance_to_goal < 0) {
    RCLCPP_ERROR(logger(), "Negative distance to target, terminating following.");
    return BT::NodeStatus::FAILURE;
  }
  RCLCPP_INFO(
    logger(), "Following Path! %.2f m away from destination.",
    feedback->distance_to_goal);
  return BT::NodeStatus::RUNNING;
}

BT::NodeStatus FollowPath::onResultReceived(const WrappedResult & wr)
{
  RCLCPP_INFO(
    logger(), "Finished following path with error code: %hu.", wr.result->error_code);
  if (wr.result->error_code == 0) {
    setOutput("final_goal_pos", wr.result->final_goal_pose);
    return BT::NodeStatus::SUCCESS;
  }

  // TODO: do some processing with the other error codes
  return BT::NodeStatus::FAILURE;
}

BT::NodeStatus FollowPath::onFailure(BT::ActionNodeErrorCode error)
{
  RCLCPP_ERROR(logger(), "%s: Failed with error %s", name().c_str(), toStr(error));
  return BT::NodeStatus::FAILURE;
}

} // namespace behavior::actions

#include "behaviortree_ros2/plugins.hpp"
CreateRosNodePlugin(behavior::actions::FollowPath, "FollowPath");
