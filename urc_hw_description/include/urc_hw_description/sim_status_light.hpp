#ifndef URC_HW_DESCRIPTION__SIM_STATUS_LIGHT_HPP_
#define URC_HW_DESCRIPTION__SIM_STATUS_LIGHT_HPP_

#include <functional>
#include <string>

#include <ignition/msgs/boolean.pb.h>
#include <ignition/transport/Node.hh>
#include <rclcpp/rclcpp.hpp>
#include <urc_msgs/msg/status_light_command.hpp>

#include "urc_hw_description/status_light_color.hpp"

namespace urc_hw_description
{

// Shows /command/status_light on the simulated rover by recoloring the status
// light visual through Gazebo's visual_config service.
class SimStatusLight : public rclcpp::Node
{
public:
  explicit SimStatusLight(const rclcpp::NodeOptions & options);

private:
  void onCommand(const urc_msgs::msg::StatusLightCommand & command);
  void onRefreshTimer();
  void requestVisualColor();

  std::string visual_config_service_;
  std::string link_name_;
  std::string visual_name_;

  // Only touched by the subscription and the timer, which share the node's
  // default mutually exclusive callback group and never run concurrently.
  urc_msgs::msg::StatusLightCommand current_command_;
  BlinkPhase blink_phase_{BlinkPhase::LIT};

  rclcpp::Subscription<urc_msgs::msg::StatusLightCommand>::SharedPtr command_subscriber_;
  rclcpp::TimerBase::SharedPtr refresh_timer_;

  std::function<void(const ignition::msgs::Boolean &, const bool)> visual_config_response_callback_;
  ignition::transport::Node gz_node_;
};

}  // namespace urc_hw_description

#endif  // URC_HW_DESCRIPTION__SIM_STATUS_LIGHT_HPP_
