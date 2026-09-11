#include "urc_state_machine/mission_state_machine.hpp"

namespace urc_state_machine
{

MissionState MissionStateMachine::state() const
{
  return state_;
}

Transition MissionStateMachine::transitionTo(
  MissionState next_state,
  MissionCommand command)
{
  state_ = next_state;
  return {true, state_, command};
}

Transition MissionStateMachine::start(SearchMode mode)
{
  const bool can_start =
    state_ == MissionState::IDLE ||
    state_ == MissionState::SUCCEEDED ||
    state_ == MissionState::FAILED ||
    state_ == MissionState::CANCELED;

  if (!can_start) {
    return {false, state_, MissionCommand::NONE};
  }

  switch (mode) {
    case SearchMode::NONE:
    case SearchMode::YOLO:
    case SearchMode::ARUCO_1:
    case SearchMode::ARUCO_2:
      break;
    default:
      return {false, state_, MissionCommand::NONE};
  }

  search_mode_ = mode;

  return transitionTo(
    MissionState::NAVIGATING,
    MissionCommand::NAVIGATE_TO_WAYPOINT);
}

Transition MissionStateMachine::handle(MissionEvent event)
{
  if (state_ != MissionState::NAVIGATING) {
    return {false, state_, MissionCommand::NONE};
  }

  if (event == MissionEvent::OPERATION_FAILED) {
    return transitionTo(MissionState::FAILED, MissionCommand::COMPLETE_FAILURE);
  }

  if (event != MissionEvent::NAVIGATION_SUCCEEDED) {
    return {false, state_, MissionCommand::NONE};
  }

  switch (search_mode_) {
    case SearchMode::NONE:
      return transitionTo(
        MissionState::SUCCEEDED,
        MissionCommand::COMPLETE_SUCCESS);

    case SearchMode::YOLO:
      return transitionTo(
        MissionState::SEARCHING_YOLO,
        MissionCommand::START_YOLO_SEARCH);

    case SearchMode::ARUCO_1:
    case SearchMode::ARUCO_2:
      return transitionTo(
        MissionState::SEARCHING_ARUCO,
        MissionCommand::START_ARUCO_SEARCH);
  }

  return {false, state_, MissionCommand::NONE};
}

}    // namespace urc_state_machine
