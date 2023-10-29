#ifndef URC_HW__URC_ROVER_DRIVETRAIN_HPP
#define URC_HW__URC_ROVER_DRIVETRAIN_HPP

#include "memory"
#include "urc_hw/hardware/serial.hpp"
#include "vector"
#include "string"
#include "iostream"
#include "rclcpp/rclcpp.hpp"
#include "hardware_interface/system_interface.hpp"
#include "urc_hw/hardware/eth.hpp"
#include "urc_hw/hardware_interface_types.hpp"
#include <memory>

namespace urc_hardware::hardware_interfaces
{

class TestHardware : public hardware_interface::SystemInterface
{
public:
  TestHardware();
  ~TestHardware();

  hardware_interface::CallbackReturn on_init(const hardware_interface::HardwareInfo& hardware_info) override;
  std::vector<hardware_interface::StateInterface> export_state_interfaces() override;
  std::vector<hardware_interface::CommandInterface> export_command_interfaces() override;
  hardware_interface::CallbackReturn on_configure(const rclcpp_lifecycle::State& previous_state) override;
  hardware_interface::CallbackReturn on_activate(const rclcpp_lifecycle::State& previous_state) override;
  hardware_interface::CallbackReturn on_deactivate(const rclcpp_lifecycle::State& previous_state) override;
  hardware_interface::return_type read(const rclcpp::Time& time, const rclcpp::Duration& period) override;
  hardware_interface::return_type write(const rclcpp::Time& time, const rclcpp::Duration& period) override;

private:
  // commands
  std::vector<double> test_joint_position_commands_;
  double status_light_cmd;
  // states
  std::vector<double> test_joint_position_states_;
  std::vector<double> test_joint_velocity_states_;
  std::vector<double> imu_quaternion_readings_;
  // hardware resources
  // std::shared_ptr<std::ostream> out;
  std::string out_header_name;
  std::shared_ptr<urc_hardware::hardware::EthernetSocket> eth_;
  std::shared_ptr<urc_hardware::hardware::Serial> serial_;
};

}  // namespace urc_hardware::hardware_interfaces

#endif  // RAMBLER_HARDWARE__RAMBLER_HARDWARE_HPP_
