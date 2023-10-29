#include "urc_hw/hardware_interface_types.hpp"
#include "pluginlib/class_list_macros.hpp"
#include "rclcpp/rclcpp.hpp"
#include "urc_controllers/test_hardware_controller.hpp"
#include <algorithm>
#include <controller_interface/controller_interface.hpp>
#include <controller_interface/controller_interface_base.hpp>
#include <functional>
#include <geometry_msgs/msg/detail/twist__struct.hpp>
#include <hardware_interface/loaned_command_interface.hpp>
#include <memory>
#include <ostream>
#include <rclcpp/logger.hpp>
#include <rclcpp/logging.hpp>
#include <rclcpp/qos.hpp>
#include <rclcpp_lifecycle/state.hpp>
#include <vector>

#include "pluginlib/class_list_macros.hpp"
PLUGINLIB_EXPORT_CLASS(urc_controllers::TestHardwareController, controller_interface::ControllerInterface);

namespace urc_controllers

{

TestHardwareController::TestHardwareController()
  : controller_interface::ControllerInterface()
  , indication_light_command_subscription_(nullptr)
  , indication_light_command_(nullptr)
{
}

controller_interface::CallbackReturn TestHardwareController::on_init()
{
  return controller_interface::CallbackReturn::SUCCESS;
}

controller_interface::CallbackReturn TestHardwareController::on_configure(const rclcpp_lifecycle::State&)
{
  base_joint_name = get_node()->get_parameter("base_joint_name").as_string();
  primary_joint_name = get_node()->get_parameter("primary_joint_name").as_string();
  end_effector_joint_name = get_node()->get_parameter("end_effector_joint_name").as_string();
  gripper_joint_name = get_node()->get_parameter("gripper_joint_name").as_string();
  indication_light_name = get_node()->get_parameter("indication_light_name").as_string();
  imu_name = get_node()->get_parameter("imu_name").as_string();

  if (base_joint_name.empty() || primary_joint_name.empty() || end_effector_joint_name.empty() ||
      gripper_joint_name.empty() || indication_light_name.empty() || imu_name.empty())
  {
    RCLCPP_ERROR(get_node()->get_logger(), "Parameter empty.");
    return CallbackReturn::ERROR;
  }

  RCLCPP_INFO(get_node()->get_logger(), "Start configurations...");

  indication_light_command_subscription_ = get_node()->create_subscription<geometry_msgs::msg::Twist>(
      "/cmd_indication", rclcpp::SystemDefaultsQoS(),
      [this](const std::shared_ptr<geometry_msgs::msg::Twist> callback) {
        this->indication_light_command_.writeFromNonRT(std::make_shared<double>(callback->linear.x));
      });

  RCLCPP_INFO(get_node()->get_logger(), "Configuration success!");
  return CallbackReturn::SUCCESS;
}

controller_interface::CallbackReturn TestHardwareController::on_activate(const rclcpp_lifecycle::State&)
{
  for (auto& interface : command_interfaces_)
  {
    if (command_interface_map_.find(interface.get_interface_name()) == command_interface_map_.end())
    {
      command_interface_map_.emplace(interface.get_interface_name(),
                                     std::vector<std::reference_wrapper<hardware_interface::LoanedCommandInterface>>());
    }
    command_interface_map_[interface.get_interface_name()].push_back(interface);
  }
  return controller_interface::CallbackReturn::SUCCESS;
}

controller_interface::CallbackReturn TestHardwareController::on_deactivate(const rclcpp_lifecycle::State&)
{
  return controller_interface::CallbackReturn::SUCCESS;
}

controller_interface::CallbackReturn TestHardwareController::on_cleanup(const rclcpp_lifecycle::State&)
{
  if (!reset())
  {
    return controller_interface::CallbackReturn::ERROR;
  }

  return controller_interface::CallbackReturn::SUCCESS;
}

controller_interface::CallbackReturn TestHardwareController::on_error(const rclcpp_lifecycle::State&)
{
  if (!reset())
  {
    return controller_interface::CallbackReturn::ERROR;
  }
  return controller_interface::CallbackReturn::SUCCESS;
}

controller_interface::CallbackReturn TestHardwareController::on_shutdown(const rclcpp_lifecycle::State&)
{
  return controller_interface::CallbackReturn::SUCCESS;
}

controller_interface::InterfaceConfiguration TestHardwareController::command_interface_configuration() const
{
  controller_interface::InterfaceConfiguration command_interfaces_configuration;
  command_interfaces_configuration.type = controller_interface::interface_configuration_type::INDIVIDUAL;

  RCLCPP_INFO(get_node()->get_logger(), "Exporting command interface configurations..");

  command_interfaces_configuration.names.push_back(base_joint_name + "/" + urc_hardware::types::HW_POSITION);
  command_interfaces_configuration.names.push_back(primary_joint_name + "/" + urc_hardware::types::HW_POSITION);
  command_interfaces_configuration.names.push_back(end_effector_joint_name + "/" + urc_hardware::types::HW_POSITION);
  command_interfaces_configuration.names.push_back(gripper_joint_name + "/" + urc_hardware::types::HW_POSITION);

  command_interfaces_configuration.names.push_back(indication_light_name + "/" + urc_hardware::types::HW_CMD);
  return command_interfaces_configuration;
}

controller_interface::InterfaceConfiguration TestHardwareController::state_interface_configuration() const
{
  controller_interface::InterfaceConfiguration state_interfaces_configuration;
  state_interfaces_configuration.type = controller_interface::interface_configuration_type::INDIVIDUAL;

  state_interfaces_configuration.names.push_back(base_joint_name + "/" + urc_hardware::types::HW_POSITION);
  state_interfaces_configuration.names.push_back(base_joint_name + "/" + urc_hardware::types::HW_VELOCITY);
  state_interfaces_configuration.names.push_back(primary_joint_name + "/" + urc_hardware::types::HW_POSITION);
  state_interfaces_configuration.names.push_back(primary_joint_name + "/" + urc_hardware::types::HW_VELOCITY);
  state_interfaces_configuration.names.push_back(end_effector_joint_name + "/" + urc_hardware::types::HW_POSITION);
  state_interfaces_configuration.names.push_back(end_effector_joint_name + "/" + urc_hardware::types::HW_VELOCITY);
  state_interfaces_configuration.names.push_back(gripper_joint_name + "/" + urc_hardware::types::HW_POSITION);
  state_interfaces_configuration.names.push_back(gripper_joint_name + "/" + urc_hardware::types::HW_VELOCITY);

  state_interfaces_configuration.names.push_back(imu_name + "/" + "quaternion.w");
  state_interfaces_configuration.names.push_back(imu_name + "/" + "quaternion.x");
  state_interfaces_configuration.names.push_back(imu_name + "/" + "quaternion.y");
  state_interfaces_configuration.names.push_back(imu_name + "/" + "quaternion.z");

  return state_interfaces_configuration;
}

controller_interface::return_type TestHardwareController::update(const rclcpp::Time&, const rclcpp::Duration&)
{
  auto light_command = indication_light_command_.readFromRT();
  if (!light_command || !(*light_command))
  {
    return controller_interface::return_type::OK;
  }

  const double light_status = *light_command->get();
  command_interface_map_[urc_hardware::types::HW_CMD][0].get().set_value(light_status);
  return controller_interface::return_type::OK;
}

bool TestHardwareController::reset()
{
  indication_light_command_.reset();
  indication_light_command_subscription_.reset();
  imu_publisher_.reset();
  return true;
}

}  // namespace urc_controllers
