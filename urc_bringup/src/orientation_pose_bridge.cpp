#include "orientation_pose_bridge.hpp"

#include <algorithm>
#include <functional>
#include <geometry_msgs/msg/pose.hpp>
#include <geometry_msgs/msg/transform_stamped.hpp>
#include <sensor_msgs/msg/imu.hpp>
#include <utility>

namespace orientation_pose_bridge
{

  OrientationPoseBridge::OrientationPoseBridge(const rclcpp::NodeOptions &options)
      : rclcpp::Node("orientation_pose_bridge", options)
  {
    const auto tf_topic = declare_parameter<std::string>("tf_topic", "/tf");
    const auto orientation_topic = declare_parameter<std::string>("orientation_topic", "/orientation");
    const auto imu_input_topic = declare_parameter<std::string>("imu_input_topic", "/imu/data_raw");
    const auto imu_output_topic = declare_parameter<std::string>("imu_output_topic", "/imu/fused");
    target_child_frame_ = declare_parameter<std::string>("target_link_name", "walli");

    orientation_publisher_ = create_publisher<urc_msgs::msg::OrientationPoses>(
        orientation_topic,
        rclcpp::SystemDefaultsQoS());
    tf_subscription_ = create_subscription<tf2_msgs::msg::TFMessage>(
        tf_topic,
        rclcpp::SystemDefaultsQoS(),
        std::bind(&OrientationPoseBridge::handleTransforms, this, std::placeholders::_1));

    imu_publisher_ = create_publisher<sensor_msgs::msg::Imu>(
        imu_output_topic,
        rclcpp::SystemDefaultsQoS());
    imu_subscription_ = create_subscription<sensor_msgs::msg::Imu>(
        imu_input_topic,
        rclcpp::SystemDefaultsQoS(),
        std::bind(&OrientationPoseBridge::handleImu, this, std::placeholders::_1));
  }

  void OrientationPoseBridge::handleTransforms(const tf2_msgs::msg::TFMessage::SharedPtr msg)
  {
    if (!orientation_publisher_)
    {
      return;
    }

    const auto target_it = std::find_if(
        msg->transforms.begin(),
        msg->transforms.end(),
        [this](const geometry_msgs::msg::TransformStamped &tf)
        { return tf.child_frame_id == target_child_frame_; });

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
    latest_quaternion_ = pose.orientation;
    have_orientation_ = true;

    orientation_publisher_->publish(std::move(output));
  }

  void OrientationPoseBridge::handleImu(const sensor_msgs::msg::Imu::SharedPtr msg)
  {
    if (!imu_publisher_)
    {
      return;
    }

    sensor_msgs::msg::Imu output = *msg;
    if (have_orientation_)
    {
      output.orientation = latest_quaternion_;
    }

    imu_publisher_->publish(output);
  }

} // namespace orientation_pose_bridge

#include "rclcpp_components/register_node_macro.hpp"
RCLCPP_COMPONENTS_REGISTER_NODE(orientation_pose_bridge::OrientationPoseBridge)
