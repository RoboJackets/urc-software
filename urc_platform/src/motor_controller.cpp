#include "motor_controller.hpp"

namespace motor_controller
{

namespace ip = boost::asio::ip;

MotorControllerWrapper::MotorControllerDriver::MotorControllerDriver(std::string ip_addr_server, int port)
{
  this->ip_addr_server_ = ip_addr_server;
  this->port_ = port;
  this->client_endpoint_.address(ip::address_v4::from_string(ip_addr_server));
  this->client_endpoint_.port(port);
  this->server_endpoint_.address(ip::address_v4::from_string("192.168.8.167"));
  this->server_endpoint_.port(port);
  this->sock_ = std::make_unique<ip::udp::socket>(io_service_, client_endpoint_);
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

bool MotorControllerWrapper::MotorControllerDriver::setSpeed(RequestMessage &message) {
  uint8_t buffer[256];
  size_t response_length;
  
  pb_ostream_t ostream = pb_ostream_from_buffer(buffer, sizeof(buffer));
  bool status = pb_encode(&ostream, RequestMessage_fields, &message);
  response_length = ostream.bytes_written;

  sock_->send_to(boost::asio::buffer(buffer), server_endpoint_);

  return status;
}

int MotorControllerWrapper::MotorControllerDriver::getPortNumber()
{
  return this->port_;
}

MotorControllerWrapper::MotorControllerWrapper(const rclcpp::NodeOptions & options)
: rclcpp::Node("motor_controller", options)
{
  std::string ip_addr_server_ = declare_parameter<std::string>("ip_addr");
  int port_ = declare_parameter<int>("port");
  publish_encoder_ticks_frequency_ = declare_parameter<double>("frequency");

  driver = std::make_unique<MotorControllerDriver>(ip_addr_server_, port_);

  _enc_pub = create_publisher<urc_msgs::msg::VelocityPair>(
    "~/encoders",
    rclcpp::SystemDefaultsQoS());

  _motor_sub = create_subscription<urc_msgs::msg::VelocityPair>(
    "~/motors",
    rclcpp::SystemDefaultsQoS(),
    [this](const urc_msgs::msg::VelocityPair vel) { sendSpeed(vel); }
  );

  timer_ = this->create_wall_timer(
    std::chrono::duration<double>(1.0 / publish_encoder_ticks_frequency_),
    [this]() { publishEncoderTicks(); }
  );  
}

void MotorControllerWrapper::publishEncoderTicks()
{
  if (driver->available()) {
    DriveEncodersMessage ticks;
    bool success = driver->getEncoderTicks(ticks);

    if (!success) {
      RCLCPP_WARN(this->get_logger(), "Decoding Failed");
    } else {
      urc_msgs::msg::VelocityPair encoder_msg;
      encoder_msg.left_velocity = ticks.leftSpeed;
      encoder_msg.right_velocity = ticks.rightSpeed;
      encoder_msg.duration = ticks.timestamp;
      encoder_msg.header.stamp = this->get_clock()->now();

      _enc_pub->publish(encoder_msg);
    }
  }

}

void MotorControllerWrapper::sendSpeed(const urc_msgs::msg::VelocityPair &vel) {
    
  RequestMessage requestMessage;
  requestMessage.requestSpeed = true;
  requestMessage.requestDiagnostics = false;
  requestMessage.leftSpeed = velocityToCounts(std::clamp(static_cast<const float&>(vel.left_velocity), MIN_SPEED, MAX_SPEED));
  requestMessage.rightSpeed = velocityToCounts(std::clamp(static_cast<const float&>(vel.right_velocity), MIN_SPEED, MAX_SPEED));
  requestMessage.duration = 1500;
  requestMessage.timestamp = (int32_t) this->get_clock()->now().seconds();
  
  bool success = driver->setSpeed(requestMessage);
}

}

RCLCPP_COMPONENTS_REGISTER_NODE(motor_controller::MotorControllerWrapper)
