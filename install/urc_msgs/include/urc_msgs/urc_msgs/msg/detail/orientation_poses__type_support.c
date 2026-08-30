// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from urc_msgs:msg/OrientationPoses.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "urc_msgs/msg/detail/orientation_poses__rosidl_typesupport_introspection_c.h"
#include "urc_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "urc_msgs/msg/detail/orientation_poses__functions.h"
#include "urc_msgs/msg/detail/orientation_poses__struct.h"


// Include directives for member types
// Member `header`
#include "std_msgs/msg/header.h"
// Member `header`
#include "std_msgs/msg/detail/header__rosidl_typesupport_introspection_c.h"
// Member `names`
#include "rosidl_runtime_c/string_functions.h"
// Member `poses`
#include "geometry_msgs/msg/pose.h"
// Member `poses`
#include "geometry_msgs/msg/detail/pose__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void urc_msgs__msg__OrientationPoses__rosidl_typesupport_introspection_c__OrientationPoses_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  urc_msgs__msg__OrientationPoses__init(message_memory);
}

void urc_msgs__msg__OrientationPoses__rosidl_typesupport_introspection_c__OrientationPoses_fini_function(void * message_memory)
{
  urc_msgs__msg__OrientationPoses__fini(message_memory);
}

size_t urc_msgs__msg__OrientationPoses__rosidl_typesupport_introspection_c__size_function__OrientationPoses__names(
  const void * untyped_member)
{
  const rosidl_runtime_c__String__Sequence * member =
    (const rosidl_runtime_c__String__Sequence *)(untyped_member);
  return member->size;
}

const void * urc_msgs__msg__OrientationPoses__rosidl_typesupport_introspection_c__get_const_function__OrientationPoses__names(
  const void * untyped_member, size_t index)
{
  const rosidl_runtime_c__String__Sequence * member =
    (const rosidl_runtime_c__String__Sequence *)(untyped_member);
  return &member->data[index];
}

void * urc_msgs__msg__OrientationPoses__rosidl_typesupport_introspection_c__get_function__OrientationPoses__names(
  void * untyped_member, size_t index)
{
  rosidl_runtime_c__String__Sequence * member =
    (rosidl_runtime_c__String__Sequence *)(untyped_member);
  return &member->data[index];
}

void urc_msgs__msg__OrientationPoses__rosidl_typesupport_introspection_c__fetch_function__OrientationPoses__names(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const rosidl_runtime_c__String * item =
    ((const rosidl_runtime_c__String *)
    urc_msgs__msg__OrientationPoses__rosidl_typesupport_introspection_c__get_const_function__OrientationPoses__names(untyped_member, index));
  rosidl_runtime_c__String * value =
    (rosidl_runtime_c__String *)(untyped_value);
  *value = *item;
}

void urc_msgs__msg__OrientationPoses__rosidl_typesupport_introspection_c__assign_function__OrientationPoses__names(
  void * untyped_member, size_t index, const void * untyped_value)
{
  rosidl_runtime_c__String * item =
    ((rosidl_runtime_c__String *)
    urc_msgs__msg__OrientationPoses__rosidl_typesupport_introspection_c__get_function__OrientationPoses__names(untyped_member, index));
  const rosidl_runtime_c__String * value =
    (const rosidl_runtime_c__String *)(untyped_value);
  *item = *value;
}

bool urc_msgs__msg__OrientationPoses__rosidl_typesupport_introspection_c__resize_function__OrientationPoses__names(
  void * untyped_member, size_t size)
{
  rosidl_runtime_c__String__Sequence * member =
    (rosidl_runtime_c__String__Sequence *)(untyped_member);
  rosidl_runtime_c__String__Sequence__fini(member);
  return rosidl_runtime_c__String__Sequence__init(member, size);
}

size_t urc_msgs__msg__OrientationPoses__rosidl_typesupport_introspection_c__size_function__OrientationPoses__poses(
  const void * untyped_member)
{
  const geometry_msgs__msg__Pose__Sequence * member =
    (const geometry_msgs__msg__Pose__Sequence *)(untyped_member);
  return member->size;
}

const void * urc_msgs__msg__OrientationPoses__rosidl_typesupport_introspection_c__get_const_function__OrientationPoses__poses(
  const void * untyped_member, size_t index)
{
  const geometry_msgs__msg__Pose__Sequence * member =
    (const geometry_msgs__msg__Pose__Sequence *)(untyped_member);
  return &member->data[index];
}

void * urc_msgs__msg__OrientationPoses__rosidl_typesupport_introspection_c__get_function__OrientationPoses__poses(
  void * untyped_member, size_t index)
{
  geometry_msgs__msg__Pose__Sequence * member =
    (geometry_msgs__msg__Pose__Sequence *)(untyped_member);
  return &member->data[index];
}

void urc_msgs__msg__OrientationPoses__rosidl_typesupport_introspection_c__fetch_function__OrientationPoses__poses(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const geometry_msgs__msg__Pose * item =
    ((const geometry_msgs__msg__Pose *)
    urc_msgs__msg__OrientationPoses__rosidl_typesupport_introspection_c__get_const_function__OrientationPoses__poses(untyped_member, index));
  geometry_msgs__msg__Pose * value =
    (geometry_msgs__msg__Pose *)(untyped_value);
  *value = *item;
}

