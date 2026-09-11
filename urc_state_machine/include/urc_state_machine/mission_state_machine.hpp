#pragma once

namespace urc_state_machine
{
enum class SearchMode
{
  NONE,
  YOLO,
  ARUCO_1,
  ARUCO_2
};

enum class MissionState
{
  IDLE,
  NAVIGATING,
  SEARCHING_YOLO,
  SEARCHING_ARUCO,
  CALCULATING_APPROACH,
  NAVIGATING_TO_ARUCO,
  SUCCEEDED,
  FAILED,
  CANCELED
};

enum class MissionEvent
{
  NAVIGATION_SUCCEEDED,
  TARGET_DETECTED,
  APPROACH_READY,
  OPERATION_FAILED,
  CANCEL_REQUESTED,
  ACTIVE_OPERATION_STOPPED
};

enum class MissionCommand
{
  NONE,
  NAVIGATE_TO_WAYPOINT,
  START_YOLO_SEARCH,
  START_ARUCO_SEARCH,
  STOP_SEARCH,
  CALCULATE_APPROACH,
  NAVIGATE_TO_ARUCO,
  CANCEL_ACTIVE_OPERATION,
  COMPLETE_SUCCESS,
  COMPLETE_FAILURE,
  COMPLETE_CANCELED
};

struct Transition
{
  bool accepted;
  MissionState state;
  MissionCommand command;
};

class MissionStateMachine
{
public:
  Transition start(SearchMode mode);
  Transition handle(MissionEvent event);
  MissionState state() const;

private:
  Transition transitionTo(MissionState state, MissionCommand command);

  MissionState state_{MissionState::IDLE};
  SearchMode search_mode_{SearchMode::NONE};
};
}
