#include "rover_pose_bridge.hpp"

#include <algorithm>
#include <functional>
#include <geometry_msgs/msg/pose.hpp>
#include <geometry_msgs/msg/transform_stamped.hpp>
#include <std_msgs/msg/header.hpp>
#include <tf2_ros/transform_broadcaster.h>
#include <utility>

namespace rover_pose_bridge
{

  RoverPoseBridge::RoverPoseBridge(const rclcpp::NodeOptions &options)
      : rclcpp::Node("rover_pose_bridge", options)
  {
  const auto tf_topic = declare_parameter<std::string>("tf_topic", "/ground_truth_pose");
  const auto rover_output = declare_parameter<std::string>("rover_pos_topic", "/rover_ground_truth");
  target_child_frame_ = declare_parameter<std::string>("target_link_name", "walli");

    publisher_ = create_publisher<urc_msgs::msg::RoverPoses>(
        rover_output,
        rclcpp::SystemDefaultsQoS());
    subscription_ = create_subscription<tf2_msgs::msg::TFMessage>(
        tf_topic,
        rclcpp::SystemDefaultsQoS(),
        std::bind(&RoverPoseBridge::handleTransforms, this, std::placeholders::_1));
    tf_broadcaster_ = std::make_unique<tf2_ros::TransformBroadcaster>(this);

  }

  void RoverPoseBridge::handleTransforms(const tf2_msgs::msg::TFMessage::SharedPtr msg) const
  {
    if (!publisher_)
    {
      RCLCPP_WARN(get_logger(), "Publisher not initialized");
      return;
    }

    const auto target_it = std::find_if(
      msg->transforms.begin(),
      msg->transforms.end(),
      [this](const geometry_msgs::msg::TransformStamped & tf) { return tf.child_frame_id == target_child_frame_; });

    if (target_it == msg->transforms.end())
    {
      RCLCPP_WARN(get_logger(), "Target frame '%s' not found in TF message", target_child_frame_.c_str());
      // Log available child_frame_ids to help debugging
      for (const auto &t : msg->transforms)
      {
        RCLCPP_DEBUG(get_logger(), "Found child_frame_id: '%s'", t.child_frame_id.c_str());
      }
      return;
    }

    urc_msgs::msg::RoverPoses output;
    output.header = target_it->header;
    geometry_msgs::msg::Pose pose;
    pose.position.x = target_it->transform.translation.x;
    pose.position.y = target_it->transform.translation.y;
    pose.position.z = target_it->transform.translation.z;
    pose.orientation = target_it->transform.rotation;

    output.names.push_back(target_it->child_frame_id);
    output.poses.push_back(pose);

    // RCLCPP_INFO(get_logger(), "Publishing rover pose for frame '%s'", target_it->child_frame_id.c_str());
    publisher_->publish(std::move(output));


    const auto frame_1 = std::find_if(
      msg->transforms.begin(),
      msg->transforms.end(),
      [this](const geometry_msgs::msg::TransformStamped & tf) { return tf.child_frame_id == "base_link"; });

    // RCLCPP_INFO(get_logger(), "Frame 'base_link' \nPosition: [%.2f, %.2f, %.2f], Orientation: [%.2f, %.2f, %.2f, %.2f]",
    //   frame_1->transform.translation.x,
    //   frame_1->transform.translation.y,
    //   frame_1->transform.translation.z,
    //   frame_1->transform.rotation.x,
    //   frame_1->transform.rotation.y,
    //   frame_1->transform.rotation.z,
    //   frame_1->transform.rotation.w);

    geometry_msgs::msg::TransformStamped tf_out;
    target_it->header.frame_id = "map";
    target_it->child_frame_id = "base_link";
    tf_out.header = target_it->header;
    tf_out.child_frame_id = target_it->child_frame_id;
    tf_out.transform = target_it->transform;
    tf_out.header.stamp = this->now();
    


    tf_broadcaster_->sendTransform(tf_out);
    // RCLCPP_INFO(get_logger(), "Broadcasted TF for frame '%s'", tf_out.child_frame_id.c_str());
    // RCLCPP_INFO(get_logger(), "Broadcasted TF for frame '%s'", tf_out.header.frame_id.c_str());
    // RCLCPP_INFO(get_logger(), "TF Position: [%.2f, %.2f, %.2f]", tf_out.transform.translation.x, tf_out.transform.translation.y, tf_out.transform.translation.z);
  }

} // namespace rover_pose_bridge

#include "rclcpp_components/register_node_macro.hpp"
RCLCPP_COMPONENTS_REGISTER_NODE(rover_pose_bridge::RoverPoseBridge)