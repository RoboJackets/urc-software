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
    "/imu", rclcpp::SystemDefaultsQoS());
}

void IMUParser::VectornavCallback(const vectornav_msgs::msg::CommonGroup & msg)
{
    sensor_msgs::msg::Imu result;
    // result.header.seq = header++;
    result.header.frame_id = std::to_string(header);
    result.orientation.x = msg.quaternion.x;
    result.orientation.y = msg.quaternion.y;
    result.orientation.z = msg.quaternion.z;
    result.orientation.w = msg.quaternion.w;
    imu_publisher->publish(result);
}

} // namespace orchestrator

RCLCPP_COMPONENTS_REGISTER_NODE(imu_parser::IMUParser)
