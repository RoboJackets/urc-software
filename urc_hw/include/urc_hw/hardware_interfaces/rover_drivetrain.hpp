#ifndef URC_HW__URC_ROVER_DRIVETRAIN_HPP
#define URC_HW__URC_ROVER_DRIVETRAIN_HPP

#include "memory"
#include "vector"
#include "hardware_interface/system_interface.hpp"

namespace urc_hardware::hardware_interfaces
{

class RoverDrivetrain : public hardware_interface::SystemInterface
{
public:
  hardware_interface::CallbackReturn on_init(const hardware_interface::HardwareInfo& hardware_info) override;
  std::vector<hardware_interface::StateInterface> export_state_interfaces() override;
  std::vector<hardware_interface::CommandInterface> export_command_interfaces() override;
  hardware_interface::CallbackReturn on_activate(const rclcpp_lifecycle::State& previous_state) override;
  hardware_interface::CallbackReturn on_deactivate(const rclcpp_lifecycle::State& previous_state) override;
  hardware_interface::return_type read(const rclcpp::Time& time, const rclcpp::Duration& period) override;
  hardware_interface::return_type write(const rclcpp::Time& time, const rclcpp::Duration& period) override;
  
  double publish_encoder_ticks_frequency_;
  const int ENCODER_CPR = 6144;
  const float WHEEL_RADIUS = 0.170;
  const float VEL_TO_COUNTS_FACTOR = ENCODER_CPR / (2 * M_PI * WHEEL_RADIUS);
  const int QPPR = 15562;
  const float MAX_SPEED = QPPR / VEL_TO_COUNTS_FACTOR;
  const float MIN_SPEED = -1 * MAX_SPEED;

private:
  // commands
  std::vector<double> wheel_velocity_cmd_;
  std::vector<double> wheel_effort_cmd_;
  // states
  std::vector<double> wheel_velocity_states_;
  std::vector<double> wheel_current_states_;
  std::vector<double> wheel_temperature_states;
};

}  // namespace urc_hardware::hardware_interfaces

#endif  // RAMBLER_HARDWARE__RAMBLER_HARDWARE_HPP_
