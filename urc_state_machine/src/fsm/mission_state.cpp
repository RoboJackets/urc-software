#include "urc_state_machine/mission_state.hpp"

namespace urc_state_machine
{
const char * stateName(State state)
{
  switch (state) {
    case State::IDLE: return "IDLE";
    case State::SEARCHING_ARUCO: return "SEARCHING_ARUCO";
    case State::NAVIGATING: return "NAVIGATING";
    case State::GO_TO_ASTRONAUT: return "GO_TO_ASTRONAUT";
    case State::WAIT_FOLLOW: return "WAIT_FOLLOW";
    case State::FOLLOWING: return "FOLLOWING";
    case State::WAIT_STAY: return "WAIT_STAY";
    case State::STAYING: return "STAYING";
    case State::FETCHING: return "FETCHING";
    case State::HOLDING_HAMMER: return "HOLDING_HAMMER";
    case State::COMING: return "COMING";
    case State::WAIT_GIVE: return "WAIT_GIVE";
    case State::GIVING: return "GIVING";
    case State::RECOVERING: return "RECOVERING";
    case State::STOPPING: return "STOPPING";
    case State::PAUSED: return "PAUSED";
    case State::RESUMING: return "RESUMING";
    case State::SUCCEEDED: return "SUCCEEDED";
    case State::CANCELED: return "CANCELED";
  }
  return "UNKNOWN";
}
}  // namespace urc_state_machine
