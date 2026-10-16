#include "urc_state_machine/mission_geometry.hpp"
#include <cmath>

namespace urc_state_machine
{
bool validPose(const geometry_msgs::msg::PoseStamped & pose)
{
  const auto & p = pose.pose.position;
  const auto & q = pose.pose.orientation;
  const double norm = q.x * q.x + q.y * q.y + q.z * q.z + q.w * q.w;
  return !pose.header.frame_id.empty() && std::isfinite(p.x) && std::isfinite(p.y) &&
         std::isfinite(p.z) && std::isfinite(norm) && std::abs(norm - 1.0) < 1e-3;
}

double distanceTo(
  const geometry_msgs::msg::PoseStamped & a,
  const geometry_msgs::msg::PoseStamped & b)
{
  return std::hypot(
    a.pose.position.x - b.pose.position.x,
    a.pose.position.y - b.pose.position.y);
}

geometry_msgs::msg::PoseStamped standoffGoal(
  const geometry_msgs::msg::PoseStamped & rover,
  const geometry_msgs::msg::PoseStamped & target, double distance)
{
  auto goal = rover;
  const double dx = target.pose.position.x - rover.pose.position.x;
  const double dy = target.pose.position.y - rover.pose.position.y;
  const double range = std::hypot(dx, dy);
  if (range <= distance) {
    return goal;
  }
  const double yaw = std::atan2(dy, dx);
  goal.pose.position.x = target.pose.position.x - distance * std::cos(yaw);
  goal.pose.position.y = target.pose.position.y - distance * std::sin(yaw);
  goal.pose.orientation.x = 0.0;
  goal.pose.orientation.y = 0.0;
  goal.pose.orientation.z = std::sin(yaw / 2.0);
  goal.pose.orientation.w = std::cos(yaw / 2.0);
  return goal;
}

}  // namespace urc_state_machine
