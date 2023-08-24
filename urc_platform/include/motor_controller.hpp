#ifndef MOTOR_CONTROLLER_ROS_WRAPPER
#define MOTOR_CONTROLLER_ROS_WRAPPER

#include <memory>
#include <string>
#include <math.h>
#include <algorithm>
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
    int port_;
    std::string ip_addr_server_;
    boost::asio::io_service io_service_;
    std::unique_ptr<boost::asio::ip::udp::socket> sock_;
    boost::asio::ip::udp::endpoint client_endpoint_;
    boost::asio::ip::udp::endpoint server_endpoint_;

public:
    MotorControllerDriver(std::string ip_addr_server, int port);
    void start();
    void stop();
    void motorsEnable();
    void motorsDisable();
    void motorsSleep();
    int available() {return sock_->available();}
    bool getEncoderTicks(DriveEncodersMessage & message);
    bool setSpeed(RequestMessage & message);
    int getPortNumber();
  };

  std::unique_ptr<MotorControllerDriver> driver;
  rclcpp::Publisher<urc_msgs::msg::VelocityPair>::SharedPtr _enc_pub;
  rclcpp::Subscription<urc_msgs::msg::VelocityPair>::SharedPtr _motor_sub;
  rclcpp::TimerBase::SharedPtr timer_;
  double publish_encoder_ticks_frequency_;

  const int ENCODER_CPR = 6144;
  const float WHEEL_RADIUS = 0.170;
  const float VEL_TO_COUNTS_FACTOR = ENCODER_CPR / (2 * M_PI * WHEEL_RADIUS);
  const int QPPR = 15562;
  const float MAX_SPEED = QPPR / VEL_TO_COUNTS_FACTOR;
  const float MIN_SPEED = -1 * MAX_SPEED;

  void publishEncoderTicks();
  void sendSpeed(const urc_msgs::msg::VelocityPair & vel);
  int velocityToCounts(float vel) {return (int)(vel * VEL_TO_COUNTS_FACTOR);}
  float countsToVelocity(int counts) {return counts / VEL_TO_COUNTS_FACTOR;}
};

}

#endif
