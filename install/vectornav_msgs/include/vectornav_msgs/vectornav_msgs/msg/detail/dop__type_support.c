// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from vectornav_msgs:msg/DOP.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "vectornav_msgs/msg/detail/dop__rosidl_typesupport_introspection_c.h"
#include "vectornav_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "vectornav_msgs/msg/detail/dop__functions.h"
#include "vectornav_msgs/msg/detail/dop__struct.h"


#ifdef __cplusplus
extern "C"
{
#endif

void vectornav_msgs__msg__DOP__rosidl_typesupport_introspection_c__DOP_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  vectornav_msgs__msg__DOP__init(message_memory);
}

void vectornav_msgs__msg__DOP__rosidl_typesupport_introspection_c__DOP_fini_function(void * message_memory)
{
  vectornav_msgs__msg__DOP__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember vectornav_msgs__msg__DOP__rosidl_typesupport_introspection_c__DOP_message_member_array[7] = {
  {
    "g",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(vectornav_msgs__msg__DOP, g),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "p",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(vectornav_msgs__msg__DOP, p),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "t",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(vectornav_msgs__msg__DOP, t),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "v",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(vectornav_msgs__msg__DOP, v),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "h",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(vectornav_msgs__msg__DOP, h),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "n",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(vectornav_msgs__msg__DOP, n),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "e",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(vectornav_msgs__msg__DOP, e),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers vectornav_msgs__msg__DOP__rosidl_typesupport_introspection_c__DOP_message_members = {
  "vectornav_msgs__msg",  // message namespace
  "DOP",  // message name
  7,  // number of fields
  sizeof(vectornav_msgs__msg__DOP),
  vectornav_msgs__msg__DOP__rosidl_typesupport_introspection_c__DOP_message_member_array,  // message members
  vectornav_msgs__msg__DOP__rosidl_typesupport_introspection_c__DOP_init_function,  // function to initialize message memory (memory has to be allocated)
  vectornav_msgs__msg__DOP__rosidl_typesupport_introspection_c__DOP_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t vectornav_msgs__msg__DOP__rosidl_typesupport_introspection_c__DOP_message_type_support_handle = {
  0,
  &vectornav_msgs__msg__DOP__rosidl_typesupport_introspection_c__DOP_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_vectornav_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, vectornav_msgs, msg, DOP)() {
  if (!vectornav_msgs__msg__DOP__rosidl_typesupport_introspection_c__DOP_message_type_support_handle.typesupport_identifier) {
    vectornav_msgs__msg__DOP__rosidl_typesupport_introspection_c__DOP_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &vectornav_msgs__msg__DOP__rosidl_typesupport_introspection_c__DOP_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
