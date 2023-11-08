
#ifndef URC_CONTROLLERS__IMU_BROADCASTER_HPP_
#define URC_CONTROLLERS__IMU_BROADCASTER_HPP_

#include <controller_interface/controller_interface.hpp>
#include <functional>
#include <geometry_msgs/msg/detail/quaternion_stamped__struct.hpp>
#include <geometry_msgs/msg/quaternion_stamped.hpp>
#include <geometry_msgs/msg/detail/twist__struct.hpp>
#include <geometry_msgs/msg/detail/twist_stamped__struct.hpp>
#include "sensor_msgs/msg/imu.hpp"
#include <hardware_interface/handle.hpp>
#include <hardware_interface/loaned_command_interface.hpp>
#include <hardware_interface/loaned_state_interface.hpp>
#include <memory>
#include <rclcpp/publisher.hpp>
#include <rclcpp/subscription.hpp>
#include <rclcpp_lifecycle/node_interfaces/lifecycle_node_interface.hpp>
#include <rclcpp_lifecycle/state.hpp>
#include "realtime_tools/realtime_tools/realtime_buffer.h"
#include <geometry_msgs/msg/twist_stamped.hpp>
#include <sensor_msgs/msg/detail/imu__struct.hpp>
#include <std_msgs/msg/detail/float32__struct.hpp>
#include <string>
#include <vector>

namespace urc_controllers
{

class IMUBroadcaster : public controller_interface::ControllerInterface
{
public:
  IMUBroadcaster();

  controller_interface::InterfaceConfiguration state_interface_configuration() const override;
  controller_interface::InterfaceConfiguration command_interface_configuration() const override;

  controller_interface::return_type update(const rclcpp::Time& time, const rclcpp::Duration& period) override;

  controller_interface::CallbackReturn on_init() override;

  controller_interface::CallbackReturn on_configure(const rclcpp_lifecycle::State& previous_state) override;

  controller_interface::CallbackReturn on_activate(const rclcpp_lifecycle::State& previous_state) override;

  controller_interface::CallbackReturn on_deactivate(const rclcpp_lifecycle::State& previous_state) override;

  controller_interface::CallbackReturn on_cleanup(const rclcpp_lifecycle::State& previous_state) override;

  controller_interface::CallbackReturn on_error(const rclcpp_lifecycle::State& previous_state) override;

  controller_interface::CallbackReturn on_shutdown(const rclcpp_lifecycle::State& previous_state) override;

protected:
  // imu related
  std::string imu_name;
  std::shared_ptr<rclcpp::Publisher<sensor_msgs::msg::Imu>> imu_state_publisher_;

  // state interfaces
  std::unordered_map<std::string, std::shared_ptr<std::reference_wrapper<hardware_interface::LoanedStateInterface>>>
      state_interfaces_map_;
  const std::vector<std::string> IMU_INTERFACES{ "orientation.x",         "orientation.y",
                                                 "orientation.z",         "orientation.w",
                                                 "linear_acceleration.x", "linear_acceleration.y",
                                                 "linear_acceleration.z", "angular_velocity.x",
                                                 "angular_velocity.y",    "angular_velocity.z" };
};

}  // namespace urc_controllers

#endif  // URC_CONTROLLERS__IMU_BROADCASTER_HPP_