#include "urc_controllers/imu_broadcaster.hpp"
#include <algorithm>
#include <array>
#include <controller_interface/controller_interface_base.hpp>
#include <geometry_msgs/msg/detail/quaternion_stamped__struct.hpp>
#include <iterator>
#include <memory>
#include <rclcpp/logging.hpp>
#include <rclcpp/qos.hpp>
#include <sensor_msgs/msg/detail/imu__struct.hpp>
#include <vector>

#include "pluginlib/class_list_macros.hpp"
PLUGINLIB_EXPORT_CLASS(urc_controllers::IMUBroadcaster, controller_interface::ControllerInterface);

namespace urc_controllers
{

IMUBroadcaster::IMUBroadcaster()
: imu_state_publisher_(nullptr) {}

controller_interface::CallbackReturn IMUBroadcaster::on_init()
{
  return controller_interface::CallbackReturn::SUCCESS;
}

controller_interface::CallbackReturn IMUBroadcaster::on_configure(const rclcpp_lifecycle::State &)
{
  imu_name = get_node()->get_parameter("imu_name").as_string();
  if (imu_name.empty()) {
    RCLCPP_ERROR(
      get_node()->get_logger(),
      "Need to have 'imu_name' parameter in the configuration file. Fail to find one.");
    return controller_interface::CallbackReturn::FAILURE;
  }

  return controller_interface::CallbackReturn::SUCCESS;
}

controller_interface::InterfaceConfiguration IMUBroadcaster::state_interface_configuration() const
{
  controller_interface::InterfaceConfiguration state_interfaces_configuration;
  state_interfaces_configuration.type =
    controller_interface::interface_configuration_type::INDIVIDUAL;

  state_interfaces_configuration.names.push_back(imu_name + "/" + "orientation.x");
  state_interfaces_configuration.names.push_back(imu_name + "/" + "orientation.y");
  state_interfaces_configuration.names.push_back(imu_name + "/" + "orientation.z");
  state_interfaces_configuration.names.push_back(imu_name + "/" + "orientation.w");
  state_interfaces_configuration.names.push_back(imu_name + "/" + "linear_acceleration.x");
  state_interfaces_configuration.names.push_back(imu_name + "/" + "linear_acceleration.y");
  state_interfaces_configuration.names.push_back(imu_name + "/" + "linear_acceleration.z");
  state_interfaces_configuration.names.push_back(imu_name + "/" + "angular_velocity.x");
  state_interfaces_configuration.names.push_back(imu_name + "/" + "angular_velocity.y");
  state_interfaces_configuration.names.push_back(imu_name + "/" + "angular_velocity.z");

  return state_interfaces_configuration;
}

controller_interface::InterfaceConfiguration IMUBroadcaster::command_interface_configuration() const
{
  auto config = controller_interface::InterfaceConfiguration();
  config.type = controller_interface::interface_configuration_type::NONE;
  return config;
}

controller_interface::CallbackReturn IMUBroadcaster::on_activate(const rclcpp_lifecycle::State &)
{
  for (auto & interface : state_interfaces_) {
    const auto interface_ptr = std::find(
      IMU_INTERFACES.begin(),
      IMU_INTERFACES.end(), interface.get_interface_name());
    if (interface_ptr == IMU_INTERFACES.end()) {
      continue;
    }

    state_interfaces_map_.emplace(
      interface.get_interface_name(),
      std::make_shared<std::reference_wrapper<hardware_interface::LoanedStateInterface>>(interface));
  }

  if (state_interfaces_map_.size() != 10) {
    RCLCPP_ERROR(get_node()->get_logger(), "Not all interface is initialized!");
    return controller_interface::CallbackReturn::ERROR;
  }

  imu_state_publisher_ = get_node()->create_publisher<sensor_msgs::msg::Imu>(
    "state_imu",
    rclcpp::SystemDefaultsQoS());

  RCLCPP_INFO(get_node()->get_logger(), "IMU Broadcaster activated!");
  return controller_interface::CallbackReturn::SUCCESS;
}

controller_interface::CallbackReturn IMUBroadcaster::on_deactivate(const rclcpp_lifecycle::State &)
{
  imu_state_publisher_.reset();
  return controller_interface::CallbackReturn::SUCCESS;
}

controller_interface::CallbackReturn IMUBroadcaster::on_cleanup(const rclcpp_lifecycle::State &)
{
  imu_state_publisher_.reset();
  return controller_interface::CallbackReturn::SUCCESS;
}

controller_interface::CallbackReturn IMUBroadcaster::on_error(const rclcpp_lifecycle::State &)
{
  imu_state_publisher_.reset();
  return controller_interface::CallbackReturn::SUCCESS;
}

controller_interface::CallbackReturn IMUBroadcaster::on_shutdown(const rclcpp_lifecycle::State &)
{
  imu_state_publisher_.reset();
  return controller_interface::CallbackReturn::SUCCESS;
}

controller_interface::return_type IMUBroadcaster::update(
  const rclcpp::Time & time,
  const rclcpp::Duration &)
{
  sensor_msgs::msg::Imu imu_message;
  imu_message.header.stamp = time;

  imu_message.orientation.x = state_interfaces_map_["orientation.x"]->get().get_value();
  imu_message.orientation.y = state_interfaces_map_["orientation.y"]->get().get_value();
  imu_message.orientation.z = state_interfaces_map_["orientation.z"]->get().get_value();
  imu_message.orientation.w = state_interfaces_map_["orientation.w"]->get().get_value();
  imu_message.linear_acceleration.x =
    state_interfaces_map_["linear_acceleration.x"]->get().get_value();
  imu_message.linear_acceleration.y =
    state_interfaces_map_["linear_acceleration.y"]->get().get_value();
  imu_message.linear_acceleration.z =
    state_interfaces_map_["linear_acceleration.z"]->get().get_value();
  imu_message.angular_velocity.x = state_interfaces_map_["angular_velocity.x"]->get().get_value();
  imu_message.angular_velocity.y = state_interfaces_map_["angular_velocity.y"]->get().get_value();
  imu_message.angular_velocity.z = state_interfaces_map_["angular_velocity.z"]->get().get_value();

  imu_state_publisher_->publish(imu_message);
  return controller_interface::return_type::OK;
}

}  // namespace urc_controllers
