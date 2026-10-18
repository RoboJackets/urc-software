// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from vectornav_msgs:msg/CommonGroup.idl
// generated code does not contain a copyright notice

#ifndef VECTORNAV_MSGS__MSG__DETAIL__COMMON_GROUP__TRAITS_HPP_
#define VECTORNAV_MSGS__MSG__DETAIL__COMMON_GROUP__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "vectornav_msgs/msg/detail/common_group__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__traits.hpp"
// Member 'yawpitchroll'
// Member 'angularrate'
// Member 'velocity'
// Member 'accel'
// Member 'imu_accel'
// Member 'imu_rate'
// Member 'magpres_mag'
// Member 'deltatheta_dtheta'
// Member 'deltatheta_dvel'
#include "geometry_msgs/msg/detail/vector3__traits.hpp"
// Member 'quaternion'
#include "geometry_msgs/msg/detail/quaternion__traits.hpp"
// Member 'position'
#include "geometry_msgs/msg/detail/point__traits.hpp"
// Member 'insstatus'
#include "vectornav_msgs/msg/detail/ins_status__traits.hpp"

namespace vectornav_msgs
{

namespace msg
{

inline void to_flow_style_yaml(
  const CommonGroup & msg,
  std::ostream & out)
{
  out << "{";
  // member: header
  {
    out << "header: ";
    to_flow_style_yaml(msg.header, out);
    out << ", ";
  }

  // member: group_fields
  {
    out << "group_fields: ";
    rosidl_generator_traits::value_to_yaml(msg.group_fields, out);
    out << ", ";
  }

  // member: timestartup
  {
    out << "timestartup: ";
    rosidl_generator_traits::value_to_yaml(msg.timestartup, out);
    out << ", ";
  }

  // member: timegps
  {
    out << "timegps: ";
    rosidl_generator_traits::value_to_yaml(msg.timegps, out);
    out << ", ";
  }

  // member: timesyncin
  {
    out << "timesyncin: ";
    rosidl_generator_traits::value_to_yaml(msg.timesyncin, out);
    out << ", ";
  }

  // member: yawpitchroll
  {
    out << "yawpitchroll: ";
    to_flow_style_yaml(msg.yawpitchroll, out);
    out << ", ";
  }

  // member: quaternion
  {
    out << "quaternion: ";
    to_flow_style_yaml(msg.quaternion, out);
    out << ", ";
  }

  // member: angularrate
  {
    out << "angularrate: ";
    to_flow_style_yaml(msg.angularrate, out);
    out << ", ";
  }

  // member: position
  {
    out << "position: ";
    to_flow_style_yaml(msg.position, out);
    out << ", ";
  }

  // member: velocity
  {
    out << "velocity: ";
    to_flow_style_yaml(msg.velocity, out);
    out << ", ";
  }

  // member: accel
  {
    out << "accel: ";
    to_flow_style_yaml(msg.accel, out);
    out << ", ";
  }

  // member: imu_accel
  {
    out << "imu_accel: ";
    to_flow_style_yaml(msg.imu_accel, out);
    out << ", ";
  }

  // member: imu_rate
  {
    out << "imu_rate: ";
    to_flow_style_yaml(msg.imu_rate, out);
    out << ", ";
  }

  // member: magpres_mag
  {
    out << "magpres_mag: ";
    to_flow_style_yaml(msg.magpres_mag, out);
    out << ", ";
  }

  // member: magpres_temp
  {
    out << "magpres_temp: ";
    rosidl_generator_traits::value_to_yaml(msg.magpres_temp, out);
    out << ", ";
  }

  // member: magpres_pres
  {
    out << "magpres_pres: ";
    rosidl_generator_traits::value_to_yaml(msg.magpres_pres, out);
    out << ", ";
  }

  // member: deltatheta_dtime
  {
    out << "deltatheta_dtime: ";
    rosidl_generator_traits::value_to_yaml(msg.deltatheta_dtime, out);
    out << ", ";
  }

  // member: deltatheta_dtheta
  {
    out << "deltatheta_dtheta: ";
    to_flow_style_yaml(msg.deltatheta_dtheta, out);
    out << ", ";
  }

  // member: deltatheta_dvel
  {
    out << "deltatheta_dvel: ";
    to_flow_style_yaml(msg.deltatheta_dvel, out);
    out << ", ";
  }

  // member: insstatus
  {
    out << "insstatus: ";
    to_flow_style_yaml(msg.insstatus, out);
    out << ", ";
  }

  // member: syncincnt
  {
    out << "syncincnt: ";
    rosidl_generator_traits::value_to_yaml(msg.syncincnt, out);
    out << ", ";
  }

  // member: timegpspps
  {
    out << "timegpspps: ";
    rosidl_generator_traits::value_to_yaml(msg.timegpspps, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const CommonGroup & msg,
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

  // member: group_fields
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "group_fields: ";
    rosidl_generator_traits::value_to_yaml(msg.group_fields, out);
    out << "\n";
  }

  // member: timestartup
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "timestartup: ";
    rosidl_generator_traits::value_to_yaml(msg.timestartup, out);
    out << "\n";
  }

  // member: timegps
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "timegps: ";
    rosidl_generator_traits::value_to_yaml(msg.timegps, out);
    out << "\n";
  }

