// generated from rosidl_typesupport_introspection_cpp/resource/idl__type_support.cpp.em
// with input from urc_msgs:msg/NavigationStatus.idl
// generated code does not contain a copyright notice

#include "array"
#include "cstddef"
#include "string"
#include "vector"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_interface/macros.h"
#include "urc_msgs/msg/detail/navigation_status__struct.hpp"
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

void NavigationStatus_init_function(
  void * message_memory, rosidl_runtime_cpp::MessageInitialization _init)
{
  new (message_memory) urc_msgs::msg::NavigationStatus(_init);
}

void NavigationStatus_fini_function(void * message_memory)
{
  auto typed_message = static_cast<urc_msgs::msg::NavigationStatus *>(message_memory);
  typed_message->~NavigationStatus();
}

static const ::rosidl_typesupport_introspection_cpp::MessageMember NavigationStatus_message_member_array[1] = {
  {
    "message",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(urc_msgs::msg::NavigationStatus, message),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  }
};

static const ::rosidl_typesupport_introspection_cpp::MessageMembers NavigationStatus_message_members = {
  "urc_msgs::msg",  // message namespace
  "NavigationStatus",  // message name
  1,  // number of fields
  sizeof(urc_msgs::msg::NavigationStatus),
  NavigationStatus_message_member_array,  // message members
  NavigationStatus_init_function,  // function to initialize message memory (memory has to be allocated)
  NavigationStatus_fini_function  // function to terminate message instance (will not free memory)
};

static const rosidl_message_type_support_t NavigationStatus_message_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &NavigationStatus_message_members,
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
get_message_type_support_handle<urc_msgs::msg::NavigationStatus>()
{
  return &::urc_msgs::msg::rosidl_typesupport_introspection_cpp::NavigationStatus_message_type_support_handle;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, urc_msgs, msg, NavigationStatus)() {
  return &::urc_msgs::msg::rosidl_typesupport_introspection_cpp::NavigationStatus_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif
