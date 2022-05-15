#ifndef JOYSTICK_DRIVER_H
#define JOYSTICK_DRIVER_H

#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/joy.hpp>
//#include <diagnostic_updater/diagnostic_updater.hpp>
//#include <diagnostic_updater/publisher.hpp>
#include <memory>
#include <urc_msgs/msg/velocity_pair.hpp>
#include <rclcpp_components/register_node_macro.hpp>
 

namespace joystick_driver
{
class JoystickDriver : public rclcpp::Node
{
public:
    explicit JoystickDriver(const rclcpp::NodeOptions &options);

private: 
};
}


#endif