#include "string"
#include "vector"
#include <string>

#ifndef ETH_PACKET_HPP_
#define ETH_PACKET_HPP_

struct EthernetStdPacket
{
  std::string header_message;
  int status_light_command;

  std::string encode()
  {
    std::string result;
    result += header_message;
    result += "urc";
    result += status_light_command;
    result += "end";

    return result;
  }
};

#endif  // !ETH_PACKET_HPP_