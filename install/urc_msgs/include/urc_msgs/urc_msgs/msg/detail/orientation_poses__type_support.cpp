// generated from rosidl_typesupport_introspection_cpp/resource/idl__type_support.cpp.em
// with input from urc_msgs:msg/OrientationPoses.idl
// generated code does not contain a copyright notice

#include "array"
#include "cstddef"
#include "string"
#include "vector"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_interface/macros.h"
#include "urc_msgs/msg/detail/orientation_poses__struct.hpp"
#include "rosidl_typesupport_introspection_cpp/field_types.hpp"
#include "rosidl_typesupport_introspection_cpp/identifier.hpp"
#include "rosidl_typesupport_introspection_cpp/message_introspection.hpp"
#include "rosidl_typesupport_introspection_cpp/message_type_support_decl.hpp"
#include "rosidl_typesupport_introspection_cpp/visibility_control.h"

namespace urc_msgs
{

namespace msg
{

namespace rosidl_typesupport_introspection_cpp
{

void OrientationPoses_init_function(
  void * message_memory, rosidl_runtime_cpp::MessageInitialization _init)
{
  new (message_memory) urc_msgs::msg::OrientationPoses(_init);
}

void OrientationPoses_fini_function(void * message_memory)
{
  auto typed_message = static_cast<urc_msgs::msg::OrientationPoses *>(message_memory);
  typed_message->~OrientationPoses();
}

size_t size_function__OrientationPoses__names(const void * untyped_member)
{
  const auto * member = reinterpret_cast<const std::vector<std::string> *>(untyped_member);
  return member->size();
}

const void * get_const_function__OrientationPoses__names(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::vector<std::string> *>(untyped_member);
  return &member[index];
}

void * get_function__OrientationPoses__names(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::vector<std::string> *>(untyped_member);
  return &member[index];
}

void fetch_function__OrientationPoses__names(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const std::string *>(
    get_const_function__OrientationPoses__names(untyped_member, index));
  auto & value = *reinterpret_cast<std::string *>(untyped_value);
  value = item;
}

void assign_function__OrientationPoses__names(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<std::string *>(
    get_function__OrientationPoses__names(untyped_member, index));
  const auto & value = *reinterpret_cast<const std::string *>(untyped_value);
  item = value;
}

void resize_function__OrientationPoses__names(void * untyped_member, size_t size)
{
  auto * member =
    reinterpret_cast<std::vector<std::string> *>(untyped_member);
  member->resize(size);
}

size_t size_function__OrientationPoses__poses(const void * untyped_member)
{
  const auto * member = reinterpret_cast<const std::vector<geometry_msgs::msg::Pose> *>(untyped_member);
  return member->size();
}

const void * get_const_function__OrientationPoses__poses(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::vector<geometry_msgs::msg::Pose> *>(untyped_member);
  return &member[index];
}

void * get_function__OrientationPoses__poses(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::vector<geometry_msgs::msg::Pose> *>(untyped_member);
  return &member[index];
}

void fetch_function__OrientationPoses__poses(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const geometry_msgs::msg::Pose *>(
    get_const_function__OrientationPoses__poses(untyped_member, index));
  auto & value = *reinterpret_cast<geometry_msgs::msg::Pose *>(untyped_value);
  value = item;
}

void assign_function__OrientationPoses__poses(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<geometry_msgs::msg::Pose *>(
    get_function__OrientationPoses__poses(untyped_member, index));
  const auto & value = *reinterpret_cast<const geometry_msgs::msg::Pose *>(untyped_value);
  item = value;
}

void resize_function__OrientationPoses__poses(void * untyped_member, size_t size)
{
  auto * member =
    reinterpret_cast<std::vector<geometry_msgs::msg::Pose> *>(untyped_member);
  member->resize(size);
}

static const ::rosidl_typesupport_introspection_cpp::MessageMember OrientationPoses_message_member_array[3] = {
  {
    "header",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<std_msgs::msg::Header>(),  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(urc_msgs::msg::OrientationPoses, header),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "names",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(urc_msgs::msg::OrientationPoses, names),  // bytes offset in struct
    nullptr,  // default value
    size_function__OrientationPoses__names,  // size() function pointer
    get_const_function__OrientationPoses__names,  // get_const(index) function pointer
    get_function__OrientationPoses__names,  // get(index) function pointer
    fetch_function__OrientationPoses__names,  // fetch(index, &value) function pointer
    assign_function__OrientationPoses__names,  // assign(index, value) function pointer
    resize_function__OrientationPoses__names  // resize(index) function pointer
  },
  {
    "poses",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<geometry_msgs::msg::Pose>(),  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(urc_msgs::msg::OrientationPoses, poses),  // bytes offset in struct
    nullptr,  // default value
    size_function__OrientationPoses__poses,  // size() function pointer
    get_const_function__OrientationPoses__poses,  // get_const(index) function pointer
    get_function__OrientationPoses__poses,  // get(index) function pointer
    fetch_function__OrientationPoses__poses,  // fetch(index, &value) function pointer
    assign_function__OrientationPoses__poses,  // assign(index, value) function pointer
    resize_function__OrientationPoses__poses  // resize(index) function pointer
  }
};

static const ::rosidl_typesupport_introspection_cpp::MessageMembers OrientationPoses_message_members = {
  "urc_msgs::msg",  // message namespace
  "OrientationPoses",  // message name
  3,  // number of fields
  sizeof(urc_msgs::msg::OrientationPoses),
  OrientationPoses_message_member_array,  // message members
  OrientationPoses_init_function,  // function to initialize message memory (memory has to be allocated)
  OrientationPoses_fini_function  // function to terminate message instance (will not free memory)
};

static const rosidl_message_type_support_t OrientationPoses_message_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &OrientationPoses_message_members,
  get_message_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_introspection_cpp

}  // namespace msg

}  // namespace urc_msgs


namespace rosidl_typesupport_introspection_cpp
{

template<>
ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<urc_msgs::msg::OrientationPoses>()
{
  return &::urc_msgs::msg::rosidl_typesupport_introspection_cpp::OrientationPoses_message_type_support_handle;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, urc_msgs, msg, OrientationPoses)() {
  return &::urc_msgs::msg::rosidl_typesupport_introspection_cpp::OrientationPoses_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif
