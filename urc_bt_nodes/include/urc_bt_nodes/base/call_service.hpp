#ifndef CALL_SERVICE_DD53F430_C731_4D3D_93FF_368D153F1B29_HPP__
#define CALL_SERVICE_DD53F430_C731_4D3D_93FF_368D153F1B29_HPP__

#include "behaviortree_cpp/action_node.h"
#include "behaviortree_cpp/basic_types.h"
#include "behaviortree_cpp/bt_factory.h"
#include "std_srvs/std_srvs/srv/detail/trigger__struct.hpp"
#include <exception>
#include <rclcpp/client.hpp>
#include <rclcpp/logging.hpp>
#include <rclcpp/node.hpp>

namespace behavior::base
{

using namespace BT;
template <typename ServT, typename ServReqT>
class CallService : public BT::SyncActionNode
{
public:
  CallService(const std::string& name) : BT::SyncActionNode(name, {}){};

  inline static PortsList providedPorts()
  {
    return {
      InputPort<rclcpp::Node::SharedPtr>("node"),  //
      InputPort<std::string>("service_name"),      //
      InputPort<ServReqT>("service_request"),      //
      InputPort<int>("timeout")                    //
    };
  }

  BT::NodeStatus tick() override
  {
    if (client_ == nullptr)
    {
      rclcpp::Node::SharedPtr node = getInput("node");
      client_ = node->create_client<ServT>("service_name");
    }

    try
    {
      ServReqT service_request = getInput("service_request");
    }
    catch (std::exception& e)
    {
      return BT::NodeStatus::FAILURE;
    }
  }

private:
  typename rclcpp::Client<ServT>::SharedPtr client_;
};

}  // namespace behavior::base

#endif /* CALL_SERVICE_DD53F430_C731_4D3D_93FF_368D153F1B29_HPP__ */
