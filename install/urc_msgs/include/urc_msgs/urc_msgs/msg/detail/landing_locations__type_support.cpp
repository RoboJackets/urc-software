// generated from rosidl_typesupport_introspection_cpp/resource/idl__type_support.cpp.em
// with input from urc_msgs:msg/LandingLocations.idl
// generated code does not contain a copyright notice

#include "array"
#include "cstddef"
#include "string"
#include "vector"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_interface/macros.h"
#include "urc_msgs/msg/detail/landing_locations__struct.hpp"
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

void LandingLocations_init_function(
  void * message_memory, rosidl_runtime_cpp::MessageInitialization _init)
{
  new (message_memory) urc_msgs::msg::LandingLocations(_init);
}

void LandingLocations_fini_function(void * message_memory)
{
  auto typed_message = static_cast<urc_msgs::msg::LandingLocations *>(message_memory);
  typed_message->~LandingLocations();
}

size_t size_function__LandingLocations__latitudes(const void * untyped_member)
{
  (void)untyped_member;
  return 100;
}

const void * get_const_function__LandingLocations__latitudes(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::array<double, 100> *>(untyped_member);
  return &member[index];
}

void * get_function__LandingLocations__latitudes(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::array<double, 100> *>(untyped_member);
  return &member[index];
}

void fetch_function__LandingLocations__latitudes(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const double *>(
    get_const_function__LandingLocations__latitudes(untyped_member, index));
  auto & value = *reinterpret_cast<double *>(untyped_value);
  value = item;
}

void assign_function__LandingLocations__latitudes(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<double *>(
    get_function__LandingLocations__latitudes(untyped_member, index));
  const auto & value = *reinterpret_cast<const double *>(untyped_value);
  item = value;
}

size_t size_function__LandingLocations__longitudes(const void * untyped_member)
{
  (void)untyped_member;
  return 100;
}

const void * get_const_function__LandingLocations__longitudes(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::array<double, 100> *>(untyped_member);
  return &member[index];
}

void * get_function__LandingLocations__longitudes(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::array<double, 100> *>(untyped_member);
  return &member[index];
}

void fetch_function__LandingLocations__longitudes(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const double *>(
    get_const_function__LandingLocations__longitudes(untyped_member, index));
  auto & value = *reinterpret_cast<double *>(untyped_value);
  value = item;
}

void assign_function__LandingLocations__longitudes(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<double *>(
    get_function__LandingLocations__longitudes(untyped_member, index));
  const auto & value = *reinterpret_cast<const double *>(untyped_value);
  item = value;
}

static const ::rosidl_typesupport_introspection_cpp::MessageMember LandingLocations_message_member_array[4] = {
  {
    "header",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<std_msgs::msg::Header>(),  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(urc_msgs::msg::LandingLocations, header),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "num_locations",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_INT32,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(urc_msgs::msg::LandingLocations, num_locations),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "latitudes",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    true,  // is array
    100,  // array size
    false,  // is upper bound
    offsetof(urc_msgs::msg::LandingLocations, latitudes),  // bytes offset in struct
    nullptr,  // default value
    size_function__LandingLocations__latitudes,  // size() function pointer
    get_const_function__LandingLocations__latitudes,  // get_const(index) function pointer
    get_function__LandingLocations__latitudes,  // get(index) function pointer
    fetch_function__LandingLocations__latitudes,  // fetch(index, &value) function pointer
    assign_function__LandingLocations__latitudes,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "longitudes",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    true,  // is array
    100,  // array size
    false,  // is upper bound
    offsetof(urc_msgs::msg::LandingLocations, longitudes),  // bytes offset in struct
    nullptr,  // default value
    size_function__LandingLocations__longitudes,  // size() function pointer
    get_const_function__LandingLocations__longitudes,  // get_const(index) function pointer
    get_function__LandingLocations__longitudes,  // get(index) function pointer
    fetch_function__LandingLocations__longitudes,  // fetch(index, &value) function pointer
    assign_function__LandingLocations__longitudes,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  }
};

static const ::rosidl_typesupport_introspection_cpp::MessageMembers LandingLocations_message_members = {
  "urc_msgs::msg",  // message namespace
  "LandingLocations",  // message name
  4,  // number of fields
  sizeof(urc_msgs::msg::LandingLocations),
  LandingLocations_message_member_array,  // message members
  LandingLocations_init_function,  // function to initialize message memory (memory has to be allocated)
  LandingLocations_fini_function  // function to terminate message instance (will not free memory)
};

static const rosidl_message_type_support_t LandingLocations_message_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &LandingLocations_message_members,
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
get_message_type_support_handle<urc_msgs::msg::LandingLocations>()
{
  return &::urc_msgs::msg::rosidl_typesupport_introspection_cpp::LandingLocations_message_type_support_handle;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, urc_msgs, msg, LandingLocations)() {
  return &::urc_msgs::msg::rosidl_typesupport_introspection_cpp::LandingLocations_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif
