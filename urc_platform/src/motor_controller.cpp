#include "motor_controller.hpp"

namespace motor_controller
{

namespace ip = boost::asio::ip;

MotorControllerWrapper::MotorControllerDriver::MotorControllerDriver(std::string ip_addr_server, int port)
{
  this->ip_addr_server_ = ip_addr_server;
  this->port_ = port;

  // old
  ip::udp::endpoint endpoint(ip::udp::v4(), port);
  // ip::udp::endpoint endpoint(ip::address_v4::broadcast(), port);
  this->sock_ = std::make_unique<ip::udp::socket>(io_service_, endpoint);
}

bool MotorControllerWrapper::MotorControllerDriver::getEncoderTicks(DriveEncodersMessage & message)
{
  size_t bytes_read;
  uint8_t buffer[256];
  boost::system::error_code error;
  ip::udp::endpoint sender_endpoint;

  bytes_read = sock_->receive_from(boost::asio::buffer(buffer), sender_endpoint);

  message = DriveEncodersMessage_init_zero;
  pb_istream_t istream = pb_istream_from_buffer(buffer, bytes_read);
  bool status = pb_decode(&istream, DriveEncodersMessage_fields, &message);

  return status;
}

int MotorControllerWrapper::MotorControllerDriver::getPortNumber()
{
  return this->port_;
}

MotorControllerWrapper::MotorControllerWrapper(const rclcpp::NodeOptions & options)
: rclcpp::Node("chassis_controller", options)
{
  std::string ip_addr_server_ = declare_parameter<std::string>("ip_addr");
  int port_ = declare_parameter<int>("port");
  publish_encoder_ticks_frequency_ = declare_parameter<double>("frequency");

  // driver.reset(new ChassisControllerDriver(ip_addr_server_, port_));
  driver = std::make_unique<MotorControllerDriver>(ip_addr_server_, port_);

  _enc_pub = this->create_publisher<urc_msgs::msg::VelocityPair>(
    "~/encoders",
    1000);

  timer_ = this->create_wall_timer(
    std::chrono::duration<double>(1.0 / publish_encoder_ticks_frequency_),
    [this](){publishEncoderTicks();});
}

void MotorControllerWrapper::publishEncoderTicks()
{

  DriveEncodersMessage ticks;
  bool success = driver->getEncoderTicks(ticks);

  if (!success) {
    RCLCPP_WARN(this->get_logger(), "Decoding Failed");
  } else {
    urc_msgs::msg::VelocityPair encoder_msg;
    encoder_msg.left_velocity = ticks.frontLeftTicks;
    encoder_msg.right_velocity = ticks.frontRightTicks;
    encoder_msg.duration = ticks.timestamp;
    encoder_msg.header.stamp = this->get_clock()->now();

    _enc_pub->publish(encoder_msg);
  }

}

}

RCLCPP_COMPONENTS_REGISTER_NODE(motor_controller::MotorControllerWrapper)
