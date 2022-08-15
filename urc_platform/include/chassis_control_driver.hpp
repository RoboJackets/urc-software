#ifndef CHASSIS_CONTROL_DRIVER_HPP
#define CHASSIS_CONTROL_DRIVER_HPP

#include <string>
#include <memory>
#include <urc_util/ethernet_socket.hpp>
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <urc_nanopb/urc.pb.h>
#include <pb_common.h>
#include <pb_encode.h>
#include <pb_decode.h>

namespace chassis_control_driver {

class ChassisControlDriver {
private:
    std::string ip_addr_server_;
    int port_;
    boost::asio::io_service io_service_;    
    std::unique_ptr<boost::asio::ip::udp::socket> sock_;
public:
    ChassisControlDriver(std::string ip_addr_server, int port);
    void start();
    void stop();
    void motorsEnable();
    void motorsDisable();
    void motorsSleep();
    DriveEncodersMessage getEncoderTicks();
};
}

#endif