void urc_msgs__msg__OrientationPoses__rosidl_typesupport_introspection_c__assign_function__OrientationPoses__poses(
  void * untyped_member, size_t index, const void * untyped_value)
{
  geometry_msgs__msg__Pose * item =
    ((geometry_msgs__msg__Pose *)
    urc_msgs__msg__OrientationPoses__rosidl_typesupport_introspection_c__get_function__OrientationPoses__poses(untyped_member, index));
  const geometry_msgs__msg__Pose * value =
    (const geometry_msgs__msg__Pose *)(untyped_value);
  *item = *value;
}

bool urc_msgs__msg__OrientationPoses__rosidl_typesupport_introspection_c__resize_function__OrientationPoses__poses(
  void * untyped_member, size_t size)
{
  geometry_msgs__msg__Pose__Sequence * member =
    (geometry_msgs__msg__Pose__Sequence *)(untyped_member);
  geometry_msgs__msg__Pose__Sequence__fini(member);
  return geometry_msgs__msg__Pose__Sequence__init(member, size);
}

static rosidl_typesupport_introspection_c__MessageMember urc_msgs__msg__OrientationPoses__rosidl_typesupport_introspection_c__OrientationPoses_message_member_array[3] = {
  {
    "header",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(urc_msgs__msg__OrientationPoses, header),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "names",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(urc_msgs__msg__OrientationPoses, names),  // bytes offset in struct
    NULL,  // default value
    urc_msgs__msg__OrientationPoses__rosidl_typesupport_introspection_c__size_function__OrientationPoses__names,  // size() function pointer
    urc_msgs__msg__OrientationPoses__rosidl_typesupport_introspection_c__get_const_function__OrientationPoses__names,  // get_const(index) function pointer
    urc_msgs__msg__OrientationPoses__rosidl_typesupport_introspection_c__get_function__OrientationPoses__names,  // get(index) function pointer
    urc_msgs__msg__OrientationPoses__rosidl_typesupport_introspection_c__fetch_function__OrientationPoses__names,  // fetch(index, &value) function pointer
    urc_msgs__msg__OrientationPoses__rosidl_typesupport_introspection_c__assign_function__OrientationPoses__names,  // assign(index, value) function pointer
    urc_msgs__msg__OrientationPoses__rosidl_typesupport_introspection_c__resize_function__OrientationPoses__names  // resize(index) function pointer
  },
  {
    "poses",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(urc_msgs__msg__OrientationPoses, poses),  // bytes offset in struct
    NULL,  // default value
    urc_msgs__msg__OrientationPoses__rosidl_typesupport_introspection_c__size_function__OrientationPoses__poses,  // size() function pointer
    urc_msgs__msg__OrientationPoses__rosidl_typesupport_introspection_c__get_const_function__OrientationPoses__poses,  // get_const(index) function pointer
    urc_msgs__msg__OrientationPoses__rosidl_typesupport_introspection_c__get_function__OrientationPoses__poses,  // get(index) function pointer
    urc_msgs__msg__OrientationPoses__rosidl_typesupport_introspection_c__fetch_function__OrientationPoses__poses,  // fetch(index, &value) function pointer
    urc_msgs__msg__OrientationPoses__rosidl_typesupport_introspection_c__assign_function__OrientationPoses__poses,  // assign(index, value) function pointer
    urc_msgs__msg__OrientationPoses__rosidl_typesupport_introspection_c__resize_function__OrientationPoses__poses  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers urc_msgs__msg__OrientationPoses__rosidl_typesupport_introspection_c__OrientationPoses_message_members = {
  "urc_msgs__msg",  // message namespace
  "OrientationPoses",  // message name
  3,  // number of fields
  sizeof(urc_msgs__msg__OrientationPoses),
  urc_msgs__msg__OrientationPoses__rosidl_typesupport_introspection_c__OrientationPoses_message_member_array,  // message members
  urc_msgs__msg__OrientationPoses__rosidl_typesupport_introspection_c__OrientationPoses_init_function,  // function to initialize message memory (memory has to be allocated)
  urc_msgs__msg__OrientationPoses__rosidl_typesupport_introspection_c__OrientationPoses_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t urc_msgs__msg__OrientationPoses__rosidl_typesupport_introspection_c__OrientationPoses_message_type_support_handle = {
  0,
  &urc_msgs__msg__OrientationPoses__rosidl_typesupport_introspection_c__OrientationPoses_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_urc_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, urc_msgs, msg, OrientationPoses)() {
  urc_msgs__msg__OrientationPoses__rosidl_typesupport_introspection_c__OrientationPoses_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, std_msgs, msg, Header)();
  urc_msgs__msg__OrientationPoses__rosidl_typesupport_introspection_c__OrientationPoses_message_member_array[2].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, geometry_msgs, msg, Pose)();
  if (!urc_msgs__msg__OrientationPoses__rosidl_typesupport_introspection_c__OrientationPoses_message_type_support_handle.typesupport_identifier) {
    urc_msgs__msg__OrientationPoses__rosidl_typesupport_introspection_c__OrientationPoses_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &urc_msgs__msg__OrientationPoses__rosidl_typesupport_introspection_c__OrientationPoses_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
