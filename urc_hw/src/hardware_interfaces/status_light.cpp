#include "urc_hw/hardware_interfaces/status_light.hpp"
#include "hardware_interface/handle.hpp"
#include "hardware_interface/hardware_info.hpp"
#include "pluginlib/class_list_macros.hpp"
#include <rclcpp/logger.hpp>
#include <rclcpp/logging.hpp>

PLUGINLIB_EXPORT_CLASS(urc_hardware::hardware_interfaces::StatusLight, hardware_interface::SystemInterface);

namespace urc_hardware::hardware_interfaces
{

StatusLight::StatusLight() = default;
StatusLight::~StatusLight() = default;

hardware_interface::CallbackReturn StatusLight::on_init(const hardware_interface::HardwareInfo& info)
{
  RCLCPP_INFO(rclcpp::get_logger(hardware_interface_name), "Initializing Status Light for robot %s..",
              info_.name.c_str());

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

  if (info.gpios.size() == 0)
  {
    RCLCPP_ERROR(rclcpp::get_logger(hardware_interface_name), "Should have at least one gpio to be the Status Light.");
    return CallbackReturn::ERROR;
  }

  bool find_light = false;
  for (hardware_interface::ComponentInfo component : info_.sensors)
  {
    if (component.name == "status_light")
    {
      find_light = true;
      break;
    }
  }

  if (!find_light)
  {
    RCLCPP_ERROR(rclcpp::get_logger(hardware_interface_name), "Not able to find sensor named 'status_light'.");
    return CallbackReturn::ERROR;
  }

  RCLCPP_INFO(rclcpp::get_logger(hardware_interface_name), "Status Light initialization success.");
  return hardware_interface::CallbackReturn::SUCCESS;
}

hardware_interface::CallbackReturn StatusLight::on_configure(const rclcpp_lifecycle::State&)
{
  signals.resize(2);
  std::fill(signals.begin(), signals.end(), 0.0);

  RCLCPP_INFO_ONCE(rclcpp::get_logger(hardware_interface_name), "Succesfully zeroed all commands on configure.");
  return hardware_interface::CallbackReturn::SUCCESS;
}

std::vector<hardware_interface::CommandInterface> StatusLight::export_command_interfaces()
{
  RCLCPP_INFO(rclcpp::get_logger(hardware_interface_name), "Exporting command interfaces...");
  std::vector<hardware_interface::CommandInterface> command_interfaces;
  command_interfaces.emplace_back("status_light", "command.color", &this->signals[0]);
  command_interfaces.emplace_back("status_light", "command.display", &this->signals[1]);
  return command_interfaces;
}

std::vector<hardware_interface::StateInterface> StatusLight::export_state_interfaces()
{
  RCLCPP_INFO(rclcpp::get_logger(hardware_interface_name), "Exporting state interfaces...");
  std::vector<hardware_interface::StateInterface> state_interfaces;
  return state_interfaces;
}

hardware_interface::CallbackReturn StatusLight::on_activate(const rclcpp_lifecycle::State&)
{
  udp_ = std::make_shared<UDPSocket<1024>>(true);
  udp_->Connect(udp_address, std::stoi(udp_port));
  RCLCPP_INFO(rclcpp::get_logger(hardware_interface_name), "Status Light started!");
  return hardware_interface::CallbackReturn::SUCCESS;
}

hardware_interface::CallbackReturn StatusLight::on_deactivate(const rclcpp_lifecycle::State&)
{
  RCLCPP_INFO(rclcpp::get_logger(hardware_interface_name), "Status Light stopping ...");
  udp_->Close();
  RCLCPP_INFO(rclcpp::get_logger(hardware_interface_name), "Status Light stopped");
  return hardware_interface::CallbackReturn::SUCCESS;
}

hardware_interface::return_type StatusLight::read(const rclcpp::Time&, const rclcpp::Duration&)
{
  return hardware_interface::return_type::OK;
}

}  // namespace urc_hardware::hardware_interfaces
