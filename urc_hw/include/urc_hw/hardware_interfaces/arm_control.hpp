#ifndef URC_HW__URC_ARM_CONTROL_HPP
#define URC_HW__URC_ARM_CONTROL_HPP

#include "memory"
#include "vector"
#include "string"

#include "hardware_interface/handle.hpp"
#include "hardware_interface/system_interface.hpp"
#include "rclcpp/rclcpp.hpp"
#include "async_sockets/basesocket.hpp"
#include "async_sockets/udpsocket.hpp"
#include "pb_encode.h"
#include "urc_nanopb/urc.pb.h"
#include <cstdint>
#include <memory>
#include <pb.h>
#include <iostream>
#include <chrono>
#include <ctime>

namespace urc_hardware::hardware_interfaces
{

class ArmControl : public hardware_interface::SystemInterface
{
public:
  ArmControl();
  ~ArmControl();

  hardware_interface::CallbackReturn on_init(const hardware_interface::HardwareInfo & hardware_info)
  override;
  hardware_interface::CallbackReturn on_configure(const rclcpp_lifecycle::State &) override;
  std::vector<hardware_interface::CommandInterface> export_command_interfaces() override;
  std::vector<hardware_interface::StateInterface> export_state_interfaces() override;
  hardware_interface::CallbackReturn on_activate(const rclcpp_lifecycle::State & previous_state)
  override;
  hardware_interface::CallbackReturn on_deactivate(const rclcpp_lifecycle::State & previous_state)
  override;
  hardware_interface::return_type read(
    const rclcpp::Time & time,
    const rclcpp::Duration & period) override;
  hardware_interface::return_type write(
    const rclcpp::Time & time,
    const rclcpp::Duration & period) override;

private:
  const std::string hardware_interface_name;
  double publish_encoder_ticks_frequency_;
  const int ENCODER_CPR = 6144;
  const int QPPR = 15562;

  // states
  std::vector<double> joint_vel_commands;
  std::vector<double> joint_vel_states;
  std::vector<double> joint_pos_states;

  // hardware resources
  std::shared_ptr<UDPSocket<128>> udp_;
  std::string udp_address;
  std::string udp_port;

  // nanopb
  uint8_t buffer[DriveEncodersMessage_size];
  size_t message_length;
};

}

#endif
