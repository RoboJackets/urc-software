// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from urc_msgs:srv/GeneratePlan.idl
// generated code does not contain a copyright notice

#ifndef URC_MSGS__SRV__DETAIL__GENERATE_PLAN__TRAITS_HPP_
#define URC_MSGS__SRV__DETAIL__GENERATE_PLAN__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "urc_msgs/srv/detail/generate_plan__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'goal'
// Member 'start'
#include "geometry_msgs/msg/detail/pose_stamped__traits.hpp"

namespace urc_msgs
{

namespace srv
{

inline void to_flow_style_yaml(
  const GeneratePlan_Request & msg,
  std::ostream & out)
{
  out << "{";
  // member: goal
  {
    out << "goal: ";
    to_flow_style_yaml(msg.goal, out);
    out << ", ";
  }

  // member: start
  {
    out << "start: ";
    to_flow_style_yaml(msg.start, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const GeneratePlan_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: goal
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "goal:\n";
    to_block_style_yaml(msg.goal, out, indentation + 2);
  }

  // member: start
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "start:\n";
    to_block_style_yaml(msg.start, out, indentation + 2);
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const GeneratePlan_Request & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace srv

}  // namespace urc_msgs

namespace rosidl_generator_traits
{

[[deprecated("use urc_msgs::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const urc_msgs::srv::GeneratePlan_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  urc_msgs::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use urc_msgs::srv::to_yaml() instead")]]
inline std::string to_yaml(const urc_msgs::srv::GeneratePlan_Request & msg)
{
  return urc_msgs::srv::to_yaml(msg);
}

template<>
inline const char * data_type<urc_msgs::srv::GeneratePlan_Request>()
{
  return "urc_msgs::srv::GeneratePlan_Request";
}

template<>
inline const char * name<urc_msgs::srv::GeneratePlan_Request>()
{
  return "urc_msgs/srv/GeneratePlan_Request";
}

template<>
struct has_fixed_size<urc_msgs::srv::GeneratePlan_Request>
  : std::integral_constant<bool, has_fixed_size<geometry_msgs::msg::PoseStamped>::value> {};

template<>
struct has_bounded_size<urc_msgs::srv::GeneratePlan_Request>
  : std::integral_constant<bool, has_bounded_size<geometry_msgs::msg::PoseStamped>::value> {};

template<>
struct is_message<urc_msgs::srv::GeneratePlan_Request>
  : std::true_type {};

}  // namespace rosidl_generator_traits

// Include directives for member types
// Member 'path'
#include "nav_msgs/msg/detail/path__traits.hpp"

namespace urc_msgs
{

namespace srv
{

inline void to_flow_style_yaml(
  const GeneratePlan_Response & msg,
  std::ostream & out)
{
  out << "{";
  // member: path
  {
    out << "path: ";
    to_flow_style_yaml(msg.path, out);
    out << ", ";
  }

  // member: error_code
  {
    out << "error_code: ";
    rosidl_generator_traits::value_to_yaml(msg.error_code, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const GeneratePlan_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: path
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "path:\n";
    to_block_style_yaml(msg.path, out, indentation + 2);
  }

  // member: error_code
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "error_code: ";
    rosidl_generator_traits::value_to_yaml(msg.error_code, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const GeneratePlan_Response & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace srv

}  // namespace urc_msgs

namespace rosidl_generator_traits
{

[[deprecated("use urc_msgs::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const urc_msgs::srv::GeneratePlan_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  urc_msgs::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use urc_msgs::srv::to_yaml() instead")]]
inline std::string to_yaml(const urc_msgs::srv::GeneratePlan_Response & msg)
{
  return urc_msgs::srv::to_yaml(msg);
}

template<>
inline const char * data_type<urc_msgs::srv::GeneratePlan_Response>()
{
  return "urc_msgs::srv::GeneratePlan_Response";
}

template<>
inline const char * name<urc_msgs::srv::GeneratePlan_Response>()
{
  return "urc_msgs/srv/GeneratePlan_Response";
}

template<>
struct has_fixed_size<urc_msgs::srv::GeneratePlan_Response>
  : std::integral_constant<bool, has_fixed_size<nav_msgs::msg::Path>::value> {};

template<>
struct has_bounded_size<urc_msgs::srv::GeneratePlan_Response>
  : std::integral_constant<bool, has_bounded_size<nav_msgs::msg::Path>::value> {};

template<>
struct is_message<urc_msgs::srv::GeneratePlan_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<urc_msgs::srv::GeneratePlan>()
{
  return "urc_msgs::srv::GeneratePlan";
}

template<>
inline const char * name<urc_msgs::srv::GeneratePlan>()
{
  return "urc_msgs/srv/GeneratePlan";
}

template<>
struct has_fixed_size<urc_msgs::srv::GeneratePlan>
  : std::integral_constant<
    bool,
    has_fixed_size<urc_msgs::srv::GeneratePlan_Request>::value &&
    has_fixed_size<urc_msgs::srv::GeneratePlan_Response>::value
  >
{
};

template<>
struct has_bounded_size<urc_msgs::srv::GeneratePlan>
  : std::integral_constant<
    bool,
    has_bounded_size<urc_msgs::srv::GeneratePlan_Request>::value &&
    has_bounded_size<urc_msgs::srv::GeneratePlan_Response>::value
  >
{
};

template<>
struct is_service<urc_msgs::srv::GeneratePlan>
  : std::true_type
{
};

template<>
struct is_service_request<urc_msgs::srv::GeneratePlan_Request>
  : std::true_type
{
};

template<>
struct is_service_response<urc_msgs::srv::GeneratePlan_Response>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits

#endif  // URC_MSGS__SRV__DETAIL__GENERATE_PLAN__TRAITS_HPP_
