#ifndef URC_STATE_MACHINE__MISSION_PARAMETERS_HPP_
#define URC_STATE_MACHINE__MISSION_PARAMETERS_HPP_
#include <string>
#include <rclcpp/rclcpp.hpp>

namespace urc_state_machine
{
struct MissionParameters
{
  std::string map_frame, base_frame, utm_frame, follower_action;
  std::string route_action, astronaut_action, command_topic, astronaut_topic, aruco_topic;
  std::string waypoint_topic, gps_topic, state_topic;
  double tick_period, target_max_age, command_max_age, phase_timeout, recovery_timeout;
  double astronaut_radius, aruco_radius, follow_distance, aruco_standoff;
  double goal_update_period, goal_update_distance, stationary_distance, stationary_duration;
  double placeholder_duration;
  int max_retries;
  bool tool_placeholder_success, cancel_on_new_waypoint;
};
MissionParameters declareMissionParameters(rclcpp::Node & node);
}  // namespace urc_state_machine
#endif
