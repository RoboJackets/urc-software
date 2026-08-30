// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from vectornav_msgs:msg/ImuGroup.idl
// generated code does not contain a copyright notice

#ifndef VECTORNAV_MSGS__MSG__DETAIL__IMU_GROUP__TRAITS_HPP_
#define VECTORNAV_MSGS__MSG__DETAIL__IMU_GROUP__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "vectornav_msgs/msg/detail/imu_group__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__traits.hpp"
// Member 'uncompmag'
// Member 'uncompaccel'
// Member 'uncompgyro'
// Member 'deltatheta_dtheta'
// Member 'deltavel'
// Member 'mag'
// Member 'accel'
// Member 'angularrate'
#include "geometry_msgs/msg/detail/vector3__traits.hpp"

namespace vectornav_msgs
{

namespace msg
{

inline void to_flow_style_yaml(
  const ImuGroup & msg,
  std::ostream & out)
{
  out << "{";
  // member: header
  {
    out << "header: ";
    to_flow_style_yaml(msg.header, out);
    out << ", ";
  }

  // member: group_fields
  {
    out << "group_fields: ";
    rosidl_generator_traits::value_to_yaml(msg.group_fields, out);
    out << ", ";
  }

  // member: imustatus
  {
    out << "imustatus: ";
    rosidl_generator_traits::value_to_yaml(msg.imustatus, out);
    out << ", ";
  }

  // member: uncompmag
  {
    out << "uncompmag: ";
    to_flow_style_yaml(msg.uncompmag, out);
    out << ", ";
  }

  // member: uncompaccel
  {
    out << "uncompaccel: ";
    to_flow_style_yaml(msg.uncompaccel, out);
    out << ", ";
  }

  // member: uncompgyro
  {
    out << "uncompgyro: ";
    to_flow_style_yaml(msg.uncompgyro, out);
    out << ", ";
  }

  // member: temp
  {
    out << "temp: ";
    rosidl_generator_traits::value_to_yaml(msg.temp, out);
    out << ", ";
  }

  // member: pres
  {
    out << "pres: ";
    rosidl_generator_traits::value_to_yaml(msg.pres, out);
    out << ", ";
  }

  // member: deltatheta_time
  {
    out << "deltatheta_time: ";
    rosidl_generator_traits::value_to_yaml(msg.deltatheta_time, out);
    out << ", ";
  }

  // member: deltatheta_dtheta
  {
    out << "deltatheta_dtheta: ";
    to_flow_style_yaml(msg.deltatheta_dtheta, out);
    out << ", ";
  }

  // member: deltavel
  {
    out << "deltavel: ";
    to_flow_style_yaml(msg.deltavel, out);
    out << ", ";
  }

  // member: mag
  {
    out << "mag: ";
    to_flow_style_yaml(msg.mag, out);
    out << ", ";
  }

  // member: accel
  {
    out << "accel: ";
    to_flow_style_yaml(msg.accel, out);
    out << ", ";
  }

  // member: angularrate
  {
    out << "angularrate: ";
    to_flow_style_yaml(msg.angularrate, out);
    out << ", ";
  }

  // member: sensat
  {
    out << "sensat: ";
    rosidl_generator_traits::value_to_yaml(msg.sensat, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const ImuGroup & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: header
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "header:\n";
    to_block_style_yaml(msg.header, out, indentation + 2);
  }

  // member: group_fields
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "group_fields: ";
    rosidl_generator_traits::value_to_yaml(msg.group_fields, out);
    out << "\n";
  }

  // member: imustatus
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "imustatus: ";
    rosidl_generator_traits::value_to_yaml(msg.imustatus, out);
    out << "\n";
  }

  // member: uncompmag
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "uncompmag:\n";
    to_block_style_yaml(msg.uncompmag, out, indentation + 2);
  }

  // member: uncompaccel
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "uncompaccel:\n";
    to_block_style_yaml(msg.uncompaccel, out, indentation + 2);
  }

  // member: uncompgyro
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "uncompgyro:\n";
    to_block_style_yaml(msg.uncompgyro, out, indentation + 2);
  }

  // member: temp
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "temp: ";
    rosidl_generator_traits::value_to_yaml(msg.temp, out);
    out << "\n";
  }

  // member: pres
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "pres: ";
    rosidl_generator_traits::value_to_yaml(msg.pres, out);
    out << "\n";
  }

  // member: deltatheta_time
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "deltatheta_time: ";
    rosidl_generator_traits::value_to_yaml(msg.deltatheta_time, out);
    out << "\n";
  }

  // member: deltatheta_dtheta
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "deltatheta_dtheta:\n";
    to_block_style_yaml(msg.deltatheta_dtheta, out, indentation + 2);
  }

  // member: deltavel
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "deltavel:\n";
    to_block_style_yaml(msg.deltavel, out, indentation + 2);
  }

  // member: mag
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "mag:\n";
    to_block_style_yaml(msg.mag, out, indentation + 2);
  }

  // member: accel
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "accel:\n";
    to_block_style_yaml(msg.accel, out, indentation + 2);
  }

  // member: angularrate
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "angularrate:\n";
    to_block_style_yaml(msg.angularrate, out, indentation + 2);
  }

  // member: sensat
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "sensat: ";
    rosidl_generator_traits::value_to_yaml(msg.sensat, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const ImuGroup & msg, bool use_flow_style = false)
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
  const vectornav_msgs::msg::ImuGroup & msg,
  std::ostream & out, size_t indentation = 0)
{
  vectornav_msgs::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use vectornav_msgs::msg::to_yaml() instead")]]
inline std::string to_yaml(const vectornav_msgs::msg::ImuGroup & msg)
{
  return vectornav_msgs::msg::to_yaml(msg);
}

template<>
inline const char * data_type<vectornav_msgs::msg::ImuGroup>()
{
  return "vectornav_msgs::msg::ImuGroup";
}

template<>
inline const char * name<vectornav_msgs::msg::ImuGroup>()
{
  return "vectornav_msgs/msg/ImuGroup";
}

template<>
struct has_fixed_size<vectornav_msgs::msg::ImuGroup>
  : std::integral_constant<bool, has_fixed_size<geometry_msgs::msg::Vector3>::value && has_fixed_size<std_msgs::msg::Header>::value> {};

template<>
struct has_bounded_size<vectornav_msgs::msg::ImuGroup>
  : std::integral_constant<bool, has_bounded_size<geometry_msgs::msg::Vector3>::value && has_bounded_size<std_msgs::msg::Header>::value> {};

template<>
struct is_message<vectornav_msgs::msg::ImuGroup>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // VECTORNAV_MSGS__MSG__DETAIL__IMU_GROUP__TRAITS_HPP_
