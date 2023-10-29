#include "urc_hw/hardware_interfaces/test_hardware.hpp"
#include "rclcpp/rclcpp.hpp"
#include "algorithm"
#include "hardware_interface/types/hardware_interface_return_values.hpp"
#include "urc_hw/hardware/serial.hpp"
#include <cstdint>
#include <memory>
#include <rclcpp/logger.hpp>
#include <rclcpp/logging.hpp>
#include <string>
#include <urc_hw/hardware/eth.hpp>
#include "urc_hw/protocal/eth_packet.hpp"

#include "pluginlib/class_list_macros.hpp"
PLUGINLIB_EXPORT_CLASS(urc_hardware::hardware_interfaces::TestHardware, hardware_interface::SystemInterface);

namespace urc_hardware::hardware_interfaces
{

TestHardware::TestHardware() = default;
TestHardware::~TestHardware() = default;

hardware_interface::CallbackReturn TestHardware::on_init(const hardware_interface::HardwareInfo& info)
{
  RCLCPP_INFO(rclcpp::get_logger("TestHardware"), "initializing hardware for robot %s..", info_.name.c_str());
  if (hardware_interface::SystemInterface::on_init(info) != hardware_interface::CallbackReturn::SUCCESS)
  {
    return hardware_interface::CallbackReturn::ERROR;
  }

  // init hardware resources
  if (info_.hardware_parameters.find("serial_port") == info_.hardware_parameters.end())
  {
    RCLCPP_ERROR(rclcpp::get_logger("TestHardware"),
                 "Error during initialization: 'ethernet_port' configuration not "
                 "found. Expect to enter the port number.");
    return hardware_interface::CallbackReturn::ERROR;
  }
  serial_ = std::make_shared<urc_hardware::hardware::Serial>();
  serial_port_name = info_.hardware_parameters["serial_port"];

  if (info_.hardware_parameters.find("ethernet_port") == info_.hardware_parameters.end())
  {
    RCLCPP_ERROR(rclcpp::get_logger("TestHardware"),
                 "Error during initialization: 'ethernet_port' configuration not "
                 "found. Expect to enter the port number.");
    return hardware_interface::CallbackReturn::ERROR;
  }
  ethernet_port_name = info_.hardware_parameters["ethernet_port"];

  if (info_.hardware_parameters.find("out_header") == info_.hardware_parameters.end())
  {
    RCLCPP_ERROR(rclcpp::get_logger("TestHardware"),
                 "Error during initialization: 'out_header' configuration not "
                 "found. Expect a string representing the headder add to each command line output.");
    return hardware_interface::CallbackReturn::ERROR;
  }
  out_header_name = info_.hardware_parameters["out_header"];

  // check joints
  test_joint_position_commands_.resize(info.joints.size(), std::numeric_limits<double>::quiet_NaN());
  test_joint_position_states_.resize(info.joints.size(), std::numeric_limits<double>::quiet_NaN());
  test_joint_velocity_states_.resize(info.joints.size(), std::numeric_limits<double>::quiet_NaN());
  imu_quaternion_readings_.resize(4, std::numeric_limits<double>::quiet_NaN());

  for (const hardware_interface::ComponentInfo& component : info.joints)
  {
    if (component.command_interfaces.size() != 1)
    {
      RCLCPP_ERROR(rclcpp::get_logger("TestHardware"),
                   "Error during initlization: expect 1 command interface (position).");
      return hardware_interface::CallbackReturn::ERROR;
    }

    if (component.command_interfaces[0].name != urc_hardware::types::HW_POSITION)
    {
      RCLCPP_ERROR(rclcpp::get_logger("TestHardware"),
                   "Error during initlization: joint has command interface %s. Expect %s.",
                   component.command_interfaces[0].name.c_str(), urc_hardware::types::HW_POSITION);
      return hardware_interface::CallbackReturn::ERROR;
    }

    if (component.state_interfaces.size() != 2)
    {
      RCLCPP_ERROR(rclcpp::get_logger("TestHardware"),
                   "Error during initlization: experct 2 state interface (position, velocity)");
      return hardware_interface::CallbackReturn::ERROR;
    }

    if (component.state_interfaces[0].name != urc_hardware::types::HW_POSITION)
    {
      RCLCPP_ERROR(rclcpp::get_logger("TestHardware"),
                   "Error during initlization: joint has state interface %s. Expect %s.",
                   component.command_interfaces[0].name.c_str(), urc_hardware::types::HW_POSITION);
      return hardware_interface::CallbackReturn::ERROR;
    }

    if (component.state_interfaces[1].name != urc_hardware::types::HW_VELOCITY)
    {
      RCLCPP_ERROR(rclcpp::get_logger("TestHardware"),
                   "Error during initlization: joint has state interface %s. Expect %s.",
                   component.command_interfaces[0].name.c_str(), urc_hardware::types::HW_VELOCITY);
      return hardware_interface::CallbackReturn::ERROR;
    }
  }

  // check other sensors & predefined flags
  if (info_.sensors[0].state_interfaces.size() != 4)
  {
    RCLCPP_ERROR(rclcpp::get_logger("TestHardware"),
                 "Error during initlization: expect 4 state interfaces for sensor 1 (imu quaternion readings)");
    return hardware_interface::CallbackReturn::ERROR;
  }

  // check gpios for indication
  if (info_.gpios.size() != 1)
  {
    RCLCPP_ERROR(rclcpp::get_logger("TestHardware"),
                 "Error during initlization: should have only 1 gpio (status indication)");
    return hardware_interface::CallbackReturn::ERROR;
  }

  if (info_.gpios[0].command_interfaces.size() != 1)
  {
    RCLCPP_ERROR(rclcpp::get_logger("TestHardware"),
                 "Error during initlization: status indication should have only 1 command interface");
    return hardware_interface::CallbackReturn::ERROR;
  }

  if (info_.gpios[0].command_interfaces[0].name != urc_hardware::types::HW_CMD)
  {
    RCLCPP_ERROR(rclcpp::get_logger("TestHardware"), "Error during initlization: status indication should be HW_CMD.");
    return hardware_interface::CallbackReturn::ERROR;
  }

  RCLCPP_INFO(rclcpp::get_logger("TestHardware"), "Testhardware initialization success.");
  return hardware_interface::CallbackReturn::SUCCESS;
}

hardware_interface::CallbackReturn TestHardware::on_configure(const rclcpp_lifecycle::State&)
{
  std::fill(test_joint_position_states_.begin(), test_joint_position_states_.end(), 0);
  std::fill(test_joint_velocity_states_.begin(), test_joint_velocity_states_.end(), 0);
  std::fill(test_joint_position_commands_.begin(), test_joint_position_commands_.end(), 0);

  RCLCPP_INFO_ONCE(rclcpp::get_logger("TestHardware"), "Succesfully zeroed all command on configuration.");
  return hardware_interface::CallbackReturn::SUCCESS;
}

std::vector<hardware_interface::StateInterface> TestHardware::export_state_interfaces()
{
  RCLCPP_INFO(rclcpp::get_logger("TestHardware"), "Exporting state interfaces...");
  std::vector<hardware_interface::StateInterface> state_interfaces;
  for (unsigned long i = 0; i < info_.joints.size(); ++i)
  {
    hardware_interface::ComponentInfo component = info_.joints[i];
    state_interfaces.emplace_back(component.name, urc_hardware::types::HW_POSITION,
                                  &this->test_joint_position_states_[i]);
    state_interfaces.emplace_back(component.name, urc_hardware::types::HW_VELOCITY,
                                  &this->test_joint_velocity_states_[i]);
  }
  state_interfaces.emplace_back(info_.sensors[0].name, "quaternion.w", &this->imu_quaternion_readings_[0]);
  state_interfaces.emplace_back(info_.sensors[0].name, "quaternion.x", &this->imu_quaternion_readings_[1]);
  state_interfaces.emplace_back(info_.sensors[0].name, "quaternion.y", &this->imu_quaternion_readings_[2]);
  state_interfaces.emplace_back(info_.sensors[0].name, "quaternion.z", &this->imu_quaternion_readings_[3]);

  return state_interfaces;
}

std::vector<hardware_interface::CommandInterface> TestHardware::export_command_interfaces()
{
  RCLCPP_INFO(rclcpp::get_logger("TestHardware"), "Exporting command interfaces...");
  std::vector<hardware_interface::CommandInterface> command_interfaces;

  for (unsigned long i = 0; i < info_.joints.size(); ++i)
  {
    hardware_interface::ComponentInfo component = info_.joints[i];
    command_interfaces.emplace_back(component.name, urc_hardware::types::HW_POSITION,
                                    &this->test_joint_position_commands_[i]);
  }
  command_interfaces.emplace_back(info_.gpios[0].name, urc_hardware::types::HW_CMD, &this->status_light_cmd);
  return command_interfaces;
}

hardware_interface::CallbackReturn TestHardware::on_activate(const rclcpp_lifecycle::State&)
{
  // serial_ = std::make_shared<hardware::Serial>();
  // if (serial_->open(serial_port_name) != hardware::return_type::SUCCESS)
  // {
  //   RCLCPP_INFO(rclcpp::get_logger("TestHardware"), "TestHardware failed to open serial port");
  //   return hardware_interface::CallbackReturn::ERROR;
  // }
  // eth_ = std::make_shared<hardware::EthernetSocket>("127.0.0.1", std::stoi(ethernet_port_name));
  status_light_cmd = 0.0;
  RCLCPP_INFO(rclcpp::get_logger("TestHardware"), "TestHardware started");
  return hardware_interface::CallbackReturn::SUCCESS;
}

hardware_interface::CallbackReturn TestHardware::on_deactivate(const rclcpp_lifecycle::State&)
{
  RCLCPP_INFO(rclcpp::get_logger("TestHardware"), "TestHardware stopping ...");

  // eth_.reset();
  RCLCPP_INFO(rclcpp::get_logger("TestHardware"), "TestHardware stopped");
  return hardware_interface::CallbackReturn::SUCCESS;
}

hardware_interface::return_type TestHardware::read(const rclcpp::Time&, const rclcpp::Duration&)
{
  return hardware_interface::return_type::OK;
}

hardware_interface::return_type TestHardware::write(const rclcpp::Time&, const rclcpp::Duration&)
{
  EthernetStdPacket packet;
  packet.header_message = out_header_name;
  packet.status_light_command = static_cast<int>(status_light_cmd);
  std::cout << packet.status_light_command << std::endl;
  std::string message = packet.encode();
  this->eth_->sendMessage(, sizeof(message));
  return hardware_interface::return_type::OK;
}

}  // namespace urc_hardware::hardware_interfaces
