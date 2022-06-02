#ifndef MOTOR_CONTROLLER_H
#define MOTOR_CONTROLLER_H

#include <rclcpp/rclcpp.hpp>
#include <time.hpp>
#include <std_msgs/msg/Bool.h>
#include <std_msgs/msg/Float64.h>
#include <urc_msgs/msg/velocity_pair.hpp>

namespace motor_controller
{
    class MotorController : public rclcpp::Node
    {
    public:
        explicit MotorController(const rclcpp::NodeOptions &options);

    private:
        urc_msgs::VelocityPair current_motor_command_;
        Time last_motors_message_;

        // seconds to wait before stopping if no new motors command comes in
        double watchdog_delay_;

        // pid values
        double p_l_, p_r_, d_l_, d_r_, i_l_, i_r_;
        double kv_l_, kv_r_;

        // launch parameters
        std::string ip_addr_;        // server ip address
        int tcpport_;                // server tcp tcp port
        double min_battery_voltage_; // min battery voltage before warnings
        double log_period_;          // Period for logging messages
        double frequency_;           // communicate frequency_ with the mbed
        double battery_alpha_;       // alpha value for voltage exponentially weighted moving average

        // current battery voltage
        double battery_avg_;

        // subscribers
        rclcpp::Subscription<urc_msgs::msg::VelocityPair>::SharedPtr _cmd_sub;

        // publishers
        rclcpp::Publisher<urc_msgs::msg::VelocityPair>::SharedPtr _enc_pub;
        rclcpp::Publisher<std_msgs::msg::Bool>::SharedPtr _enabled_pub;
        rclcpp::Publisher<std_msgs::msg::Float64>::SharedPtr _battery_pub;

        void cmdCallback(const urc_msgs::msg::VelocityPair &msg);
    }
}

#endif