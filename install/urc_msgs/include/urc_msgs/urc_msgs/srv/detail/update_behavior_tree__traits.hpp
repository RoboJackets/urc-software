// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from urc_msgs:srv/UpdateBehaviorTree.idl
// generated code does not contain a copyright notice

#ifndef URC_MSGS__SRV__DETAIL__UPDATE_BEHAVIOR_TREE__TRAITS_HPP_
#define URC_MSGS__SRV__DETAIL__UPDATE_BEHAVIOR_TREE__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "urc_msgs/srv/detail/update_behavior_tree__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace urc_msgs
{

namespace srv
{

inline void to_flow_style_yaml(
  const UpdateBehaviorTree_Request & msg,
  std::ostream & out)
{
  out << "{";
  // member: tree_content
  {
    out << "tree_content: ";
    rosidl_generator_traits::value_to_yaml(msg.tree_content, out);
    out << ", ";
  }

  // member: tree_dir
  {
    out << "tree_dir: ";
    rosidl_generator_traits::value_to_yaml(msg.tree_dir, out);
    out << ", ";
  }

  // member: use_dir
  {
    out << "use_dir: ";
    rosidl_generator_traits::value_to_yaml(msg.use_dir, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const UpdateBehaviorTree_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: tree_content
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "tree_content: ";
    rosidl_generator_traits::value_to_yaml(msg.tree_content, out);
    out << "\n";
  }

  // member: tree_dir
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "tree_dir: ";
    rosidl_generator_traits::value_to_yaml(msg.tree_dir, out);
    out << "\n";
  }

  // member: use_dir
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "use_dir: ";
    rosidl_generator_traits::value_to_yaml(msg.use_dir, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const UpdateBehaviorTree_Request & msg, bool use_flow_style = false)
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
  const urc_msgs::srv::UpdateBehaviorTree_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  urc_msgs::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use urc_msgs::srv::to_yaml() instead")]]
inline std::string to_yaml(const urc_msgs::srv::UpdateBehaviorTree_Request & msg)
{
  return urc_msgs::srv::to_yaml(msg);
}

template<>
inline const char * data_type<urc_msgs::srv::UpdateBehaviorTree_Request>()
{
  return "urc_msgs::srv::UpdateBehaviorTree_Request";
}

template<>
inline const char * name<urc_msgs::srv::UpdateBehaviorTree_Request>()
{
  return "urc_msgs/srv/UpdateBehaviorTree_Request";
}

template<>
struct has_fixed_size<urc_msgs::srv::UpdateBehaviorTree_Request>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<urc_msgs::srv::UpdateBehaviorTree_Request>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<urc_msgs::srv::UpdateBehaviorTree_Request>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace urc_msgs
{

namespace srv
{

inline void to_flow_style_yaml(
  const UpdateBehaviorTree_Response & msg,
  std::ostream & out)
{
  out << "{";
  // member: success
  {
    out << "success: ";
    rosidl_generator_traits::value_to_yaml(msg.success, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const UpdateBehaviorTree_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: success
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "success: ";
    rosidl_generator_traits::value_to_yaml(msg.success, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const UpdateBehaviorTree_Response & msg, bool use_flow_style = false)
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
  const urc_msgs::srv::UpdateBehaviorTree_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  urc_msgs::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use urc_msgs::srv::to_yaml() instead")]]
inline std::string to_yaml(const urc_msgs::srv::UpdateBehaviorTree_Response & msg)
{
  return urc_msgs::srv::to_yaml(msg);
}

template<>
inline const char * data_type<urc_msgs::srv::UpdateBehaviorTree_Response>()
{
  return "urc_msgs::srv::UpdateBehaviorTree_Response";
}

template<>
inline const char * name<urc_msgs::srv::UpdateBehaviorTree_Response>()
{
  return "urc_msgs/srv/UpdateBehaviorTree_Response";
}

template<>
struct has_fixed_size<urc_msgs::srv::UpdateBehaviorTree_Response>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<urc_msgs::srv::UpdateBehaviorTree_Response>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<urc_msgs::srv::UpdateBehaviorTree_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<urc_msgs::srv::UpdateBehaviorTree>()
{
  return "urc_msgs::srv::UpdateBehaviorTree";
}

template<>
inline const char * name<urc_msgs::srv::UpdateBehaviorTree>()
{
  return "urc_msgs/srv/UpdateBehaviorTree";
}

template<>
struct has_fixed_size<urc_msgs::srv::UpdateBehaviorTree>
  : std::integral_constant<
    bool,
    has_fixed_size<urc_msgs::srv::UpdateBehaviorTree_Request>::value &&
    has_fixed_size<urc_msgs::srv::UpdateBehaviorTree_Response>::value
  >
{
};

template<>
struct has_bounded_size<urc_msgs::srv::UpdateBehaviorTree>
  : std::integral_constant<
    bool,
    has_bounded_size<urc_msgs::srv::UpdateBehaviorTree_Request>::value &&
    has_bounded_size<urc_msgs::srv::UpdateBehaviorTree_Response>::value
  >
{
};

template<>
struct is_service<urc_msgs::srv::UpdateBehaviorTree>
  : std::true_type
{
};

template<>
struct is_service_request<urc_msgs::srv::UpdateBehaviorTree_Request>
  : std::true_type
{
};

template<>
struct is_service_response<urc_msgs::srv::UpdateBehaviorTree_Response>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits

#endif  // URC_MSGS__SRV__DETAIL__UPDATE_BEHAVIOR_TREE__TRAITS_HPP_
