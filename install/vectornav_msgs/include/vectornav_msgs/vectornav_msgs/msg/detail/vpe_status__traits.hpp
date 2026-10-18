// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from vectornav_msgs:msg/VpeStatus.idl
// generated code does not contain a copyright notice

#ifndef VECTORNAV_MSGS__MSG__DETAIL__VPE_STATUS__TRAITS_HPP_
#define VECTORNAV_MSGS__MSG__DETAIL__VPE_STATUS__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "vectornav_msgs/msg/detail/vpe_status__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace vectornav_msgs
{

namespace msg
{

inline void to_flow_style_yaml(
  const VpeStatus & msg,
  std::ostream & out)
{
  out << "{";
  // member: attitude_quality
  {
    out << "attitude_quality: ";
    rosidl_generator_traits::value_to_yaml(msg.attitude_quality, out);
    out << ", ";
  }

  // member: gyro_saturation
  {
    out << "gyro_saturation: ";
    rosidl_generator_traits::value_to_yaml(msg.gyro_saturation, out);
    out << ", ";
  }

  // member: gyro_saturation_recovery
  {
    out << "gyro_saturation_recovery: ";
    rosidl_generator_traits::value_to_yaml(msg.gyro_saturation_recovery, out);
    out << ", ";
  }

  // member: mag_disturbance
  {
    out << "mag_disturbance: ";
    rosidl_generator_traits::value_to_yaml(msg.mag_disturbance, out);
    out << ", ";
  }

  // member: mag_saturation
  {
    out << "mag_saturation: ";
    rosidl_generator_traits::value_to_yaml(msg.mag_saturation, out);
    out << ", ";
  }

  // member: acc_disturbance
  {
    out << "acc_disturbance: ";
    rosidl_generator_traits::value_to_yaml(msg.acc_disturbance, out);
    out << ", ";
  }

  // member: acc_saturation
  {
    out << "acc_saturation: ";
    rosidl_generator_traits::value_to_yaml(msg.acc_saturation, out);
    out << ", ";
  }

  // member: known_mag_disturbance
  {
    out << "known_mag_disturbance: ";
    rosidl_generator_traits::value_to_yaml(msg.known_mag_disturbance, out);
    out << ", ";
  }

  // member: known_accel_disturbance
  {
    out << "known_accel_disturbance: ";
    rosidl_generator_traits::value_to_yaml(msg.known_accel_disturbance, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const VpeStatus & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: attitude_quality
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "attitude_quality: ";
    rosidl_generator_traits::value_to_yaml(msg.attitude_quality, out);
    out << "\n";
  }

  // member: gyro_saturation
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "gyro_saturation: ";
    rosidl_generator_traits::value_to_yaml(msg.gyro_saturation, out);
    out << "\n";
  }

  // member: gyro_saturation_recovery
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "gyro_saturation_recovery: ";
    rosidl_generator_traits::value_to_yaml(msg.gyro_saturation_recovery, out);
    out << "\n";
  }

  // member: mag_disturbance
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "mag_disturbance: ";
    rosidl_generator_traits::value_to_yaml(msg.mag_disturbance, out);
    out << "\n";
  }

  // member: mag_saturation
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "mag_saturation: ";
    rosidl_generator_traits::value_to_yaml(msg.mag_saturation, out);
    out << "\n";
  }

  // member: acc_disturbance
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "acc_disturbance: ";
    rosidl_generator_traits::value_to_yaml(msg.acc_disturbance, out);
    out << "\n";
  }

  // member: acc_saturation
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "acc_saturation: ";
    rosidl_generator_traits::value_to_yaml(msg.acc_saturation, out);
    out << "\n";
  }

  // member: known_mag_disturbance
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "known_mag_disturbance: ";
    rosidl_generator_traits::value_to_yaml(msg.known_mag_disturbance, out);
    out << "\n";
  }

  // member: known_accel_disturbance
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "known_accel_disturbance: ";
    rosidl_generator_traits::value_to_yaml(msg.known_accel_disturbance, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const VpeStatus & msg, bool use_flow_style = false)
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
  const vectornav_msgs::msg::VpeStatus & msg,
  std::ostream & out, size_t indentation = 0)
{
  vectornav_msgs::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use vectornav_msgs::msg::to_yaml() instead")]]
inline std::string to_yaml(const vectornav_msgs::msg::VpeStatus & msg)
{
  return vectornav_msgs::msg::to_yaml(msg);
}

template<>
inline const char * data_type<vectornav_msgs::msg::VpeStatus>()
{
  return "vectornav_msgs::msg::VpeStatus";
}

template<>
inline const char * name<vectornav_msgs::msg::VpeStatus>()
{
  return "vectornav_msgs/msg/VpeStatus";
}

template<>
struct has_fixed_size<vectornav_msgs::msg::VpeStatus>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<vectornav_msgs::msg::VpeStatus>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<vectornav_msgs::msg::VpeStatus>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // VECTORNAV_MSGS__MSG__DETAIL__VPE_STATUS__TRAITS_HPP_
