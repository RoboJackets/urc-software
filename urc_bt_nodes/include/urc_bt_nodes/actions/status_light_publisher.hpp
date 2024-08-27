#ifndef STATUS_LIGHT_PUBLISHER_HPP__
#define STATUS_LIGHT_PUBLISHER_HPP__

#include <string>

#include "behaviortree_cpp/basic_types.h"
#include "behaviortree_cpp/tree_node.h"
#include "behaviortree_cpp/tree_node.h"
#include "behaviortree_ros2/ros_node_params.hpp"
#include "behaviortree_ros2/bt_topic_pub_node.hpp"

#include "urc_msgs/msg/status_light_command.hpp"

namespace behavior::actions
{

int stringToColor(std::string color)
{
  if (color == "red") {
    return urc_msgs::msg::StatusLightCommand::RED;
  }
  if (color == "green") {
    return urc_msgs::msg::StatusLightCommand::GREEN;
  }
  if (color == "blue") {
    return urc_msgs::msg::StatusLightCommand::BLUE;
  }

  throw std::invalid_argument("Invalid color!");
}

int stringToState(std::string state)
{
  if (state == "on") {
    return urc_msgs::msg::StatusLightCommand::ON;
  }
  if (state == "off") {
    return urc_msgs::msg::StatusLightCommand::OFF;
  }
  if (state == "blink") {
    return urc_msgs::msg::StatusLightCommand::BLINK;
  }

  throw std::invalid_argument("Invalid state!");
}

class StatusLightPublisher : public BT::RosTopicPubNode<urc_msgs::msg::StatusLightCommand>
{
public:
  StatusLightPublisher(
    const std::string & instance_name, const BT::NodeConfig & conf,
    const BT::RosNodeParams & params)
  : BT::RosTopicPubNode<urc_msgs::msg::StatusLightCommand>(instance_name, conf, params) {}

  static BT::PortsList providedPorts()
  {
    return providedBasicPorts(
      {BT::InputPort<std::string>("color"),
        BT::InputPort<std::string>("state")});
  }

  bool setMessage(urc_msgs::msg::StatusLightCommand & msg) override;
};
}

#endif
