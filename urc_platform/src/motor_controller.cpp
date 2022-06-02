#include "motor_controller.hpp"

namespace motor_controller
{
    MotorController::MotorController(const rclcpp::NodeOptions &options) : rclcpp::Node("motor_controller", options)
    {
        _cmd_sub = create_subscription<urc_msgs::msg::VelocityPair>(
            "~/motors",
            rclcpp::SystemDefaultQoS(),
            [this](const urc_msgs::msg::VelocityPair msg)
            { MotorController::cmdCallback(msg); });

        _enc_pub = create_publisher<urc_msgs::msg::VelocityPair>(
            "~/encoders",
            rclcpp::SystemDefaultsQoS());

        _enabled_pub = create_publisher<std_msgs::msg::Bool>(
            "~/robot_enabled",
            rclcpp::SystemDefaultsQoS());

        _battery_pub = create_publisher<std_msgs::msg::Float64>(
            "~/battery",
            rclcpp::SystemDefaultsQoS());

        get_parameter("ip_addr", ip_addr_);
        get_parameter("port", tcpport_);
        get_parameter("battery_alpha", battery_alpha_);
        get_parameter("min_battery_voltage", min_battery_voltage_);

        get_parameter("p_l", p_l_);
        get_parameter("p_r", p_r_);
        get_parameter("d_l", d_l_);
        get_parameter("d_r", d_r_);
        get_parameter("i_r", i_r_);
        get_parameter("i_l", i_l_);
        get_parameter("kv_l", kv_l_);
        get_parameter("kv_r", kv_r_);

        get_parameter("watchdog_delay", watchdog_delay_);
        get_parameter("frequency", frequency_);

        get_parameter_or("log_period", log_period_, 5.0);
    }

    void MotorController::cmdCallback(const urc_msgs::msg::VelocityPair &msg)
    {
        current_motor_command_ = *msg;
        last_motors_message_ = rclcpp::Node::now();
    }
}