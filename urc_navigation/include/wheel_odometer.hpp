#ifndef WHEEL_ODOMETER_H
#define WHEEL_ODOMETER_H

#include <urc_msgs/msg/velocity_pair.hpp>
#include <nav_msgs/msg/odometry.hpp>
#include <geometry_msgs/msg/quaternion.hpp>
#include <rclcpp/rclcpp.hpp>
#include <rclcpp_components/register_node_macro.hpp>
#include <tf2_ros/transform_broadcaster.h>
#include <tf2/transform_datatypes.h>
#include <tf2_geometry_msgs/tf2_geometry_msgs.hpp>
#include <tf2/LinearMath/Quaternion.h>
#include <tf2/convert.h>

namespace wheel_odometer
{
class WheelOdometer : public rclcpp::Node
{
public:
  explicit WheelOdometer(const rclcpp::NodeOptions & options);

private:
  rclcpp::Subscription<urc_msgs::msg::VelocityPair>::SharedPtr _enc_sub;
  rclcpp::Publisher<nav_msgs::msg::Odometry>::SharedPtr _odometry_pub;

  std::unique_ptr<tf2_ros::TransformBroadcaster> _tf_broadcaster;

  double wheel_sep;

  float x;
  float y;
  float yaw;

  void enc_callback(const urc_msgs::msg::VelocityPair & msg);
  geometry_msgs::msg::Quaternion createQuaternionMsgFromYaw(double yaw);
};
}

#endif
