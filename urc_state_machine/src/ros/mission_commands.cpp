#include "urc_state_machine/nav_coordinator.hpp"
#include "urc_state_machine/mission_resume.hpp"

namespace nav_coordinator
{
void NavCoordinator::command(const Command & input)
{
  if (mission_.kind == Kind::NONE || !fresh(input.stamp, parameters_.command_max_age) ||
    rclcpp::Time(input.stamp) <= last_command_stamp_)
  {
    return;
  }
  const bool intervention = input.command == Command::ABORT || input.command == Command::RESUME;
  const bool allowed_source = input.source == Command::REMOTE ||
    (intervention && input.source == Command::OPERATOR) ||
    (input.command == Command::FOLLOW && input.source == Command::GESTURE);
  if (!allowed_source) {
    return;
  }
  last_command_stamp_ = rclcpp::Time(input.stamp);
  if (input.command == Command::ABORT) {
    abortMission(input.source == Command::OPERATOR ? "Operator abort" : "Astronaut abort");
    return;
  }
  if (input.command == Command::RESUME) {
    resumeMission(mission_.resume);
    return;
  }
  if (mission_.kind != Kind::ASTRONAUT || mission_.state == State::RESUMING ||
    mission_.state == State::STOPPING)
  {
    return;
  }
  Event event;
  switch (input.command) {
    case Command::FOLLOW: event = Event::FOLLOW; break;
    case Command::STAY: event = Event::STAY; break;
    case Command::FETCH: event = Event::FETCH; break;
    case Command::COME: event = Event::COME; break;
    case Command::GIVE: event = Event::GIVE; break;
    default: return;
  }
  if (mission_.state == State::PAUSED) {
    if (const auto state = urc_state_machine::commandedResume(mission_.resume, event)) {
      resumeMission(*state);
    }
    return;
  }
  if (event == Event::STAY && mission_.state == State::RECOVERING &&
    (mission_.resume == State::FOLLOWING || mission_.resume == State::WAIT_STAY))
  {
    stopMission(State::STAYING, 0, "Remote STAY");
    return;
  }
  transitionOn(event);
}
}  // namespace nav_coordinator
