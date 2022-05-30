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

            // subscribers
            rclcpp::Subscription<urc_msgs::msg::VelocityPair>::SharedPtr _cmd_sub;

            // publishers
            rclcpp::Publisher<urc_msgs::msg::VelocityPair>::SharedPtr _enc_pub;
            rclcpp::Publisher<std_msgs::msg::Bool>::SharedPtr _enabled_pub;
            rclcpp::Publisher<std_msgs::msg::Float64>::SharedPtr _battery_pub;

            void cmdCallback(const urc_msgs::msg::VelocityPair& msg);
    }
}

#endif