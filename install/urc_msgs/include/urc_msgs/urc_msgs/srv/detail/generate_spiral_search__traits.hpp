// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from urc_msgs:srv/GenerateSpiralSearch.idl
// generated code does not contain a copyright notice

#ifndef URC_MSGS__SRV__DETAIL__GENERATE_SPIRAL_SEARCH__TRAITS_HPP_
#define URC_MSGS__SRV__DETAIL__GENERATE_SPIRAL_SEARCH__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "urc_msgs/srv/detail/generate_spiral_search__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'center'
#include "geometry_msgs/msg/detail/pose_stamped__traits.hpp"

namespace urc_msgs
{

namespace srv
{

inline void to_flow_style_yaml(
  const GenerateSpiralSearch_Request & msg,
  std::ostream & out)
{
  out << "{";
  // member: center
  {
    out << "center: ";
    to_flow_style_yaml(msg.center, out);
    out << ", ";
  }

  // member: search_radius
  {
    out << "search_radius: ";
    rosidl_generator_traits::value_to_yaml(msg.search_radius, out);
    out << ", ";
  }

  // member: track_spacing
  {
    out << "track_spacing: ";
    rosidl_generator_traits::value_to_yaml(msg.track_spacing, out);
    out << ", ";
  }

  // member: waypoint_spacing
  {
    out << "waypoint_spacing: ";
    rosidl_generator_traits::value_to_yaml(msg.waypoint_spacing, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const GenerateSpiralSearch_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: center
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "center:\n";
    to_block_style_yaml(msg.center, out, indentation + 2);
  }

  // member: search_radius
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "search_radius: ";
    rosidl_generator_traits::value_to_yaml(msg.search_radius, out);
    out << "\n";
  }

  // member: track_spacing
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "track_spacing: ";
    rosidl_generator_traits::value_to_yaml(msg.track_spacing, out);
    out << "\n";
  }

  // member: waypoint_spacing
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "waypoint_spacing: ";
    rosidl_generator_traits::value_to_yaml(msg.waypoint_spacing, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const GenerateSpiralSearch_Request & msg, bool use_flow_style = false)
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
  const urc_msgs::srv::GenerateSpiralSearch_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  urc_msgs::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use urc_msgs::srv::to_yaml() instead")]]
inline std::string to_yaml(const urc_msgs::srv::GenerateSpiralSearch_Request & msg)
{
  return urc_msgs::srv::to_yaml(msg);
}

template<>
inline const char * data_type<urc_msgs::srv::GenerateSpiralSearch_Request>()
{
  return "urc_msgs::srv::GenerateSpiralSearch_Request";
}

template<>
inline const char * name<urc_msgs::srv::GenerateSpiralSearch_Request>()
{
  return "urc_msgs/srv/GenerateSpiralSearch_Request";
}

template<>
struct has_fixed_size<urc_msgs::srv::GenerateSpiralSearch_Request>
  : std::integral_constant<bool, has_fixed_size<geometry_msgs::msg::PoseStamped>::value> {};

template<>
struct has_bounded_size<urc_msgs::srv::GenerateSpiralSearch_Request>
  : std::integral_constant<bool, has_bounded_size<geometry_msgs::msg::PoseStamped>::value> {};

template<>
struct is_message<urc_msgs::srv::GenerateSpiralSearch_Request>
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
  const GenerateSpiralSearch_Response & msg,
  std::ostream & out)
{
  out << "{";
  // member: path
  {
    out << "path: ";
    to_flow_style_yaml(msg.path, out);
    out << ", ";
  }

  // member: track_spacing
  {
    out << "track_spacing: ";
    rosidl_generator_traits::value_to_yaml(msg.track_spacing, out);
    out << ", ";
  }

  // member: path_length
  {
    out << "path_length: ";
    rosidl_generator_traits::value_to_yaml(msg.path_length, out);
    out << ", ";
  }

  // member: traversability_checked
  {
    out << "traversability_checked: ";
    rosidl_generator_traits::value_to_yaml(msg.traversability_checked, out);
    out << ", ";
  }

  // member: truncated
  {
    out << "truncated: ";
    rosidl_generator_traits::value_to_yaml(msg.truncated, out);
    out << ", ";
  }

  // member: skipped_waypoints
  {
    out << "skipped_waypoints: ";
    rosidl_generator_traits::value_to_yaml(msg.skipped_waypoints, out);
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
  const GenerateSpiralSearch_Response & msg,
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

  // member: track_spacing
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "track_spacing: ";
    rosidl_generator_traits::value_to_yaml(msg.track_spacing, out);
    out << "\n";
  }

  // member: path_length
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "path_length: ";
    rosidl_generator_traits::value_to_yaml(msg.path_length, out);
    out << "\n";
  }

