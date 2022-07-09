#include "include/control.hpp"

namespace control
{
Control::Control(const rclcpp::NodeOptions & options)
: rclcpp::Node("motor_controller", options)
{
    //left wheel pubs
    left_wheel_effort_publisher = create_publisher<std_msgs::Float64>(
        "~/left_wheel_effort_controller/command",
        rclcpp::SystemDefaultsQoS());
    right_wheel_effort_publisher = create_publisher<std_msgs::Float64>(
        "~/right_wheel_effort_controller/command",
        rclcpp::SystemDefaultsQoS());

    //right wheel pubs
    right_wheel_shock_publisher = create_publisher<std_msgs::Float64>(
        "~/right_wheel_shock_controller/command",
        rclcpp::SystemDefaultsQoS());
    left_wheel_shock_publisher = create_publisher<std_msgs::Float64>(
        "~/left_wheel_shock_controller/command",
        rclcpp::SystemDefaultsQoS());

    //wheel speed pub
    wheel_speed_publisher = create_publisher<urc_msgs::msg::VelocityPair>(
        "~/encoders",
        rclcpp::SystemDefaultsQoS());

    //Indicates the robot is running
    enabled_pub = create_publisher<std_msgs::Bool>(
        "~/robot_enabled",
        rclcpp::SystemDefaultsQoS());
    enabledCheck();

    speed_P_left = declare_parameter<double>("speed_P_left");
    speed_P_right = declare_parameter<double>("speed_P_right");
    speed_D_left = declare_parameter<double>("speed_D_left");
    speed_D_right = declare_parameter<double>("speed_D_right");
    speed_I_left = declare_parameter<double>("speed_I_left");
    speed_I_right = declare_parameter<double>("speed_I_right");
    wheel_radius = declare_parameter<double>("wheel_radius");
    max_effort = declare_parameter<double>("max_effort");
    rate = declare_parameter<double>("rate");

    //speed and state subs
    speed_sub = create_subscription<urc_msgs::msg::VelocityPair>(
        "~/motors", rclcpp::SystemDefaultsQoS(),
        [this](const urc_msgs::msg::VelocityPair msg)
        {speedCallback(msg);});
    state_sub = create_subscription<sensor_msgs::msg::JointState>(
        "~/joint_states", rclcpp::SystemDefaultsQoS(),
        [this](const sensor_msgs::msg::JointState msg)
        {jointStateCallback(msg);});

    runPID();
}

void Control::speedCallback(const urc_msgs::velocity_pair &msg)
{
    speed_set_point_left = msg.left_velocity;
    speed_set_point_right = msg.right_velocity;
}

void Control::jointStateCallback(const sensor_msgs::msg::JointState &msg)
{
    auto iterator = std::find(msg.name.begin(), msg.name.end(), "left_axle");
    if (iterator != msg.name.end()) {
        auto index = std::distance(msg.name.begin(), iterator);
        speed_measured_left = (msg.velocity[index]) * wheel_radius;
    }

    iterator = std::find(msg.name.begin(), msg.name.end(), "right_axle");
    if (iterator != msg.name.end()) {
        auto index = std::distance(msg.name.begin(), iterator);
        speed_measured_right = (msg.velocity[index]) * wheel_radius;
    }
}

void Control::indicateEnabled()
{
    std_msgs::Bool enabled_msg;
    enabled_msg.data = true;
    enabled_pub.publish(enabled_msg);
}

void Control::runPID()
{
    prev_time = rclcpp::Time::now();
    ros::Rate{rate_var};

    while (rclcpp::ok())
    {
        current_time = rclcpp::Time::now();
        double dt = current_time.toSec() - prev_time.toSec();
        prev_time = current_time;

        double error_left = speed_set_point_left - speed_measured_left;
        double dError_left = (error_left - speed_last_error_left) / dt;
        speed_left_error_accum += error_left;
        speed_last_error_left = error_left;

        effort_left += speed_P_left * error_left + speed_D_left * dError_left + speed_I_left * speed_left_error_accum;

        double error_right = speed_set_point_right - speed_measured_right;
        double dError_right = (error_right - speed_last_error_right) / dt;
        speed_right_error_accum += error_right;
        speed_last_error_right = error_right;

        effort_right +=
            speed_P_right * error_right + speed_D_right * dError_right + speed_I_right * speed_right_error_accum;

        effort_right = std::min(max_effort, std::max(-max_effort, effort_right));
        effort_left = std::min(max_effort, std::max(-max_effort, effort_left));

        std_msgs::Float64 left_wheel_message;
        std_msgs::Float64 right_wheel_message;

        left_wheel_message.data = effort_left;
        right_wheel_message.data = effort_right;

        left_wheel_effort_publisher.publish(left_wheel_message);
        right_wheel_effort_publisher.publish(right_wheel_message);
        igvc_msgs::velocity_pair speed_measured;
        speed_measured.left_velocity = speed_measured_left;
        speed_measured.right_velocity = speed_measured_right;
        now = rclcpp::Time::now();
        rclcpp::Duration duration = now - prev;
        speed_measured.duration = duration.toSec();
        speed_measured.header.stamp = ros::Time::now();
        wheel_speed_publisher.publish(speed_measured);
        rate.sleep();
        prev = now;
    }
}

}

RCLCPP_COMPONENTS_REGISTER_NODE(control::Control)