#include "urc_state_machine/nav_coordinator.hpp"

#include <chrono>

namespace nav_coordinator
{
void NavCoordinator::initializeStatusLight()
{
  status_light_pub_ = create_publisher<urc_msgs::msg::StatusLightCommand>(
    parameters_.status_light_topic, rclcpp::QoS(1).reliable().transient_local());
  // The existing hardware and simulation consumers are volatile subscribers.
  status_light_timer_ = create_wall_timer(
    std::chrono::duration<double>(parameters_.status_light_refresh_period),
    [this]() {publishStatusLight();});
}

void NavCoordinator::publishStatusLight()
{
  using Command = urc_msgs::msg::StatusLightCommand;
  Command command;
  if (!autonomous_) {
    command.color = Command::BLUE;
    command.state = Command::ON;
  } else if (arrival_indicated_) {
    command.color = Command::GREEN;
    command.state = Command::BLINK;
  } else {
    command.color = Command::RED;
    command.state = Command::ON;
  }
  status_light_pub_->publish(command);
}
}  // namespace nav_coordinator
