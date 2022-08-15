#include "chassis_control_ROS_wrapper.hpp"

namespace chassis_control_ros_wrapper {

ChassisControlROSWrapper::ChassisControlROSWrapper(const rclcpp::NodeOptions & options)
: rclcpp::Node("chassis_control_driver", options) 
{
    std::string ip_addr_server_ = declare_parameter<std::string>("ip_addr");
    int port_ = declare_parameter<int>("port");
    publish_encoder_ticks_frequency_ = declare_parameter<int>("frequency");

    driver.reset(new chassis_control_driver::ChassisControlDriver(ip_addr_server_, port_));

    _enc_pub = this->create_publisher<urc_msgs::msg::VelocityPair>("~/encoders", 1000);
    // timer_ = this->create_wall_timer(
    //     10ms,
    //     std::bind(&ChassisControlROSWrapper::publishEncoderTicks, this));
}

void ChassisControlROSWrapper::publishEncoderTicks() {

    DriveEncodersMessage ticks = driver->getEncoderTicks();

    urc_msgs::msg::VelocityPair encoder_msg;
    encoder_msg.left_velocity = ticks.frontLeftTicks;
    encoder_msg.right_velocity = ticks.frontRightTicks;
    encoder_msg.duration = ticks.timestamp;
    encoder_msg.header.stamp = this->get_clock()->now();

    _enc_pub->publish(encoder_msg);
}

}

RCLCPP_COMPONENTS_REGISTER_NODE(chassis_control_ros_wrapper::ChassisControlROSWrapper)