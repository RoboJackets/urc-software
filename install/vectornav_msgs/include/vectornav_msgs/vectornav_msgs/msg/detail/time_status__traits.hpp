// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from vectornav_msgs:msg/TimeStatus.idl
// generated code does not contain a copyright notice

#ifndef VECTORNAV_MSGS__MSG__DETAIL__TIME_STATUS__TRAITS_HPP_
#define VECTORNAV_MSGS__MSG__DETAIL__TIME_STATUS__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "vectornav_msgs/msg/detail/time_status__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace vectornav_msgs
{

namespace msg
{

inline void to_flow_style_yaml(
  const TimeStatus & msg,
  std::ostream & out)
{
  out << "{";
  // member: time_ok
  {
    out << "time_ok: ";
    rosidl_generator_traits::value_to_yaml(msg.time_ok, out);
    out << ", ";
  }

  // member: date_ok
  {
    out << "date_ok: ";
    rosidl_generator_traits::value_to_yaml(msg.date_ok, out);
    out << ", ";
  }

  // member: utctime_ok
  {
    out << "utctime_ok: ";
    rosidl_generator_traits::value_to_yaml(msg.utctime_ok, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const TimeStatus & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: time_ok
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "time_ok: ";
    rosidl_generator_traits::value_to_yaml(msg.time_ok, out);
    out << "\n";
  }

  // member: date_ok
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "date_ok: ";
    rosidl_generator_traits::value_to_yaml(msg.date_ok, out);
    out << "\n";
  }

  // member: utctime_ok
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "utctime_ok: ";
    rosidl_generator_traits::value_to_yaml(msg.utctime_ok, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const TimeStatus & msg, bool use_flow_style = false)
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
  const vectornav_msgs::msg::TimeStatus & msg,
  std::ostream & out, size_t indentation = 0)
{
  vectornav_msgs::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use vectornav_msgs::msg::to_yaml() instead")]]
inline std::string to_yaml(const vectornav_msgs::msg::TimeStatus & msg)
{
  return vectornav_msgs::msg::to_yaml(msg);
}

template<>
inline const char * data_type<vectornav_msgs::msg::TimeStatus>()
{
  return "vectornav_msgs::msg::TimeStatus";
}

template<>
inline const char * name<vectornav_msgs::msg::TimeStatus>()
{
  return "vectornav_msgs/msg/TimeStatus";
}

template<>
struct has_fixed_size<vectornav_msgs::msg::TimeStatus>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<vectornav_msgs::msg::TimeStatus>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<vectornav_msgs::msg::TimeStatus>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // VECTORNAV_MSGS__MSG__DETAIL__TIME_STATUS__TRAITS_HPP_
