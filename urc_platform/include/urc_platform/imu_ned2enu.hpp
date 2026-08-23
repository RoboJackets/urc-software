#ifndef IMU_NED2ENU_H
#define IMU_NED2ENU_H

#include <rclcpp/publisher.hpp>
#include <rclcpp/subscription.hpp>
#include <sensor_msgs/msg/imu.hpp>
#include <tf2/LinearMath/Quaternion.h>
#include <tf2_geometry_msgs/tf2_geometry_msgs.hpp>
#include <rclcpp_components/register_node_macro.hpp>

namespace imu_ned2enu
{
class ImuNED2ENU : public rclcpp::Node
{
public:
  explicit ImuNED2ENU(const rclcpp::NodeOptions & options);

private:
  rclcpp::Subscription<sensor_msgs::msg::Imu>::SharedPtr imu_subscriber;
  std::shared_ptr<rclcpp::Publisher<sensor_msgs::msg::Imu>> imu_publisher;
};
}

#endif
