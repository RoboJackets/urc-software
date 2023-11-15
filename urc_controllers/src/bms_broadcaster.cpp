#include "urc_controllers/bms_broadcaster.hpp"
#include <algorithm>
#include <array>
#include <controller_interface/controller_interface_base.hpp>
#include <cstddef>
#include <geometry_msgs/msg/detail/quaternion_stamped__struct.hpp>
#include <iterator>
#include <memory>
#include <rclcpp/logging.hpp>
#include <rclcpp/qos.hpp>
#include <sensor_msgs/msg/detail/imu__struct.hpp>
#include <string>
#include <urc_msgs/msg/detail/battery_info__struct.hpp>
#include <vector>

#include "pluginlib/class_list_macros.hpp"
PLUGINLIB_EXPORT_CLASS(urc_controllers::BMSBroadcaster, controller_interface::ControllerInterface);

namespace urc_controllers
{

BMSBroadcaster::BMSBroadcaster()
: battery_info_publisher_(nullptr) {}

controller_interface::CallbackReturn BMSBroadcaster::on_init()
{
  return controller_interface::CallbackReturn::SUCCESS;
}

controller_interface::CallbackReturn BMSBroadcaster::on_configure(const rclcpp_lifecycle::State &)
{
  bms_name = get_node()->get_parameter("bms_name").as_string();
  if (bms_name.empty()) {
    RCLCPP_ERROR(
      get_node()->get_logger(),
      "Need to have 'bms_name' parameter in the configuration file. Fail to find one.");
    return controller_interface::CallbackReturn::FAILURE;
  }
  cell_num = get_node()->get_parameter("cell_num").as_int();
  if (cell_num < 0) {
    RCLCPP_ERROR(
      get_node()->get_logger(),
      "Need to have 'cell_num' parameter in the configuration file. Fail to find one.");
    return controller_interface::CallbackReturn::FAILURE;
  }

  return controller_interface::CallbackReturn::SUCCESS;
}

controller_interface::InterfaceConfiguration BMSBroadcaster::state_interface_configuration() const
{
  controller_interface::InterfaceConfiguration state_interfaces_configuration;
  state_interfaces_configuration.type =
    controller_interface::interface_configuration_type::INDIVIDUAL;

  for (std::string s : INTERFACE_NAMES) {
    state_interfaces_configuration.names.push_back(bms_name + "/" + s);
  }

  for (int i = 1; i <= cell_num; ++i) {
    state_interfaces_configuration.names.push_back(
      bms_name + "/" + "cell" + std::to_string(
        i) + "_voltage");
  }

  return state_interfaces_configuration;
}

controller_interface::InterfaceConfiguration BMSBroadcaster::command_interface_configuration() const
{
  auto config = controller_interface::InterfaceConfiguration();
  config.type = controller_interface::interface_configuration_type::NONE;
  return config;
}

controller_interface::CallbackReturn BMSBroadcaster::on_activate(const rclcpp_lifecycle::State &)
{
  for (auto & interface : state_interfaces_) {
    state_interfaces_map_.emplace(
      interface.get_interface_name(),
      std::make_shared<std::reference_wrapper<hardware_interface::LoanedStateInterface>>(interface));
  }

  battery_info_publisher_ =
    get_node()->create_publisher<urc_msgs::msg::BatteryInfo>(
    "state_battery",
    rclcpp::SystemDefaultsQoS());

  RCLCPP_INFO(get_node()->get_logger(), "BMS Broadcaster activated!");
  return controller_interface::CallbackReturn::SUCCESS;
}

controller_interface::CallbackReturn BMSBroadcaster::on_deactivate(const rclcpp_lifecycle::State &)
{
  battery_info_publisher_.reset();
  return controller_interface::CallbackReturn::SUCCESS;
}

controller_interface::CallbackReturn BMSBroadcaster::on_cleanup(const rclcpp_lifecycle::State &)
{
  battery_info_publisher_.reset();
  return controller_interface::CallbackReturn::SUCCESS;
}

controller_interface::CallbackReturn BMSBroadcaster::on_error(const rclcpp_lifecycle::State &)
{
  battery_info_publisher_.reset();
  return controller_interface::CallbackReturn::SUCCESS;
}

controller_interface::CallbackReturn BMSBroadcaster::on_shutdown(const rclcpp_lifecycle::State &)
{
  battery_info_publisher_.reset();
  return controller_interface::CallbackReturn::SUCCESS;
}

controller_interface::return_type BMSBroadcaster::update(
  const rclcpp::Time &,
  const rclcpp::Duration &)
{
  urc_msgs::msg::BatteryInfo battery_message;
  battery_message.cell_voltage = state_interfaces_map_["main_voltage"]->get().get_value();
  battery_message.cell_charge_percentage =
    state_interfaces_map_["charge_percentage"]->get().get_value();
  battery_message.cell_discharge_current =
    state_interfaces_map_["discharge_current"]->get().get_value();
  battery_message.cell_temperature = state_interfaces_map_["temperature"]->get().get_value();
  for (int i = 1; i <= cell_num; ++i) {
    battery_message.cell_voltages.emplace_back(
      state_interfaces_map_["cell" + std::to_string(i) + "_voltage"]->get().get_value());
  }

  battery_info_publisher_->publish(battery_message);
  return controller_interface::return_type::OK;
}

}  // namespace urc_controllers
