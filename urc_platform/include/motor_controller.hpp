#ifndef MOTOR_CONTROLLER_H
#define MOTOR_CONTROLLER_H

#include <rclcpp/rclcpp.hpp>
#include <rclcpp/time.hpp>
#include <rclcpp_components/register_node_macro.hpp>
#include <memory>
#include <string>
#include <std_msgs/msg/bool.hpp>
#include <std_msgs/msg/float64.hpp>
#include <urc_msgs/msg/velocity_pair.hpp>
#include <diagnostic_updater/diagnostic_updater.hpp>
#include <diagnostic_updater/publisher.hpp>

#include "../../external/nanopb/pb_common.h"
#include "../../external/nanopb/pb_encode.h"
#include "../../external/nanopb/pb_decode.h"

namespace motor_controller
{
    class MotorController : public rclcpp::Node
    {
    public:
        explicit MotorController(const rclcpp::NodeOptions &options);

    private:
        urc_msgs::msg::VelocityPair current_motor_command_;
        rclcpp::Time last_motors_message_;

        // seconds to wait before stopping if no new motors command comes in
        double watchdog_delay_;

        // pid values
        double p_l_, p_r_, d_l_, d_r_, i_l_, i_r_;
        double kv_l_, kv_r_;

        std::string ip_addr_;        // server ip address
        int tcpport_;                // server tcp tcp port
        double min_battery_voltage_; // min battery voltage before warnings
        double log_period_;          // Period for logging messages
        double frequency_;           // communicate frequency_ with the mbed
        double battery_alpha_;       // alpha value for voltage exponentially weighted moving average

        // current battery voltage
        double battery_avg_;

        // Ethernet socket of server
        EthernetSocket socket_;

        // subscribers
        rclcpp::Subscription<urc_msgs::msg::VelocityPair>::SharedPtr _cmd_sub;

        // publishers
        rclcpp::Publisher<urc_msgs::msg::VelocityPair>::SharedPtr _enc_pub;
        rclcpp::Publisher<std_msgs::msg::Bool>::SharedPtr _enabled_pub;
        rclcpp::Publisher<std_msgs::msg::Float64>::SharedPtr _battery_pub;

        // diagnostics
        diagnostic_updater::Updater mc_updater_;
        diagnostic_updater::Updater battery_updater_;

        double mc_hertz = 0;

        void cmdCallback(const urc_msgs::msg::VelocityPair &msg);
        void mc_diagnostic(diagnostic_updater::DiagnosticStatusWrapper &stat);
        void battery_diagnostic(diagnostic_updater::DiagnosticStatusWrapper &stat);

        void setPID();
        void sendRequest();
        void receiveResponse();
        void publishResponse(const ResponseMessage &response);
    }
}

#endif