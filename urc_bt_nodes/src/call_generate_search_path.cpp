#include "urc_bt_nodes/call_generate_search_path.hpp"
#include "behaviortree_cpp/basic_types.h"
#include <nav_msgs/msg/detail/path__struct.hpp>
#include <rclcpp/logging.hpp>
#include <urc_msgs/action/detail/search_aruco__struct.hpp>
#include <urc_msgs/action/search_aruco.hpp>
#include "behaviortree_ros2/plugins.hpp"

namespace behavior::actions
{
bool CallSearchPathGenerator::setRequest(typename Request::SharedPtr & request)
{
  RCLCPP_INFO(logger(), "Calling service to generate search path.");
  return true;
}

BT::NodeStatus CallSearchPathGenerator::onResponseReceived(const typename Response::SharedPtr & response)
{
  if (response->error_code == 0) {
    setOutput("path", response->path);
    return BT::NodeStatus::SUCCESS;
  } else {
    RCLCPP_WARN(logger(), "Failed to generate search path.");
    return BT::NodeStatus::FAILURE;
  }
}
} // namespace behavior::actions

CreateRosNodePlugin(behavior::actions::CallSearchPathGenerator, "Search");
