// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from aruco_msgs:msg/Marker.idl
// generated code does not contain a copyright notice

#ifndef ARUCO_MSGS__MSG__DETAIL__MARKER__TRAITS_HPP_
#define ARUCO_MSGS__MSG__DETAIL__MARKER__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "aruco_msgs/msg/detail/marker__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__traits.hpp"
// Member 'pose'
#include "geometry_msgs/msg/detail/pose_with_covariance__traits.hpp"

namespace aruco_msgs
{

namespace msg
{

inline void to_flow_style_yaml(
  const Marker & msg,
  std::ostream & out)
{
  out << "{";
  // member: header
  {
    out << "header: ";
    to_flow_style_yaml(msg.header, out);
    out << ", ";
  }

  // member: id
  {
    out << "id: ";
    rosidl_generator_traits::value_to_yaml(msg.id, out);
    out << ", ";
  }

  // member: pose
  {
    out << "pose: ";
    to_flow_style_yaml(msg.pose, out);
    out << ", ";
  }

  // member: confidence
  {
    out << "confidence: ";
    rosidl_generator_traits::value_to_yaml(msg.confidence, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const Marker & msg,
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

  // member: id
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "id: ";
    rosidl_generator_traits::value_to_yaml(msg.id, out);
    out << "\n";
  }

  // member: pose
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "pose:\n";
    to_block_style_yaml(msg.pose, out, indentation + 2);
  }

  // member: confidence
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "confidence: ";
    rosidl_generator_traits::value_to_yaml(msg.confidence, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const Marker & msg, bool use_flow_style = false)
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

}  // namespace aruco_msgs

namespace rosidl_generator_traits
{

[[deprecated("use aruco_msgs::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const aruco_msgs::msg::Marker & msg,
  std::ostream & out, size_t indentation = 0)
{
  aruco_msgs::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use aruco_msgs::msg::to_yaml() instead")]]
inline std::string to_yaml(const aruco_msgs::msg::Marker & msg)
{
  return aruco_msgs::msg::to_yaml(msg);
}

template<>
inline const char * data_type<aruco_msgs::msg::Marker>()
{
  return "aruco_msgs::msg::Marker";
}

template<>
inline const char * name<aruco_msgs::msg::Marker>()
{
  return "aruco_msgs/msg/Marker";
}

template<>
struct has_fixed_size<aruco_msgs::msg::Marker>
  : std::integral_constant<bool, has_fixed_size<geometry_msgs::msg::PoseWithCovariance>::value && has_fixed_size<std_msgs::msg::Header>::value> {};

template<>
struct has_bounded_size<aruco_msgs::msg::Marker>
  : std::integral_constant<bool, has_bounded_size<geometry_msgs::msg::PoseWithCovariance>::value && has_bounded_size<std_msgs::msg::Header>::value> {};

template<>
struct is_message<aruco_msgs::msg::Marker>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // ARUCO_MSGS__MSG__DETAIL__MARKER__TRAITS_HPP_
