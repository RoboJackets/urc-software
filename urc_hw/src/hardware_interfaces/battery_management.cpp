#include "urc_hw/hardware_interfaces/battery_management.hpp"
#include "async_sockets/udpsocket.hpp"
#include "hardware_interface/hardware_info.hpp"
#include "hardware_interface/sensor_interface.hpp"
#include "pluginlib/class_list_macros.hpp"
#include <algorithm>
#include <async_sockets/udpserver.hpp>
#include <cstdlib>
#include <rclcpp/logger.hpp>
#include <rclcpp/logging.hpp>
#include <string>
#include <unistd.h>
#include <urc_nanopb/urc.pb.h>
#include <vector>

PLUGINLIB_EXPORT_CLASS(urc_hardware::hardware_interfaces::BatteryManagement, hardware_interface::SensorInterface);

namespace urc_hardware::hardware_interfaces
{

BatteryManagement::BatteryManagement() : hardware_interface_name("BatteryManagement"){};
BatteryManagement::~BatteryManagement() = default;

hardware_interface::CallbackReturn BatteryManagement::on_init(const hardware_interface::HardwareInfo& info)
{
  if (hardware_interface::SensorInterface::on_init(info) != hardware_interface::CallbackReturn::SUCCESS)
  {
    return hardware_interface::CallbackReturn::ERROR;
  }

  if (info_.hardware_parameters.find("udp_self_address") == info_.hardware_parameters.end())
  {
    RCLCPP_ERROR(rclcpp::get_logger(hardware_interface_name),
                 "Error during initialization: 'udp_self_address' configuration not "
                 "found. Expect to enter the udp server address.");
    return hardware_interface::CallbackReturn::ERROR;
  }
  if (info_.hardware_parameters.find("udp_self_port") == info_.hardware_parameters.end())
  {
    RCLCPP_ERROR(rclcpp::get_logger(hardware_interface_name),
                 "Error during initialization: 'udp_self_port' configuration not "
                 "found. Expect to enter the port number.");
    return hardware_interface::CallbackReturn::ERROR;
  }

  udp_self_address = info_.hardware_parameters["udp_self_address"];
  udp_self_port = info_.hardware_parameters["udp_self_port"];

  if (info.sensors.size() == 0)
  {
    RCLCPP_ERROR(rclcpp::get_logger(hardware_interface_name),
                 "Should have at least one sensor to be the BatteryManagement.");
    return CallbackReturn::ERROR;
  }

  std::vector<hardware_interface::ComponentInfo>::iterator ptr;
  bool find = false;
  for (auto i = info_.sensors.begin(); i < info_.sensors.end(); ++i)
  {
    if (i->name == "battery_management")
    {
      find = true;
      ptr = i;
      break;
    }
  }

  if (!find)
  {
    RCLCPP_ERROR(rclcpp::get_logger(hardware_interface_name), "Not able to find sensor named 'battery_management'.");
    return CallbackReturn::ERROR;
  }

  cell_voltages.resize(8);
  core_status.resize(4);
  return hardware_interface::CallbackReturn::SUCCESS;
}

hardware_interface::CallbackReturn BatteryManagement::on_configure(const rclcpp_lifecycle::State&)
{
  return hardware_interface::CallbackReturn::SUCCESS;
}

std::vector<hardware_interface::StateInterface> BatteryManagement::export_state_interfaces()
{
  std::vector<hardware_interface::StateInterface> state_interfaces;

  std::vector<hardware_interface::ComponentInfo>::iterator ptr;
  for (auto i = info_.sensors.begin(); i < info_.sensors.end(); ++i)
  {
    if (i->name == "battery_management")
    {
      ptr = i;
      break;
    }
  }

  for (auto state_inteface : ptr->state_interfaces)
  {
    if (std::find(interface_names.begin(), interface_names.end(), state_inteface.name) != interface_names.end())
    {
      if (state_inteface.name.substr(0, 4) == "cell" && state_inteface.name.substr(5, 13) == "_voltage")
      {
        state_interfaces.emplace_back("battery_management", state_inteface.name, this->cell_voltages[4]);
      }
      // std::strtol(state_inteface.name.at(4));
      else if (interface_names.find(state_inteface.name) != interface_names.end())
      {
      }
    }
  }

  return state_interfaces;
}

hardware_interface::CallbackReturn BatteryManagement::on_activate(const rclcpp_lifecycle::State&)
{
  udp_ = std::make_shared<UDPServer<128>>();
  udp_->Bind(udp_self_address.c_str(), std::stoi(udp_self_port));
  udp_->onRawMessageReceived = [this](const char* buf, ssize_t size, std::string, std::uint16_t) {
    /* Allocate space for the decoded message. */
    BatteryManagement message = BattereyMessage_init_zero;

    /* Create a stream that reads from the buffer. */
    pb_istream_t stream = pb_istream_from_buffer((unsigned char*)buf, size);

    /* Now we are ready to decode the message. */
    bool status = pb_decode(&stream, BatteryManagementMessage_fields, &message);

    /* Check for errors... */
    if (!status)
    {
      printf("Decoding failed: %s\n", PB_GET_ERROR(&stream));
      return 1;
    }

    return 0;
  };
  RCLCPP_INFO(rclcpp::get_logger(hardware_interface_name), "BatteryManagement activated!");
  return hardware_interface::CallbackReturn::SUCCESS;
}

hardware_interface::CallbackReturn BatteryManagement::on_deactivate(const rclcpp_lifecycle::State&)
{
  udp_->Close();
  RCLCPP_INFO(rclcpp::get_logger(hardware_interface_name), "BatteryManagement deactivated!");
  return hardware_interface::CallbackReturn::SUCCESS;
}

hardware_interface::return_type BatteryManagement::read(const rclcpp::Time&, const rclcpp::Duration&)
{
  return hardware_interface::return_type::OK;
}

}  // namespace urc_hardware::hardware_interfaces
