#ifndef URC_HW__STATUS_LIGHT_HW_INTERFACE_HPP
#define URC_HW__STATUS_LIGHT_HW_INTERFACE_HPP

#include "memory"
#include "vector"
#include "string"

#include "hardware_interface/handle.hpp"
#include "hardware_interface/system_interface.hpp"
#include "rclcpp/rclcpp.hpp"
#include "async_sockets/basesocket.hpp"
#include "async_sockets/udpsocket.hpp"
#include "pb_encode.h"
#include "urc_nanopb/urc.pb.h"
#include <cstdint>
#include <memory>
#include <pb.h>

namespace urc_hardware::hardware_interfaces
{
  std::string num_to_state(uint8_t num)
  {
    switch (num)
    {
    case 0:
      return "off";
    case 1:
      return "on";
    case 2:
      return "blinking";
    default:
      return "unknown";
    }
  }

  class StatusLight : public hardware_interface::SystemInterface
  {
  public:
    StatusLight();
    ~StatusLight();

    hardware_interface::CallbackReturn on_init(const hardware_interface::HardwareInfo &hardware_info)
        override;
    std::vector<hardware_interface::CommandInterface> export_command_interfaces() override;
    std::vector<hardware_interface::StateInterface> export_state_interfaces() override;
    hardware_interface::CallbackReturn on_configure(const rclcpp_lifecycle::State &previous_state)
        override;
    hardware_interface::CallbackReturn on_activate(const rclcpp_lifecycle::State &previous_state)
        override;
    hardware_interface::CallbackReturn on_deactivate(const rclcpp_lifecycle::State &previous_state)
        override;
    hardware_interface::return_type read(
        const rclcpp::Time &time,
        const rclcpp::Duration &period) override;
    hardware_interface::return_type write(
        const rclcpp::Time &time,
        const rclcpp::Duration &period) override;

  private:
    // basic info
    const std::string hardware_interface_name;
    // states
    std::vector<double> signals; // [0]: color selection, [1]: state (on, off, blinking)

    // hardware resources
    std::shared_ptr<UDPSocket<128>> udp_;
    std::string udp_address;
    std::string udp_port;

    // nanopb
    uint8_t buffer[TeensyMessage_size];
    size_t message_length;

    uint8_t lightStates[3]; // current state of each light (red, green, blue).
  };

} // namespace urc_hardware::hardware_interfaces

#endif // URC_HW__STATUS_LIGHT_HW_INTERFACE_HPP
