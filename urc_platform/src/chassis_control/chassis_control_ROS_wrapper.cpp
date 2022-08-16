#include "chassis_control_ROS_wrapper.hpp"

namespace chassis_control_ros_wrapper {

namespace ip = boost::asio::ip;

ChassisControlDriver::ChassisControlDriver(std::string ip_addr_server, int port) {
    this->ip_addr_server_ = ip_addr_server;
    this->port_ = port;

    ip::udp::endpoint endpoint(ip::udp::v4(), port);
    this->sock_ = std::make_unique<ip::udp::socket>(io_service_, endpoint);
}

DriveEncodersMessage ChassisControlDriver::getEncoderTicks() {
    size_t bytes_read;
    uint8_t buffer[256];  
    boost::system::error_code error; 

    memset(buffer, 0, sizeof(buffer));
    bytes_read = sock_->receive(boost::asio::buffer(buffer, sizeof(buffer) - 1), 0, error);

    // Empty message where the decoded buffer will be stored
    DriveEncodersMessage response_msg = DriveEncodersMessage_init_zero;

    pb_istream_t istream = pb_istream_from_buffer(buffer, bytes_read);
    bool status = pb_decode(&istream, DriveEncodersMessage_fields, &response_msg);

    if (!status) {
        // report error
    }

    return response_msg;
}

ChassisControlROSWrapper::ChassisControlROSWrapper(const rclcpp::NodeOptions & options)
: rclcpp::Node("chassis_control_driver", options) 
{
    std::string ip_addr_server_ = declare_parameter<std::string>("ip_addr");
    int port_ = declare_parameter<int>("port");
    publish_encoder_ticks_frequency_ = declare_parameter<int>("frequency");

    driver.reset(new ChassisControlDriver(ip_addr_server_, port_));

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