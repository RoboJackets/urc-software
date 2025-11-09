#include "orientation_pose_bridge.hpp"

#include <algorithm>
#include <functional>
#include <geometry_msgs/msg/pose.hpp>
#include <geometry_msgs/msg/transform_stamped.hpp>
#include <std_msgs/msg/header.hpp>
#include <utility>

namespace orientation_pose_bridge
{

  OrientationPoseBridge::OrientationPoseBridge(const rclcpp::NodeOptions &options)
      : rclcpp::Node("orientation_pose_bridge", options)
  {
  const auto tf_topic = declare_parameter<std::string>("tf_topic", "/tf");
  const auto orientation_output = declare_parameter<std::string>("orientation_topic", "/orientation");
  target_child_frame_ = declare_parameter<std::string>("target_link_name", "walli");

    publisher_ = create_publisher<urc_msgs::msg::OrientationPoses>(
        orientation_output,
        rclcpp::SystemDefaultsQoS());
    subscription_ = create_subscription<tf2_msgs::msg::TFMessage>(
        tf_topic,
        rclcpp::SystemDefaultsQoS(),
        std::bind(&OrientationPoseBridge::handleTransforms, this, std::placeholders::_1));
  }

  void OrientationPoseBridge::handleTransforms(const tf2_msgs::msg::TFMessage::SharedPtr msg) const
  {
    if (!publisher_)
    {
      return;
    }

    const auto target_it = std::find_if(
      msg->transforms.begin(),
      msg->transforms.end(),
      [this](const geometry_msgs::msg::TransformStamped & tf) { return tf.child_frame_id == target_child_frame_; });

    if (target_it == msg->transforms.end())
    {
      return;
    }

    urc_msgs::msg::OrientationPoses output;
    output.header = target_it->header;
    geometry_msgs::msg::Pose pose;
    pose.position.x = target_it->transform.translation.x;
    pose.position.y = target_it->transform.translation.y;
    pose.position.z = target_it->transform.translation.z;
    pose.orientation = target_it->transform.rotation;

    output.names.push_back(target_it->child_frame_id);
    output.poses.push_back(pose);

    publisher_->publish(std::move(output));
  }

} // namespace orientation_pose_bridge

#include "rclcpp_components/register_node_macro.hpp"
RCLCPP_COMPONENTS_REGISTER_NODE(orientation_pose_bridge::OrientationPoseBridge)
