// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from urc_msgs:msg/VelocityPair.idl
// generated code does not contain a copyright notice

#ifndef URC_MSGS__MSG__DETAIL__VELOCITY_PAIR__TRAITS_HPP_
#define URC_MSGS__MSG__DETAIL__VELOCITY_PAIR__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "urc_msgs/msg/detail/velocity_pair__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__traits.hpp"

namespace urc_msgs
{

namespace msg
{

inline void to_flow_style_yaml(
  const VelocityPair & msg,
  std::ostream & out)
{
  out << "{";
  // member: header
  {
    out << "header: ";
    to_flow_style_yaml(msg.header, out);
    out << ", ";
  }

  // member: left_velocity
  {
    out << "left_velocity: ";
    rosidl_generator_traits::value_to_yaml(msg.left_velocity, out);
    out << ", ";
  }

  // member: right_velocity
  {
    out << "right_velocity: ";
    rosidl_generator_traits::value_to_yaml(msg.right_velocity, out);
    out << ", ";
  }

  // member: duration
  {
    out << "duration: ";
    rosidl_generator_traits::value_to_yaml(msg.duration, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const VelocityPair & msg,
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

  // member: left_velocity
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "left_velocity: ";
    rosidl_generator_traits::value_to_yaml(msg.left_velocity, out);
    out << "\n";
  }

  // member: right_velocity
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "right_velocity: ";
    rosidl_generator_traits::value_to_yaml(msg.right_velocity, out);
    out << "\n";
  }

  // member: duration
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "duration: ";
    rosidl_generator_traits::value_to_yaml(msg.duration, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const VelocityPair & msg, bool use_flow_style = false)
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
  const urc_msgs::msg::VelocityPair & msg,
  std::ostream & out, size_t indentation = 0)
{
  urc_msgs::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use urc_msgs::msg::to_yaml() instead")]]
inline std::string to_yaml(const urc_msgs::msg::VelocityPair & msg)
{
  return urc_msgs::msg::to_yaml(msg);
}

template<>
inline const char * data_type<urc_msgs::msg::VelocityPair>()
{
  return "urc_msgs::msg::VelocityPair";
}

template<>
inline const char * name<urc_msgs::msg::VelocityPair>()
{
  return "urc_msgs/msg/VelocityPair";
}

template<>
struct has_fixed_size<urc_msgs::msg::VelocityPair>
  : std::integral_constant<bool, has_fixed_size<std_msgs::msg::Header>::value> {};

template<>
struct has_bounded_size<urc_msgs::msg::VelocityPair>
  : std::integral_constant<bool, has_bounded_size<std_msgs::msg::Header>::value> {};

template<>
struct is_message<urc_msgs::msg::VelocityPair>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // URC_MSGS__MSG__DETAIL__VELOCITY_PAIR__TRAITS_HPP_
