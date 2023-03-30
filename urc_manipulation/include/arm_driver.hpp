#ifndef ARM_DRIVER_H
#define ARM_DRIVER_H

#include <rclcpp/rclcpp.hpp>

namespace arm_driver
{
class ArmDriver : public rclcpp::Node
{
public:
  explicit ArmDriver(const rclcpp::NodeOptions & options);

private:

};
}


#endif
