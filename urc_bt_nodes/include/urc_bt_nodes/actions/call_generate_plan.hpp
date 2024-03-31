#ifndef CALL_GENERATE_PLAN_CC0D7EFA_5619_4D48_88B3_B305A8565228_HPP__
#define CALL_GENERATE_PLAN_CC0D7EFA_5619_4D48_88B3_B305A8565228_HPP__

#include "urc_msgs/srv/generate_plan.hpp"
#include "behaviortree_cpp/basic_types.h"
#include "behaviortree_cpp/tree_node.h"
#include "behaviortree_ros2/bt_service_node.hpp"
#include "behaviortree_ros2/ros_node_params.hpp"
#include <geometry_msgs/msg/detail/pose__struct.hpp>
#include <geometry_msgs/msg/detail/pose_stamped__struct.hpp>
#include <geometry_msgs/msg/pose_stamped.hpp>
#include <nav_msgs/msg/path.hpp>
#include <rclcpp/logger.hpp>
#include <rclcpp/node.hpp>
#include <string>
#include <urc_msgs/srv/detail/generate_plan__struct.hpp>

namespace behavior::actions
{

class CallGeneratePlan : public BT::RosServiceNode<urc_msgs::srv::GeneratePlan>
{
public:
  CallGeneratePlan(const std::string& name, const BT::NodeConfig& conf, const BT::RosNodeParams& params)
    : BT::RosServiceNode<urc_msgs::srv::GeneratePlan>(name, conf, params){};

  bool setRequest(Request::SharedPtr& request) override final;
  virtual BT::NodeStatus onResponseReceived(const Response::SharedPtr& response) override final;

  static BT::PortsList providedPorts()
  {
    return providedBasicPorts({ BT::InputPort<geometry_msgs::msg::Pose>("start_pose"),
                                BT::InputPort<geometry_msgs::msg::Pose>("goal_pose"),
                                BT::OutputPort<nav_msgs::msg::Path>("path", "Path to follow.") });
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

#endif /* CALL_GENERATE_PLAN_CC0D7EFA_5619_4D48_88B3_B305A8565228_HPP__ */
