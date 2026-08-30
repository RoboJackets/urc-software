// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from vectornav_msgs:msg/AttitudeGroup.idl
// generated code does not contain a copyright notice

#ifndef VECTORNAV_MSGS__MSG__DETAIL__ATTITUDE_GROUP__TRAITS_HPP_
#define VECTORNAV_MSGS__MSG__DETAIL__ATTITUDE_GROUP__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "vectornav_msgs/msg/detail/attitude_group__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__traits.hpp"
// Member 'vpestatus'
#include "vectornav_msgs/msg/detail/vpe_status__traits.hpp"
// Member 'yawpitchroll'
// Member 'magned'
// Member 'accelned'
// Member 'linearaccelbody'
// Member 'linearaccelned'
// Member 'ypru'
#include "geometry_msgs/msg/detail/vector3__traits.hpp"
// Member 'quaternion'
#include "geometry_msgs/msg/detail/quaternion__traits.hpp"

namespace vectornav_msgs
{

namespace msg
{

inline void to_flow_style_yaml(
  const AttitudeGroup & msg,
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

  // member: vpestatus
  {
    out << "vpestatus: ";
    to_flow_style_yaml(msg.vpestatus, out);
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

  // member: dcm
  {
    if (msg.dcm.size() == 0) {
      out << "dcm: []";
    } else {
      out << "dcm: [";
      size_t pending_items = msg.dcm.size();
      for (auto item : msg.dcm) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: magned
  {
    out << "magned: ";
    to_flow_style_yaml(msg.magned, out);
    out << ", ";
  }

  // member: accelned
  {
    out << "accelned: ";
    to_flow_style_yaml(msg.accelned, out);
    out << ", ";
  }

  // member: linearaccelbody
  {
    out << "linearaccelbody: ";
    to_flow_style_yaml(msg.linearaccelbody, out);
    out << ", ";
  }

  // member: linearaccelned
  {
    out << "linearaccelned: ";
    to_flow_style_yaml(msg.linearaccelned, out);
    out << ", ";
  }

  // member: ypru
  {
    out << "ypru: ";
    to_flow_style_yaml(msg.ypru, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const AttitudeGroup & msg,
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

  // member: vpestatus
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "vpestatus:\n";
    to_block_style_yaml(msg.vpestatus, out, indentation + 2);
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

  // member: dcm
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.dcm.size() == 0) {
      out << "dcm: []\n";
    } else {
      out << "dcm:\n";
      for (auto item : msg.dcm) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: magned
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "magned:\n";
    to_block_style_yaml(msg.magned, out, indentation + 2);
  }

  // member: accelned
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "accelned:\n";
    to_block_style_yaml(msg.accelned, out, indentation + 2);
  }

  // member: linearaccelbody
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "linearaccelbody:\n";
    to_block_style_yaml(msg.linearaccelbody, out, indentation + 2);
  }

  // member: linearaccelned
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "linearaccelned:\n";
    to_block_style_yaml(msg.linearaccelned, out, indentation + 2);
  }

  // member: ypru
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "ypru:\n";
    to_block_style_yaml(msg.ypru, out, indentation + 2);
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const AttitudeGroup & msg, bool use_flow_style = false)
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
  const vectornav_msgs::msg::AttitudeGroup & msg,
  std::ostream & out, size_t indentation = 0)
{
  vectornav_msgs::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use vectornav_msgs::msg::to_yaml() instead")]]
inline std::string to_yaml(const vectornav_msgs::msg::AttitudeGroup & msg)
{
  return vectornav_msgs::msg::to_yaml(msg);
}

template<>
inline const char * data_type<vectornav_msgs::msg::AttitudeGroup>()
{
  return "vectornav_msgs::msg::AttitudeGroup";
}

template<>
inline const char * name<vectornav_msgs::msg::AttitudeGroup>()
{
  return "vectornav_msgs/msg/AttitudeGroup";
}

template<>
struct has_fixed_size<vectornav_msgs::msg::AttitudeGroup>
  : std::integral_constant<bool, has_fixed_size<geometry_msgs::msg::Quaternion>::value && has_fixed_size<geometry_msgs::msg::Vector3>::value && has_fixed_size<std_msgs::msg::Header>::value && has_fixed_size<vectornav_msgs::msg::VpeStatus>::value> {};

template<>
struct has_bounded_size<vectornav_msgs::msg::AttitudeGroup>
  : std::integral_constant<bool, has_bounded_size<geometry_msgs::msg::Quaternion>::value && has_bounded_size<geometry_msgs::msg::Vector3>::value && has_bounded_size<std_msgs::msg::Header>::value && has_bounded_size<vectornav_msgs::msg::VpeStatus>::value> {};

template<>
struct is_message<vectornav_msgs::msg::AttitudeGroup>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // VECTORNAV_MSGS__MSG__DETAIL__ATTITUDE_GROUP__TRAITS_HPP_
