#ifndef BT_ARUCO_TAG_DETECTED
#define BT_ARUCO_TAG_DETECTED

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/int16.hpp"
#include "behaviortree_cpp_v3/condition_node.h"

namespace bt_ARUCO_tag_deteceted
{

class BtARUCOTagDetected : public BT::ConditionNode
{
public:
  BtARUCOTagDetected(const std::string & condition_name, const BT::NodeConfiguration & conf);
  BtARUCOTagDetected() = delete;

  BT::NodeStatus tick() override;

  static BT::PortsList providedPorts()
  {
    return {
      BT::InputPort<std::string>(
        "aruco_count_topic", std::string("/cv/aruco_count"), "ARUCO tag count topic")
    };
  }

private:
  void arucoTagCountCallback(std_msgs::msg::Int16::SharedPtr msg);

  rclcpp::Node::SharedPtr node_;
  rclcpp::CallbackGroup::SharedPtr callback_group_;
  rclcpp::executors::SingleThreadedExecutor callback_group_executor_;
  rclcpp::Subscription<std_msgs::msg::Int16>::SharedPtr aruco_tag_count_sub_;
  std::string aruco_tag_count_topic_;
  bool aruco_tag_detected_;
};

}

#endif
