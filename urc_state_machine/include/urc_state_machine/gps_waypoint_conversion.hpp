#ifndef URC_STATE_MACHINE__GPS_WAYPOINT_CONVERSION_HPP_
#define URC_STATE_MACHINE__GPS_WAYPOINT_CONVERSION_HPP_

#include <string>

#include <builtin_interfaces/msg/time.hpp>
#include <geometry_msgs/msg/pose_stamped.hpp>
#include <urc_msgs/msg/waypoint.hpp>

namespace tf2_ros
{
class Buffer;
}

namespace nav_coordinator
{
// Converts latitude/longitude at zero altitude through UTM into the map frame.
// Returns an identity orientation; throws std::runtime_error if the transform fails.
geometry_msgs::msg::PoseStamped convertGpsToMapWaypoint(
  const urc_msgs::msg::Waypoint & waypoint,
  tf2_ros::Buffer & tf_buffer,
  const std::string & map_frame,
  const std::string & utm_frame,
  const builtin_interfaces::msg::Time & stamp);
}

#endif
