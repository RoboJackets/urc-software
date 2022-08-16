#include "chassis_controller.hpp"

namespace chassis_controller {

namespace ip = boost::asio::ip;

ChassisControllerDriver::ChassisControllerDriver(std::string ip_addr_server, int port) {
    this->ip_addr_server_ = ip_addr_server;
    this->port_ = port;

    ip::udp::endpoint endpoint(ip::udp::v4(), port);
    this->sock_ = std::make_unique<ip::udp::socket>(io_service_, endpoint);
}

DriveEncodersMessage ChassisControllerDriver::getEncoderTicks() {
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

}