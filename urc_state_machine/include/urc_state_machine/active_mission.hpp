#ifndef URC_STATE_MACHINE__ACTIVE_MISSION_HPP_
#define URC_STATE_MACHINE__ACTIVE_MISSION_HPP_

#include <memory>
#include <optional>

#include <geometry_msgs/msg/pose_stamped.hpp>
#include <rclcpp_action/rclcpp_action.hpp>
#include <urc_msgs/action/execute_autonomous_mission.hpp>
#include <urc_msgs/msg/detection_bounding_box.hpp>

#include "urc_state_machine/mission_state.hpp"

namespace urc_state_machine
{

enum class NavigationLeg
{
  INITIAL_WAYPOINT,
  ARUCO_APPROACH
};

struct ActiveMission
{
  using ExecuteMission = urc_msgs::action::ExecuteAutonomousMission;
  using MissionGoalHandle = rclcpp_action::ServerGoalHandle<ExecuteMission>;

  std::shared_ptr<MissionGoalHandle> goal_handle;
  geometry_msgs::msg::PoseStamped original_waypoint;
  SearchMode search_mode{SearchMode::NONE};
  NavigationLeg navigation_leg{NavigationLeg::INITIAL_WAYPOINT};
  std::optional<urc_msgs::msg::DetectionBoundingBox> bounding_box;
  std::optional<geometry_msgs::msg::PoseStamped> aruco_pose;
  bool cancellation_requested{false};
};

}  // namespace urc_state_machine

#endif  // URC_STATE_MACHINE__ACTIVE_MISSION_HPP_
