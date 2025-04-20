#include "imu_ned2enu.hpp"
#include <rclcpp/logging.hpp>

namespace imu_ned2enu
{
ImuNED2ENU::ImuNED2ENU(const rclcpp::NodeOptions & options)
: Node("imu_ned2enu", options)
{
  declare_parameter("imu_in_topic", "/vectornav/imu");
  declare_parameter("imu_out_topic", "/imu/data");

  imu_publisher = create_publisher<sensor_msgs::msg::Imu>(
    get_parameter("imu_out_topic").as_string(), rclcpp::SystemDefaultsQoS());

  imu_subscriber = create_subscription<sensor_msgs::msg::Imu>(
    get_parameter("imu_in_topic").as_string(), rclcpp::SystemDefaultsQoS(),
    [this](const sensor_msgs::msg::Imu::SharedPtr msg) {
      sensor_msgs::msg::Imu msg_out = *msg;
      
      tf2::Quaternion q_ned;
      tf2::fromMsg(msg->orientation, q_ned);
      tf2::Quaternion q_rot;
      q_rot.setRPY(0, 0, -M_PI/2); // we are only using the yaw rotation
      tf2::Quaternion q_enu = q_rot * q_ned;
      q_enu.normalize();
      msg_out.orientation = tf2::toMsg(q_enu);

      msg_out.angular_velocity.x = msg->angular_velocity.y;
      msg_out.angular_velocity.y = msg->angular_velocity.x;
      msg_out.angular_velocity.z = -msg->angular_velocity.z;

      msg_out.linear_acceleration.x = msg->linear_acceleration.y;
      msg_out.linear_acceleration.y = msg->linear_acceleration.x;
      msg_out.linear_acceleration.z = -msg->linear_acceleration.z;

      imu_publisher->publish(msg_out);
    });
}
} // namespace imu_ned2enu

RCLCPP_COMPONENTS_REGISTER_NODE(imu_ned2enu::ImuNED2ENU)
