#ifndef CHASSIS_CONTROL_ROS_WRAPPER
#define CHASSIS_CONTROL_ROS_WRAPPER

#include <memory>
#include <string>
#include <rclcpp/rclcpp.hpp>
#include <rclcpp/time.hpp>
#include <rclcpp_components/register_node_macro.hpp>
#include <std_msgs/msg/bool.hpp>
#include <std_msgs/msg/float64.hpp>
#include <urc_msgs/msg/velocity_pair.hpp>
#include <urc_nanopb/urc.pb.h>
#include <pb_common.h>
#include <pb_encode.h>
#include <pb_decode.h>

#include "chassis_controller_driver.hpp"

namespace chassis_controller {

class ChassisControllerWrapper : public rclcpp::Node {
public:
    explicit ChassisControllerWrapper(const rclcpp::NodeOptions & options);

private:
    std::unique_ptr<ChassisControllerDriver> driver;
    rclcpp::Publisher<urc_msgs::msg::VelocityPair>::SharedPtr _enc_pub;
    rclcpp::TimerBase::SharedPtr timer_;
    double publish_encoder_ticks_frequency_;
    
    void publishEncoderTicks();
};

}

#endif