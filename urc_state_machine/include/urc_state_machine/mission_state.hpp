#ifndef URC_STATE_MACHINE__MISSION_STATE_HPP_
#define URC_STATE_MACHINE__MISSION_STATE_HPP_

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

}  // namespace urc_state_machine

#endif  // URC_STATE_MACHINE__MISSION_STATE_HPP_
