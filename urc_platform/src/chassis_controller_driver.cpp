#include "chassis_controller.hpp"

namespace chassis_controller
{

namespace ip = boost::asio::ip;

ChassisControllerDriver::ChassisControllerDriver(std::string ip_addr_server, int port)
{
  this->ip_addr_server_ = ip_addr_server;
  this->port_ = port;

  // old
  ip::udp::endpoint endpoint(ip::udp::v4(), port);
  // ip::udp::endpoint endpoint(ip::address_v4::broadcast(), port);
  this->sock_ = std::make_unique<ip::udp::socket>(io_service_, endpoint);
}

bool ChassisControllerDriver::getEncoderTicks(DriveEncodersMessage & message)
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

int ChassisControllerDriver::getPortNumber()
{
  return this->port_;
}


}
