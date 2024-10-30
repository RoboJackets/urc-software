// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from urc_msgs:msg/NavigationStatus.idl
// generated code does not contain a copyright notice

#ifndef URC_MSGS__MSG__DETAIL__NAVIGATION_STATUS__TRAITS_HPP_
#define URC_MSGS__MSG__DETAIL__NAVIGATION_STATUS__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "urc_msgs/msg/detail/navigation_status__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace urc_msgs
{

namespace msg
{

inline void to_flow_style_yaml(
  const NavigationStatus & msg,
  std::ostream & out)
{
  out << "{";
  // member: message
  {
    out << "message: ";
    rosidl_generator_traits::value_to_yaml(msg.message, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const NavigationStatus & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: message
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "message: ";
    rosidl_generator_traits::value_to_yaml(msg.message, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const NavigationStatus & msg, bool use_flow_style = false)
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
  const urc_msgs::msg::NavigationStatus & msg,
  std::ostream & out, size_t indentation = 0)
{
  urc_msgs::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use urc_msgs::msg::to_yaml() instead")]]
inline std::string to_yaml(const urc_msgs::msg::NavigationStatus & msg)
{
  return urc_msgs::msg::to_yaml(msg);
}

template<>
inline const char * data_type<urc_msgs::msg::NavigationStatus>()
{
  return "urc_msgs::msg::NavigationStatus";
}

template<>
inline const char * name<urc_msgs::msg::NavigationStatus>()
{
  return "urc_msgs/msg/NavigationStatus";
}

template<>
struct has_fixed_size<urc_msgs::msg::NavigationStatus>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<urc_msgs::msg::NavigationStatus>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<urc_msgs::msg::NavigationStatus>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // URC_MSGS__MSG__DETAIL__NAVIGATION_STATUS__TRAITS_HPP_
