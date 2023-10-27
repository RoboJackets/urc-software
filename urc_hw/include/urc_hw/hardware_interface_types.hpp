#include "hardware_interface/types/hardware_interface_type_values.hpp"

namespace urc_hardware::types
{
// kinematics & dynamics
constexpr char HW_IF_POSITION[] = "position";
constexpr char HW_IF_VELOCITY[] = "velocity";
constexpr char HW_IF_ACCELERATION[] = "acceleration";
constexpr char HW_IF_EFFORT[] = "effort";

// measurement values
constexpr char HW_IF_CURRENT[] = "current";
constexpr char HW_IF_VOLTAGE[] = "voltage";
constexpr char HW_IF_TEMERATURE[] = "temperature";

// control flags & status
constexpr char HW_IF_GENERAL_STATUS[] = "general_status";
constexpr char HW_IF_CONTROL_FLAG[] = "control_flag";

}  // namespace urc_hardware::types
