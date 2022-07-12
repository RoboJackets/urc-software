#include "ground_truth.hpp"

namespace ground_truth
{
GroundTruth::GroundTruth(const rclcpp::NodeOptions & options)
: rclcpp::Node("ground_truth", options)
{
}

void GroundTruth::groundTruthCallback(const nav_msgs::Odometry::ConstPtr& msg)
{
}

void GroundTruth::odomCallback(const nav_msgs::Odometry::ConstPtr& msg)
{
}

void GroundTruth::utmCallback(const ros::TimerEvent& event, const tf::Transform& odom_to_utm)
{
}


} // namespace ground_truth

RCLCPP_COMPONENTS_REGISTER_NODE(ground_truth::GroundTruth)
