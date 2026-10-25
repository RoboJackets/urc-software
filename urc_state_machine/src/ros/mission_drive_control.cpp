#include "urc_state_machine/nav_coordinator.hpp"


namespace nav_coordinator
{
void NavCoordinator::initializeDriveControl()
{
  drive_mode_pub_ = create_publisher<std_msgs::msg::String>(
    parameters_.drive_mode_command_topic, rclcpp::QoS(1).reliable());
  drive_mode_sub_ = create_subscription<std_msgs::msg::String>(
    parameters_.drive_mode_topic, rclcpp::QoS(1).reliable().transient_local(),
    [this](std_msgs::msg::String::ConstSharedPtr mode) {
      if (mode->data != "autonomous" && mode->data != "teleop" && mode->data != "disabled") {
        return;
      }
      autonomous_ = mode->data == "autonomous";
      teleop_available_ = mode->data == "teleop";
      if (!autonomous_) {
        arrival_indicated_ = false;
        if (mission_.kind != Kind::NONE && mission_.state != State::RESUMING &&
        mission_.state != State::PAUSED && mission_.state != State::STOPPING)
        {
          abortMission("Drive authority left autonomous mode");
        }
      }
      if (status_light_pub_) {
        publishStatusLight();
      }
    });
  setAutonomousMode(false);
  abort_service_ = create_service<std_srvs::srv::Trigger>(
    parameters_.abort_service,
    [this](std_srvs::srv::Trigger::Request::SharedPtr,
    std_srvs::srv::Trigger::Response::SharedPtr response) {
      response->success = mission_.kind != Kind::NONE;
      response->message = response->success ? "Abort requested; waiting for navigation to stop" :
      "No active mission";
      if (response->success) {
        abortMission("Operator abort");
      }
    });
  resume_service_ = create_service<std_srvs::srv::Trigger>(
    parameters_.resume_service,
    [this](std_srvs::srv::Trigger::Request::SharedPtr,
    std_srvs::srv::Trigger::Response::SharedPtr response) {
      response->success = resumeMission(mission_.resume);
      response->message = response->success ? "Resume requested; waiting for navigation readiness" :
      "Resume rejected: mission must be paused with valid inputs";
    });
}

void NavCoordinator::abortMission(const std::string & reason)
{
  if (mission_.kind == Kind::NONE || mission_.state == State::PAUSED ||
    (mission_.state == State::STOPPING && mission_.after_stop == State::CANCELED))
  {
    return;
  }
  stopMission(State::PAUSED, mission_.error_code, reason);
}

bool NavCoordinator::phaseInputsReady(State state) const
{
  if (!navigation_->ready() || !roverPose()) {
    return false;
  }
  if ((state == State::FOLLOWING || state == State::WAIT_STAY || state == State::COMING) &&
    !astronautFresh())
  {
    return false;
  }
  return true;
}

bool NavCoordinator::resumeMission(State state)
{
  if (mission_.kind == Kind::NONE || mission_.state != State::PAUSED ||
    navigation_->busy() || !teleop_available_ || !phaseInputsReady(state))
  {
    return false;
  }
  mission_.retries = 0;
  beginResume(state);
  return true;
}

void NavCoordinator::beginResume(State state)
{
  mission_.resume = state;
  changeState(State::RESUMING);
  setAutonomousMode(true);
}

void NavCoordinator::setAutonomousMode(bool autonomous)
{
  std_msgs::msg::String mode;
  mode.data = autonomous ? "autonomous" : "teleop";
  drive_mode_pub_->publish(mode);
}

void NavCoordinator::updateResume()
{
  if (mission_.state == State::PAUSED ||
    (mission_.kind == Kind::NONE && mission_.state == State::CANCELED))
  {
    if (autonomous_) {
      setAutonomousMode(false);
    }
    return;
  }
  if (mission_.state != State::RESUMING) {
    return;
  }
  if (phaseElapsed() > parameters_.recovery_timeout) {
    abortMission("Navigation readiness timed out");
    return;
  }
  if (!autonomous_) {
    setAutonomousMode(true);
    return;
  }
  if (navigation_->busy()) {
    return;
  }
  if (!phaseInputsReady(mission_.resume)) {
    abortMission("Required inputs unavailable on resume");
    return;
  }
  last_command_stamp_ = now();
  changeState(mission_.resume);
}
}  // namespace nav_coordinator
