#ifndef CONTROL_H_
#define CONTROL_H_

#include <rclcpp/rclcpp.hpp>
#include <rclcpp/time.hpp>
#include <urc_msgs/msg/velocity_pair.hpp>
#include <sensor_msgs/msg/joint_state.hpp>
#include <rclcpp_components/register_node_macro.hpp>
#include <std_msgs/msg/bool.hpp>
#include <std_msgs/msg/float64.hpp>
#include <algorithm>

namespace control
{
class Control : public rclcpp::Node
{
public:
    explicit Control(const rclcpp::NodeOptions & options);

private:
    rclcpp::Publisher<urc_msgs::msg::VelocityPair>::SharedPtr _enc_pub;
    
    rclcpp::Publisher<std_msgs::msg::Float64>::SharedPtr left_wheel_effort_publisher;
    rclcpp::Publisher<std_msgs::msg::Float64>::SharedPtr right_wheel_effort_publisher;

    rclcpp::Publisher<std_msgs::msg::Float64>::SharedPtr right_wheel_shock_publisher;
    rclcpp::Publisher<std_msgs::msg::Float64>::SharedPtr left_wheel_shock_publisher;
    
    rclcpp::Publisher<urc_msgs::msg::VelocityPair>::SharedPtr wheel_speed_publisher;

    rclcpp::Publisher<std_msgs::msg::Bool>::SharedPtr enabled_pub;    

    rclcpp::Subscription<urc_msgs::msg::VelocityPair>::SharedPtr speed_sub;
    rclcpp::Subscription<sensor_msgs::msg::JointState>::SharedPtr state_sub;

    double speed_P_left, speed_P_right, speed_I_left, speed_I_right, speed_D_left, speed_D_right;
    double wheel_radius;
    double max_effort;
    double rate_var;

    double speed_last_error_left, speed_last_error_right, speed_left_error_accum, speed_right_error_accum = 0.0;
    double effort_right, effort_left = 0.0;

    double speed_set_point_left = 0.0;
    double speed_set_point_right = 0.0;
    double speed_measured_left = 0.0;
    double speed_measured_right = 0.0;
    
    rclcpp::Time prev_time, current_time;

    void speedCallback(const urc_msgs::msg::VelocityPair &msg);
    void jointStateCallback(const sensor_msgs::msg::JointState &msg);
    void indicateEnabled();
    void setShockPoint();
    void runPID();
};
}

#endif