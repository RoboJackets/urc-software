#include "urc_state_machine/mission_parameters.hpp"
#include <cmath>
#include <stdexcept>

namespace urc_state_machine
{
MissionParameters declareMissionParameters(rclcpp::Node & node)
{
  auto text = [&node](const char * name, const char * value) {
      auto result = node.declare_parameter<std::string>(name, value);
      if (result.empty()) {
        throw std::invalid_argument(std::string(name) + " is empty");
      }
      return result;
    };
  auto positive = [&node](const char * name, double value) {
      const double result = node.declare_parameter<double>(name, value);
      if (!std::isfinite(result) || result <= 0.0) {
        throw std::invalid_argument(std::string(name) + " must be finite and positive");
      }
      return result;
    };
  MissionParameters p;
  p.map_frame = text("map_frame_id", "map");
  p.base_frame = text("base_frame_id", "base_link");
  p.utm_frame = text("utm_frame_id", "utm");
  p.follower_action = text("follower_action_name", "navigate_to_waypoint");
  p.route_action = text("mission_action_name", "execute_autonomous_mission");
  p.astronaut_action = text("astronaut_action_name", "execute_astronaut_mission");
  p.command_topic = text("command_topic", "/command");
  p.astronaut_topic = text("astronaut_pose_topic", "/astronaut/pose");
  p.aruco_topic = text("aruco_topic", "/aruco/detections");
  p.waypoint_topic = text("waypoint_topic", "/nav/waypoint");
  p.gps_topic = text("gps_waypoint_topic", "/waypoint");
  p.state_topic = text("state_topic", "nav_coordinator_state");
  p.tick_period = positive("tick_period", 0.1);
  p.target_max_age = positive("target_max_age", 2.0);
  p.command_max_age = positive("command_max_age", 2.0);
  p.phase_timeout = positive("phase_timeout", 180.0);
  p.recovery_timeout = positive("recovery_timeout", 5.0);
  p.astronaut_radius = positive("astronaut_arrival_radius", 3.0);
  p.aruco_radius = positive("aruco_arrival_radius", 1.0);
  p.follow_distance = positive("follow_distance", 2.0);
  p.aruco_standoff = positive("aruco_standoff", 0.5);
  p.goal_update_period = positive("goal_update_period", 1.0);
  p.goal_update_distance = positive("goal_update_distance", 0.5);
  p.stationary_distance = positive("stationary_distance", 0.25);
  p.stationary_duration = positive("stationary_duration", 2.0);
  p.placeholder_duration = positive("tool_placeholder_duration", 1.0);
  p.max_retries = node.declare_parameter<int>("max_retries", 1);
  p.tool_placeholder_success = node.declare_parameter<bool>("tool_placeholder_success", false);
  p.cancel_on_new_waypoint = node.declare_parameter<bool>("cancel_on_new_waypoint", true);
  if (p.max_retries < 0 || p.follow_distance >= p.astronaut_radius ||
    p.aruco_standoff >= p.aruco_radius)
  {
    throw std::invalid_argument("Invalid retry budget or standoff");
  }
  return p;
}
}  // namespace urc_state_machine
