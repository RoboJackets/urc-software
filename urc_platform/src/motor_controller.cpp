#include "motor_controller.hpp"

namespace motor_controller
{
    MotorController::MotorController(const rclcpp::NodeOptions &options) : rclcpp::Node("motor_controller", options)
    {
        _cmd_sub = create_subscription<urc_msgs::msg::VelocityPair>(
            "~/motors",
            rclcpp::SystemDefaultQoS(),
            [this](const urc_msgs::msg::VelocityPair msg) { MotorController::cmdCallback(msg); }
        )
    }

    void MotorController::cmdCallback(const urc_msgs::msg::VelocityPair& msg) 
    {
        current_motor_command_ = *msg;
        last_motors_message_ = rclcpp::Node::now();
    }
}