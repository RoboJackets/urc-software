#include "urc_state_machine/mission_state.hpp"

namespace urc_state_machine
{
State astronautTransition(State state, Event event)
{
  constexpr struct Transition
  {
    State from;
    Event event;
    State to;
  } transitions[] = {
    {State::IDLE, Event::START, State::GO_TO_ASTRONAUT},
    {State::GO_TO_ASTRONAUT, Event::NAVIGATION_REACHED, State::WAIT_FOLLOW},
    {State::WAIT_FOLLOW, Event::FOLLOW, State::FOLLOWING},
    {State::FOLLOWING, Event::PERSON_STOPPED, State::WAIT_STAY},
    {State::FOLLOWING, Event::STAY, State::STAYING},
    {State::WAIT_STAY, Event::PERSON_MOVED, State::FOLLOWING},
    {State::WAIT_STAY, Event::STAY, State::STAYING},
    {State::STAYING, Event::FETCH, State::FETCHING},
    {State::FETCHING, Event::GRASP_CONFIRMED, State::HOLDING_HAMMER},
    {State::HOLDING_HAMMER, Event::COME, State::COMING},
    {State::COMING, Event::NAVIGATION_REACHED, State::WAIT_GIVE},
    {State::WAIT_GIVE, Event::GIVE, State::GIVING},
    {State::GIVING, Event::RELEASE_CONFIRMED, State::SUCCEEDED},
  };
  for (const auto & transition : transitions) {
    if (transition.from == state && transition.event == event) {
      return transition.to;
    }
  }
  return state;
}
}  // namespace urc_state_machine
