#include "imu_parser.hpp"

namespace imu_parser
{

int header = 0;
IMUParser::IMUParser(const rclcpp::NodeOptions & options)
: rclcpp::Node("imu_parser", options)
{
    vectornav_subscriber = create_subscription<vectornav_msgs::msg::CommonGroup>(
    "/vectornav/raw/common", rclcpp::SystemDefaultsQoS(),
    [this](const vectornav_msgs::msg::CommonGroup msg) {VectornavCallback(msg);});

    imu_publisher = create_publisher<sensor_msgs::msg::Imu>(
    "/imu/data", rclcpp::SystemDefaultsQoS());
}

void IMUParser::VectornavCallback(const vectornav_msgs::msg::CommonGroup & msg)
{
    sensor_msgs::msg::Imu result;
    result.header.frame_id = std::to_string(header++);

    result.orientation.x = msg.quaternion.x;
    result.orientation.y = msg.quaternion.y;
    result.orientation.z = msg.quaternion.z;
    result.orientation.w = msg.quaternion.w;
    result.orientation_covariance = {
        0.01,  0.0,   0.0,
        0.0,   0.01,  0.0,
        0.0,   0.0,   0.01
    };

    result.angular_velocity.x = msg.angularrate.x;
    result.angular_velocity.y = msg.angularrate.y;
    result.angular_velocity.z = msg.angularrate.z;
    result.angular_velocity_covariance = {
        0.01,  0.0,   0.0,
        0.0,   0.01,  0.0,
        0.0,   0.0,   0.01
    };

    result.linear_acceleration.x = msg.accel.x;
    result.linear_acceleration.y = msg.accel.y;
    result.linear_acceleration.z = msg.accel.z;
    result.linear_acceleration_covariance = {
        0.01,  0.0,   0.0,
        0.0,   0.01,  0.0,
        0.0,   0.0,   0.01
    };


    imu_publisher->publish(result);
}

} // namespace orchestrator

RCLCPP_COMPONENTS_REGISTER_NODE(imu_parser::IMUParser)
