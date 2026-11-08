#ifndef URC_STATE_MACHINE__MISSION_GEOMETRY_HPP_
#define URC_STATE_MACHINE__MISSION_GEOMETRY_HPP_
#include <geometry_msgs/msg/pose_stamped.hpp>

namespace urc_state_machine
{
// Goals and observations require finite positions and a unit quaternion.
bool validPose(const geometry_msgs::msg::PoseStamped & pose);
// Planar distances are in meters; both poses must already share a frame.
double distanceTo(
  const geometry_msgs::msg::PoseStamped & a,
  const geometry_msgs::msg::PoseStamped & b);
// Never drive backwards merely to restore standoff when already close to the target.
geometry_msgs::msg::PoseStamped standoffGoal(
  const geometry_msgs::msg::PoseStamped & rover,
  const geometry_msgs::msg::PoseStamped & target, double distance);
}  // namespace urc_state_machine
#endif
