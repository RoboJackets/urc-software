// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from urc_msgs:action/NavigateToWaypoint.idl
// generated code does not contain a copyright notice

#ifndef URC_MSGS__ACTION__DETAIL__NAVIGATE_TO_WAYPOINT__TRAITS_HPP_
#define URC_MSGS__ACTION__DETAIL__NAVIGATE_TO_WAYPOINT__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "urc_msgs/action/detail/navigate_to_waypoint__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'path'
#include "nav_msgs/msg/detail/path__traits.hpp"
// Member 'goal'
#include "geometry_msgs/msg/detail/pose_stamped__traits.hpp"

namespace urc_msgs
{

namespace action
{

inline void to_flow_style_yaml(
  const NavigateToWaypoint_Goal & msg,
  std::ostream & out)
{
  out << "{";
  // member: path
  {
    out << "path: ";
    to_flow_style_yaml(msg.path, out);
    out << ", ";
  }

  // member: goal
  {
    out << "goal: ";
    to_flow_style_yaml(msg.goal, out);
    out << ", ";
  }

  // member: has_path
  {
    out << "has_path: ";
    rosidl_generator_traits::value_to_yaml(msg.has_path, out);
    out << ", ";
  }

  // member: has_goal
  {
    out << "has_goal: ";
    rosidl_generator_traits::value_to_yaml(msg.has_goal, out);
    out << ", ";
  }

  // member: enforce_goal_heading
  {
    out << "enforce_goal_heading: ";
    rosidl_generator_traits::value_to_yaml(msg.enforce_goal_heading, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const NavigateToWaypoint_Goal & msg,
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

  // member: goal
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "goal:\n";
    to_block_style_yaml(msg.goal, out, indentation + 2);
  }

  // member: has_path
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "has_path: ";
    rosidl_generator_traits::value_to_yaml(msg.has_path, out);
    out << "\n";
  }

  // member: has_goal
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "has_goal: ";
    rosidl_generator_traits::value_to_yaml(msg.has_goal, out);
    out << "\n";
  }

