// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from vectornav_msgs:action/MagCal.idl
// generated code does not contain a copyright notice

#ifndef VECTORNAV_MSGS__ACTION__DETAIL__MAG_CAL__TRAITS_HPP_
#define VECTORNAV_MSGS__ACTION__DETAIL__MAG_CAL__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "vectornav_msgs/action/detail/mag_cal__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace vectornav_msgs
{

namespace action
{

inline void to_flow_style_yaml(
  const MagCal_Goal & msg,
  std::ostream & out)
{
  (void)msg;
  out << "null";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const MagCal_Goal & msg,
  std::ostream & out, size_t indentation = 0)
{
  (void)msg;
  (void)indentation;
  out << "null\n";
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const MagCal_Goal & msg, bool use_flow_style = false)
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

}  // namespace vectornav_msgs

namespace rosidl_generator_traits
{

[[deprecated("use vectornav_msgs::action::to_block_style_yaml() instead")]]
inline void to_yaml(
  const vectornav_msgs::action::MagCal_Goal & msg,
  std::ostream & out, size_t indentation = 0)
{
  vectornav_msgs::action::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use vectornav_msgs::action::to_yaml() instead")]]
inline std::string to_yaml(const vectornav_msgs::action::MagCal_Goal & msg)
{
  return vectornav_msgs::action::to_yaml(msg);
}

template<>
inline const char * data_type<vectornav_msgs::action::MagCal_Goal>()
{
  return "vectornav_msgs::action::MagCal_Goal";
}

template<>
inline const char * name<vectornav_msgs::action::MagCal_Goal>()
{
  return "vectornav_msgs/action/MagCal_Goal";
}

template<>
struct has_fixed_size<vectornav_msgs::action::MagCal_Goal>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<vectornav_msgs::action::MagCal_Goal>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<vectornav_msgs::action::MagCal_Goal>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace vectornav_msgs
{

namespace action
{

inline void to_flow_style_yaml(
  const MagCal_Result & msg,
  std::ostream & out)
{
  out << "{";
  // member: avg_dev
  {
    if (msg.avg_dev.size() == 0) {
      out << "avg_dev: []";
    } else {
      out << "avg_dev: [";
      size_t pending_items = msg.avg_dev.size();
      for (auto item : msg.avg_dev) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: calib
  {
    if (msg.calib.size() == 0) {
      out << "calib: []";
    } else {
      out << "calib: [";
      size_t pending_items = msg.calib.size();
      for (auto item : msg.calib) {
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
  const MagCal_Result & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: avg_dev
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.avg_dev.size() == 0) {
      out << "avg_dev: []\n";
    } else {
      out << "avg_dev:\n";
      for (auto item : msg.avg_dev) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: calib
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.calib.size() == 0) {
      out << "calib: []\n";
    } else {
      out << "calib:\n";
      for (auto item : msg.calib) {
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

inline std::string to_yaml(const MagCal_Result & msg, bool use_flow_style = false)
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

}  // namespace vectornav_msgs

namespace rosidl_generator_traits
{

[[deprecated("use vectornav_msgs::action::to_block_style_yaml() instead")]]
inline void to_yaml(
  const vectornav_msgs::action::MagCal_Result & msg,
  std::ostream & out, size_t indentation = 0)
{
  vectornav_msgs::action::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use vectornav_msgs::action::to_yaml() instead")]]
inline std::string to_yaml(const vectornav_msgs::action::MagCal_Result & msg)
{
  return vectornav_msgs::action::to_yaml(msg);
}

template<>
inline const char * data_type<vectornav_msgs::action::MagCal_Result>()
{
  return "vectornav_msgs::action::MagCal_Result";
}

template<>
inline const char * name<vectornav_msgs::action::MagCal_Result>()
{
  return "vectornav_msgs/action/MagCal_Result";
}

template<>
struct has_fixed_size<vectornav_msgs::action::MagCal_Result>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<vectornav_msgs::action::MagCal_Result>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<vectornav_msgs::action::MagCal_Result>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace vectornav_msgs
{

namespace action
{

inline void to_flow_style_yaml(
  const MagCal_Feedback & msg,
  std::ostream & out)
{
  out << "{";
  // member: curr_avg_dev
  {
    if (msg.curr_avg_dev.size() == 0) {
      out << "curr_avg_dev: []";
    } else {
      out << "curr_avg_dev: [";
      size_t pending_items = msg.curr_avg_dev.size();
      for (auto item : msg.curr_avg_dev) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: curr_calib
  {
    if (msg.curr_calib.size() == 0) {
      out << "curr_calib: []";
    } else {
      out << "curr_calib: [";
      size_t pending_items = msg.curr_calib.size();
      for (auto item : msg.curr_calib) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: samples
  {
    out << "samples: ";
    rosidl_generator_traits::value_to_yaml(msg.samples, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const MagCal_Feedback & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: curr_avg_dev
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.curr_avg_dev.size() == 0) {
      out << "curr_avg_dev: []\n";
    } else {
      out << "curr_avg_dev:\n";
      for (auto item : msg.curr_avg_dev) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: curr_calib
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.curr_calib.size() == 0) {
      out << "curr_calib: []\n";
    } else {
      out << "curr_calib:\n";
      for (auto item : msg.curr_calib) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: samples
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "samples: ";
    rosidl_generator_traits::value_to_yaml(msg.samples, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const MagCal_Feedback & msg, bool use_flow_style = false)
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

}  // namespace vectornav_msgs

namespace rosidl_generator_traits
{

[[deprecated("use vectornav_msgs::action::to_block_style_yaml() instead")]]
inline void to_yaml(
  const vectornav_msgs::action::MagCal_Feedback & msg,
  std::ostream & out, size_t indentation = 0)
{
  vectornav_msgs::action::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use vectornav_msgs::action::to_yaml() instead")]]
inline std::string to_yaml(const vectornav_msgs::action::MagCal_Feedback & msg)
{
  return vectornav_msgs::action::to_yaml(msg);
}

template<>
inline const char * data_type<vectornav_msgs::action::MagCal_Feedback>()
{
  return "vectornav_msgs::action::MagCal_Feedback";
}

template<>
inline const char * name<vectornav_msgs::action::MagCal_Feedback>()
{
  return "vectornav_msgs/action/MagCal_Feedback";
}

template<>
struct has_fixed_size<vectornav_msgs::action::MagCal_Feedback>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<vectornav_msgs::action::MagCal_Feedback>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<vectornav_msgs::action::MagCal_Feedback>
  : std::true_type {};

}  // namespace rosidl_generator_traits

// Include directives for member types
// Member 'goal_id'
#include "unique_identifier_msgs/msg/detail/uuid__traits.hpp"
// Member 'goal'
#include "vectornav_msgs/action/detail/mag_cal__traits.hpp"

namespace vectornav_msgs
{

namespace action
{

inline void to_flow_style_yaml(
  const MagCal_SendGoal_Request & msg,
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
  const MagCal_SendGoal_Request & msg,
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

inline std::string to_yaml(const MagCal_SendGoal_Request & msg, bool use_flow_style = false)
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

}  // namespace vectornav_msgs

namespace rosidl_generator_traits
{

[[deprecated("use vectornav_msgs::action::to_block_style_yaml() instead")]]
inline void to_yaml(
  const vectornav_msgs::action::MagCal_SendGoal_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  vectornav_msgs::action::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use vectornav_msgs::action::to_yaml() instead")]]
inline std::string to_yaml(const vectornav_msgs::action::MagCal_SendGoal_Request & msg)
{
  return vectornav_msgs::action::to_yaml(msg);
}

template<>
inline const char * data_type<vectornav_msgs::action::MagCal_SendGoal_Request>()
{
  return "vectornav_msgs::action::MagCal_SendGoal_Request";
}

template<>
inline const char * name<vectornav_msgs::action::MagCal_SendGoal_Request>()
{
  return "vectornav_msgs/action/MagCal_SendGoal_Request";
}

template<>
struct has_fixed_size<vectornav_msgs::action::MagCal_SendGoal_Request>
  : std::integral_constant<bool, has_fixed_size<unique_identifier_msgs::msg::UUID>::value && has_fixed_size<vectornav_msgs::action::MagCal_Goal>::value> {};

template<>
struct has_bounded_size<vectornav_msgs::action::MagCal_SendGoal_Request>
  : std::integral_constant<bool, has_bounded_size<unique_identifier_msgs::msg::UUID>::value && has_bounded_size<vectornav_msgs::action::MagCal_Goal>::value> {};

template<>
struct is_message<vectornav_msgs::action::MagCal_SendGoal_Request>
  : std::true_type {};

}  // namespace rosidl_generator_traits

// Include directives for member types
// Member 'stamp'
#include "builtin_interfaces/msg/detail/time__traits.hpp"

namespace vectornav_msgs
{

namespace action
{

inline void to_flow_style_yaml(
  const MagCal_SendGoal_Response & msg,
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
  const MagCal_SendGoal_Response & msg,
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

inline std::string to_yaml(const MagCal_SendGoal_Response & msg, bool use_flow_style = false)
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

}  // namespace vectornav_msgs

namespace rosidl_generator_traits
{

[[deprecated("use vectornav_msgs::action::to_block_style_yaml() instead")]]
inline void to_yaml(
  const vectornav_msgs::action::MagCal_SendGoal_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  vectornav_msgs::action::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use vectornav_msgs::action::to_yaml() instead")]]
inline std::string to_yaml(const vectornav_msgs::action::MagCal_SendGoal_Response & msg)
{
  return vectornav_msgs::action::to_yaml(msg);
}

template<>
inline const char * data_type<vectornav_msgs::action::MagCal_SendGoal_Response>()
{
  return "vectornav_msgs::action::MagCal_SendGoal_Response";
}

template<>
inline const char * name<vectornav_msgs::action::MagCal_SendGoal_Response>()
{
  return "vectornav_msgs/action/MagCal_SendGoal_Response";
}

template<>
struct has_fixed_size<vectornav_msgs::action::MagCal_SendGoal_Response>
  : std::integral_constant<bool, has_fixed_size<builtin_interfaces::msg::Time>::value> {};

template<>
struct has_bounded_size<vectornav_msgs::action::MagCal_SendGoal_Response>
  : std::integral_constant<bool, has_bounded_size<builtin_interfaces::msg::Time>::value> {};

template<>
struct is_message<vectornav_msgs::action::MagCal_SendGoal_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<vectornav_msgs::action::MagCal_SendGoal>()
{
  return "vectornav_msgs::action::MagCal_SendGoal";
}

template<>
inline const char * name<vectornav_msgs::action::MagCal_SendGoal>()
{
  return "vectornav_msgs/action/MagCal_SendGoal";
}

template<>
struct has_fixed_size<vectornav_msgs::action::MagCal_SendGoal>
  : std::integral_constant<
    bool,
    has_fixed_size<vectornav_msgs::action::MagCal_SendGoal_Request>::value &&
    has_fixed_size<vectornav_msgs::action::MagCal_SendGoal_Response>::value
  >
{
};

template<>
struct has_bounded_size<vectornav_msgs::action::MagCal_SendGoal>
  : std::integral_constant<
    bool,
    has_bounded_size<vectornav_msgs::action::MagCal_SendGoal_Request>::value &&
    has_bounded_size<vectornav_msgs::action::MagCal_SendGoal_Response>::value
  >
{
};

template<>
struct is_service<vectornav_msgs::action::MagCal_SendGoal>
  : std::true_type
{
};

template<>
struct is_service_request<vectornav_msgs::action::MagCal_SendGoal_Request>
  : std::true_type
{
};

template<>
struct is_service_response<vectornav_msgs::action::MagCal_SendGoal_Response>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits

// Include directives for member types
// Member 'goal_id'
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__traits.hpp"

namespace vectornav_msgs
{

namespace action
{

inline void to_flow_style_yaml(
  const MagCal_GetResult_Request & msg,
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
  const MagCal_GetResult_Request & msg,
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

inline std::string to_yaml(const MagCal_GetResult_Request & msg, bool use_flow_style = false)
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

}  // namespace vectornav_msgs

namespace rosidl_generator_traits
{

[[deprecated("use vectornav_msgs::action::to_block_style_yaml() instead")]]
inline void to_yaml(
  const vectornav_msgs::action::MagCal_GetResult_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  vectornav_msgs::action::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use vectornav_msgs::action::to_yaml() instead")]]
inline std::string to_yaml(const vectornav_msgs::action::MagCal_GetResult_Request & msg)
{
  return vectornav_msgs::action::to_yaml(msg);
}

template<>
inline const char * data_type<vectornav_msgs::action::MagCal_GetResult_Request>()
{
  return "vectornav_msgs::action::MagCal_GetResult_Request";
}

template<>
inline const char * name<vectornav_msgs::action::MagCal_GetResult_Request>()
{
  return "vectornav_msgs/action/MagCal_GetResult_Request";
}

template<>
struct has_fixed_size<vectornav_msgs::action::MagCal_GetResult_Request>
  : std::integral_constant<bool, has_fixed_size<unique_identifier_msgs::msg::UUID>::value> {};

template<>
struct has_bounded_size<vectornav_msgs::action::MagCal_GetResult_Request>
  : std::integral_constant<bool, has_bounded_size<unique_identifier_msgs::msg::UUID>::value> {};

template<>
struct is_message<vectornav_msgs::action::MagCal_GetResult_Request>
  : std::true_type {};

}  // namespace rosidl_generator_traits

// Include directives for member types
// Member 'result'
// already included above
// #include "vectornav_msgs/action/detail/mag_cal__traits.hpp"

namespace vectornav_msgs
{

namespace action
{

inline void to_flow_style_yaml(
  const MagCal_GetResult_Response & msg,
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
  const MagCal_GetResult_Response & msg,
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

inline std::string to_yaml(const MagCal_GetResult_Response & msg, bool use_flow_style = false)
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

}  // namespace vectornav_msgs

namespace rosidl_generator_traits
{

[[deprecated("use vectornav_msgs::action::to_block_style_yaml() instead")]]
inline void to_yaml(
  const vectornav_msgs::action::MagCal_GetResult_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  vectornav_msgs::action::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use vectornav_msgs::action::to_yaml() instead")]]
inline std::string to_yaml(const vectornav_msgs::action::MagCal_GetResult_Response & msg)
{
  return vectornav_msgs::action::to_yaml(msg);
}

template<>
inline const char * data_type<vectornav_msgs::action::MagCal_GetResult_Response>()
{
  return "vectornav_msgs::action::MagCal_GetResult_Response";
}

template<>
inline const char * name<vectornav_msgs::action::MagCal_GetResult_Response>()
{
  return "vectornav_msgs/action/MagCal_GetResult_Response";
}

template<>
struct has_fixed_size<vectornav_msgs::action::MagCal_GetResult_Response>
  : std::integral_constant<bool, has_fixed_size<vectornav_msgs::action::MagCal_Result>::value> {};

template<>
struct has_bounded_size<vectornav_msgs::action::MagCal_GetResult_Response>
  : std::integral_constant<bool, has_bounded_size<vectornav_msgs::action::MagCal_Result>::value> {};

template<>
struct is_message<vectornav_msgs::action::MagCal_GetResult_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<vectornav_msgs::action::MagCal_GetResult>()
{
  return "vectornav_msgs::action::MagCal_GetResult";
}

template<>
inline const char * name<vectornav_msgs::action::MagCal_GetResult>()
{
  return "vectornav_msgs/action/MagCal_GetResult";
}

template<>
struct has_fixed_size<vectornav_msgs::action::MagCal_GetResult>
  : std::integral_constant<
    bool,
    has_fixed_size<vectornav_msgs::action::MagCal_GetResult_Request>::value &&
    has_fixed_size<vectornav_msgs::action::MagCal_GetResult_Response>::value
  >
{
};

template<>
struct has_bounded_size<vectornav_msgs::action::MagCal_GetResult>
  : std::integral_constant<
    bool,
    has_bounded_size<vectornav_msgs::action::MagCal_GetResult_Request>::value &&
    has_bounded_size<vectornav_msgs::action::MagCal_GetResult_Response>::value
  >
{
};

template<>
struct is_service<vectornav_msgs::action::MagCal_GetResult>
  : std::true_type
{
};

template<>
struct is_service_request<vectornav_msgs::action::MagCal_GetResult_Request>
  : std::true_type
{
};

template<>
struct is_service_response<vectornav_msgs::action::MagCal_GetResult_Response>
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
// #include "vectornav_msgs/action/detail/mag_cal__traits.hpp"

namespace vectornav_msgs
{

namespace action
{

inline void to_flow_style_yaml(
  const MagCal_FeedbackMessage & msg,
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
  const MagCal_FeedbackMessage & msg,
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

inline std::string to_yaml(const MagCal_FeedbackMessage & msg, bool use_flow_style = false)
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

}  // namespace vectornav_msgs

namespace rosidl_generator_traits
{

[[deprecated("use vectornav_msgs::action::to_block_style_yaml() instead")]]
inline void to_yaml(
  const vectornav_msgs::action::MagCal_FeedbackMessage & msg,
  std::ostream & out, size_t indentation = 0)
{
  vectornav_msgs::action::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use vectornav_msgs::action::to_yaml() instead")]]
inline std::string to_yaml(const vectornav_msgs::action::MagCal_FeedbackMessage & msg)
{
  return vectornav_msgs::action::to_yaml(msg);
}

template<>
inline const char * data_type<vectornav_msgs::action::MagCal_FeedbackMessage>()
{
  return "vectornav_msgs::action::MagCal_FeedbackMessage";
}

template<>
inline const char * name<vectornav_msgs::action::MagCal_FeedbackMessage>()
{
  return "vectornav_msgs/action/MagCal_FeedbackMessage";
}

template<>
struct has_fixed_size<vectornav_msgs::action::MagCal_FeedbackMessage>
  : std::integral_constant<bool, has_fixed_size<unique_identifier_msgs::msg::UUID>::value && has_fixed_size<vectornav_msgs::action::MagCal_Feedback>::value> {};

template<>
struct has_bounded_size<vectornav_msgs::action::MagCal_FeedbackMessage>
  : std::integral_constant<bool, has_bounded_size<unique_identifier_msgs::msg::UUID>::value && has_bounded_size<vectornav_msgs::action::MagCal_Feedback>::value> {};

template<>
struct is_message<vectornav_msgs::action::MagCal_FeedbackMessage>
  : std::true_type {};

}  // namespace rosidl_generator_traits


namespace rosidl_generator_traits
{

template<>
struct is_action<vectornav_msgs::action::MagCal>
  : std::true_type
{
};

template<>
struct is_action_goal<vectornav_msgs::action::MagCal_Goal>
  : std::true_type
{
};

template<>
struct is_action_result<vectornav_msgs::action::MagCal_Result>
  : std::true_type
{
};

template<>
struct is_action_feedback<vectornav_msgs::action::MagCal_Feedback>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits


#endif  // VECTORNAV_MSGS__ACTION__DETAIL__MAG_CAL__TRAITS_HPP_
