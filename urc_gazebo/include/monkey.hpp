#ifndef MONKEY_H_
#define MONKEY_H_

#include <rclcpp/rclcpp.hpp>
#include <rclcpp/time.hpp>
#include <rclcpp/timer.hpp>
#include <rclcpp/duration.hpp>
#include <std_msgs/msg/float64.hpp>
//#include <geometry_msgs/msg/vector3.hpp>
//#include <nav_msgs/msg/odometry.hpp>
/*
#include <robot_localization/navsat_conversions.h>
#include <tf2/transform_datatypes.h>
#include <tf2/LinearMath/Quaternion.h>
#include <tf2/LinearMath/Matrix3x3.h>
#include <tf2_ros/transform_broadcaster.h>
#include <tf2_geometry_msgs/tf2_geometry_msgs.h>
#include <Vector3.h>
#include <Transform.h>
#include <geometry_msgs/TransformStamped.h>
#include <random>
*/
#include <rclcpp_components/register_node_macro.hpp>

namespace monkey
{
class Monkey : public rclcpp::Node
{
public:
  explicit Monkey(const rclcpp::NodeOptions & options);

private:
    rclcpp::Publisher<std_msgs::msg::Float64>::SharedPtr testpub;
    double testnum = 69.0;

};
} // namespace monkey

#endif
