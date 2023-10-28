#include "hardware_interface/types/hardware_interface_type_values.hpp"

namespace urc_hardware::types
{
// kinematics & dynamics
constexpr char HW_POSITION[] = "position";
constexpr char HW_VELOCITY[] = "velocity";
constexpr char HW_ACCELERATION[] = "acceleration";
constexpr char HW_EFFORT[] = "effort";

// signals
constexpr char HW_CMD[] = "command";

// measurement values
constexpr char HW_SCALAR_MEASUREMENT[] = "scalar_measurement";

// control flags & status
constexpr char HW_FLAG[] = "flag";

}  // namespace urc_hardware::types