  // member: enforce_goal_heading
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "enforce_goal_heading: ";
    rosidl_generator_traits::value_to_yaml(msg.enforce_goal_heading, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const NavigateToWaypoint_Goal & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace action

}  // namespace urc_msgs

namespace rosidl_generator_traits
{

[[deprecated("use urc_msgs::action::to_block_style_yaml() instead")]]
inline void to_yaml(
  const urc_msgs::action::NavigateToWaypoint_Goal & msg,
  std::ostream & out, size_t indentation = 0)
{
  urc_msgs::action::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use urc_msgs::action::to_yaml() instead")]]
inline std::string to_yaml(const urc_msgs::action::NavigateToWaypoint_Goal & msg)
{
  return urc_msgs::action::to_yaml(msg);
}

template<>
inline const char * data_type<urc_msgs::action::NavigateToWaypoint_Goal>()
{
  return "urc_msgs::action::NavigateToWaypoint_Goal";
}

template<>
inline const char * name<urc_msgs::action::NavigateToWaypoint_Goal>()
{
  return "urc_msgs/action/NavigateToWaypoint_Goal";
}

template<>
struct has_fixed_size<urc_msgs::action::NavigateToWaypoint_Goal>
  : std::integral_constant<bool, has_fixed_size<geometry_msgs::msg::PoseStamped>::value && has_fixed_size<nav_msgs::msg::Path>::value> {};

template<>
struct has_bounded_size<urc_msgs::action::NavigateToWaypoint_Goal>
  : std::integral_constant<bool, has_bounded_size<geometry_msgs::msg::PoseStamped>::value && has_bounded_size<nav_msgs::msg::Path>::value> {};

template<>
struct is_message<urc_msgs::action::NavigateToWaypoint_Goal>
  : std::true_type {};

}  // namespace rosidl_generator_traits

// Include directives for member types
// Member 'result'
#include "std_msgs/msg/detail/empty__traits.hpp"

namespace urc_msgs
{

namespace action
{

inline void to_flow_style_yaml(
  const NavigateToWaypoint_Result & msg,
  std::ostream & out)
{
  out << "{";
  // member: result
  {
    out << "result: ";
    to_flow_style_yaml(msg.result, out);
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
  const NavigateToWaypoint_Result & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: result
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "result:\n";
    to_block_style_yaml(msg.result, out, indentation + 2);
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

inline std::string to_yaml(const NavigateToWaypoint_Result & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace action

}  // namespace urc_msgs

namespace rosidl_generator_traits
{

[[deprecated("use urc_msgs::action::to_block_style_yaml() instead")]]
inline void to_yaml(
  const urc_msgs::action::NavigateToWaypoint_Result & msg,
  std::ostream & out, size_t indentation = 0)
{
  urc_msgs::action::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use urc_msgs::action::to_yaml() instead")]]
inline std::string to_yaml(const urc_msgs::action::NavigateToWaypoint_Result & msg)
{
  return urc_msgs::action::to_yaml(msg);
}

template<>
inline const char * data_type<urc_msgs::action::NavigateToWaypoint_Result>()
{
  return "urc_msgs::action::NavigateToWaypoint_Result";
}

template<>
inline const char * name<urc_msgs::action::NavigateToWaypoint_Result>()
{
  return "urc_msgs/action/NavigateToWaypoint_Result";
}

template<>
struct has_fixed_size<urc_msgs::action::NavigateToWaypoint_Result>
  : std::integral_constant<bool, has_fixed_size<std_msgs::msg::Empty>::value> {};

template<>
struct has_bounded_size<urc_msgs::action::NavigateToWaypoint_Result>
  : std::integral_constant<bool, has_bounded_size<std_msgs::msg::Empty>::value> {};

template<>
struct is_message<urc_msgs::action::NavigateToWaypoint_Result>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace urc_msgs
{

namespace action
{

inline void to_flow_style_yaml(
  const NavigateToWaypoint_Feedback & msg,
  std::ostream & out)
{
  out << "{";
  // member: distance_to_goal
  {
    out << "distance_to_goal: ";
    rosidl_generator_traits::value_to_yaml(msg.distance_to_goal, out);
    out << ", ";
  }

  // member: is_planning
  {
    out << "is_planning: ";
    rosidl_generator_traits::value_to_yaml(msg.is_planning, out);
    out << ", ";
  }

  // member: replan_count
  {
    out << "replan_count: ";
    rosidl_generator_traits::value_to_yaml(msg.replan_count, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const NavigateToWaypoint_Feedback & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: distance_to_goal
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "distance_to_goal: ";
    rosidl_generator_traits::value_to_yaml(msg.distance_to_goal, out);
    out << "\n";
  }

  // member: is_planning
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "is_planning: ";
    rosidl_generator_traits::value_to_yaml(msg.is_planning, out);
    out << "\n";
  }

  // member: replan_count
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "replan_count: ";
    rosidl_generator_traits::value_to_yaml(msg.replan_count, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const NavigateToWaypoint_Feedback & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace action

}  // namespace urc_msgs

namespace rosidl_generator_traits
{

[[deprecated("use urc_msgs::action::to_block_style_yaml() instead")]]
inline void to_yaml(
  const urc_msgs::action::NavigateToWaypoint_Feedback & msg,
  std::ostream & out, size_t indentation = 0)
{
  urc_msgs::action::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use urc_msgs::action::to_yaml() instead")]]
inline std::string to_yaml(const urc_msgs::action::NavigateToWaypoint_Feedback & msg)
{
  return urc_msgs::action::to_yaml(msg);
}

template<>
inline const char * data_type<urc_msgs::action::NavigateToWaypoint_Feedback>()
{
  return "urc_msgs::action::NavigateToWaypoint_Feedback";
}

template<>
inline const char * name<urc_msgs::action::NavigateToWaypoint_Feedback>()
{
  return "urc_msgs/action/NavigateToWaypoint_Feedback";
}

template<>
struct has_fixed_size<urc_msgs::action::NavigateToWaypoint_Feedback>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<urc_msgs::action::NavigateToWaypoint_Feedback>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<urc_msgs::action::NavigateToWaypoint_Feedback>
  : std::true_type {};

}  // namespace rosidl_generator_traits

// Include directives for member types
// Member 'goal_id'
#include "unique_identifier_msgs/msg/detail/uuid__traits.hpp"
// Member 'goal'
#include "urc_msgs/action/detail/navigate_to_waypoint__traits.hpp"

namespace urc_msgs
{

namespace action
{

inline void to_flow_style_yaml(
  const NavigateToWaypoint_SendGoal_Request & msg,
  std::ostream & out)
{
  out << "{";
  // member: goal_id
  {
    out << "goal_id: ";
    to_flow_style_yaml(msg.goal_id, out);
    out << ", ";
  }

  // member: goal
  {
    out << "goal: ";
    to_flow_style_yaml(msg.goal, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const NavigateToWaypoint_SendGoal_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: goal_id
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "goal_id:\n";
    to_block_style_yaml(msg.goal_id, out, indentation + 2);
  }

  // member: goal
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "goal:\n";
    to_block_style_yaml(msg.goal, out, indentation + 2);
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const NavigateToWaypoint_SendGoal_Request & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace action

}  // namespace urc_msgs

namespace rosidl_generator_traits
{

[[deprecated("use urc_msgs::action::to_block_style_yaml() instead")]]
inline void to_yaml(
  const urc_msgs::action::NavigateToWaypoint_SendGoal_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  urc_msgs::action::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use urc_msgs::action::to_yaml() instead")]]
inline std::string to_yaml(const urc_msgs::action::NavigateToWaypoint_SendGoal_Request & msg)
{
  return urc_msgs::action::to_yaml(msg);
}

template<>
inline const char * data_type<urc_msgs::action::NavigateToWaypoint_SendGoal_Request>()
{
  return "urc_msgs::action::NavigateToWaypoint_SendGoal_Request";
}

template<>
inline const char * name<urc_msgs::action::NavigateToWaypoint_SendGoal_Request>()
{
  return "urc_msgs/action/NavigateToWaypoint_SendGoal_Request";
}

template<>
struct has_fixed_size<urc_msgs::action::NavigateToWaypoint_SendGoal_Request>
  : std::integral_constant<bool, has_fixed_size<unique_identifier_msgs::msg::UUID>::value && has_fixed_size<urc_msgs::action::NavigateToWaypoint_Goal>::value> {};

template<>
struct has_bounded_size<urc_msgs::action::NavigateToWaypoint_SendGoal_Request>
  : std::integral_constant<bool, has_bounded_size<unique_identifier_msgs::msg::UUID>::value && has_bounded_size<urc_msgs::action::NavigateToWaypoint_Goal>::value> {};

template<>
struct is_message<urc_msgs::action::NavigateToWaypoint_SendGoal_Request>
  : std::true_type {};

}  // namespace rosidl_generator_traits

// Include directives for member types
// Member 'stamp'
#include "builtin_interfaces/msg/detail/time__traits.hpp"

namespace urc_msgs
{

namespace action
{

inline void to_flow_style_yaml(
  const NavigateToWaypoint_SendGoal_Response & msg,
  std::ostream & out)
{
  out << "{";
  // member: accepted
  {
    out << "accepted: ";
    rosidl_generator_traits::value_to_yaml(msg.accepted, out);
    out << ", ";
  }

  // member: stamp
  {
    out << "stamp: ";
    to_flow_style_yaml(msg.stamp, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const NavigateToWaypoint_SendGoal_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: accepted
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "accepted: ";
    rosidl_generator_traits::value_to_yaml(msg.accepted, out);
    out << "\n";
  }

  // member: stamp
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "stamp:\n";
    to_block_style_yaml(msg.stamp, out, indentation + 2);
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const NavigateToWaypoint_SendGoal_Response & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace action

}  // namespace urc_msgs

namespace rosidl_generator_traits
{

[[deprecated("use urc_msgs::action::to_block_style_yaml() instead")]]
inline void to_yaml(
  const urc_msgs::action::NavigateToWaypoint_SendGoal_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  urc_msgs::action::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use urc_msgs::action::to_yaml() instead")]]
inline std::string to_yaml(const urc_msgs::action::NavigateToWaypoint_SendGoal_Response & msg)
{
  return urc_msgs::action::to_yaml(msg);
}

template<>
inline const char * data_type<urc_msgs::action::NavigateToWaypoint_SendGoal_Response>()
{
  return "urc_msgs::action::NavigateToWaypoint_SendGoal_Response";
}

template<>
inline const char * name<urc_msgs::action::NavigateToWaypoint_SendGoal_Response>()
{
  return "urc_msgs/action/NavigateToWaypoint_SendGoal_Response";
}

template<>
struct has_fixed_size<urc_msgs::action::NavigateToWaypoint_SendGoal_Response>
  : std::integral_constant<bool, has_fixed_size<builtin_interfaces::msg::Time>::value> {};

template<>
struct has_bounded_size<urc_msgs::action::NavigateToWaypoint_SendGoal_Response>
  : std::integral_constant<bool, has_bounded_size<builtin_interfaces::msg::Time>::value> {};

template<>
struct is_message<urc_msgs::action::NavigateToWaypoint_SendGoal_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<urc_msgs::action::NavigateToWaypoint_SendGoal>()
{
  return "urc_msgs::action::NavigateToWaypoint_SendGoal";
}

template<>
inline const char * name<urc_msgs::action::NavigateToWaypoint_SendGoal>()
{
  return "urc_msgs/action/NavigateToWaypoint_SendGoal";
}

template<>
struct has_fixed_size<urc_msgs::action::NavigateToWaypoint_SendGoal>
  : std::integral_constant<
    bool,
    has_fixed_size<urc_msgs::action::NavigateToWaypoint_SendGoal_Request>::value &&
    has_fixed_size<urc_msgs::action::NavigateToWaypoint_SendGoal_Response>::value
  >
{
};

template<>
struct has_bounded_size<urc_msgs::action::NavigateToWaypoint_SendGoal>
  : std::integral_constant<
    bool,
    has_bounded_size<urc_msgs::action::NavigateToWaypoint_SendGoal_Request>::value &&
    has_bounded_size<urc_msgs::action::NavigateToWaypoint_SendGoal_Response>::value
  >
{
};

template<>
struct is_service<urc_msgs::action::NavigateToWaypoint_SendGoal>
  : std::true_type
{
};

template<>
struct is_service_request<urc_msgs::action::NavigateToWaypoint_SendGoal_Request>
  : std::true_type
{
};

template<>
struct is_service_response<urc_msgs::action::NavigateToWaypoint_SendGoal_Response>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits

// Include directives for member types
// Member 'goal_id'
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__traits.hpp"

namespace urc_msgs
{

namespace action
{

inline void to_flow_style_yaml(
  const NavigateToWaypoint_GetResult_Request & msg,
  std::ostream & out)
{
  out << "{";
  // member: goal_id
  {
    out << "goal_id: ";
    to_flow_style_yaml(msg.goal_id, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const NavigateToWaypoint_GetResult_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: goal_id
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "goal_id:\n";
    to_block_style_yaml(msg.goal_id, out, indentation + 2);
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const NavigateToWaypoint_GetResult_Request & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace action

}  // namespace urc_msgs

namespace rosidl_generator_traits
{

[[deprecated("use urc_msgs::action::to_block_style_yaml() instead")]]
inline void to_yaml(
  const urc_msgs::action::NavigateToWaypoint_GetResult_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  urc_msgs::action::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use urc_msgs::action::to_yaml() instead")]]
inline std::string to_yaml(const urc_msgs::action::NavigateToWaypoint_GetResult_Request & msg)
{
  return urc_msgs::action::to_yaml(msg);
}

template<>
inline const char * data_type<urc_msgs::action::NavigateToWaypoint_GetResult_Request>()
{
  return "urc_msgs::action::NavigateToWaypoint_GetResult_Request";
}

template<>
inline const char * name<urc_msgs::action::NavigateToWaypoint_GetResult_Request>()
{
  return "urc_msgs/action/NavigateToWaypoint_GetResult_Request";
}

template<>
struct has_fixed_size<urc_msgs::action::NavigateToWaypoint_GetResult_Request>
  : std::integral_constant<bool, has_fixed_size<unique_identifier_msgs::msg::UUID>::value> {};

template<>
struct has_bounded_size<urc_msgs::action::NavigateToWaypoint_GetResult_Request>
  : std::integral_constant<bool, has_bounded_size<unique_identifier_msgs::msg::UUID>::value> {};

template<>
struct is_message<urc_msgs::action::NavigateToWaypoint_GetResult_Request>
  : std::true_type {};

}  // namespace rosidl_generator_traits

// Include directives for member types
// Member 'result'
// already included above
// #include "urc_msgs/action/detail/navigate_to_waypoint__traits.hpp"

namespace urc_msgs
{

namespace action
{

inline void to_flow_style_yaml(
  const NavigateToWaypoint_GetResult_Response & msg,
  std::ostream & out)
{
  out << "{";
  // member: status
  {
    out << "status: ";
    rosidl_generator_traits::value_to_yaml(msg.status, out);
    out << ", ";
  }

  // member: result
  {
    out << "result: ";
    to_flow_style_yaml(msg.result, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const NavigateToWaypoint_GetResult_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: status
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "status: ";
    rosidl_generator_traits::value_to_yaml(msg.status, out);
    out << "\n";
  }

  // member: result
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "result:\n";
    to_block_style_yaml(msg.result, out, indentation + 2);
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const NavigateToWaypoint_GetResult_Response & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace action

}  // namespace urc_msgs

namespace rosidl_generator_traits
{

[[deprecated("use urc_msgs::action::to_block_style_yaml() instead")]]
inline void to_yaml(
  const urc_msgs::action::NavigateToWaypoint_GetResult_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  urc_msgs::action::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use urc_msgs::action::to_yaml() instead")]]
inline std::string to_yaml(const urc_msgs::action::NavigateToWaypoint_GetResult_Response & msg)
{
  return urc_msgs::action::to_yaml(msg);
}

template<>
inline const char * data_type<urc_msgs::action::NavigateToWaypoint_GetResult_Response>()
{
  return "urc_msgs::action::NavigateToWaypoint_GetResult_Response";
}

template<>
inline const char * name<urc_msgs::action::NavigateToWaypoint_GetResult_Response>()
{
  return "urc_msgs/action/NavigateToWaypoint_GetResult_Response";
}

template<>
struct has_fixed_size<urc_msgs::action::NavigateToWaypoint_GetResult_Response>
  : std::integral_constant<bool, has_fixed_size<urc_msgs::action::NavigateToWaypoint_Result>::value> {};

template<>
struct has_bounded_size<urc_msgs::action::NavigateToWaypoint_GetResult_Response>
  : std::integral_constant<bool, has_bounded_size<urc_msgs::action::NavigateToWaypoint_Result>::value> {};

template<>
struct is_message<urc_msgs::action::NavigateToWaypoint_GetResult_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<urc_msgs::action::NavigateToWaypoint_GetResult>()
{
  return "urc_msgs::action::NavigateToWaypoint_GetResult";
}

template<>
inline const char * name<urc_msgs::action::NavigateToWaypoint_GetResult>()
{
  return "urc_msgs/action/NavigateToWaypoint_GetResult";
}

template<>
struct has_fixed_size<urc_msgs::action::NavigateToWaypoint_GetResult>
  : std::integral_constant<
    bool,
    has_fixed_size<urc_msgs::action::NavigateToWaypoint_GetResult_Request>::value &&
    has_fixed_size<urc_msgs::action::NavigateToWaypoint_GetResult_Response>::value
  >
{
};

template<>
struct has_bounded_size<urc_msgs::action::NavigateToWaypoint_GetResult>
  : std::integral_constant<
    bool,
    has_bounded_size<urc_msgs::action::NavigateToWaypoint_GetResult_Request>::value &&
    has_bounded_size<urc_msgs::action::NavigateToWaypoint_GetResult_Response>::value
  >
{
};

template<>
struct is_service<urc_msgs::action::NavigateToWaypoint_GetResult>
  : std::true_type
{
};

template<>
struct is_service_request<urc_msgs::action::NavigateToWaypoint_GetResult_Request>
  : std::true_type
{
};

template<>
struct is_service_response<urc_msgs::action::NavigateToWaypoint_GetResult_Response>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits

// Include directives for member types
// Member 'goal_id'
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__traits.hpp"
// Member 'feedback'
// already included above
// #include "urc_msgs/action/detail/navigate_to_waypoint__traits.hpp"

namespace urc_msgs
{

namespace action
{

inline void to_flow_style_yaml(
  const NavigateToWaypoint_FeedbackMessage & msg,
  std::ostream & out)
{
  out << "{";
  // member: goal_id
  {
    out << "goal_id: ";
    to_flow_style_yaml(msg.goal_id, out);
    out << ", ";
  }

  // member: feedback
  {
    out << "feedback: ";
    to_flow_style_yaml(msg.feedback, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const NavigateToWaypoint_FeedbackMessage & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: goal_id
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "goal_id:\n";
    to_block_style_yaml(msg.goal_id, out, indentation + 2);
  }

  // member: feedback
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "feedback:\n";
    to_block_style_yaml(msg.feedback, out, indentation + 2);
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const NavigateToWaypoint_FeedbackMessage & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace action

}  // namespace urc_msgs

namespace rosidl_generator_traits
{

[[deprecated("use urc_msgs::action::to_block_style_yaml() instead")]]
inline void to_yaml(
  const urc_msgs::action::NavigateToWaypoint_FeedbackMessage & msg,
  std::ostream & out, size_t indentation = 0)
{
  urc_msgs::action::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use urc_msgs::action::to_yaml() instead")]]
inline std::string to_yaml(const urc_msgs::action::NavigateToWaypoint_FeedbackMessage & msg)
{
  return urc_msgs::action::to_yaml(msg);
}

template<>
inline const char * data_type<urc_msgs::action::NavigateToWaypoint_FeedbackMessage>()
{
  return "urc_msgs::action::NavigateToWaypoint_FeedbackMessage";
}

template<>
inline const char * name<urc_msgs::action::NavigateToWaypoint_FeedbackMessage>()
{
  return "urc_msgs/action/NavigateToWaypoint_FeedbackMessage";
}

template<>
struct has_fixed_size<urc_msgs::action::NavigateToWaypoint_FeedbackMessage>
  : std::integral_constant<bool, has_fixed_size<unique_identifier_msgs::msg::UUID>::value && has_fixed_size<urc_msgs::action::NavigateToWaypoint_Feedback>::value> {};

template<>
struct has_bounded_size<urc_msgs::action::NavigateToWaypoint_FeedbackMessage>
  : std::integral_constant<bool, has_bounded_size<unique_identifier_msgs::msg::UUID>::value && has_bounded_size<urc_msgs::action::NavigateToWaypoint_Feedback>::value> {};

template<>
struct is_message<urc_msgs::action::NavigateToWaypoint_FeedbackMessage>
  : std::true_type {};

}  // namespace rosidl_generator_traits


namespace rosidl_generator_traits
{

template<>
struct is_action<urc_msgs::action::NavigateToWaypoint>
  : std::true_type
{
};

template<>
struct is_action_goal<urc_msgs::action::NavigateToWaypoint_Goal>
  : std::true_type
{
};

template<>
struct is_action_result<urc_msgs::action::NavigateToWaypoint_Result>
  : std::true_type
{
};

template<>
struct is_action_feedback<urc_msgs::action::NavigateToWaypoint_Feedback>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits


#endif  // URC_MSGS__ACTION__DETAIL__NAVIGATE_TO_WAYPOINT__TRAITS_HPP_
