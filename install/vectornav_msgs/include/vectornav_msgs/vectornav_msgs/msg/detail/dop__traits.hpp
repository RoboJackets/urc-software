// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from vectornav_msgs:msg/DOP.idl
// generated code does not contain a copyright notice

#ifndef VECTORNAV_MSGS__MSG__DETAIL__DOP__TRAITS_HPP_
#define VECTORNAV_MSGS__MSG__DETAIL__DOP__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "vectornav_msgs/msg/detail/dop__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace vectornav_msgs
{

namespace msg
{

inline void to_flow_style_yaml(
  const DOP & msg,
  std::ostream & out)
{
  out << "{";
  // member: g
  {
    out << "g: ";
    rosidl_generator_traits::value_to_yaml(msg.g, out);
    out << ", ";
  }

  // member: p
  {
    out << "p: ";
    rosidl_generator_traits::value_to_yaml(msg.p, out);
    out << ", ";
  }

  // member: t
  {
    out << "t: ";
    rosidl_generator_traits::value_to_yaml(msg.t, out);
    out << ", ";
  }

  // member: v
  {
    out << "v: ";
    rosidl_generator_traits::value_to_yaml(msg.v, out);
    out << ", ";
  }

  // member: h
  {
    out << "h: ";
    rosidl_generator_traits::value_to_yaml(msg.h, out);
    out << ", ";
  }

  // member: n
  {
    out << "n: ";
    rosidl_generator_traits::value_to_yaml(msg.n, out);
    out << ", ";
  }

  // member: e
  {
    out << "e: ";
    rosidl_generator_traits::value_to_yaml(msg.e, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const DOP & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: g
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "g: ";
    rosidl_generator_traits::value_to_yaml(msg.g, out);
    out << "\n";
  }

  // member: p
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "p: ";
    rosidl_generator_traits::value_to_yaml(msg.p, out);
    out << "\n";
  }

  // member: t
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "t: ";
    rosidl_generator_traits::value_to_yaml(msg.t, out);
    out << "\n";
  }

  // member: v
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "v: ";
    rosidl_generator_traits::value_to_yaml(msg.v, out);
    out << "\n";
  }

  // member: h
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "h: ";
    rosidl_generator_traits::value_to_yaml(msg.h, out);
    out << "\n";
  }

  // member: n
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "n: ";
    rosidl_generator_traits::value_to_yaml(msg.n, out);
    out << "\n";
  }

  // member: e
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "e: ";
    rosidl_generator_traits::value_to_yaml(msg.e, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const DOP & msg, bool use_flow_style = false)
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
  const vectornav_msgs::msg::DOP & msg,
  std::ostream & out, size_t indentation = 0)
{
  vectornav_msgs::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use vectornav_msgs::msg::to_yaml() instead")]]
inline std::string to_yaml(const vectornav_msgs::msg::DOP & msg)
{
  return vectornav_msgs::msg::to_yaml(msg);
}

template<>
inline const char * data_type<vectornav_msgs::msg::DOP>()
{
  return "vectornav_msgs::msg::DOP";
}

template<>
inline const char * name<vectornav_msgs::msg::DOP>()
{
  return "vectornav_msgs/msg/DOP";
}

template<>
struct has_fixed_size<vectornav_msgs::msg::DOP>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<vectornav_msgs::msg::DOP>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<vectornav_msgs::msg::DOP>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // VECTORNAV_MSGS__MSG__DETAIL__DOP__TRAITS_HPP_
