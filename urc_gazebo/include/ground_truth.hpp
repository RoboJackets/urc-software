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
  explicit Ground_truth();

private:
  rclcppp::Subscription<>::SharedPtr _ground_truth_sub;
  rclcpp::Publisher<>::SharedPtr _ground_truth_pub;
   
  void groundTruthCallback(const nav_msgs::Odometry::ConstPtr& msg);
  void odomCallback(const nav_msgs::Odometry::ConstPtr& msg); 
  void utmCallback(const ros::TimerEvent& event, const tf::Transform& odom_to_utm);

};
} // namespace ground_truth

#endif
