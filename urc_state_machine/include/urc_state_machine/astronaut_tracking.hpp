#ifndef URC_STATE_MACHINE__ASTRONAUT_TRACKING_HPP_
#define URC_STATE_MACHINE__ASTRONAUT_TRACKING_HPP_
#include <optional>
#include <geometry_msgs/msg/pose_stamped.hpp>

namespace urc_state_machine
{
// Stores only the latest observation and stationarity anchor, not an unbounded path history.
// Input poses must be valid, transformed into map, and freshness-checked by the caller.
class AstronautTracking
{
public:
  void observe(const geometry_msgs::msg::PoseStamped & pose, double stationary_distance);
  void reset();
  const std::optional<geometry_msgs::msg::PoseStamped> & pose() const;
  bool stationary(double duration) const;

private:
  std::optional<geometry_msgs::msg::PoseStamped> latest_, anchor_;
};
}  // namespace urc_state_machine
#endif
