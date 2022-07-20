#ifndef GROUND_TRUTH_H
#define GROUND_TRUTH_H

#include <rclcpp/rclcpp.hpp>
#include <rclcpp/time.hpp>
#include <rclcpp/timer.hpp>
#include <rclcpp/duration.hpp>
#include <geometry_msgs/msg/vector3.hpp>
#include <nav_msgs/msg/odometry.hpp>
#include <robot_localization/navsat_conversions.h>
#include <tf2/transform_datatypes.h>
#include <tf2/LinearMath/Quaternion.h>
#include <tf2/LinearMath/Matrix3x3.h>
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

    rclcpp::Timer utm_timer;

    void groundTruthCallback(const nav_msgs::msg::Odometry & msg);
    void odomCallback(const nav_msgs::msg::Odometry & msg);
    void utmCallback(const ros::TimerEvent &event, const tf::Transform &odom_to_utm);
  };
} // namespace ground_truth

#endif
