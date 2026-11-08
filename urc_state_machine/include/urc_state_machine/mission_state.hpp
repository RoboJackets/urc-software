#ifndef URC_STATE_MACHINE__MISSION_STATE_HPP_
#define URC_STATE_MACHINE__MISSION_STATE_HPP_

namespace urc_state_machine
{
enum class MissionKind { NONE, ROUTE, ASTRONAUT, WAYPOINT };
enum class State
{
  IDLE, NAVIGATING, SEARCHING_ARUCO, GO_TO_ASTRONAUT, WAIT_FOLLOW,
  FOLLOWING, WAIT_STAY, STAYING, FETCHING, HOLDING_HAMMER, COMING,
  WAIT_GIVE, GIVING, RECOVERING, STOPPING, PAUSED, RESUMING, SUCCEEDED, CANCELED
};
enum class Event
{
  START, NAVIGATION_REACHED,
  FOLLOW, STAY, FETCH, COME, GIVE, PERSON_STOPPED, PERSON_MOVED,
  GRASP_CONFIRMED, RELEASE_CONFIRMED
};
// Pure transition functions: callers validate guards before supplying an event.
// Invalid events preserve the state; shared recovery and stop barriers live in the runner.
State astronautTransition(State state, Event event);
const char * stateName(State state);
}  // namespace urc_state_machine
#endif
