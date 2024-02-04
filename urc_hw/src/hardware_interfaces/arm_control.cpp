#include "urc_hw/hardware_interfaces/arm_control.hpp"
#include "hardware_interface/types/hardware_interface_return_values.hpp"
#include "pluginlib/class_list_macros.hpp"
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <iostream>
#include <iterator>
#include <ostream>
#include <pb.h>
#include <pb_encode.h>
#include <pb_decode.h>
#include <rclcpp/clock.hpp>
#include <rclcpp/time.hpp>
#include <string>
#include <urc_nanopb/urc.pb.h>

PLUGINLIB_EXPORT_CLASS(
  urc_hardware::hardware_interfaces::ArmControl,
  hardware_interface::SystemInterface);

namespace urc_hardware::hardware_interfaces
{

ArmControl::ArmControl()
: hardware_interface_name("Arm Control")
  , joint_vel_commands(5, 0)
  , joint_vel_states(5, 0)
  , joint_pos_states(5, 0) {}
ArmControl::~ArmControl() = default;

hardware_interface::CallbackReturn ArmControl::on_init(
  const hardware_interface::HardwareInfo & info)
{
  if (hardware_interface::SystemInterface::on_init(info) !=
    hardware_interface::CallbackReturn::SUCCESS)
  {
    return hardware_interface::CallbackReturn::ERROR;
  }

  if (info_.hardware_parameters.find("udp_address") == info_.hardware_parameters.end()) {
    RCLCPP_ERROR(
      rclcpp::get_logger(hardware_interface_name),
      "Error during initialization: 'udp_address' configuration not "
      "found. Expect to enter the udp server address.");
    return hardware_interface::CallbackReturn::ERROR;
  }
  if (info_.hardware_parameters.find("udp_port") == info_.hardware_parameters.end()) {
    RCLCPP_ERROR(
      rclcpp::get_logger(hardware_interface_name),
      "Error during initialization: 'udp_port' configuration not "
      "found. Expect to enter the port number.");
    return hardware_interface::CallbackReturn::ERROR;
  }

  udp_address = info_.hardware_parameters["udp_address"];
  udp_port = info_.hardware_parameters["udp_port"];

  return hardware_interface::CallbackReturn::SUCCESS;
}

hardware_interface::CallbackReturn ArmControl::on_configure(const rclcpp_lifecycle::State &)
{
  std::fill(joint_vel_commands.begin(), joint_vel_commands.end(), 0.0);
  std::fill(joint_vel_states.begin(), joint_vel_states.end(), 0.0);
  std::fill(joint_pos_states.begin(), joint_pos_states.end(), 0.0);
  return hardware_interface::CallbackReturn::SUCCESS;
}

std::vector<hardware_interface::CommandInterface> ArmControl::export_command_interfaces()
{
  std::vector<hardware_interface::CommandInterface> command_interfaces;
  command_interfaces.emplace_back("shoulderjoint", "velocity", &this->joint_vel_commands[0]);
  command_interfaces.emplace_back("bicepjoint", "velocity", &this->joint_vel_commands[1]);
  command_interfaces.emplace_back("elbowjoint", "velocity", &this->joint_vel_commands[2]);
  command_interfaces.emplace_back("wristjoint", "velocity", &this->joint_vel_commands[3]);
  command_interfaces.emplace_back("clawjoint", "velocity", &this->joint_vel_commands[4]);
  return command_interfaces;
}

std::vector<hardware_interface::StateInterface> ArmControl::export_state_interfaces()
{
  std::vector<hardware_interface::StateInterface> state_interfaces;
  state_interfaces.emplace_back("shoulderjoint", "velocity", &this->joint_vel_states[0]);
  state_interfaces.emplace_back("bicepjoint", "velocity", &this->joint_vel_states[1]);
  state_interfaces.emplace_back("elbowjoint", "velocity", &this->joint_vel_states[2]);
  state_interfaces.emplace_back("wristjoint", "velocity", &this->joint_vel_states[3]);
  state_interfaces.emplace_back("clawjoint", "velocity", &this->joint_vel_states[4]);

  state_interfaces.emplace_back("shoulderjoint", "position", &this->joint_pos_states[0]);
  state_interfaces.emplace_back("bicepjoint", "position", &this->joint_pos_states[1]);
  state_interfaces.emplace_back("elbowjoint", "position", &this->joint_pos_states[2]);
  state_interfaces.emplace_back("wristjoint", "position", &this->joint_pos_states[3]);
  state_interfaces.emplace_back("clawjoint", "position", &this->joint_pos_states[4]);
  return state_interfaces;
}

hardware_interface::CallbackReturn ArmControl::on_activate(const rclcpp_lifecycle::State &)
{
  udp_ = std::make_shared<UDPSocket<128>>(true);
  udp_->Connect(udp_address, std::stoi(udp_port));
  RCLCPP_INFO(rclcpp::get_logger(hardware_interface_name), "Arm Control activated!");
  return hardware_interface::CallbackReturn::SUCCESS;
}

hardware_interface::CallbackReturn ArmControl::on_deactivate(const rclcpp_lifecycle::State &)
{
  udp_->Close();
  RCLCPP_INFO(rclcpp::get_logger(hardware_interface_name), "Arm Control deactivated!");
  return hardware_interface::CallbackReturn::SUCCESS;
}

hardware_interface::return_type ArmControl::read(
  const rclcpp::Time &,
  const rclcpp::Duration &)
{
  return hardware_interface::return_type::OK;
}

hardware_interface::return_type ArmControl::write(
  const rclcpp::Time & time,
  const rclcpp::Duration & duration)
{
  if (duration.seconds() < 0.001) {
    return hardware_interface::return_type::OK;
  }
  ArmEncodersMessage message = ArmEncodersMessage_init_zero;
  pb_ostream_t stream = pb_ostream_from_buffer(buffer, sizeof(buffer));

  message.shoulderSpeed = joint_vel_commands[0];
  message.has_shoulderSpeed = true;
  message.bicepSpeed = joint_vel_commands[1];
  message.has_bicepSpeed = true;
  message.elbowSpeed = joint_vel_commands[2];
  message.has_elbowSpeed = true;
  message.wristSpeed = joint_vel_commands[3];
  message.has_wristSpeed = true;
  message.clawSpeed = joint_vel_commands[4];
  message.has_clawSpeed = true;
  message.timestamp = time.nanoseconds();

  bool status = pb_encode(&stream, ArmEncodersMessage_fields, &message);
  message_length = stream.bytes_written;

  if (!status) {
    return hardware_interface::return_type::ERROR;
  }
  udp_->Send((char *)buffer, sizeof(buffer));

  return hardware_interface::return_type::OK;
}

}
