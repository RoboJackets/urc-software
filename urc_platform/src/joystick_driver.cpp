#include "joystick_driver.hpp"
#include "urc_msgs/msg/velocity_pair.h"

namespace joystick_driver
{

JoystickDriver::JoystickDriver(const rclcpp::NodeOptions &options)
: rclcpp::Node("joystick_driver", options)
{
}

}

RCLCPP_COMPONENTS_REGISTER_NODE(joystick_driver::JoystickDriver)