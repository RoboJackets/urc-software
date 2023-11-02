#ifndef URC_HW__IMU_HW_INTERFACE_HPP
#define URC_HW__IMU_HW_INTERFACE_HPP

#include "memory"
#include "vector"
#include "rclcpp/rclcpp.hpp"
#include "hardware_interface/sensor_interface.hpp"
#include "async_sockets/basesocket.hpp"
#include "async_sockets/udpsocket.hpp"
#include "urc_nanopb/urc.pb.h"
#include "pb_decode.h"
#include <string>

namespace urc_hardware::hardware_interfaces
{

class IMU : public hardware_interface::SensorInterface
{
public:
  IMU();
  ~IMU();

  hardware_interface::CallbackReturn on_init(const hardware_interface::HardwareInfo& hardware_info) override;
  std::vector<hardware_interface::StateInterface> export_state_interfaces() override;
  hardware_interface::CallbackReturn on_configure(const rclcpp_lifecycle::State& previous_state) override;
  hardware_interface::CallbackReturn on_activate(const rclcpp_lifecycle::State& previous_state) override;
  hardware_interface::CallbackReturn on_deactivate(const rclcpp_lifecycle::State& previous_state) override;
  hardware_interface::return_type read(const rclcpp::Time& time, const rclcpp::Duration& period) override;

private:
  // basic info
  const std::string hardware_interface_name;
  // states
  std::vector<double> quaternions;
  std::vector<double> linear_accelerations;
  std::vector<double> angular_accelerations;

  // hardware resources
  std::shared_ptr<UDPSocket<1024>> udp_;
  std::string udp_address;
  std::string udp_port;

  // nanopb
  IMUMessage packet;
  uint8_t buffer[20];
};

}  // namespace urc_hardware::hardware_interfaces

#endif  // URC_HW__IMU_HW_INTERFACE_HPP
