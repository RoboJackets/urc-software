#include "pure_pursuit.hpp"

namespace pure_pursuit
{

PurePursuit::PurePursuit(PurePursuitParams params)
{
  params_ = params;
}

geometry_msgs::msg::TwistStamped PurePursuit::getCommandVelocity(
  const geometry_msgs::msg::Pose & current_pose)
{
  double linear_vel, angular_vel;

  linear_vel = params_.desired_linear_velocity;

  geometry_msgs::msg::TwistStamped cmd_vel;
  cmd_vel.twist.linear.x = linear_vel;
  cmd_vel.twist.angular.z = angular_vel;

  return cmd_vel;
}

} // namespace pure_pursuit
