#ifndef ETHERNETSOCKET_H
#define ETHERNETSOCKET_H

#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <memory>
#include <sstream>
#include <string>

/**
 * The EthernetSocket class provides a wrapper for the
 * boost::ip::udp library that is meant to ease communication with
 * ethernet devices.
 */
class EthernetSocket
{
public:
  /**
  Constructor opens the socket using UDP and binds it to an
  endpoint. This endpoint is constructed using the broadcast ip address and
  specified port.

  @param[in] port port to communicate through
  @throw std::runtime_error is socket couldn't open or connect
  */
  EthernetSocket(int port);

  /**
  Constructor opens the socket using UDP and binds it to an
  endpoint. This endpoint is constructed using the specified ip address and
  port, providing the socket with a unique address.

  @param[in] ip_addr ip address to communicate with
  @param[in] port port to communicate through
  @throw std::runtime_error is socket couldn't open or connect
  */
  EthernetSocket(std::string ip_addr, int port);

  /**
  Shut down the socket
  */
  ~EthernetSocket();

  /**
  Transmit a std::string to the endpoint
  @param[in] msg the string to transmit
  */
  void sendMessage(char * message, size_t len);

  /**
  read a message from the UDP connection
  @return a char array of the characters read
  */
  size_t readMessage(unsigned char (& buffer)[256]);

  /**
  Getter for IP address
  @return ip address as string
  */
  std::string getIP();

  /**
  Getter for port number
  @return port as int
  */
  int getPort();

  /**
  Get version of boost used by this library
  @return version number in major_version.minor_version.patch_level format
  */
  std::string getBoostVersion();

private:
  boost::asio::io_service io_service_;                   // provides core io functionality
  std::unique_ptr<boost::asio::ip::udp::socket> sock_;   // udp connection socket
};

#endif
