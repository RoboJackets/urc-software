#ifndef MOTOR_CONTROLLER_ROS_WRAPPER
#define MOTOR_CONTROLLER_ROS_WRAPPER

#include <memory>
#include <string>
#include <rclcpp/rclcpp.hpp>
#include <rclcpp/time.hpp>
#include <rclcpp_components/register_node_macro.hpp>
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <std_msgs/msg/bool.hpp>
#include <std_msgs/msg/float64.hpp>
#include <urc_msgs/msg/velocity_pair.hpp>
#include <urc_nanopb/urc.pb.h>
#include <pb_common.h>
#include <pb_encode.h>
#include <pb_decode.h>

namespace motor_controller
{

class MotorControllerWrapper : public rclcpp::Node
{
public:
  explicit MotorControllerWrapper(const rclcpp::NodeOptions & options);

private:
  class MotorControllerDriver
  {
private:
    std::string ip_addr_server_;
    int port_;
    boost::asio::io_service io_service_;
    std::unique_ptr<boost::asio::ip::udp::socket> sock_;

public:
    MotorControllerDriver(std::string ip_addr_server, int port);
    void start();
    void stop();
    void motorsEnable();
    void motorsDisable();
    void motorsSleep();
    bool getEncoderTicks(DriveEncodersMessage & message);
    int getPortNumber();
  };

  std::unique_ptr<MotorControllerDriver> driver;
  rclcpp::Publisher<urc_msgs::msg::VelocityPair>::SharedPtr _enc_pub;
  rclcpp::TimerBase::SharedPtr timer_;
  double publish_encoder_ticks_frequency_;

  void publishEncoderTicks();
};

}

#endif
