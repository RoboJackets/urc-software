#ifndef GROUND_TRUTH_H
#define GROUND_TRUTH_H

#include <geometry_msgs/Vector3.h>
#include <nav_msgs/Odometry.h>
#include <parameter_assertions/assertions.h>
#include <robot_localization/navsat_conversions.h>
#include <ros/ros.h>
#include <tf/transform_broadcaster.h>
#include <tf/transform_datatypes.h>
#include <tf/transform_listener.h>
#include <random>

namespace ground_truth
{
  class GroundTruth : public rclcpp::Node
  {
  public:
    explicit GroundTruth(const rclcpp::NodeOptions & options);

  private:
    nav_msgs::Odometry _og_pose;
    ros::Time _last_estimate;

    rclcppp::Subscription<nav_msgs::Odometry>::SharedPtr _ground_truth_sub;
    rclcpp::Subscription<nav_msgs::Odometry>::SharedPtr _estimate_sub;
    rclcpp::Publisher<nav_msgs::Odometry>::SharedPtr _ground_truth_pub;

    // TODO set this as a launch file parameter
    double longitude = -84.405001;
    double latitude = 33.774497;

    double utm_x, utm_y;

    tf::Transform utm_to_odom;

    ros::Timer utm_timer;

    void groundTruthCallback(const nav_msgs::Odometry::ConstPtr &msg);
    void odomCallback(const nav_msgs::Odometry::ConstPtr &msg);
    void utmCallback(const ros::TimerEvent &event, const tf::Transform &odom_to_utm);
  };
} // namespace ground_truth

#endif
