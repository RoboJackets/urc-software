#include "ground_truth.hpp"

#include <algorithm>
#include <functional>
#include <geometry_msgs/msg/pose.hpp>
#include <tf2/LinearMath/Matrix3x3.h>
#include <tf2/LinearMath/Quaternion.h>

namespace ground_truth
{

GroundTruth::GroundTruth(const rclcpp::NodeOptions & options)
  : rclcpp::Node("ground_truth", options)
{
  const auto tf_topic = declare_parameter<std::string>("tf_topic", "/ground_truth_pose");
  const auto odom_topic =
    declare_parameter<std::string>("odom_topic", "/ground_truth/odom");
  target_child_frame_ = declare_parameter<std::string>("target_child_frame", "walli");
  odom_frame_id_ = declare_parameter<std::string>("odom_frame_id", "map");
  base_frame_id_ = declare_parameter<std::string>("base_frame_id", "walli");

  odom_publisher_ = create_publisher<nav_msgs::msg::Odometry>(
    odom_topic,
    rclcpp::SystemDefaultsQoS());

  tf_subscription_ = create_subscription<tf2_msgs::msg::TFMessage>(
    tf_topic,
    rclcpp::SystemDefaultsQoS(),
    std::bind(&GroundTruth::handleTransforms, this, std::placeholders::_1));
}

void GroundTruth::handleTransforms(const tf2_msgs::msg::TFMessage::SharedPtr msg) const
{
  if (!odom_publisher_ || msg->transforms.empty())
  {
    return;
  }

  const auto matching_target = std::find_if(
    msg->transforms.begin(),
    msg->transforms.end(),
    [this](const geometry_msgs::msg::TransformStamped & tf)
    {
      return tf.child_frame_id == target_child_frame_;
    });

  const auto & target_tf = *matching_target;

  tf2::Quaternion q_in(
    target_tf.transform.rotation.x,
    target_tf.transform.rotation.y,
    target_tf.transform.rotation.z,
    target_tf.transform.rotation.w);
  double roll = 0.0;
  double pitch = 0.0;
  double yaw = 0.0;
  tf2::Matrix3x3(q_in).getRPY(roll, pitch, yaw);
  tf2::Quaternion q_out;
  q_out.setRPY(0.0, 0.0, yaw);
  q_out.normalize();

  geometry_msgs::msg::Pose pose;
  pose.position.x = target_tf.transform.translation.x;
  pose.position.y = target_tf.transform.translation.y;
  pose.position.z = 0.0;
  pose.orientation.x = q_out.x();
  pose.orientation.y = q_out.y();
  pose.orientation.z = q_out.z();
  pose.orientation.w = q_out.w();

  nav_msgs::msg::Odometry odom_msg;
  odom_msg.header = target_tf.header;
  odom_msg.header.frame_id = odom_frame_id_;
  odom_msg.child_frame_id = base_frame_id_;
  odom_msg.pose.pose = pose;

  odom_publisher_->publish(std::move(odom_msg));
}

}  // namespace ground_truth

#include "rclcpp_components/register_node_macro.hpp"
RCLCPP_COMPONENTS_REGISTER_NODE(ground_truth::GroundTruth)
