#include "urc_hw/hardware/eth.hpp"
#include <boost/asio/ip/address_v4.hpp>
#include <boost/system/error_code.hpp>
#include <iostream>
#include <memory>
#include <ostream>

namespace ip = boost::asio::ip;

namespace urc_hardware::hardware
{

EthernetSocket::EthernetSocket(std::string ip_addr, int port) : resolver(io_service)
{
  // resolve all possible endpoints

  // look through endpoints and hit socket's connect() member function until
  // a successful UDP connection is established
  this->sock_ = std::make_unique<ip::udp::socket>(io_service);
  RCLCPP_INFO(rclcpp::get_logger("Ethernet"), "Establishing connection...");
  sender_endpoint_ =
      std::make_unique<boost::asio::ip::udp::endpoint>(boost::asio::ip::address_v4::from_string(ip_addr), port);
  boost::system::error_code err;
  sock_->connect(*sender_endpoint_, err);
}

EthernetSocket::~EthernetSocket()
{
  // shut down the UDP connection
  this->sock_->shutdown(ip::udp::socket::shutdown_send);
}

void EthernetSocket::sendMessage(const char* message, size_t len)
{
  this->sock_->send_to(boost::asio::buffer(message, len), *sender_endpoint_);
}

size_t EthernetSocket::readMessage(unsigned char (&buffer)[256])
{
  // read data from UDP connection
  boost::system::error_code error;
  size_t len = sock_->receive(boost::asio::buffer(buffer, sizeof(buffer) - 1), 0, error);

  if (error == boost::asio::error::eof)
  {
    len = 0;
  }
  else if (error)
  {
    throw boost::system::system_error(error);
  }

  return len;
}

std::string EthernetSocket::getIP()
{
  return sock_->remote_endpoint().address().to_string();
}

int EthernetSocket::getPort()
{
  return static_cast<int>(sock_->remote_endpoint().port());
}

std::string EthernetSocket::getBoostVersion()
{
  std::stringstream version;
  version << BOOST_VERSION / 100000 << "." <<  // major version
      BOOST_VERSION / 100 % 1000 << "." <<     // minor version
      BOOST_VERSION % 100;                     // patch level

  return version.str();
}

}  // namespace urc_hardware::hardware
