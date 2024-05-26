#ifndef STATUS_LIGHT_PUBLISHER_HPP__
#define STATUS_LIGHT_PUBLISHER_HPP__

#include "behaviortree_cpp/basic_types.h"
#include "behaviortree_cpp/tree_node.h"
#include "behaviortree_cpp/tree_node.h"
#include "behaviortree_ros2/ros_node_params.hpp"
#include "behaviortree_ros2/bt_topic_pub_node.hpp"
#include "string"
#include "std_msgs/msg/int8.hpp"

namespace behavior::actions
{
class StatusLightPublisher : public BT::RosTopicPubNode<std_msgs::msg::Int8>
{
    public:
    StatusLightPublisher(const std::string& instance_name, const BT::NodeConfig& conf,
        const BT::RosNodeParams& params)
    : BT::RosTopicPubNode<std_msgs::msg::Int8>(instance_name, conf, params) {}
    
    static BT::PortsList providedPorts() {
        return providedBasicPorts({
            BT::InputPort<std_msgs::msg::Int8>("color"),
            BT::InputPort<std_msgs::msg::Int8>("display")
        });
    }

    bool setMessage(std_msgs::msg::Int8& msg) override;

};
}

#endif
