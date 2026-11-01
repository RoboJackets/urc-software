#include "urc_hw_description/status_light_color.hpp"

namespace urc_hw_description
{
namespace
{

using StatusLightCommand = urc_msgs::msg::StatusLightCommand;

// Matches the status_light_off material in the rover URDF.
constexpr StatusLightRgb kUnlitColor{0.1, 0.1, 0.1};
constexpr StatusLightRgb kRed{1.0, 0.0, 0.0};
constexpr StatusLightRgb kGreen{0.0, 1.0, 0.0};
constexpr StatusLightRgb kBlue{0.0, 0.0, 1.0};

StatusLightRgb commandedColor(uint8_t color)
{
  switch (color) {
    case StatusLightCommand::RED:
      return kRed;
    case StatusLightCommand::GREEN:
      return kGreen;
    case StatusLightCommand::BLUE:
      return kBlue;
    default:
      return kUnlitColor;
  }
}

}  // namespace

StatusLightRgb statusLightColor(
  const StatusLightCommand & command,
  BlinkPhase blink_phase)
{
  switch (command.state) {
    case StatusLightCommand::ON:
      return commandedColor(command.color);
    case StatusLightCommand::BLINK:
      return blink_phase == BlinkPhase::LIT ? commandedColor(command.color) : kUnlitColor;
    default:
      return kUnlitColor;
  }
}

}  // namespace urc_hw_description
