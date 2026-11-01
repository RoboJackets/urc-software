#ifndef URC_STATE_MACHINE__MISSION_TIMEOUTS_HPP_
#define URC_STATE_MACHINE__MISSION_TIMEOUTS_HPP_

#include "urc_state_machine/mission_state.hpp"

namespace urc_state_machine
{
struct MissionTimeouts
{
  double navigation{180.0};
  double search{180.0};
  double tool{180.0};
  double following{0.0};
  double command_wait{0.0};
};

// Seconds per phase; zero disables its deadline. STAYING always waits for a command.
double phaseTimeout(State state, const MissionTimeouts & timeouts);
}  // namespace urc_state_machine

#endif  // URC_STATE_MACHINE__MISSION_TIMEOUTS_HPP_