  // member: timesyncin
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "timesyncin: ";
    rosidl_generator_traits::value_to_yaml(msg.timesyncin, out);
    out << "\n";
  }

  // member: yawpitchroll
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "yawpitchroll:\n";
    to_block_style_yaml(msg.yawpitchroll, out, indentation + 2);
  }

  // member: quaternion
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "quaternion:\n";
    to_block_style_yaml(msg.quaternion, out, indentation + 2);
  }

  // member: angularrate
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "angularrate:\n";
    to_block_style_yaml(msg.angularrate, out, indentation + 2);
  }

  // member: position
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "position:\n";
    to_block_style_yaml(msg.position, out, indentation + 2);
  }

  // member: velocity
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "velocity:\n";
    to_block_style_yaml(msg.velocity, out, indentation + 2);
  }

  // member: accel
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "accel:\n";
    to_block_style_yaml(msg.accel, out, indentation + 2);
  }

  // member: imu_accel
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "imu_accel:\n";
    to_block_style_yaml(msg.imu_accel, out, indentation + 2);
  }

  // member: imu_rate
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "imu_rate:\n";
    to_block_style_yaml(msg.imu_rate, out, indentation + 2);
  }

  // member: magpres_mag
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "magpres_mag:\n";
    to_block_style_yaml(msg.magpres_mag, out, indentation + 2);
  }

  // member: magpres_temp
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "magpres_temp: ";
    rosidl_generator_traits::value_to_yaml(msg.magpres_temp, out);
    out << "\n";
  }

  // member: magpres_pres
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "magpres_pres: ";
    rosidl_generator_traits::value_to_yaml(msg.magpres_pres, out);
    out << "\n";
  }

  // member: deltatheta_dtime
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "deltatheta_dtime: ";
    rosidl_generator_traits::value_to_yaml(msg.deltatheta_dtime, out);
    out << "\n";
  }

  // member: deltatheta_dtheta
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "deltatheta_dtheta:\n";
    to_block_style_yaml(msg.deltatheta_dtheta, out, indentation + 2);
  }

  // member: deltatheta_dvel
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "deltatheta_dvel:\n";
    to_block_style_yaml(msg.deltatheta_dvel, out, indentation + 2);
  }

  // member: insstatus
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "insstatus:\n";
    to_block_style_yaml(msg.insstatus, out, indentation + 2);
  }

  // member: syncincnt
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "syncincnt: ";
    rosidl_generator_traits::value_to_yaml(msg.syncincnt, out);
    out << "\n";
  }

  // member: timegpspps
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "timegpspps: ";
    rosidl_generator_traits::value_to_yaml(msg.timegpspps, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const CommonGroup & msg, bool use_flow_style = false)
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
  const vectornav_msgs::msg::CommonGroup & msg,
  std::ostream & out, size_t indentation = 0)
{
  vectornav_msgs::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use vectornav_msgs::msg::to_yaml() instead")]]
inline std::string to_yaml(const vectornav_msgs::msg::CommonGroup & msg)
{
  return vectornav_msgs::msg::to_yaml(msg);
}

template<>
inline const char * data_type<vectornav_msgs::msg::CommonGroup>()
{
  return "vectornav_msgs::msg::CommonGroup";
}

template<>
inline const char * name<vectornav_msgs::msg::CommonGroup>()
{
  return "vectornav_msgs/msg/CommonGroup";
}

template<>
struct has_fixed_size<vectornav_msgs::msg::CommonGroup>
  : std::integral_constant<bool, has_fixed_size<geometry_msgs::msg::Point>::value && has_fixed_size<geometry_msgs::msg::Quaternion>::value && has_fixed_size<geometry_msgs::msg::Vector3>::value && has_fixed_size<std_msgs::msg::Header>::value && has_fixed_size<vectornav_msgs::msg::InsStatus>::value> {};

template<>
struct has_bounded_size<vectornav_msgs::msg::CommonGroup>
  : std::integral_constant<bool, has_bounded_size<geometry_msgs::msg::Point>::value && has_bounded_size<geometry_msgs::msg::Quaternion>::value && has_bounded_size<geometry_msgs::msg::Vector3>::value && has_bounded_size<std_msgs::msg::Header>::value && has_bounded_size<vectornav_msgs::msg::InsStatus>::value> {};

template<>
struct is_message<vectornav_msgs::msg::CommonGroup>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // VECTORNAV_MSGS__MSG__DETAIL__COMMON_GROUP__TRAITS_HPP_
