#include "urc_bt_nodes/base/log_info.hpp"
#include "behaviortree_cpp/basic_types.h"
#include "behaviortree_cpp/exceptions.h"
#include <memory>
#include <rclcpp/logger.hpp>
#include <rclcpp/logging.hpp>
#include <string>
#include <rclcpp/rclcpp.hpp>
#include <behaviortree_ros2/plugins.hpp>

namespace behavior::base
{

using namespace BT;

NodeStatus LogInfo::tick()
{
  Expected<std::shared_ptr<rclcpp::Logger>> logger = getInput<std::shared_ptr<rclcpp::Logger>>("logger");
  Expected<std::string> msg = getInput<std::string>("message");

  if (!logger)
  {
    throw RuntimeError("Logging node does not have logger input.", logger.error());
  }
  if (!msg)
  {
    throw RuntimeError("Message not get.", msg.error());
  }

  RCLCPP_INFO(*logger->get(), "%s", msg->c_str());
  return NodeStatus::SUCCESS;
}

}  // namespace behavior::base

BT_REGISTER_NODES(factory)
{
  factory.registerNodeType<behavior::base::LogInfo>("LogInfo");
}
