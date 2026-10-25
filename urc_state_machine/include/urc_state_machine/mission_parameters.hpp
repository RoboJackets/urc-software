#ifndef URC_STATE_MACHINE__MISSION_PARAMETERS_HPP_
#define URC_STATE_MACHINE__MISSION_PARAMETERS_HPP_
#include <string>
#include <rclcpp/rclcpp.hpp>
#include "urc_state_machine/mission_timeouts.hpp"

namespace urc_state_machine
{
struct MissionParameters
{
  std::string map_frame, base_frame, utm_frame, follower_action;
  std::string route_action, astronaut_action, command_topic, astronaut_topic, aruco_topic;
  std::string waypoint_topic, gps_topic, state_topic;
  std::string status_light_topic, drive_mode_topic, drive_mode_command_topic;
  std::string abort_service, resume_service, spiral_search_service;
  double status_light_refresh_period;
  double tick_period, target_max_age, command_max_age, recovery_timeout;
  MissionTimeouts timeouts;
  double astronaut_radius, route_radius, follow_distance, aruco_standoff, aruco_association_radius;
  double goal_update_period, goal_update_distance, stationary_distance, stationary_duration;
  double placeholder_duration, spiral_search_radius;
  int max_retries;
  bool tool_placeholder_success, cancel_on_new_waypoint, aruco_refinement;
};
MissionParameters declareMissionParameters(rclcpp::Node & node);
}  // namespace urc_state_machine
#endif
