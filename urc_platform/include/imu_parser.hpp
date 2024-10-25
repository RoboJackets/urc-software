#ifndef IMU_PARSER_H
#define IMU_PARSER_H

#include <bits/stdc++.h>
#include <math.h>
#include <rclcpp/qos.hpp>
#include <rclcpp/rclcpp.hpp>
#include <rclcpp_components/register_node_macro.hpp>
#include <sensor_msgs/msg/imu.hpp>
#include <unistd.h>
#include <vectornav_msgs/msg/common_group.hpp>

namespace imu_parser
{

class IMUParser : public rclcpp::Node
{
public:
  explicit IMUParser(const rclcpp::NodeOptions & options);

private:
  rclcpp::Publisher<sensor_msgs::msg::Imu>::SharedPtr
    imu_publisher;

  rclcpp::Subscription<vectornav_msgs::msg::CommonGroup>::SharedPtr vectornav_subscriber;

  void VectornavCallback(const vectornav_msgs::msg::CommonGroup & msg);

};

} // namespace imu_parser

#endif
