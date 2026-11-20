#include "urc_state_machine/mission_resume.hpp"

namespace urc_state_machine
{
std::optional<State> commandedResume(State interrupted, Event command)
{
  if (command == Event::FOLLOW &&
    (interrupted == State::WAIT_FOLLOW || interrupted == State::FOLLOWING ||
    interrupted == State::WAIT_STAY))
  {
    return State::FOLLOWING;
  }
  if (command == Event::STAY &&
    (interrupted == State::FOLLOWING || interrupted == State::WAIT_STAY ||
    interrupted == State::STAYING))
  {
    return State::STAYING;
  }
  if (command == Event::FETCH &&
    (interrupted == State::STAYING || interrupted == State::FETCHING))
  {
    return State::FETCHING;
  }
  if (command == Event::COME &&
    (interrupted == State::HOLDING_HAMMER || interrupted == State::COMING))
  {
    return State::COMING;
  }
  if (command == Event::GIVE &&
    (interrupted == State::WAIT_GIVE || interrupted == State::GIVING))
  {
    return State::GIVING;
  }
  return std::nullopt;
}

}  // namespace urc_state_machine
