#include "urc_controllers/status_light_controller.hpp"
#include <algorithm>
#include <array>
#include <controller_interface/controller_interface_base.hpp>
#include <hardware_interface/loaned_command_interface.hpp>
#include <iterator>
#include <memory>
#include <rclcpp/logging.hpp>
#include <rclcpp/qos.hpp>
#include <sensor_msgs/msg/detail/imu__struct.hpp>
#include <std_msgs/msg/detail/int8__struct.hpp>
#include <vector>

#include "pluginlib/class_list_macros.hpp"
PLUGINLIB_EXPORT_CLASS(
  urc_controllers::StatusLightController,
  controller_interface::ControllerInterface);

namespace urc_controllers
{

StatusLightController::StatusLightController()
: status_light_command_subscriber_(nullptr), color_command_(0), state_command_(0) {}

controller_interface::CallbackReturn StatusLightController::on_init()
{
  return controller_interface::CallbackReturn::SUCCESS;
}

controller_interface::CallbackReturn StatusLightController::on_configure(
  const rclcpp_lifecycle::State &)
{
  status_light_name = get_node()->get_parameter("status_light_name").as_string();
  if (status_light_name.empty()) {
    RCLCPP_ERROR(
      get_node()->get_logger(),
      "Need to have 'status_light_name' parameter in the configuration file. Fail to find one.");
    return controller_interface::CallbackReturn::FAILURE;
  }
  return controller_interface::CallbackReturn::SUCCESS;
}

controller_interface::InterfaceConfiguration StatusLightController::command_interface_configuration()
const
{
  controller_interface::InterfaceConfiguration command_interfaces_configuration;
  command_interfaces_configuration.type =
    controller_interface::interface_configuration_type::INDIVIDUAL;

  command_interfaces_configuration.names.push_back(status_light_name + "/" + "color");
  command_interfaces_configuration.names.push_back(status_light_name + "/" + "state");
  return command_interfaces_configuration;
}

controller_interface::InterfaceConfiguration StatusLightController::state_interface_configuration()
const
{
  return controller_interface::InterfaceConfiguration();
}

controller_interface::CallbackReturn StatusLightController::on_activate(
  const rclcpp_lifecycle::State &)
{
  for (auto & interface : command_interfaces_) {
    const auto interface_ptr =
      std::find(
      STATUS_LIGHT_INTERFACES.begin(),
      STATUS_LIGHT_INTERFACES.end(), interface.get_interface_name());
    if (interface_ptr == STATUS_LIGHT_INTERFACES.end()) {
      continue;
    }

    command_interface_map.emplace(
      interface.get_interface_name(),
      std::make_shared<std::reference_wrapper<hardware_interface::LoanedCommandInterface>>(
        interface));
  }

  if (command_interface_map.size() != 2) {
    RCLCPP_ERROR(get_node()->get_logger(), "Not all interfaces are initialized!");
    return controller_interface::CallbackReturn::ERROR;
  }

  status_light_command_subscriber_ =
    get_node()->create_subscription<urc_msgs::msg::StatusLightCommand>(
    "/command/status_light", rclcpp::SystemDefaultsQoS(),
    [this](std::shared_ptr<urc_msgs::msg::StatusLightCommand> msg)
    {
      color_command_.writeFromNonRT(static_cast<uint8_t>(msg->color));
      state_command_.writeFromNonRT(static_cast<uint8_t>(msg->state));
    });

  RCLCPP_INFO(get_node()->get_logger(), "StatusLightController activated!");
  return controller_interface::CallbackReturn::SUCCESS;
}

controller_interface::CallbackReturn StatusLightController::on_deactivate(
  const rclcpp_lifecycle::State &)
{
  status_light_command_subscriber_.reset();
  return controller_interface::CallbackReturn::SUCCESS;
}

controller_interface::CallbackReturn StatusLightController::on_cleanup(
  const rclcpp_lifecycle::State &)
{
  status_light_command_subscriber_.reset();
  return controller_interface::CallbackReturn::SUCCESS;
}

controller_interface::CallbackReturn StatusLightController::on_error(
  const rclcpp_lifecycle::State &)
{
  status_light_command_subscriber_.reset();
  return controller_interface::CallbackReturn::SUCCESS;
}

controller_interface::CallbackReturn StatusLightController::on_shutdown(
  const rclcpp_lifecycle::State &)
{
  status_light_command_subscriber_.reset();
  return controller_interface::CallbackReturn::SUCCESS;
}

controller_interface::return_type StatusLightController::update(
  const rclcpp::Time &,
  const rclcpp::Duration &)
{
  command_interface_map["color"]->get().set_value(*color_command_.readFromRT());
  command_interface_map["state"]->get().set_value(*state_command_.readFromRT());
  return controller_interface::return_type::OK;
}

} // namespace urc_controllers
