#ifndef URC_STATE_MACHINE__MISSION_RESUME_HPP_
#define URC_STATE_MACHINE__MISSION_RESUME_HPP_

#include <optional>
#include "urc_state_machine/mission_state.hpp"

namespace urc_state_machine
{
// Reissued task commands can restart their own task, never skip an unfinished task.
std::optional<State> commandedResume(State interrupted, Event command);
}  // namespace urc_state_machine

#endif  // URC_STATE_MACHINE__MISSION_RESUME_HPP_
