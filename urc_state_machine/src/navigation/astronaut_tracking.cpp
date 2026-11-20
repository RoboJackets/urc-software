#include "urc_state_machine/astronaut_tracking.hpp"
#include <rclcpp/time.hpp>
#include "urc_state_machine/mission_geometry.hpp"

namespace urc_state_machine
{
void AstronautTracking::observe(
  const geometry_msgs::msg::PoseStamped & pose, double stationary_distance)
{
  if (latest_ && rclcpp::Time(pose.header.stamp) <= rclcpp::Time(latest_->header.stamp)) {
    return;
  }
  if (!anchor_ || distanceTo(*anchor_, pose) > stationary_distance) {
    anchor_ = pose;
  }
  latest_ = pose;
}
void AstronautTracking::reset()
{
  latest_.reset(); anchor_.reset();
}
const std::optional<geometry_msgs::msg::PoseStamped> & AstronautTracking::pose() const
{
  return latest_;
}
bool AstronautTracking::stationary(double duration) const
{
  return latest_ && anchor_ &&
         (rclcpp::Time(latest_->header.stamp) - rclcpp::Time(anchor_->header.stamp)).seconds() >=
         duration;
}
}  // namespace urc_state_machine
