// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from urc_msgs:msg/LandingLocations.idl
// generated code does not contain a copyright notice

#ifndef URC_MSGS__MSG__DETAIL__LANDING_LOCATIONS__TRAITS_HPP_
#define URC_MSGS__MSG__DETAIL__LANDING_LOCATIONS__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "urc_msgs/msg/detail/landing_locations__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__traits.hpp"

namespace urc_msgs
{

namespace msg
{

inline void to_flow_style_yaml(
  const LandingLocations & msg,
  std::ostream & out)
{
  out << "{";
  // member: header
  {
    out << "header: ";
    to_flow_style_yaml(msg.header, out);
    out << ", ";
  }

  // member: num_locations
  {
    out << "num_locations: ";
    rosidl_generator_traits::value_to_yaml(msg.num_locations, out);
    out << ", ";
  }

  // member: latitudes
  {
    if (msg.latitudes.size() == 0) {
      out << "latitudes: []";
    } else {
      out << "latitudes: [";
      size_t pending_items = msg.latitudes.size();
      for (auto item : msg.latitudes) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: longitudes
  {
    if (msg.longitudes.size() == 0) {
      out << "longitudes: []";
    } else {
      out << "longitudes: [";
      size_t pending_items = msg.longitudes.size();
      for (auto item : msg.longitudes) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const LandingLocations & msg,
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

  // member: num_locations
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "num_locations: ";
    rosidl_generator_traits::value_to_yaml(msg.num_locations, out);
    out << "\n";
  }

  // member: latitudes
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.latitudes.size() == 0) {
      out << "latitudes: []\n";
    } else {
      out << "latitudes:\n";
      for (auto item : msg.latitudes) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: longitudes
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.longitudes.size() == 0) {
      out << "longitudes: []\n";
    } else {
      out << "longitudes:\n";
      for (auto item : msg.longitudes) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const LandingLocations & msg, bool use_flow_style = false)
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
  const urc_msgs::msg::LandingLocations & msg,
  std::ostream & out, size_t indentation = 0)
{
  urc_msgs::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use urc_msgs::msg::to_yaml() instead")]]
inline std::string to_yaml(const urc_msgs::msg::LandingLocations & msg)
{
  return urc_msgs::msg::to_yaml(msg);
}

template<>
inline const char * data_type<urc_msgs::msg::LandingLocations>()
{
  return "urc_msgs::msg::LandingLocations";
}

template<>
inline const char * name<urc_msgs::msg::LandingLocations>()
{
  return "urc_msgs/msg/LandingLocations";
}

template<>
struct has_fixed_size<urc_msgs::msg::LandingLocations>
  : std::integral_constant<bool, has_fixed_size<std_msgs::msg::Header>::value> {};

template<>
struct has_bounded_size<urc_msgs::msg::LandingLocations>
  : std::integral_constant<bool, has_bounded_size<std_msgs::msg::Header>::value> {};

template<>
struct is_message<urc_msgs::msg::LandingLocations>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // URC_MSGS__MSG__DETAIL__LANDING_LOCATIONS__TRAITS_HPP_
