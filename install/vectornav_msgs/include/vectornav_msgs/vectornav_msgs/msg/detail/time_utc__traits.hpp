// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from vectornav_msgs:msg/TimeUTC.idl
// generated code does not contain a copyright notice

#ifndef VECTORNAV_MSGS__MSG__DETAIL__TIME_UTC__TRAITS_HPP_
#define VECTORNAV_MSGS__MSG__DETAIL__TIME_UTC__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "vectornav_msgs/msg/detail/time_utc__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace vectornav_msgs
{

namespace msg
{

inline void to_flow_style_yaml(
  const TimeUTC & msg,
  std::ostream & out)
{
  out << "{";
  // member: year
  {
    out << "year: ";
    rosidl_generator_traits::value_to_yaml(msg.year, out);
    out << ", ";
  }

  // member: month
  {
    out << "month: ";
    rosidl_generator_traits::value_to_yaml(msg.month, out);
    out << ", ";
  }

  // member: day
  {
    out << "day: ";
    rosidl_generator_traits::value_to_yaml(msg.day, out);
    out << ", ";
  }

  // member: hour
  {
    out << "hour: ";
    rosidl_generator_traits::value_to_yaml(msg.hour, out);
    out << ", ";
  }

  // member: min
  {
    out << "min: ";
    rosidl_generator_traits::value_to_yaml(msg.min, out);
    out << ", ";
  }

  // member: sec
  {
    out << "sec: ";
    rosidl_generator_traits::value_to_yaml(msg.sec, out);
    out << ", ";
  }

  // member: ms
  {
    out << "ms: ";
    rosidl_generator_traits::value_to_yaml(msg.ms, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const TimeUTC & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: year
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "year: ";
    rosidl_generator_traits::value_to_yaml(msg.year, out);
    out << "\n";
  }

  // member: month
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "month: ";
    rosidl_generator_traits::value_to_yaml(msg.month, out);
    out << "\n";
  }

  // member: day
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "day: ";
    rosidl_generator_traits::value_to_yaml(msg.day, out);
    out << "\n";
  }

  // member: hour
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "hour: ";
    rosidl_generator_traits::value_to_yaml(msg.hour, out);
    out << "\n";
  }

  // member: min
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "min: ";
    rosidl_generator_traits::value_to_yaml(msg.min, out);
    out << "\n";
  }

  // member: sec
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "sec: ";
    rosidl_generator_traits::value_to_yaml(msg.sec, out);
    out << "\n";
  }

  // member: ms
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "ms: ";
    rosidl_generator_traits::value_to_yaml(msg.ms, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const TimeUTC & msg, bool use_flow_style = false)
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
  const vectornav_msgs::msg::TimeUTC & msg,
  std::ostream & out, size_t indentation = 0)
{
  vectornav_msgs::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use vectornav_msgs::msg::to_yaml() instead")]]
inline std::string to_yaml(const vectornav_msgs::msg::TimeUTC & msg)
{
  return vectornav_msgs::msg::to_yaml(msg);
}

template<>
inline const char * data_type<vectornav_msgs::msg::TimeUTC>()
{
  return "vectornav_msgs::msg::TimeUTC";
}

template<>
inline const char * name<vectornav_msgs::msg::TimeUTC>()
{
  return "vectornav_msgs/msg/TimeUTC";
}

template<>
struct has_fixed_size<vectornav_msgs::msg::TimeUTC>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<vectornav_msgs::msg::TimeUTC>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<vectornav_msgs::msg::TimeUTC>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // VECTORNAV_MSGS__MSG__DETAIL__TIME_UTC__TRAITS_HPP_
