#include "behaviortree_cpp/bt_factory.h"
#include "urc_bt_nodes/base/call_trigger.hpp"
#include "urc_bt_nodes/base/log_info.hpp"

// register nodes
namespace behavior::base
{

using namespace BT;
inline void RegisterNodes(BehaviorTreeFactory& factory)
{
  factory.registerNodeType<LogInfo>("LogInfo");
  //   factory.registerNodeType<CallTrigger>("CallTrigger");
}

BT_REGISTER_NODES(factory)
{
  RegisterNodes(factory);
}

}  // namespace behavior::base

// define all the generic conversions from StringView to types
namespace BT
{

template <>
inline std::shared_ptr<rclcpp::Logger> convertFromString(StringView str)
{
  return std::make_shared<rclcpp::Logger>(rclcpp::get_logger(std::string(str).c_str()));
}

}  // namespace BT