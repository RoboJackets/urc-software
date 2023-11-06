#include "urc_hw/hardware_interfaces/rover_drivetrain.hpp"
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
#include <string>
#include <urc_nanopb/urc.pb.h>

PLUGINLIB_EXPORT_CLASS(urc_hardware::hardware_interfaces::StatusLight, hardware_interface::SystemInterface);

namespace urc_hardware::hardware_interfaces
{

RoverDrivetrain::RoverDrivetrain() : hardware_interface_name("Rover Drivetrain"), signals(2, 0){};
RoverDrivetrain::~RoverDrivetrain() = default;

hardware_interface::CallbackReturn RoverDrivetrain::on_init(const hardware_interface::HardwareInfo& info)
{
  if (hardware_interface::SystemInterface::on_init(info) != hardware_interface::CallbackReturn::SUCCESS)
  {
    return hardware_interface::CallbackReturn::ERROR;
  }

  if (info_.hardware_parameters.find("udp_address") == info_.hardware_parameters.end())
  {
    RCLCPP_ERROR(rclcpp::get_logger(hardware_interface_name),
                 "Error during initialization: 'udp_address' configuration not "
                 "found. Expect to enter the udp server address.");
    return hardware_interface::CallbackReturn::ERROR;
  }
  if (info_.hardware_parameters.find("udp_port") == info_.hardware_parameters.end())
  {
    RCLCPP_ERROR(rclcpp::get_logger(hardware_interface_name),
                 "Error during initialization: 'udp_port' configuration not "
                 "found. Expect to enter the port number.");
    return hardware_interface::CallbackReturn::ERROR;
  }

  udp_address = info_.hardware_parameters["udp_address"];
  udp_port = info_.hardware_parameters["udp_port"];

  bool find_drivetrain = false;
  for (hardware_interface::ComponentInfo component : info_.joints)
  {
    if (component.name == "rover_drivetrain")
    {
      find_drivetrain = true;
      break;
    }
  }

  if (!find_drivetrain)
  {
    RCLCPP_ERROR(rclcpp::get_logger(hardware_interface_name), "Not able to find sensor named 'rover_drivetrain'.");
    return CallbackReturn::ERROR;
  }
  return hardware_interface::CallbackReturn::SUCCESS;
}

hardware_interface::CallbackReturn RoverDrivetrain::on_configure(const rclcpp_lifecycle::State&)
{
  std::fill(signals.begin(), signals.end(), 0.0);
  return hardware_interface::CallbackReturn::SUCCESS;
}

std::vector<hardware_interface::CommandInterface> RoverDrivetrain::export_command_interfaces()
{
  std::vector<hardware_interface::CommandInterface> command_interfaces;
  command_interfaces.emplace_back("rover_drivetrain", "leftSpeed", &this->signals[0]);
  command_interfaces.emplace_back("rover_drivetrain", "rightSpeed", &this->signals[1]);
  return command_interfaces;
}

std::vector<hardware_interface::StateInterface> RoverDrivetrain::export_state_interfaces()
{
  std::vector<hardware_interface::StateInterface> state_interfaces;
  return state_interfaces;
}

hardware_interface::CallbackReturn RoverDrivetrain::on_activate(const rclcpp_lifecycle::State&)
{
  udp_ = std::make_shared<UDPSocket<128>>(true);
  udp_->Connect(udp_address, std::stoi(udp_port));
  RCLCPP_INFO(rclcpp::get_logger(hardware_interface_name), "Rover Drivetrain activated!");
  return hardware_interface::CallbackReturn::SUCCESS;
}

hardware_interface::CallbackReturn RoverDrivetrain::on_deactivate(const rclcpp_lifecycle::State&)
{
  udp_->Close();
  RCLCPP_INFO(rclcpp::get_logger(hardware_interface_name), "Rover Drivetrain deactivated!");
  return hardware_interface::CallbackReturn::SUCCESS;
}

hardware_interface::return_type RoverDrivetrain::read(const rclcpp::Time&, const rclcpp::Duration&)
{
  return hardware_interface::return_type::OK;
}

hardware_interface::return_type RoverDrivetrain::write(const rclcpp::Time&, const rclcpp::Duration&)
{
  DriveEncodersMessage message = DriveEncodersMessage_init_zero;
  pb_ostream_t stream = pb_ostream_from_buffer(buffer, sizeof(buffer));

  message.leftSpeed = signals[0];
  message.rightSpeed = signals[1];
  message.timestamp = std::chrono::system_clock::now().count();

  bool status = pb_encode(&stream, DriveEncodersMessage_fields, &message);
  message_length = stream.bytes_written;

  if (!status)
  {
    return hardware_interface::return_type::ERROR;
  }
  udp_->Send((char*)buffer, sizeof(buffer));
  return hardware_interface::return_type::OK;
}

}  // namespace urc_hardware::hardware_interfaces
