#ifndef HARDWARE_INTERFACES_BATTERY_MANAGEMENT_HPP__
#define HARDWARE_INTERFACES_BATTERY_MANAGEMENT_HPP__

#include "memory"
#include "vector"
#include "rclcpp/rclcpp.hpp"
#include "hardware_interface/sensor_interface.hpp"
#include "async_sockets/basesocket.hpp"
#include "async_sockets/udpsocket.hpp"
#include "urc_nanopb/urc.pb.h"
#include "pb_decode.h"
#include <async_sockets/udpserver.hpp>
#include <mutex>
#include <set>
#include <string>
#include <vector>

namespace urc_hardware::hardware_interfaces
{

class BatteryManagement : public hardware_interface::SensorInterface
{
public:
  BatteryManagement();
  ~BatteryManagement();

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
  std::vector<double> core_status;    // main voltage, charge percentage, discharge current, temperature
  std::vector<double> cell_voltages;  // individual cell voltages

  // hardware resources
  std::shared_ptr<UDPServer<128>> udp_;
  std::string udp_self_address;
  std::string udp_self_port;

  // nanopb
  uint8_t buffer[128];
  void decode(const char* buf, ssize_t size);
  BatteryMessage current_message;
  std::mutex guard;

  // mapping
  const std::set<std::string> INTERFACE_NAMES{ "main_voltage", "charge_percentage", "discharge_current",
                                               "temperature" };
};

}  // namespace urc_hardware::hardware_interfaces

#endif /* HARDWARE_INTERFACES_BATTERY_MANAGEMENT_HPP__ */
