#include "urc_state_machine/nav_coordinator.hpp"
#include <stdexcept>
#include "urc_state_machine/gps_waypoint_conversion.hpp"
#include "urc_state_machine/mission_geometry.hpp"

namespace nav_coordinator
{
void NavCoordinator::waypoint(const Pose & input)
{
  if ((mission_.kind != Kind::NONE && mission_.kind != Kind::WAYPOINT) ||
    (navigation_->busy() && !parameters_.cancel_on_new_waypoint) ||
    input.header.frame_id != parameters_.map_frame || !urc_state_machine::validPose(input))
  {
    return;
  }
  navigation_->cancel();
  begin(Kind::WAYPOINT, input);
  changeState(State::NAVIGATING);
}

void NavCoordinator::gpsWaypoint(const urc_msgs::msg::Waypoint & input)
{
  if (mission_.kind != Kind::NONE && mission_.kind != Kind::WAYPOINT) {
    return;
  }
  try {
    waypoint(
      convertGpsToMapWaypoint(
        input, *tf_buffer_, parameters_.map_frame, parameters_.utm_frame, now()));
  } catch (const std::exception & error) {
    RCLCPP_WARN_THROTTLE(
      get_logger(), *get_clock(), 5000,
      "GPS waypoint rejected: %s", error.what());
  }
}
}  // namespace nav_coordinator
