#include "joystick_driver.hpp"

namespace joystick_driver
{

JoystickDriver::JoystickDriver(const rclcpp::NodeOptions &options)
: rclcpp::Node("joystick_driver", options)
{
}

}

RCLCPP_COMPONENTS_REGISTER_NODE(joystick_driver::JoystickDriver)