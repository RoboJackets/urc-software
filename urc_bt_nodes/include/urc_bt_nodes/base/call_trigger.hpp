#ifndef CALL_SERVICE_DD53F430_C731_4D3D_93FF_368D153F1B29_HPP__
#define CALL_SERVICE_DD53F430_C731_4D3D_93FF_368D153F1B29_HPP__

#include "behaviortree_cpp/action_node.h"
#include "behaviortree_cpp/basic_types.h"
#include "std_srvs/std_srvs/srv/detail/trigger__struct.hpp"
#include <future>
#include <rclcpp/client.hpp>
#include <rclcpp/create_client.hpp>
#include <rclcpp/logging.hpp>
#include <rclcpp/node.hpp>
#include <string>

namespace behavior::base
{

using namespace BT;
using namespace std::chrono_literals;
class CallTrigger : public BT::SyncActionNode
{
public:
  CallTrigger(const std::string& name, const NodeConfig& config) : BT::SyncActionNode(name, config){};

  inline static PortsList providedPorts()
  {
    return {
      InputPort<rclcpp::Node::SharedPtr>("nh"),
      InputPort<std::string>("service_name"),  //
      InputPort<int>("timeout")                //
    };
  }

  NodeStatus tick() override;

private:
  void Call();

  bool in_progress_;
  std::future<bool> result_;
  rclcpp::Client<std_srvs::srv::Trigger>::SharedPtr client_;
};

}  // namespace behavior::base

#endif /* CALL_SERVICE_DD53F430_C731_4D3D_93FF_368D153F1B29_HPP__ */
