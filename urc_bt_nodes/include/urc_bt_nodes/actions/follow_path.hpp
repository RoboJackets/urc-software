#ifndef FOLLOW_PATH_CC276572_BA01_446A_BFE6_15052217C4BD_HPP__
#define FOLLOW_PATH_CC276572_BA01_446A_BFE6_15052217C4BD_HPP__

#include "behaviortree_cpp/basic_types.h"
#include "behaviortree_cpp/tree_node.h"
#include "behaviortree_cpp/tree_node.h"
#include "behaviortree_ros2/ros_node_params.hpp"
#include "behaviortree_ros2/bt_action_node.hpp"
#include "string"
#include <nav_msgs/msg/detail/path__struct.hpp>
#include <urc_msgs/action/detail/follow_path__struct.hpp>

namespace behavior::actions
{

class FollowPath : public BT::RosActionNode<urc_msgs::action::FollowPath>
{
public:
  FollowPath(const std::string& name, const BT::NodeConfig& conf, const BT::RosNodeParams& params)
    : BT::RosActionNode<urc_msgs::action::FollowPath>(name, conf, params){};
  static BT::PortsList providedPorts()
  {
    return providedBasicPorts({ BT::InputPort<nav_msgs::msg::Path>("path") });
  }

  bool setGoal(Goal& goal) override;
  void onHalt() override;
  BT::NodeStatus onFeedback(const std::shared_ptr<const Feedback> feedback) override;
  BT::NodeStatus onResultReceived(const WrappedResult& wr) override;
  virtual BT::NodeStatus onFailure(BT::ActionNodeErrorCode error) override;
};

}  // namespace behavior::actions

#endif /* FOLLOW_PATH_CC276572_BA01_446A_BFE6_15052217C4BD_HPP__ */
