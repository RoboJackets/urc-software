#include "bt_ARUCO_tag_detected.hpp"
#include "behaviortree_cpp_v3/bt_factory.h"

namespace bt_ARUCO_tag_deteceted
{

BtARUCOTagDetected::BtARUCOTagDetected(
  const std::string & condition_name,
  const BT::NodeConfiguration & conf)
: BT::ConditionNode(condition_name, conf),
  aruco_tag_count_topic_("/cv/aruco_count"),
  aruco_tag_detected_(false)
{
  getInput("aruco_count_topic", aruco_tag_count_topic_);
  node_ = config().blackboard->get<rclcpp::Node::SharedPtr>("node");
  callback_group_ = node_->create_callback_group(
    rclcpp::CallbackGroupType::MutuallyExclusive,
    false);
  callback_group_executor_.add_callback_group(callback_group_, node_->get_node_base_interface());

  rclcpp::SubscriptionOptions sub_option;
  sub_option.callback_group = callback_group_;
  aruco_tag_count_sub_ = node_->create_subscription<std_msgs::msg::Int16>(
    aruco_tag_count_topic_,
    rclcpp::SystemDefaultsQoS(),
    std::bind(&BtARUCOTagDetected::arucoTagCountCallback, this, std::placeholders::_1),
    sub_option);
}

BT::NodeStatus BtARUCOTagDetected::tick()
{
  callback_group_executor_.spin_some();
  if (aruco_tag_detected_) {
    return BT::NodeStatus::SUCCESS;
  }
  return BT::NodeStatus::FAILURE;
}


void BtARUCOTagDetected::arucoTagCountCallback(std_msgs::msg::Int16::SharedPtr msg)
{
  aruco_tag_detected_ = msg->data > 0;
}

}

BT_REGISTER_NODES(factory)
{
  factory.registerNodeType<bt_ARUCO_tag_deteceted::BtARUCOTagDetected>("ARUCOTagDetected");
}
