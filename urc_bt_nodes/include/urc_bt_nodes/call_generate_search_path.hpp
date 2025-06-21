#ifndef SEARCH_HPP
#define SEARCH_HPP

#include "behaviortree_cpp/basic_types.h"
#include "behaviortree_cpp/tree_node.h"
#include "behaviortree_ros2/ros_node_params.hpp"
#include "behaviortree_ros2/bt_service_node.hpp"
#include "string"
#include <nav_msgs/msg/path.hpp>
#include <urc_msgs/srv/generate_search_path.hpp>

namespace behavior::actions
{

class CallSearchPathGenerator : public BT::RosServiceNode<urc_msgs::srv::GenerateSearchPath>
{
public:
  CallSearchPathGenerator(
    const std::string & name, const BT::NodeConfig & conf,
    const BT::RosNodeParams & params)
  : BT::RosServiceNode<urc_msgs::srv::GenerateSearchPath>(name, conf, params) {}

  bool setRequest(Request::SharedPtr & request) override final;
  virtual BT::NodeStatus onResponseReceived(const Response::SharedPtr & response) override final;

  static BT::PortsList providedPorts()
  {
    return providedBasicPorts({
      BT::OutputPort<nav_msgs::msg::Path>("path")
    });
  }
};

}  // namespace behavior::actions

#endif /* SEARCH_HPP */
