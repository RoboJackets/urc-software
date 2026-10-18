// generated from rosidl_typesupport_introspection_cpp/resource/idl__type_support.cpp.em
// with input from vectornav_msgs:action/MagCal.idl
// generated code does not contain a copyright notice

#include "array"
#include "cstddef"
#include "string"
#include "vector"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_interface/macros.h"
#include "vectornav_msgs/action/detail/mag_cal__struct.hpp"
#include "rosidl_typesupport_introspection_cpp/field_types.hpp"
#include "rosidl_typesupport_introspection_cpp/identifier.hpp"
#include "rosidl_typesupport_introspection_cpp/message_introspection.hpp"
#include "rosidl_typesupport_introspection_cpp/message_type_support_decl.hpp"
#include "rosidl_typesupport_introspection_cpp/visibility_control.h"

namespace vectornav_msgs
{

namespace action
{

namespace rosidl_typesupport_introspection_cpp
{

void MagCal_Goal_init_function(
  void * message_memory, rosidl_runtime_cpp::MessageInitialization _init)
{
  new (message_memory) vectornav_msgs::action::MagCal_Goal(_init);
}

void MagCal_Goal_fini_function(void * message_memory)
{
  auto typed_message = static_cast<vectornav_msgs::action::MagCal_Goal *>(message_memory);
  typed_message->~MagCal_Goal();
}

static const ::rosidl_typesupport_introspection_cpp::MessageMember MagCal_Goal_message_member_array[1] = {
  {
    "structure_needs_at_least_one_member",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_UINT8,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(vectornav_msgs::action::MagCal_Goal, structure_needs_at_least_one_member),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  }
};

static const ::rosidl_typesupport_introspection_cpp::MessageMembers MagCal_Goal_message_members = {
  "vectornav_msgs::action",  // message namespace
  "MagCal_Goal",  // message name
  1,  // number of fields
  sizeof(vectornav_msgs::action::MagCal_Goal),
  MagCal_Goal_message_member_array,  // message members
  MagCal_Goal_init_function,  // function to initialize message memory (memory has to be allocated)
  MagCal_Goal_fini_function  // function to terminate message instance (will not free memory)
};

static const rosidl_message_type_support_t MagCal_Goal_message_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &MagCal_Goal_message_members,
  get_message_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_introspection_cpp

}  // namespace action

}  // namespace vectornav_msgs


namespace rosidl_typesupport_introspection_cpp
{

template<>
ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<vectornav_msgs::action::MagCal_Goal>()
{
  return &::vectornav_msgs::action::rosidl_typesupport_introspection_cpp::MagCal_Goal_message_type_support_handle;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, vectornav_msgs, action, MagCal_Goal)() {
  return &::vectornav_msgs::action::rosidl_typesupport_introspection_cpp::MagCal_Goal_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif

// already included above
// #include "array"
// already included above
// #include "cstddef"
// already included above
// #include "string"
// already included above
// #include "vector"
// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"
// already included above
// #include "rosidl_typesupport_cpp/message_type_support.hpp"
// already included above
// #include "rosidl_typesupport_interface/macros.h"
// already included above
// #include "vectornav_msgs/action/detail/mag_cal__struct.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/field_types.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/identifier.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/message_introspection.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/message_type_support_decl.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/visibility_control.h"

namespace vectornav_msgs
{

namespace action
{

namespace rosidl_typesupport_introspection_cpp
{

void MagCal_Result_init_function(
  void * message_memory, rosidl_runtime_cpp::MessageInitialization _init)
{
  new (message_memory) vectornav_msgs::action::MagCal_Result(_init);
}

void MagCal_Result_fini_function(void * message_memory)
{
  auto typed_message = static_cast<vectornav_msgs::action::MagCal_Result *>(message_memory);
  typed_message->~MagCal_Result();
}

size_t size_function__MagCal_Result__avg_dev(const void * untyped_member)
{
  (void)untyped_member;
  return 12;
}

const void * get_const_function__MagCal_Result__avg_dev(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::array<float, 12> *>(untyped_member);
  return &member[index];
}

void * get_function__MagCal_Result__avg_dev(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::array<float, 12> *>(untyped_member);
  return &member[index];
}

void fetch_function__MagCal_Result__avg_dev(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const float *>(
    get_const_function__MagCal_Result__avg_dev(untyped_member, index));
  auto & value = *reinterpret_cast<float *>(untyped_value);
  value = item;
}

void assign_function__MagCal_Result__avg_dev(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<float *>(
    get_function__MagCal_Result__avg_dev(untyped_member, index));
  const auto & value = *reinterpret_cast<const float *>(untyped_value);
  item = value;
}

size_t size_function__MagCal_Result__calib(const void * untyped_member)
{
  (void)untyped_member;
  return 12;
}

const void * get_const_function__MagCal_Result__calib(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::array<float, 12> *>(untyped_member);
  return &member[index];
}

void * get_function__MagCal_Result__calib(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::array<float, 12> *>(untyped_member);
  return &member[index];
}

void fetch_function__MagCal_Result__calib(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const float *>(
    get_const_function__MagCal_Result__calib(untyped_member, index));
  auto & value = *reinterpret_cast<float *>(untyped_value);
  value = item;
}

void assign_function__MagCal_Result__calib(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<float *>(
    get_function__MagCal_Result__calib(untyped_member, index));
  const auto & value = *reinterpret_cast<const float *>(untyped_value);
  item = value;
}

static const ::rosidl_typesupport_introspection_cpp::MessageMember MagCal_Result_message_member_array[2] = {
  {
    "avg_dev",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    true,  // is array
    12,  // array size
    false,  // is upper bound
    offsetof(vectornav_msgs::action::MagCal_Result, avg_dev),  // bytes offset in struct
    nullptr,  // default value
    size_function__MagCal_Result__avg_dev,  // size() function pointer
    get_const_function__MagCal_Result__avg_dev,  // get_const(index) function pointer
    get_function__MagCal_Result__avg_dev,  // get(index) function pointer
    fetch_function__MagCal_Result__avg_dev,  // fetch(index, &value) function pointer
    assign_function__MagCal_Result__avg_dev,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "calib",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    true,  // is array
    12,  // array size
    false,  // is upper bound
    offsetof(vectornav_msgs::action::MagCal_Result, calib),  // bytes offset in struct
    nullptr,  // default value
    size_function__MagCal_Result__calib,  // size() function pointer
    get_const_function__MagCal_Result__calib,  // get_const(index) function pointer
    get_function__MagCal_Result__calib,  // get(index) function pointer
    fetch_function__MagCal_Result__calib,  // fetch(index, &value) function pointer
    assign_function__MagCal_Result__calib,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  }
};

static const ::rosidl_typesupport_introspection_cpp::MessageMembers MagCal_Result_message_members = {
  "vectornav_msgs::action",  // message namespace
  "MagCal_Result",  // message name
  2,  // number of fields
  sizeof(vectornav_msgs::action::MagCal_Result),
  MagCal_Result_message_member_array,  // message members
  MagCal_Result_init_function,  // function to initialize message memory (memory has to be allocated)
  MagCal_Result_fini_function  // function to terminate message instance (will not free memory)
};

static const rosidl_message_type_support_t MagCal_Result_message_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &MagCal_Result_message_members,
  get_message_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_introspection_cpp

}  // namespace action

}  // namespace vectornav_msgs


namespace rosidl_typesupport_introspection_cpp
{

template<>
ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<vectornav_msgs::action::MagCal_Result>()
{
  return &::vectornav_msgs::action::rosidl_typesupport_introspection_cpp::MagCal_Result_message_type_support_handle;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, vectornav_msgs, action, MagCal_Result)() {
  return &::vectornav_msgs::action::rosidl_typesupport_introspection_cpp::MagCal_Result_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif

// already included above
// #include "array"
// already included above
// #include "cstddef"
// already included above
// #include "string"
// already included above
// #include "vector"
// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"
// already included above
// #include "rosidl_typesupport_cpp/message_type_support.hpp"
// already included above
// #include "rosidl_typesupport_interface/macros.h"
// already included above
// #include "vectornav_msgs/action/detail/mag_cal__struct.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/field_types.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/identifier.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/message_introspection.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/message_type_support_decl.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/visibility_control.h"

namespace vectornav_msgs
{

namespace action
{

namespace rosidl_typesupport_introspection_cpp
{

void MagCal_Feedback_init_function(
  void * message_memory, rosidl_runtime_cpp::MessageInitialization _init)
{
  new (message_memory) vectornav_msgs::action::MagCal_Feedback(_init);
}

void MagCal_Feedback_fini_function(void * message_memory)
{
  auto typed_message = static_cast<vectornav_msgs::action::MagCal_Feedback *>(message_memory);
  typed_message->~MagCal_Feedback();
}

size_t size_function__MagCal_Feedback__curr_avg_dev(const void * untyped_member)
{
  (void)untyped_member;
  return 12;
}

const void * get_const_function__MagCal_Feedback__curr_avg_dev(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::array<float, 12> *>(untyped_member);
  return &member[index];
}

void * get_function__MagCal_Feedback__curr_avg_dev(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::array<float, 12> *>(untyped_member);
  return &member[index];
}

void fetch_function__MagCal_Feedback__curr_avg_dev(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const float *>(
    get_const_function__MagCal_Feedback__curr_avg_dev(untyped_member, index));
  auto & value = *reinterpret_cast<float *>(untyped_value);
  value = item;
}

void assign_function__MagCal_Feedback__curr_avg_dev(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<float *>(
    get_function__MagCal_Feedback__curr_avg_dev(untyped_member, index));
  const auto & value = *reinterpret_cast<const float *>(untyped_value);
  item = value;
}

size_t size_function__MagCal_Feedback__curr_calib(const void * untyped_member)
{
  (void)untyped_member;
  return 12;
}

const void * get_const_function__MagCal_Feedback__curr_calib(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::array<float, 12> *>(untyped_member);
  return &member[index];
}

void * get_function__MagCal_Feedback__curr_calib(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::array<float, 12> *>(untyped_member);
  return &member[index];
}

void fetch_function__MagCal_Feedback__curr_calib(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const float *>(
    get_const_function__MagCal_Feedback__curr_calib(untyped_member, index));
  auto & value = *reinterpret_cast<float *>(untyped_value);
  value = item;
}

void assign_function__MagCal_Feedback__curr_calib(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<float *>(
    get_function__MagCal_Feedback__curr_calib(untyped_member, index));
  const auto & value = *reinterpret_cast<const float *>(untyped_value);
  item = value;
}

static const ::rosidl_typesupport_introspection_cpp::MessageMember MagCal_Feedback_message_member_array[3] = {
  {
    "curr_avg_dev",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    true,  // is array
    12,  // array size
    false,  // is upper bound
    offsetof(vectornav_msgs::action::MagCal_Feedback, curr_avg_dev),  // bytes offset in struct
    nullptr,  // default value
    size_function__MagCal_Feedback__curr_avg_dev,  // size() function pointer
    get_const_function__MagCal_Feedback__curr_avg_dev,  // get_const(index) function pointer
    get_function__MagCal_Feedback__curr_avg_dev,  // get(index) function pointer
    fetch_function__MagCal_Feedback__curr_avg_dev,  // fetch(index, &value) function pointer
    assign_function__MagCal_Feedback__curr_avg_dev,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "curr_calib",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    true,  // is array
    12,  // array size
    false,  // is upper bound
    offsetof(vectornav_msgs::action::MagCal_Feedback, curr_calib),  // bytes offset in struct
    nullptr,  // default value
    size_function__MagCal_Feedback__curr_calib,  // size() function pointer
    get_const_function__MagCal_Feedback__curr_calib,  // get_const(index) function pointer
    get_function__MagCal_Feedback__curr_calib,  // get(index) function pointer
    fetch_function__MagCal_Feedback__curr_calib,  // fetch(index, &value) function pointer
    assign_function__MagCal_Feedback__curr_calib,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "samples",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_UINT32,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(vectornav_msgs::action::MagCal_Feedback, samples),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  }
};

static const ::rosidl_typesupport_introspection_cpp::MessageMembers MagCal_Feedback_message_members = {
  "vectornav_msgs::action",  // message namespace
  "MagCal_Feedback",  // message name
  3,  // number of fields
  sizeof(vectornav_msgs::action::MagCal_Feedback),
  MagCal_Feedback_message_member_array,  // message members
  MagCal_Feedback_init_function,  // function to initialize message memory (memory has to be allocated)
  MagCal_Feedback_fini_function  // function to terminate message instance (will not free memory)
};

static const rosidl_message_type_support_t MagCal_Feedback_message_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &MagCal_Feedback_message_members,
  get_message_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_introspection_cpp

}  // namespace action

}  // namespace vectornav_msgs


namespace rosidl_typesupport_introspection_cpp
{

template<>
ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<vectornav_msgs::action::MagCal_Feedback>()
{
  return &::vectornav_msgs::action::rosidl_typesupport_introspection_cpp::MagCal_Feedback_message_type_support_handle;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, vectornav_msgs, action, MagCal_Feedback)() {
  return &::vectornav_msgs::action::rosidl_typesupport_introspection_cpp::MagCal_Feedback_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif

// already included above
// #include "array"
// already included above
// #include "cstddef"
// already included above
// #include "string"
// already included above
// #include "vector"
// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"
// already included above
// #include "rosidl_typesupport_cpp/message_type_support.hpp"
// already included above
// #include "rosidl_typesupport_interface/macros.h"
// already included above
// #include "vectornav_msgs/action/detail/mag_cal__struct.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/field_types.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/identifier.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/message_introspection.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/message_type_support_decl.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/visibility_control.h"

namespace vectornav_msgs
{

namespace action
{

namespace rosidl_typesupport_introspection_cpp
{

void MagCal_SendGoal_Request_init_function(
  void * message_memory, rosidl_runtime_cpp::MessageInitialization _init)
{
  new (message_memory) vectornav_msgs::action::MagCal_SendGoal_Request(_init);
}

void MagCal_SendGoal_Request_fini_function(void * message_memory)
{
  auto typed_message = static_cast<vectornav_msgs::action::MagCal_SendGoal_Request *>(message_memory);
  typed_message->~MagCal_SendGoal_Request();
}

static const ::rosidl_typesupport_introspection_cpp::MessageMember MagCal_SendGoal_Request_message_member_array[2] = {
  {
    "goal_id",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<unique_identifier_msgs::msg::UUID>(),  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(vectornav_msgs::action::MagCal_SendGoal_Request, goal_id),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "goal",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<vectornav_msgs::action::MagCal_Goal>(),  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(vectornav_msgs::action::MagCal_SendGoal_Request, goal),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  }
};

static const ::rosidl_typesupport_introspection_cpp::MessageMembers MagCal_SendGoal_Request_message_members = {
  "vectornav_msgs::action",  // message namespace
  "MagCal_SendGoal_Request",  // message name
  2,  // number of fields
  sizeof(vectornav_msgs::action::MagCal_SendGoal_Request),
  MagCal_SendGoal_Request_message_member_array,  // message members
  MagCal_SendGoal_Request_init_function,  // function to initialize message memory (memory has to be allocated)
  MagCal_SendGoal_Request_fini_function  // function to terminate message instance (will not free memory)
};

static const rosidl_message_type_support_t MagCal_SendGoal_Request_message_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &MagCal_SendGoal_Request_message_members,
  get_message_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_introspection_cpp

}  // namespace action

}  // namespace vectornav_msgs


namespace rosidl_typesupport_introspection_cpp
{

template<>
ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<vectornav_msgs::action::MagCal_SendGoal_Request>()
{
  return &::vectornav_msgs::action::rosidl_typesupport_introspection_cpp::MagCal_SendGoal_Request_message_type_support_handle;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, vectornav_msgs, action, MagCal_SendGoal_Request)() {
  return &::vectornav_msgs::action::rosidl_typesupport_introspection_cpp::MagCal_SendGoal_Request_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif

// already included above
// #include "array"
// already included above
// #include "cstddef"
// already included above
// #include "string"
// already included above
// #include "vector"
// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"
// already included above
// #include "rosidl_typesupport_cpp/message_type_support.hpp"
// already included above
// #include "rosidl_typesupport_interface/macros.h"
// already included above
// #include "vectornav_msgs/action/detail/mag_cal__struct.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/field_types.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/identifier.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/message_introspection.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/message_type_support_decl.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/visibility_control.h"

namespace vectornav_msgs
{

namespace action
{

namespace rosidl_typesupport_introspection_cpp
{

void MagCal_SendGoal_Response_init_function(
  void * message_memory, rosidl_runtime_cpp::MessageInitialization _init)
{
  new (message_memory) vectornav_msgs::action::MagCal_SendGoal_Response(_init);
}

void MagCal_SendGoal_Response_fini_function(void * message_memory)
{
  auto typed_message = static_cast<vectornav_msgs::action::MagCal_SendGoal_Response *>(message_memory);
  typed_message->~MagCal_SendGoal_Response();
}

static const ::rosidl_typesupport_introspection_cpp::MessageMember MagCal_SendGoal_Response_message_member_array[2] = {
  {
    "accepted",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(vectornav_msgs::action::MagCal_SendGoal_Response, accepted),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "stamp",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<builtin_interfaces::msg::Time>(),  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(vectornav_msgs::action::MagCal_SendGoal_Response, stamp),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  }
};

static const ::rosidl_typesupport_introspection_cpp::MessageMembers MagCal_SendGoal_Response_message_members = {
  "vectornav_msgs::action",  // message namespace
  "MagCal_SendGoal_Response",  // message name
  2,  // number of fields
  sizeof(vectornav_msgs::action::MagCal_SendGoal_Response),
  MagCal_SendGoal_Response_message_member_array,  // message members
  MagCal_SendGoal_Response_init_function,  // function to initialize message memory (memory has to be allocated)
  MagCal_SendGoal_Response_fini_function  // function to terminate message instance (will not free memory)
};

static const rosidl_message_type_support_t MagCal_SendGoal_Response_message_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &MagCal_SendGoal_Response_message_members,
  get_message_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_introspection_cpp

}  // namespace action

}  // namespace vectornav_msgs


namespace rosidl_typesupport_introspection_cpp
{

template<>
ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<vectornav_msgs::action::MagCal_SendGoal_Response>()
{
  return &::vectornav_msgs::action::rosidl_typesupport_introspection_cpp::MagCal_SendGoal_Response_message_type_support_handle;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, vectornav_msgs, action, MagCal_SendGoal_Response)() {
  return &::vectornav_msgs::action::rosidl_typesupport_introspection_cpp::MagCal_SendGoal_Response_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif

#include "rosidl_runtime_c/service_type_support_struct.h"
// already included above
// #include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_cpp/service_type_support.hpp"
// already included above
// #include "rosidl_typesupport_interface/macros.h"
// already included above
// #include "rosidl_typesupport_introspection_cpp/visibility_control.h"
// already included above
// #include "vectornav_msgs/action/detail/mag_cal__struct.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/identifier.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/message_type_support_decl.hpp"
#include "rosidl_typesupport_introspection_cpp/service_introspection.hpp"
#include "rosidl_typesupport_introspection_cpp/service_type_support_decl.hpp"

namespace vectornav_msgs
{

namespace action
{

namespace rosidl_typesupport_introspection_cpp
{

// this is intentionally not const to allow initialization later to prevent an initialization race
static ::rosidl_typesupport_introspection_cpp::ServiceMembers MagCal_SendGoal_service_members = {
  "vectornav_msgs::action",  // service namespace
  "MagCal_SendGoal",  // service name
  // these two fields are initialized below on the first access
  // see get_service_type_support_handle<vectornav_msgs::action::MagCal_SendGoal>()
  nullptr,  // request message
  nullptr  // response message
};

static const rosidl_service_type_support_t MagCal_SendGoal_service_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &MagCal_SendGoal_service_members,
  get_service_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_introspection_cpp

}  // namespace action

}  // namespace vectornav_msgs


namespace rosidl_typesupport_introspection_cpp
{

template<>
ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_service_type_support_t *
get_service_type_support_handle<vectornav_msgs::action::MagCal_SendGoal>()
{
  // get a handle to the value to be returned
  auto service_type_support =
    &::vectornav_msgs::action::rosidl_typesupport_introspection_cpp::MagCal_SendGoal_service_type_support_handle;
  // get a non-const and properly typed version of the data void *
  auto service_members = const_cast<::rosidl_typesupport_introspection_cpp::ServiceMembers *>(
    static_cast<const ::rosidl_typesupport_introspection_cpp::ServiceMembers *>(
      service_type_support->data));
  // make sure that both the request_members_ and the response_members_ are initialized
  // if they are not, initialize them
  if (
    service_members->request_members_ == nullptr ||
    service_members->response_members_ == nullptr)
  {
    // initialize the request_members_ with the static function from the external library
    service_members->request_members_ = static_cast<
      const ::rosidl_typesupport_introspection_cpp::MessageMembers *
      >(
      ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<
        ::vectornav_msgs::action::MagCal_SendGoal_Request
      >()->data
      );
    // initialize the response_members_ with the static function from the external library
    service_members->response_members_ = static_cast<
      const ::rosidl_typesupport_introspection_cpp::MessageMembers *
      >(
      ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<
        ::vectornav_msgs::action::MagCal_SendGoal_Response
      >()->data
      );
  }
  // finally return the properly initialized service_type_support handle
  return service_type_support;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, vectornav_msgs, action, MagCal_SendGoal)() {
  return ::rosidl_typesupport_introspection_cpp::get_service_type_support_handle<vectornav_msgs::action::MagCal_SendGoal>();
}

#ifdef __cplusplus
}
#endif

// already included above
// #include "array"
// already included above
// #include "cstddef"
// already included above
// #include "string"
// already included above
// #include "vector"
// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"
// already included above
// #include "rosidl_typesupport_cpp/message_type_support.hpp"
// already included above
// #include "rosidl_typesupport_interface/macros.h"
// already included above
// #include "vectornav_msgs/action/detail/mag_cal__struct.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/field_types.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/identifier.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/message_introspection.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/message_type_support_decl.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/visibility_control.h"

namespace vectornav_msgs
{

namespace action
{

namespace rosidl_typesupport_introspection_cpp
{

void MagCal_GetResult_Request_init_function(
  void * message_memory, rosidl_runtime_cpp::MessageInitialization _init)
{
  new (message_memory) vectornav_msgs::action::MagCal_GetResult_Request(_init);
}

void MagCal_GetResult_Request_fini_function(void * message_memory)
{
  auto typed_message = static_cast<vectornav_msgs::action::MagCal_GetResult_Request *>(message_memory);
  typed_message->~MagCal_GetResult_Request();
}

static const ::rosidl_typesupport_introspection_cpp::MessageMember MagCal_GetResult_Request_message_member_array[1] = {
  {
    "goal_id",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<unique_identifier_msgs::msg::UUID>(),  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(vectornav_msgs::action::MagCal_GetResult_Request, goal_id),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  }
};

static const ::rosidl_typesupport_introspection_cpp::MessageMembers MagCal_GetResult_Request_message_members = {
  "vectornav_msgs::action",  // message namespace
  "MagCal_GetResult_Request",  // message name
  1,  // number of fields
  sizeof(vectornav_msgs::action::MagCal_GetResult_Request),
  MagCal_GetResult_Request_message_member_array,  // message members
  MagCal_GetResult_Request_init_function,  // function to initialize message memory (memory has to be allocated)
  MagCal_GetResult_Request_fini_function  // function to terminate message instance (will not free memory)
};

static const rosidl_message_type_support_t MagCal_GetResult_Request_message_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &MagCal_GetResult_Request_message_members,
  get_message_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_introspection_cpp

}  // namespace action

}  // namespace vectornav_msgs


namespace rosidl_typesupport_introspection_cpp
{

template<>
ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<vectornav_msgs::action::MagCal_GetResult_Request>()
{
  return &::vectornav_msgs::action::rosidl_typesupport_introspection_cpp::MagCal_GetResult_Request_message_type_support_handle;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, vectornav_msgs, action, MagCal_GetResult_Request)() {
  return &::vectornav_msgs::action::rosidl_typesupport_introspection_cpp::MagCal_GetResult_Request_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif

// already included above
// #include "array"
// already included above
// #include "cstddef"
// already included above
// #include "string"
// already included above
// #include "vector"
// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"
// already included above
// #include "rosidl_typesupport_cpp/message_type_support.hpp"
// already included above
// #include "rosidl_typesupport_interface/macros.h"
// already included above
// #include "vectornav_msgs/action/detail/mag_cal__struct.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/field_types.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/identifier.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/message_introspection.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/message_type_support_decl.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/visibility_control.h"

namespace vectornav_msgs
{

namespace action
{

namespace rosidl_typesupport_introspection_cpp
{

void MagCal_GetResult_Response_init_function(
  void * message_memory, rosidl_runtime_cpp::MessageInitialization _init)
{
  new (message_memory) vectornav_msgs::action::MagCal_GetResult_Response(_init);
}

void MagCal_GetResult_Response_fini_function(void * message_memory)
{
  auto typed_message = static_cast<vectornav_msgs::action::MagCal_GetResult_Response *>(message_memory);
  typed_message->~MagCal_GetResult_Response();
}

static const ::rosidl_typesupport_introspection_cpp::MessageMember MagCal_GetResult_Response_message_member_array[2] = {
  {
    "status",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_INT8,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(vectornav_msgs::action::MagCal_GetResult_Response, status),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "result",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<vectornav_msgs::action::MagCal_Result>(),  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(vectornav_msgs::action::MagCal_GetResult_Response, result),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  }
};

static const ::rosidl_typesupport_introspection_cpp::MessageMembers MagCal_GetResult_Response_message_members = {
  "vectornav_msgs::action",  // message namespace
  "MagCal_GetResult_Response",  // message name
  2,  // number of fields
  sizeof(vectornav_msgs::action::MagCal_GetResult_Response),
  MagCal_GetResult_Response_message_member_array,  // message members
  MagCal_GetResult_Response_init_function,  // function to initialize message memory (memory has to be allocated)
  MagCal_GetResult_Response_fini_function  // function to terminate message instance (will not free memory)
};

static const rosidl_message_type_support_t MagCal_GetResult_Response_message_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &MagCal_GetResult_Response_message_members,
  get_message_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_introspection_cpp

}  // namespace action

}  // namespace vectornav_msgs


namespace rosidl_typesupport_introspection_cpp
{

template<>
ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<vectornav_msgs::action::MagCal_GetResult_Response>()
{
  return &::vectornav_msgs::action::rosidl_typesupport_introspection_cpp::MagCal_GetResult_Response_message_type_support_handle;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, vectornav_msgs, action, MagCal_GetResult_Response)() {
  return &::vectornav_msgs::action::rosidl_typesupport_introspection_cpp::MagCal_GetResult_Response_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif

// already included above
// #include "rosidl_runtime_c/service_type_support_struct.h"
// already included above
// #include "rosidl_typesupport_cpp/message_type_support.hpp"
// already included above
// #include "rosidl_typesupport_cpp/service_type_support.hpp"
// already included above
// #include "rosidl_typesupport_interface/macros.h"
// already included above
// #include "rosidl_typesupport_introspection_cpp/visibility_control.h"
// already included above
// #include "vectornav_msgs/action/detail/mag_cal__struct.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/identifier.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/message_type_support_decl.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/service_introspection.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/service_type_support_decl.hpp"

namespace vectornav_msgs
{

namespace action
{

namespace rosidl_typesupport_introspection_cpp
{

// this is intentionally not const to allow initialization later to prevent an initialization race
static ::rosidl_typesupport_introspection_cpp::ServiceMembers MagCal_GetResult_service_members = {
  "vectornav_msgs::action",  // service namespace
  "MagCal_GetResult",  // service name
  // these two fields are initialized below on the first access
  // see get_service_type_support_handle<vectornav_msgs::action::MagCal_GetResult>()
  nullptr,  // request message
  nullptr  // response message
};

static const rosidl_service_type_support_t MagCal_GetResult_service_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &MagCal_GetResult_service_members,
  get_service_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_introspection_cpp

}  // namespace action

}  // namespace vectornav_msgs


namespace rosidl_typesupport_introspection_cpp
{

template<>
ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_service_type_support_t *
get_service_type_support_handle<vectornav_msgs::action::MagCal_GetResult>()
{
  // get a handle to the value to be returned
  auto service_type_support =
    &::vectornav_msgs::action::rosidl_typesupport_introspection_cpp::MagCal_GetResult_service_type_support_handle;
  // get a non-const and properly typed version of the data void *
  auto service_members = const_cast<::rosidl_typesupport_introspection_cpp::ServiceMembers *>(
    static_cast<const ::rosidl_typesupport_introspection_cpp::ServiceMembers *>(
      service_type_support->data));
  // make sure that both the request_members_ and the response_members_ are initialized
  // if they are not, initialize them
  if (
    service_members->request_members_ == nullptr ||
    service_members->response_members_ == nullptr)
  {
    // initialize the request_members_ with the static function from the external library
    service_members->request_members_ = static_cast<
      const ::rosidl_typesupport_introspection_cpp::MessageMembers *
      >(
      ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<
        ::vectornav_msgs::action::MagCal_GetResult_Request
      >()->data
      );
    // initialize the response_members_ with the static function from the external library
    service_members->response_members_ = static_cast<
      const ::rosidl_typesupport_introspection_cpp::MessageMembers *
      >(
      ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<
        ::vectornav_msgs::action::MagCal_GetResult_Response
      >()->data
      );
  }
  // finally return the properly initialized service_type_support handle
  return service_type_support;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, vectornav_msgs, action, MagCal_GetResult)() {
  return ::rosidl_typesupport_introspection_cpp::get_service_type_support_handle<vectornav_msgs::action::MagCal_GetResult>();
}

#ifdef __cplusplus
}
#endif

// already included above
// #include "array"
// already included above
// #include "cstddef"
// already included above
// #include "string"
// already included above
// #include "vector"
// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"
// already included above
// #include "rosidl_typesupport_cpp/message_type_support.hpp"
// already included above
// #include "rosidl_typesupport_interface/macros.h"
// already included above
// #include "vectornav_msgs/action/detail/mag_cal__struct.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/field_types.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/identifier.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/message_introspection.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/message_type_support_decl.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/visibility_control.h"

namespace vectornav_msgs
{

namespace action
{

namespace rosidl_typesupport_introspection_cpp
{

void MagCal_FeedbackMessage_init_function(
  void * message_memory, rosidl_runtime_cpp::MessageInitialization _init)
{
  new (message_memory) vectornav_msgs::action::MagCal_FeedbackMessage(_init);
}

void MagCal_FeedbackMessage_fini_function(void * message_memory)
{
  auto typed_message = static_cast<vectornav_msgs::action::MagCal_FeedbackMessage *>(message_memory);
  typed_message->~MagCal_FeedbackMessage();
}

static const ::rosidl_typesupport_introspection_cpp::MessageMember MagCal_FeedbackMessage_message_member_array[2] = {
  {
    "goal_id",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<unique_identifier_msgs::msg::UUID>(),  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(vectornav_msgs::action::MagCal_FeedbackMessage, goal_id),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "feedback",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<vectornav_msgs::action::MagCal_Feedback>(),  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(vectornav_msgs::action::MagCal_FeedbackMessage, feedback),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  }
};

static const ::rosidl_typesupport_introspection_cpp::MessageMembers MagCal_FeedbackMessage_message_members = {
  "vectornav_msgs::action",  // message namespace
  "MagCal_FeedbackMessage",  // message name
  2,  // number of fields
  sizeof(vectornav_msgs::action::MagCal_FeedbackMessage),
  MagCal_FeedbackMessage_message_member_array,  // message members
  MagCal_FeedbackMessage_init_function,  // function to initialize message memory (memory has to be allocated)
  MagCal_FeedbackMessage_fini_function  // function to terminate message instance (will not free memory)
};

static const rosidl_message_type_support_t MagCal_FeedbackMessage_message_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &MagCal_FeedbackMessage_message_members,
  get_message_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_introspection_cpp

}  // namespace action

}  // namespace vectornav_msgs


namespace rosidl_typesupport_introspection_cpp
{

template<>
ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<vectornav_msgs::action::MagCal_FeedbackMessage>()
{
  return &::vectornav_msgs::action::rosidl_typesupport_introspection_cpp::MagCal_FeedbackMessage_message_type_support_handle;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, vectornav_msgs, action, MagCal_FeedbackMessage)() {
  return &::vectornav_msgs::action::rosidl_typesupport_introspection_cpp::MagCal_FeedbackMessage_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif
