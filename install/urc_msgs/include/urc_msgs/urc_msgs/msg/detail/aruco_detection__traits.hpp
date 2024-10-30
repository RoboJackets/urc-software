// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from urc_msgs:msg/ArucoDetection.idl
// generated code does not contain a copyright notice

#ifndef URC_MSGS__MSG__DETAIL__ARUCO_DETECTION__TRAITS_HPP_
#define URC_MSGS__MSG__DETAIL__ARUCO_DETECTION__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "urc_msgs/msg/detail/aruco_detection__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__traits.hpp"

namespace urc_msgs
{

namespace msg
{

inline void to_flow_style_yaml(
  const ArucoDetection & msg,
  std::ostream & out)
{
  out << "{";
  // member: header
  {
    out << "header: ";
    to_flow_style_yaml(msg.header, out);
    out << ", ";
  }

  // member: x_angle
  {
    out << "x_angle: ";
    rosidl_generator_traits::value_to_yaml(msg.x_angle, out);
    out << ", ";
  }

  // member: y_angle
  {
    out << "y_angle: ";
    rosidl_generator_traits::value_to_yaml(msg.y_angle, out);
    out << ", ";
  }

  // member: distance
  {
    out << "distance: ";
    rosidl_generator_traits::value_to_yaml(msg.distance, out);
    out << ", ";
  }

  // member: id
  {
    out << "id: ";
    rosidl_generator_traits::value_to_yaml(msg.id, out);
    out << ", ";
  }

  // member: which_camera
  {
    out << "which_camera: ";
    rosidl_generator_traits::value_to_yaml(msg.which_camera, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const ArucoDetection & msg,
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

  // member: x_angle
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "x_angle: ";
    rosidl_generator_traits::value_to_yaml(msg.x_angle, out);
    out << "\n";
  }

  // member: y_angle
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "y_angle: ";
    rosidl_generator_traits::value_to_yaml(msg.y_angle, out);
    out << "\n";
  }

  // member: distance
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "distance: ";
    rosidl_generator_traits::value_to_yaml(msg.distance, out);
    out << "\n";
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

  // member: which_camera
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "which_camera: ";
    rosidl_generator_traits::value_to_yaml(msg.which_camera, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const ArucoDetection & msg, bool use_flow_style = false)
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
  const urc_msgs::msg::ArucoDetection & msg,
  std::ostream & out, size_t indentation = 0)
{
  urc_msgs::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use urc_msgs::msg::to_yaml() instead")]]
inline std::string to_yaml(const urc_msgs::msg::ArucoDetection & msg)
{
  return urc_msgs::msg::to_yaml(msg);
}

template<>
inline const char * data_type<urc_msgs::msg::ArucoDetection>()
{
  return "urc_msgs::msg::ArucoDetection";
}

template<>
inline const char * name<urc_msgs::msg::ArucoDetection>()
{
  return "urc_msgs/msg/ArucoDetection";
}

template<>
struct has_fixed_size<urc_msgs::msg::ArucoDetection>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<urc_msgs::msg::ArucoDetection>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<urc_msgs::msg::ArucoDetection>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // URC_MSGS__MSG__DETAIL__ARUCO_DETECTION__TRAITS_HPP_
