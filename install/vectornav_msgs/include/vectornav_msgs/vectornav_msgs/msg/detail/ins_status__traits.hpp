// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from vectornav_msgs:msg/InsStatus.idl
// generated code does not contain a copyright notice

#ifndef VECTORNAV_MSGS__MSG__DETAIL__INS_STATUS__TRAITS_HPP_
#define VECTORNAV_MSGS__MSG__DETAIL__INS_STATUS__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "vectornav_msgs/msg/detail/ins_status__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace vectornav_msgs
{

namespace msg
{

inline void to_flow_style_yaml(
  const InsStatus & msg,
  std::ostream & out)
{
  out << "{";
  // member: mode
  {
    out << "mode: ";
    rosidl_generator_traits::value_to_yaml(msg.mode, out);
    out << ", ";
  }

  // member: gps_fix
  {
    out << "gps_fix: ";
    rosidl_generator_traits::value_to_yaml(msg.gps_fix, out);
    out << ", ";
  }

  // member: time_error
  {
    out << "time_error: ";
    rosidl_generator_traits::value_to_yaml(msg.time_error, out);
    out << ", ";
  }

  // member: imu_error
  {
    out << "imu_error: ";
    rosidl_generator_traits::value_to_yaml(msg.imu_error, out);
    out << ", ";
  }

  // member: mag_pres_error
  {
    out << "mag_pres_error: ";
    rosidl_generator_traits::value_to_yaml(msg.mag_pres_error, out);
    out << ", ";
  }

  // member: gps_error
  {
    out << "gps_error: ";
    rosidl_generator_traits::value_to_yaml(msg.gps_error, out);
    out << ", ";
  }

  // member: gps_heading_ins
  {
    out << "gps_heading_ins: ";
    rosidl_generator_traits::value_to_yaml(msg.gps_heading_ins, out);
    out << ", ";
  }

  // member: gps_compass
  {
    out << "gps_compass: ";
    rosidl_generator_traits::value_to_yaml(msg.gps_compass, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const InsStatus & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: mode
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "mode: ";
    rosidl_generator_traits::value_to_yaml(msg.mode, out);
    out << "\n";
  }

  // member: gps_fix
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "gps_fix: ";
    rosidl_generator_traits::value_to_yaml(msg.gps_fix, out);
    out << "\n";
  }

  // member: time_error
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "time_error: ";
    rosidl_generator_traits::value_to_yaml(msg.time_error, out);
    out << "\n";
  }

  // member: imu_error
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "imu_error: ";
    rosidl_generator_traits::value_to_yaml(msg.imu_error, out);
    out << "\n";
  }

  // member: mag_pres_error
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "mag_pres_error: ";
    rosidl_generator_traits::value_to_yaml(msg.mag_pres_error, out);
    out << "\n";
  }

  // member: gps_error
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "gps_error: ";
    rosidl_generator_traits::value_to_yaml(msg.gps_error, out);
    out << "\n";
  }

  // member: gps_heading_ins
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "gps_heading_ins: ";
    rosidl_generator_traits::value_to_yaml(msg.gps_heading_ins, out);
    out << "\n";
  }

  // member: gps_compass
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "gps_compass: ";
    rosidl_generator_traits::value_to_yaml(msg.gps_compass, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const InsStatus & msg, bool use_flow_style = false)
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

}  // namespace vectornav_msgs

namespace rosidl_generator_traits
{

[[deprecated("use vectornav_msgs::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const vectornav_msgs::msg::InsStatus & msg,
  std::ostream & out, size_t indentation = 0)
{
  vectornav_msgs::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use vectornav_msgs::msg::to_yaml() instead")]]
inline std::string to_yaml(const vectornav_msgs::msg::InsStatus & msg)
{
  return vectornav_msgs::msg::to_yaml(msg);
}

template<>
inline const char * data_type<vectornav_msgs::msg::InsStatus>()
{
  return "vectornav_msgs::msg::InsStatus";
}

template<>
inline const char * name<vectornav_msgs::msg::InsStatus>()
{
  return "vectornav_msgs/msg/InsStatus";
}

template<>
struct has_fixed_size<vectornav_msgs::msg::InsStatus>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<vectornav_msgs::msg::InsStatus>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<vectornav_msgs::msg::InsStatus>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // VECTORNAV_MSGS__MSG__DETAIL__INS_STATUS__TRAITS_HPP_
