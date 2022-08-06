#ifndef GROUND_TRUTH_H
#define GROUND_TRUTH_H

#include <rclcpp/rclcpp.hpp>
#include <rclcpp/time.hpp>
#include <rclcpp/timer.hpp>
#include <rclcpp/duration.hpp>
#include <geometry_msgs/msg/vector3.hpp>
#include <nav_msgs/msg/odometry.hpp>
//#include <robot_localization/navsat_conversions.h>
#include <tf2/transform_datatypes.h>
#include <tf2/LinearMath/Quaternion.h>
#include <tf2/LinearMath/Matrix3x3.h>
#include <tf2_ros/transform_broadcaster.h>
#include <tf2_geometry_msgs/tf2_geometry_msgs.h>
#include <tf2/LinearMath/Vector3.h>
#include <tf2/LinearMath/Transform.h>
#include <tf2_ros/buffer.h>
#include <tf2_ros/transform_listener.h>
#include <random>
#include <rclcpp_components/register_node_macro.hpp>

namespace ground_truth
{
  class GroundTruth : public rclcpp::Node
  {
  public:
    explicit GroundTruth(const rclcpp::NodeOptions & options);

  private:
    nav_msgs::msg::Odometry _og_pose;
    rclcpp::Time _last_estimate;

    rclcpp::Subscription<nav_msgs::msg::Odometry>::SharedPtr _ground_truth_sub;
    rclcpp::Subscription<nav_msgs::msg::Odometry>::SharedPtr _estimate_sub;
    rclcpp::Publisher<nav_msgs::msg::Odometry>::SharedPtr _ground_truth_pub;

    // TODO set this as a launch file parameter
    double longitude = -84.405001;
    double latitude = 33.774497;

    double utm_x, utm_y;

    tf2::Transform utm_to_odom;

    tf2_ros::Buffer tfBuffer_;
    tf2_ros::TransformListener tfListener_;
    
    //static tf2_ros::TransformBroadcaster br; //Causing problems?

    nav_msgs::msg::Odometry g_og_pose;
    rclcpp::Time g_last_estimate;

    double x_noise_std_dev; 
    double y_noise_std_dev; 
    double z_noise_std_dev; 
    double roll_noise_std_dev; 
    double pitch_noise_std_dev; 
    double yaw_noise_std_dev;
    std::default_random_engine engine;
    std::normal_distribution<double> x_distribution;
    std::normal_distribution<double> y_distribution;
    std::normal_distribution<double> z_distribution;
    std::normal_distribution<double> roll_distribution;
    std::normal_distribution<double> pitch_distribution;
    std::normal_distribution<double> yaw_distribution;

    tf2::Quaternion createQuaternionMsgFromYaw(double yaw);
    void groundTruthCallback(const nav_msgs::msg::Odometry & msg);
    void odomCallback(const nav_msgs::msg::Odometry & msg);
    void utmCallback();
  };
} // namespace ground_truth
#endif

