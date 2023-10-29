
#ifndef TEST_HARDWARE_CONTROLLER_HPP_
#define TEST_HARDWARE_CONTROLLER_HPP_

#include <controller_interface/controller_interface.hpp>
#include <functional>
#include <geometry_msgs/msg/detail/quaternion__struct.hpp>
#include <geometry_msgs/msg/detail/twist__struct.hpp>
#include <geometry_msgs/msg/detail/twist_stamped__struct.hpp>
#include <hardware_interface/handle.hpp>
#include <hardware_interface/loaned_command_interface.hpp>
#include <memory>
#include <rclcpp/publisher.hpp>
#include <rclcpp/subscription.hpp>
#include <rclcpp_lifecycle/node_interfaces/lifecycle_node_interface.hpp>
#include <rclcpp_lifecycle/state.hpp>
#include "realtime_tools/realtime_tools/realtime_buffer.h"
#include <geometry_msgs/msg/twist_stamped.hpp>
#include <std_msgs/msg/detail/float32__struct.hpp>
#include <string>
#include <vector>

namespace urc_controllers
{

using Twist = geometry_msgs::msg::TwistStamped;

class TestHardwareController : public controller_interface::ControllerInterface
{
public:
  TestHardwareController();

  controller_interface::InterfaceConfiguration command_interface_configuration() const override;

  controller_interface::InterfaceConfiguration state_interface_configuration() const override;

  controller_interface::return_type update(const rclcpp::Time& time, const rclcpp::Duration& period) override;

  controller_interface::CallbackReturn on_init() override;

  controller_interface::CallbackReturn on_configure(const rclcpp_lifecycle::State& previous_state) override;

  controller_interface::CallbackReturn on_activate(const rclcpp_lifecycle::State& previous_state) override;

  controller_interface::CallbackReturn on_deactivate(const rclcpp_lifecycle::State& previous_state) override;

  controller_interface::CallbackReturn on_cleanup(const rclcpp_lifecycle::State& previous_state) override;

  controller_interface::CallbackReturn on_error(const rclcpp_lifecycle::State& previous_state) override;

  controller_interface::CallbackReturn on_shutdown(const rclcpp_lifecycle::State& previous_state) override;

protected:
  // joints related
  std::string base_joint_name;
  std::string primary_joint_name;
  std::string end_effector_joint_name;
  std::string gripper_joint_name;

  // indication light related
  std::string indication_light_name;
  std::shared_ptr<rclcpp::Subscription<std_msgs::msg::Float32>> indication_light_command_subscription_;
  realtime_tools::RealtimeBuffer<std::shared_ptr<double>> indication_light_command_;

  // imu related
  std::string imu_name;
  std::shared_ptr<rclcpp::Publisher<geometry_msgs::msg::Quaternion>> imu_publisher_;

  // command interfaces
  std::unordered_map<std::string, std::vector<std::reference_wrapper<hardware_interface::LoanedCommandInterface>>>
      command_interface_map_;

private:
  bool reset();
};
}  // namespace urc_controllers

#endif  // TEST_HARDWARE_CONTROLLER_HPP_