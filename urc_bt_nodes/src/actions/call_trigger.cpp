#include "urc_bt_nodes/actions/call_trigger.hpp"
#include "behaviortree_cpp/basic_types.h"
#include <rclcpp/logger.hpp>
#include <rclcpp/logging.hpp>

namespace behavior::actions
{

  bool CallTrigger::setRequest(typename Request::SharedPtr &)
  {
    return true;
  }

  BT::NodeStatus CallTrigger::onResponseReceived(const typename Response::SharedPtr &response)
  {
    if (response->success)
    {
      return BT::NodeStatus::SUCCESS;
    }
    else
    {
      RCLCPP_WARN(logger(), "Service call failed. %s", response->message.c_str());
      return BT::NodeStatus::FAILURE;
    }
  }

} // namespace behavior::actions

#include "behaviortree_ros2/plugins.hpp"
CreateRosNodePlugin(behavior::actions::CallTrigger, "CallTrigger");
