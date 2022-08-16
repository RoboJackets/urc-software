#ifndef TEST_DRIVER_H
#define TEST_DRIVER_H

#include <memory>
#include <string>
#include <rclcpp/rclcpp.hpp>
#include <rclcpp/time.hpp>
#include <rclcpp_components/register_node_macro.hpp>
#include <std_msgs/msg/bool.hpp>
#include <std_msgs/msg/float64.hpp>
#include <urc_msgs/msg/velocity_pair.hpp>
#include <diagnostic_updater/diagnostic_updater.hpp>
#include <diagnostic_updater/publisher.hpp>
#include <urc_util/ethernet_socket.hpp>
#include <urc_nanopb/urc.pb.h>

#include <pb_common.h>
#include <pb_encode.h>
#include <pb_decode.h>

namespace test_driver
{

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

class ChassisControlROSWrapper : public rclcpp::Node {
public:
    explicit ChassisControlROSWrapper(const rclcpp::NodeOptions & options);

private:
    std::unique_ptr<ChassisControlDriver> driver;
    rclcpp::Publisher<urc_msgs::msg::VelocityPair>::SharedPtr _enc_pub;
    rclcpp::TimerBase::SharedPtr timer_;
    double publish_encoder_ticks_frequency_;
    
    void publishEncoderTicks();

};

}

#endif
