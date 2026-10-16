#include "urc_state_machine/mission_state.hpp"

namespace urc_state_machine
{
State routeTransition(State state, Event event)
{
  constexpr struct Transition
  {
    State from;
    Event event;
    State to;
  } transitions[] = {
    {State::IDLE, Event::START, State::NAVIGATING},
    {State::NAVIGATING, Event::NAVIGATION_REACHED, State::SEARCHING_ARUCO},
    {State::SEARCHING_ARUCO, Event::MARKER_FOUND, State::CALCULATING_APPROACH},
    {State::CALCULATING_APPROACH, Event::APPROACH_READY, State::NAVIGATING_TO_ARUCO},
    {State::NAVIGATING_TO_ARUCO, Event::NAVIGATION_REACHED, State::VERIFY_ARRIVAL},
    {State::VERIFY_ARRIVAL, Event::ARRIVAL_CONFIRMED, State::SUCCEEDED},
  };
  for (const auto & transition : transitions) {
    if (transition.from == state && transition.event == event) {
      return transition.to;
    }
  }
  return state;
}
}  // namespace urc_state_machine
