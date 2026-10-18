// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from urc_msgs:msg/BatteryInfo.idl
// generated code does not contain a copyright notice

#ifndef URC_MSGS__MSG__DETAIL__BATTERY_INFO__TRAITS_HPP_
#define URC_MSGS__MSG__DETAIL__BATTERY_INFO__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "urc_msgs/msg/detail/battery_info__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace urc_msgs
{

namespace msg
{

inline void to_flow_style_yaml(
  const BatteryInfo & msg,
  std::ostream & out)
{
  out << "{";
  // member: cell_voltage
  {
    out << "cell_voltage: ";
    rosidl_generator_traits::value_to_yaml(msg.cell_voltage, out);
    out << ", ";
  }

  // member: cell_charge_percentage
  {
    out << "cell_charge_percentage: ";
    rosidl_generator_traits::value_to_yaml(msg.cell_charge_percentage, out);
    out << ", ";
  }

  // member: cell_discharge_current
  {
    out << "cell_discharge_current: ";
    rosidl_generator_traits::value_to_yaml(msg.cell_discharge_current, out);
    out << ", ";
  }

  // member: cell_temperature
  {
    out << "cell_temperature: ";
    rosidl_generator_traits::value_to_yaml(msg.cell_temperature, out);
    out << ", ";
  }

  // member: cell_voltages
  {
    if (msg.cell_voltages.size() == 0) {
      out << "cell_voltages: []";
    } else {
      out << "cell_voltages: [";
      size_t pending_items = msg.cell_voltages.size();
      for (auto item : msg.cell_voltages) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const BatteryInfo & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: cell_voltage
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "cell_voltage: ";
    rosidl_generator_traits::value_to_yaml(msg.cell_voltage, out);
    out << "\n";
  }

  // member: cell_charge_percentage
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "cell_charge_percentage: ";
    rosidl_generator_traits::value_to_yaml(msg.cell_charge_percentage, out);
    out << "\n";
  }

  // member: cell_discharge_current
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "cell_discharge_current: ";
    rosidl_generator_traits::value_to_yaml(msg.cell_discharge_current, out);
    out << "\n";
  }

  // member: cell_temperature
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "cell_temperature: ";
    rosidl_generator_traits::value_to_yaml(msg.cell_temperature, out);
    out << "\n";
  }

  // member: cell_voltages
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.cell_voltages.size() == 0) {
      out << "cell_voltages: []\n";
    } else {
      out << "cell_voltages:\n";
      for (auto item : msg.cell_voltages) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const BatteryInfo & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace msg

}  // namespace urc_msgs

namespace rosidl_generator_traits
{

[[deprecated("use urc_msgs::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const urc_msgs::msg::BatteryInfo & msg,
  std::ostream & out, size_t indentation = 0)
{
  urc_msgs::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use urc_msgs::msg::to_yaml() instead")]]
inline std::string to_yaml(const urc_msgs::msg::BatteryInfo & msg)
{
  return urc_msgs::msg::to_yaml(msg);
}

template<>
inline const char * data_type<urc_msgs::msg::BatteryInfo>()
{
  return "urc_msgs::msg::BatteryInfo";
}

template<>
inline const char * name<urc_msgs::msg::BatteryInfo>()
{
  return "urc_msgs/msg/BatteryInfo";
}

template<>
struct has_fixed_size<urc_msgs::msg::BatteryInfo>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<urc_msgs::msg::BatteryInfo>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<urc_msgs::msg::BatteryInfo>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // URC_MSGS__MSG__DETAIL__BATTERY_INFO__TRAITS_HPP_
