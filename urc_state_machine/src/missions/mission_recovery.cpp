#include "urc_state_machine/nav_coordinator.hpp"

namespace nav_coordinator
{
void NavCoordinator::retryStateOrFail(State resume, uint16_t code, const std::string & reason)
{
  if (mission_.retries >= parameters_.max_retries) {
    stopMission(State::FAILED, code, reason + "; retry budget exhausted");
    return;
  }
  ++mission_.retries;
  mission_.resume = resume;
  mission_.state = State::RECOVERING;
  mission_.error_code = code;
  mission_.reason = reason;
  mission_.phase_started = urc_state_machine::MissionClock::now();
  navigation_->cancel();
  publishState();
}

// A retry re-executes its phase only after navigation stops and required inputs recover.
void NavCoordinator::updateRecovery()
{
  if (phaseElapsed() > parameters_.recovery_timeout) {
    stopMission(State::FAILED, mission_.error_code, mission_.reason + "; recovery timed out");
    return;
  }
  if (navigation_->busy() || !navigation_->ready() || !roverPose()) {
    return;
  }
  if ((mission_.resume == State::FOLLOWING || mission_.resume == State::COMING ||
    mission_.resume == State::WAIT_STAY) && !astronautFresh())
  {
    return;
  }
  if (mission_.resume == State::CALCULATING_APPROACH && !markerFresh()) {
    return;
  }
  changeState(mission_.resume);
}

void NavCoordinator::updateStopping()
{
  if (!navigation_->busy()) {
    if (mission_.after_stop == State::STAYING) {
      changeState(State::STAYING);
    } else {
      finishMission();
    }
  } else if (phaseElapsed() > parameters_.recovery_timeout) {
    RCLCPP_ERROR_THROTTLE(
      get_logger(), *get_clock(), 5000,
      "Waiting for navigation to stop; mission ownership remains locked");
  }
}

// Keep ownership during cancellation, even if the server stops responding.
void NavCoordinator::stopMission(State next, uint16_t code, const std::string & reason)
{
  mission_.state = State::STOPPING;
  mission_.after_stop = next;
  mission_.error_code = code;
  mission_.reason = reason;
  mission_.phase_started = urc_state_machine::MissionClock::now();
  navigation_->cancel();
  publishState();
}
}  // namespace nav_coordinator
