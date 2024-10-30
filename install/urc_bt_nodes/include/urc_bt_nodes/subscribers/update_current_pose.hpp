#ifndef UPDATE_CURRENT_POSE_HPP_
#define UPDATE_CURRENT_POSE_HPP_

#include "behaviortree_ros2/bt_topic_sub_node.hpp"
#include <geometry_msgs/msg/pose.hpp>
#include <geometry_msgs/msg/pose_stamped.hpp>
#include <nav_msgs/msg/odometry.hpp>

using namespace BT;

namespace behavior::subscribers
{
class UpdateCurrentPose : public RosTopicSubNode<geometry_msgs::msg::PoseStamped>
{
public:
  UpdateCurrentPose(const std::string & name, const NodeConfig & conf, const RosNodeParams & params)
  : RosTopicSubNode<geometry_msgs::msg::PoseStamped>(name, conf, params) {}

  static PortsList providedPorts()
  {
    return providedBasicPorts({OutputPort<geometry_msgs::msg::Pose>("pose")});
  }

  NodeStatus onTick(const std::shared_ptr<geometry_msgs::msg::PoseStamped> & last_msg) override;
};
} // namespace behavior::subscribers

#endif /* UPDATE_CURRENT_POSE_HPP_ */
