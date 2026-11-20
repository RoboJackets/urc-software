#ifndef URC_STATE_MACHINE__ACTIVE_MISSION_HPP_
#define URC_STATE_MACHINE__ACTIVE_MISSION_HPP_
#include <cstdint>
#include <chrono>
#include <optional>
#include <string>
#include <geometry_msgs/msg/pose_stamped.hpp>
#include "urc_state_machine/mission_state.hpp"

namespace urc_state_machine
{
using MissionClock = std::chrono::steady_clock;
// One mission owns this context and the follower until its stop barrier has completed.
// Retry state survives phase re-entry; action handles stay in the ROS node.
struct ActiveMission
{
  MissionKind kind{MissionKind::NONE};
  State state{State::IDLE};
  State resume{State::IDLE};
  State after_stop{State::IDLE};
  geometry_msgs::msg::PoseStamped waypoint;
  std::optional<geometry_msgs::msg::PoseStamped> marker;
  std::optional<geometry_msgs::msg::PoseStamped> navigation_goal;
  int retries{0};
  uint16_t error_code{0};
  std::string reason;
  MissionClock::time_point phase_started{MissionClock::now()};
  MissionClock::time_point last_goal_update{MissionClock::now()};
  bool operation_started{false};
  bool navigation_reached{false};
};
}  // namespace urc_state_machine
#endif
