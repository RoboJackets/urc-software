#include "urc_state_machine/mission_timeouts.hpp"

namespace urc_state_machine
{
double phaseTimeout(State state, const MissionTimeouts & timeouts)
{
  switch (state) {
    case State::NAVIGATING:
    case State::GO_TO_ASTRONAUT:
    case State::COMING:
      return timeouts.navigation;
    case State::SEARCHING_ARUCO:
      return timeouts.search;
    case State::FETCHING:
    case State::GIVING:
      return timeouts.tool;
    case State::FOLLOWING:
    case State::WAIT_STAY:
      return timeouts.following;
    case State::WAIT_FOLLOW:
    case State::HOLDING_HAMMER:
    case State::WAIT_GIVE:
      return timeouts.command_wait;
    default:
      return 0.0;
  }
}
}  // namespace urc_state_machine
