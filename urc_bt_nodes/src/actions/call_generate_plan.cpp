#include "urc_bt_nodes/actions/call_generate_plan.hpp"
#include "behaviortree_ros2/plugins.hpp"
#include "behaviortree_cpp/basic_types.h"
#include <geometry_msgs/msg/detail/pose__struct.hpp>
#include <geometry_msgs/msg/detail/pose_stamped__struct.hpp>
#include <rclcpp/logger.hpp>
#include <rclcpp/logging.hpp>
#include <stdexcept>

namespace behavior::actions
{

bool CallGeneratePlan::setRequest(typename Request::SharedPtr & request)
{
  auto start_pose = getInput<geometry_msgs::msg::Pose>("start_pose").value();
  auto goal_pose = getInput<geometry_msgs::msg::Pose>("goal_pose").value();

  RCLCPP_INFO(
    node_->get_logger(), "Calling service to generate plan from (%.2f, %.2f) to (%.2f, %.2f)",
    start_pose.position.x, start_pose.position.y, goal_pose.position.x, goal_pose.position.y);

  request->goal = goal_pose;
  return true;
}

BT::NodeStatus CallGeneratePlan::onResponseReceived(const typename Response::SharedPtr & response)
{
  if (response->error_code == 0) {
    setOutput("path", response->path);
    return BT::NodeStatus::SUCCESS;
  } else {
    RCLCPP_WARN(node_->get_logger(), "Failed to plan path.");
    return BT::NodeStatus::FAILURE;
  }
}

} // namespace behavior::actions

namespace BT
{
template<>
inline geometry_msgs::msg::Pose convertFromString(StringView str)
{
  auto coordinates = splitString(str, ',');
  if (coordinates.size() != 3) {
    throw std::runtime_error("Invalid input for pose. It should have three entries (x, y, theta)");
  }

  geometry_msgs::msg::Pose output;
  output.position.x = convertFromString<double>(coordinates[0]);
  output.position.y = convertFromString<double>(coordinates[1]);

  // Convert theta to quaternion without tf2
  double theta = convertFromString<double>(coordinates[2]);
  output.orientation.x = 0.0;
  output.orientation.y = 0.0;
  output.orientation.z = std::sin(theta / 2.0);
  output.orientation.w = std::cos(theta / 2.0);

  return output;
}
} // namespace BT

CreateRosNodePlugin(behavior::actions::CallGeneratePlan, "CallGeneratePlan");
