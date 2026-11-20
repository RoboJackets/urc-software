#include "urc_state_machine/nav_coordinator.hpp"

namespace nav_coordinator
{
void NavCoordinator::retryStateOrPause(State resume, uint16_t code, const std::string & reason)
{
  if (resume == State::SEARCHING_ARUCO) {
    resume = State::NAVIGATING;
  }
  if (mission_.retries >= parameters_.max_retries) {
    stopMission(State::PAUSED, code, reason + "; retry budget exhausted");
    return;
  }
  ++mission_.retries;
  mission_.resume = resume;
  mission_.state = State::RECOVERING;
  arrival_indicated_ = false;
  mission_.error_code = code;
  mission_.reason = reason;
  mission_.phase_started = urc_state_machine::MissionClock::now();
  spiral_search_->cancel();
  navigation_->cancel();
  publishState();
}

// A retry re-executes its phase only after navigation stops and required inputs recover.
void NavCoordinator::updateRecovery()
{
  if (phaseElapsed() > parameters_.recovery_timeout) {
    stopMission(State::PAUSED, mission_.error_code, mission_.reason + "; recovery timed out");
    return;
  }
  if (navigation_->busy() || !phaseInputsReady(mission_.resume)) {
    return;
  }
  changeState(mission_.resume);
}

void NavCoordinator::updateStopping()
{
  if (!navigation_->busy()) {
    if (mission_.after_stop == State::PAUSED) {
      mission_.state = State::PAUSED;
      mission_.phase_started = urc_state_machine::MissionClock::now();
      tracking_.reset();
      last_command_stamp_ = now();
      setAutonomousMode(false);
      publishState();
    } else if (mission_.after_stop == State::STAYING ||
      mission_.after_stop == State::SEARCHING_ARUCO)
    {
      changeState(mission_.after_stop);
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
  if (mission_.state != State::RECOVERING && mission_.state != State::RESUMING &&
    mission_.state != State::STOPPING && mission_.state != State::PAUSED)
  {
    mission_.resume = mission_.state == State::SEARCHING_ARUCO ?
      State::NAVIGATING : mission_.state;
  }
  mission_.state = State::STOPPING;
  arrival_indicated_ = false;
  mission_.after_stop = next;
  mission_.error_code = code;
  mission_.reason = reason;
  mission_.phase_started = urc_state_machine::MissionClock::now();
  spiral_search_->cancel();
  navigation_->cancel();
  publishState();
}
}  // namespace nav_coordinator
