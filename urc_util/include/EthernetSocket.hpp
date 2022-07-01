#ifndef ETHERNETSOCKET_H
#define ETHERNETSOCKET_H

#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <memory>
#include <sstream>
#include <string>
#include <iostream>

class EthernetSocket
{
public:
    /**
    Creates Ethernet socket
    @param[in] ip_addr
    @param[in] port
    @throw std::runtime_error is socket couldn't open or connect
    */
    EthernetSocket(std::string ip_addr, int port);
    /**
    
    /**
    Transmit a std::string to the endpoint
    @param[in] msg the string to transmit
    */
    void sendMessage(char *message, size_t len);

    /**
    read a message from the TCP connections
    @return a char array of the characters read
    */
    size_t readMessage(unsigned char (&buffer)[256]);

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
    boost::asio::io_service io_service_;                 // provides core io functionality
    std::unique_ptr<boost::asio::ip::udp::socket> sock_; // tcp connection socket
};

#endif