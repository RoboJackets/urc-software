#ifndef CALL_TRIGGER_BF19F36F_3E0F_49B8_AC4F_53643F93E828_HPP__
#define CALL_TRIGGER_BF19F36F_3E0F_49B8_AC4F_53643F93E828_HPP__

#include "std_srvs/srv/trigger.hpp"
#include "behaviortree_cpp/basic_types.h"
#include "behaviortree_cpp/tree_node.h"
#include "behaviortree_ros2/bt_service_node.hpp"
#include "behaviortree_ros2/ros_node_params.hpp"
#include <rclcpp/logger.hpp>
#include <rclcpp/node.hpp>
#include <string>

namespace behavior::actions
{

class CallTrigger : public BT::RosServiceNode<std_srvs::srv::Trigger>
{
public:
  CallTrigger(const std::string& name, const BT::NodeConfig& conf, const BT::RosNodeParams& params)
    : BT::RosServiceNode<std_srvs::srv::Trigger>(name, conf, params){};

  bool setRequest(Request::SharedPtr& request) override final;
  virtual BT::NodeStatus onResponseReceived(const Response::SharedPtr& response) override final;

  static BT::PortsList providedPorts()
  {
    return providedBasicPorts({});
  }
};

}  // namespace behavior::actions

namespace BT
{

template <>
inline std::shared_ptr<rclcpp::Logger> convertFromString(StringView str)
{
  return std::make_shared<rclcpp::Logger>(rclcpp::get_logger(std::string(str).c_str()));
}

};  // namespace BT

#endif /* CALL_TRIGGER_BF19F36F_3E0F_49B8_AC4F_53643F93E828_HPP__ */