  // member: traversability_checked
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "traversability_checked: ";
    rosidl_generator_traits::value_to_yaml(msg.traversability_checked, out);
    out << "\n";
  }

  // member: truncated
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "truncated: ";
    rosidl_generator_traits::value_to_yaml(msg.truncated, out);
    out << "\n";
  }

  // member: skipped_waypoints
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "skipped_waypoints: ";
    rosidl_generator_traits::value_to_yaml(msg.skipped_waypoints, out);
    out << "\n";
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

inline std::string to_yaml(const GenerateSpiralSearch_Response & msg, bool use_flow_style = false)
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
  const urc_msgs::srv::GenerateSpiralSearch_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  urc_msgs::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use urc_msgs::srv::to_yaml() instead")]]
inline std::string to_yaml(const urc_msgs::srv::GenerateSpiralSearch_Response & msg)
{
  return urc_msgs::srv::to_yaml(msg);
}

template<>
inline const char * data_type<urc_msgs::srv::GenerateSpiralSearch_Response>()
{
  return "urc_msgs::srv::GenerateSpiralSearch_Response";
}

template<>
inline const char * name<urc_msgs::srv::GenerateSpiralSearch_Response>()
{
  return "urc_msgs/srv/GenerateSpiralSearch_Response";
}

template<>
struct has_fixed_size<urc_msgs::srv::GenerateSpiralSearch_Response>
  : std::integral_constant<bool, has_fixed_size<nav_msgs::msg::Path>::value> {};

template<>
struct has_bounded_size<urc_msgs::srv::GenerateSpiralSearch_Response>
  : std::integral_constant<bool, has_bounded_size<nav_msgs::msg::Path>::value> {};

template<>
struct is_message<urc_msgs::srv::GenerateSpiralSearch_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<urc_msgs::srv::GenerateSpiralSearch>()
{
  return "urc_msgs::srv::GenerateSpiralSearch";
}

template<>
inline const char * name<urc_msgs::srv::GenerateSpiralSearch>()
{
  return "urc_msgs/srv/GenerateSpiralSearch";
}

template<>
struct has_fixed_size<urc_msgs::srv::GenerateSpiralSearch>
  : std::integral_constant<
    bool,
    has_fixed_size<urc_msgs::srv::GenerateSpiralSearch_Request>::value &&
    has_fixed_size<urc_msgs::srv::GenerateSpiralSearch_Response>::value
  >
{
};

template<>
struct has_bounded_size<urc_msgs::srv::GenerateSpiralSearch>
  : std::integral_constant<
    bool,
    has_bounded_size<urc_msgs::srv::GenerateSpiralSearch_Request>::value &&
    has_bounded_size<urc_msgs::srv::GenerateSpiralSearch_Response>::value
  >
{
};

template<>
struct is_service<urc_msgs::srv::GenerateSpiralSearch>
  : std::true_type
{
};

template<>
struct is_service_request<urc_msgs::srv::GenerateSpiralSearch_Request>
  : std::true_type
{
};

template<>
struct is_service_response<urc_msgs::srv::GenerateSpiralSearch_Response>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits

#endif  // URC_MSGS__SRV__DETAIL__GENERATE_SPIRAL_SEARCH__TRAITS_HPP_
