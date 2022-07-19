#include "wheel_odometer.hpp"
#include "tf2/transform_datatypes.h"
#include "tf2_geometry_msgs.h"

namespace wheel_odometer
{

WheelOdometer::WheelOdometer(const rclcpp::NodeOptions &options)
: rclcpp::Node("wheel_odometer", options)
{
    _enc_sub = create_subscription<urc_msgs::msg::VelocityPair>(
        "~/encoders",
        rclcpp::SystemDefaultsQoS(),
        [this](const urc_msgs::msg::VelocityPair msg)
        { WheelOdometer::enc_callback(msg); });

    _odometry_pub = create_publisher<nav_msgs::msg::Odometry>(
        "~/wheel_odometry",
        1000);

    wheel_sep = declare_parameter<double>("wheel_sep", 0.5);

    // initializing sequence number for messages
    seq = 0;

    // initialize position - map published is relative to position at time t=0
    x = 0;
    y = 0;
    yaw = 0;
}

void WheelOdometer::enc_callback(const urc_msgs::msg::VelocityPair &msg)
{
    float leftVelocity = msg.left_velocity;
    float rightVelocity = msg.right_velocity;
    float deltaT = msg.duration;

    float angularVelocity = (rightVelocity - leftVelocity) / wheel_sep;
    float deltaTheta = angularVelocity * deltaT;
    float velocity = (rightVelocity + leftVelocity) / 2;

    geometry_msgs::msg::Vector3 linearVelocities;
    linearVelocities.z = 0;

    if (fabs(rightVelocity - leftVelocity) > 1e-4) {
        // 1e-4 is the point where less of a difference is straight
        linearVelocities.y = velocity * sin(deltaTheta);
        linearVelocities.x = velocity * cos(deltaTheta);
    }
    else {
        // limit where turn radius is infinite (ie. straight line)
        linearVelocities.y = 0;
        linearVelocities.x = velocity;
    }
    // set angular velocities - assuming 2D operation
    geometry_msgs::msg::Vector3 angularVelocities;
    angularVelocities.x = 0.0;
    angularVelocities.y = 0.0;
    angularVelocities.z = angularVelocity;

    nav_msgs::msg::Odometry odom;
    odom.twist.twist.linear = linearVelocities;
    odom.twist.twist.angular = angularVelocities;

    // update global positions
    // note x and y velocities are local reference frame - convert to global then increment poition
    float dx = linearVelocities.x * deltaT;
    float dy = linearVelocities.y * deltaT;
    x += dx * cos(yaw) - dy * sin(yaw);
    y += dx * sin(yaw) + dy * cos(yaw);
    yaw += deltaTheta;

    // enter message info for global position
    odom.pose.pose.position.x = x;
    odom.pose.pose.position.y = y;
    odom.pose.pose.orientation = WheelOdometer::createQuaternionMsgFromYaw(yaw);

    // Row-major representation of the 6x6 covariance matrix
    // The orientation parameters use a fixed-axis representation.
    // In order, the parameters are:
    // (x, y, z, rotation about X axis, rotation about Y axis, rotation about Z axis)
    odom.twist.covariance = {0.02, 1e-4, 1e-4, 1e-4, 1e-4, 1e-4, 1e-4, 0.25, 1e-4, 1e-4, 1e-4, 1e-4,
                             1e-4, 1e-4, 1e6, 1e-4, 1e-4, 1e-4, 1e-4, 1e-4, 1e-4, 1e6, 1e-4, 1e-4,
                             1e-4, 1e-4, 1e-4, 1e-4, 1e6, 1e-4, 1e-4, 1e-4, 1e-4, 1e-4, 1e-4, 0.62};

    // the position covariance takes same form as twist covariance above
    // this grows without bounds as error accumulates - disregard exact reading with high variance
    odom.pose.covariance = {0.01, 1e-6, 1e-6, 1e-6, 1e-6, 1e-6, 1e-6, 0.01, 1e-6, 1e-6, 1e-6, 1e-6,
                            1e-6, 1e-6, 1e6, 1e-6, 1e-6, 1e-6, 1e-6, 1e-6, 1e-6, 1e6, 1e-6, 1e-6,
                            1e-6, 1e-6, 1e-6, 1e-6, 1e6, 1e-6, 1e-6, 1e-6, 1e-6, 1e-6, 1e-6, 1e6};

    // setting reference frames
    odom.header.frame_id = "odom";
    odom.child_frame_id = "base_footprint";
    // set time then publish
    odom.header.stamp = this->get_clock()->now();
    _odometry_pub->publish(odom);
}

geometry_msgs::msg::Quaternion createQuaternionMsgFromYaw(double yaw)
{
    tf2::Quaternion q;
    q.setRPY(0, 0, yaw);
    return tf2::toMsg(q);
}
}

RCLCPP_COMPONENTS_REGISTER_NODE(wheel_odometer::WheelOdometer)