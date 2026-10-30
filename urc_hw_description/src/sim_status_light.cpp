#include "urc_hw_description/sim_status_light.hpp"

#include <chrono>
#include <stdexcept>

#include <ignition/msgs/visual.pb.h>
#include <rclcpp_components/register_node_macro.hpp>

namespace urc_hw_description
{
namespace
{

using StatusLightCommand = urc_msgs::msg::StatusLightCommand;

constexpr int kWarningThrottleMs = 5000;

std::string requireNonEmptyString(const rclcpp::Node & node, const std::string & name)
{
  const auto value = node.get_parameter(name).as_string();
  if (value.empty()) {
    throw std::invalid_argument("Parameter '" + name + "' must not be empty");
  }
  return value;
}

void setOpaqueColor(ignition::msgs::Color & target, const StatusLightRgb & color)
{
  target.set_r(static_cast<float>(color.red));
  target.set_g(static_cast<float>(color.green));
  target.set_b(static_cast<float>(color.blue));
  target.set_a(1.0F);
}

ignition::msgs::Visual makeVisualColorRequest(
  const std::string & link_name,
  const std::string & visual_name,
  const StatusLightRgb & color)
{
  ignition::msgs::Visual request;
  request.set_name(visual_name);
  request.set_parent_name(link_name);
  auto * material = request.mutable_material();
  setOpaqueColor(*material->mutable_ambient(), color);
  setOpaqueColor(*material->mutable_diffuse(), color);
  setOpaqueColor(*material->mutable_emissive(), color);
  return request;
}

}  // namespace

SimStatusLight::SimStatusLight(const rclcpp::NodeOptions & options)
: Node("sim_status_light", options)
{
  declare_parameter("command_topic", "/command/status_light");
  declare_parameter("world_name", "leo_marsyard");
  declare_parameter("link_name", "status_light_link");
  declare_parameter("visual_name", "status_light_link_visual");
  declare_parameter("refresh_period_ms", 500);

  const auto command_topic = requireNonEmptyString(*this, "command_topic");
  visual_config_service_ =
    "/world/" + requireNonEmptyString(*this, "world_name") + "/visual_config";
  link_name_ = requireNonEmptyString(*this, "link_name");
  visual_name_ = requireNonEmptyString(*this, "visual_name");

  const auto refresh_period_ms = get_parameter("refresh_period_ms").as_int();
  if (refresh_period_ms <= 0) {
    throw std::invalid_argument("Parameter 'refresh_period_ms' must be positive");
  }

  // Runs on a gz-transport thread, so it only logs.
  visual_config_response_callback_ =
    [this](const ignition::msgs::Boolean & /*reply*/, const bool success) {
      if (!success) {
        RCLCPP_WARN_THROTTLE(
          get_logger(), *get_clock(), kWarningThrottleMs,
          "Gazebo did not accept the status light color on %s",
          visual_config_service_.c_str());
      }
    };

  command_subscriber_ = create_subscription<StatusLightCommand>(
    command_topic, rclcpp::SystemDefaultsQoS(),
    [this](const StatusLightCommand::SharedPtr msg) {onCommand(*msg);});

  refresh_timer_ = create_wall_timer(
    std::chrono::milliseconds(refresh_period_ms),
    [this]() {onRefreshTimer();});
}

void SimStatusLight::onCommand(const StatusLightCommand & command)
{
  current_command_ = command;
  blink_phase_ = BlinkPhase::LIT;
  requestVisualColor();
}

// Also re-sends steady colors, so the light recovers if Gazebo starts after this node.
void SimStatusLight::onRefreshTimer()
{
  blink_phase_ = blink_phase_ == BlinkPhase::LIT ? BlinkPhase::DARK : BlinkPhase::LIT;
  requestVisualColor();
}

void SimStatusLight::requestVisualColor()
{
  const auto request = makeVisualColorRequest(
    link_name_, visual_name_, statusLightColor(current_command_, blink_phase_));
  if (!gz_node_.Request(visual_config_service_, request, visual_config_response_callback_)) {
    RCLCPP_WARN_THROTTLE(
      get_logger(), *get_clock(), kWarningThrottleMs,
      "Could not send the status light color to %s", visual_config_service_.c_str());
  }
}

}  // namespace urc_hw_description

RCLCPP_COMPONENTS_REGISTER_NODE(urc_hw_description::SimStatusLight)
