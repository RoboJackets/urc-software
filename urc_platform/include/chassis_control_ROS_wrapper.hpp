#ifndef CHASSIS_CONTROL_ROS_WRAPPER
#define CHASSIS_CONTROL_ROS_WRAPPER


#include <memory>
#include <rclcpp/rclcpp.hpp>
#include <rclcpp/time.hpp>
#include <rclcpp_components/register_node_macro.hpp>
#include <std_msgs/msg/bool.hpp>
#include <std_msgs/msg/float64.hpp>
#include <urc_msgs/msg/velocity_pair.hpp>
#include "chassis_control_driver.hpp"

namespace chassis_control_ros_wrapper {

class ChassisControlROSWrapper : rclcpp::Node {
private:
    std::unique_ptr<chassis_control_driver::ChassisControlDriver> driver;
    rclcpp::Publisher<urc_msgs::msg::VelocityPair>::SharedPtr _enc_pub;
    rclcpp::TimerBase::SharedPtr timer_;
    double publish_encoder_ticks_frequency_;

public:
    ChassisControlROSWrapper(const rclcpp::NodeOptions & options);
    void publishEncoderTicks();
};

}



#endif