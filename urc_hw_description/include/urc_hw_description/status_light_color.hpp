#ifndef URC_HW_DESCRIPTION__STATUS_LIGHT_COLOR_HPP_
#define URC_HW_DESCRIPTION__STATUS_LIGHT_COLOR_HPP_

#include <urc_msgs/msg/status_light_command.hpp>

namespace urc_hw_description
{

// Channel intensities in [0, 1].
struct StatusLightRgb
{
  double red;
  double green;
  double blue;
};

enum class BlinkPhase
{
  LIT,
  DARK
};

// A BLINK command shows its color only during the LIT phase.
// OFF, or an unknown color or state, shows the unlit color.
StatusLightRgb statusLightColor(
  const urc_msgs::msg::StatusLightCommand & command,
  BlinkPhase blink_phase);

}  // namespace urc_hw_description

#endif  // URC_HW_DESCRIPTION__STATUS_LIGHT_COLOR_HPP_
