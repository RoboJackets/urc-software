#ifndef LOG_INFO_B11B9468_675B_49F7_9582_049158C306CE_HPP__
#define LOG_INFO_B11B9468_675B_49F7_9582_049158C306CE_HPP__

#include "behaviortree_cpp/bt_factory.h"
#include <behaviortree_cpp/action_node.h>
#include <behaviortree_cpp/basic_types.h>
#include <behaviortree_cpp/tree_node.h>
#include <rclcpp/logger.hpp>
#include <string>

namespace behavior::base
{

using namespace BT;
class LogInfo : public BT::SyncActionNode
{
public:
  LogInfo(const std::string& name, const NodeConfig& config) : SyncActionNode(name, config){};

  static PortsList providedPorts()
  {
    return { InputPort<std::string>("logger"), InputPort<std::string>("message") };
  }

  NodeStatus tick() override;
};

inline void RegisterNodes(BehaviorTreeFactory& factory)
{
  factory.registerNodeType<LogInfo>("LogInfo");
}

}  // namespace behavior::base

#endif /* LOG_INFO_B11B9468_675B_49F7_9582_049158C306CE_HPP__ */
