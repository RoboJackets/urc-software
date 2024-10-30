// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from urc_msgs:msg/BatteryInfo.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "urc_msgs/msg/detail/battery_info__rosidl_typesupport_introspection_c.h"
#include "urc_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "urc_msgs/msg/detail/battery_info__functions.h"
#include "urc_msgs/msg/detail/battery_info__struct.h"


// Include directives for member types
// Member `cell_voltages`
#include "rosidl_runtime_c/primitives_sequence_functions.h"

#ifdef __cplusplus
extern "C"
{
#endif

void urc_msgs__msg__BatteryInfo__rosidl_typesupport_introspection_c__BatteryInfo_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  urc_msgs__msg__BatteryInfo__init(message_memory);
}

void urc_msgs__msg__BatteryInfo__rosidl_typesupport_introspection_c__BatteryInfo_fini_function(void * message_memory)
{
  urc_msgs__msg__BatteryInfo__fini(message_memory);
}

size_t urc_msgs__msg__BatteryInfo__rosidl_typesupport_introspection_c__size_function__BatteryInfo__cell_voltages(
  const void * untyped_member)
{
  const rosidl_runtime_c__float__Sequence * member =
    (const rosidl_runtime_c__float__Sequence *)(untyped_member);
  return member->size;
}

const void * urc_msgs__msg__BatteryInfo__rosidl_typesupport_introspection_c__get_const_function__BatteryInfo__cell_voltages(
  const void * untyped_member, size_t index)
{
  const rosidl_runtime_c__float__Sequence * member =
    (const rosidl_runtime_c__float__Sequence *)(untyped_member);
  return &member->data[index];
}

void * urc_msgs__msg__BatteryInfo__rosidl_typesupport_introspection_c__get_function__BatteryInfo__cell_voltages(
  void * untyped_member, size_t index)
{
  rosidl_runtime_c__float__Sequence * member =
    (rosidl_runtime_c__float__Sequence *)(untyped_member);
  return &member->data[index];
}

void urc_msgs__msg__BatteryInfo__rosidl_typesupport_introspection_c__fetch_function__BatteryInfo__cell_voltages(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const float * item =
    ((const float *)
    urc_msgs__msg__BatteryInfo__rosidl_typesupport_introspection_c__get_const_function__BatteryInfo__cell_voltages(untyped_member, index));
  float * value =
    (float *)(untyped_value);
  *value = *item;
}

void urc_msgs__msg__BatteryInfo__rosidl_typesupport_introspection_c__assign_function__BatteryInfo__cell_voltages(
  void * untyped_member, size_t index, const void * untyped_value)
{
  float * item =
    ((float *)
    urc_msgs__msg__BatteryInfo__rosidl_typesupport_introspection_c__get_function__BatteryInfo__cell_voltages(untyped_member, index));
  const float * value =
    (const float *)(untyped_value);
  *item = *value;
}

bool urc_msgs__msg__BatteryInfo__rosidl_typesupport_introspection_c__resize_function__BatteryInfo__cell_voltages(
  void * untyped_member, size_t size)
{
  rosidl_runtime_c__float__Sequence * member =
    (rosidl_runtime_c__float__Sequence *)(untyped_member);
  rosidl_runtime_c__float__Sequence__fini(member);
  return rosidl_runtime_c__float__Sequence__init(member, size);
}

static rosidl_typesupport_introspection_c__MessageMember urc_msgs__msg__BatteryInfo__rosidl_typesupport_introspection_c__BatteryInfo_message_member_array[5] = {
  {
    "cell_voltage",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(urc_msgs__msg__BatteryInfo, cell_voltage),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "cell_charge_percentage",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(urc_msgs__msg__BatteryInfo, cell_charge_percentage),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "cell_discharge_current",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(urc_msgs__msg__BatteryInfo, cell_discharge_current),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "cell_temperature",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(urc_msgs__msg__BatteryInfo, cell_temperature),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "cell_voltages",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(urc_msgs__msg__BatteryInfo, cell_voltages),  // bytes offset in struct
    NULL,  // default value
    urc_msgs__msg__BatteryInfo__rosidl_typesupport_introspection_c__size_function__BatteryInfo__cell_voltages,  // size() function pointer
    urc_msgs__msg__BatteryInfo__rosidl_typesupport_introspection_c__get_const_function__BatteryInfo__cell_voltages,  // get_const(index) function pointer
    urc_msgs__msg__BatteryInfo__rosidl_typesupport_introspection_c__get_function__BatteryInfo__cell_voltages,  // get(index) function pointer
    urc_msgs__msg__BatteryInfo__rosidl_typesupport_introspection_c__fetch_function__BatteryInfo__cell_voltages,  // fetch(index, &value) function pointer
    urc_msgs__msg__BatteryInfo__rosidl_typesupport_introspection_c__assign_function__BatteryInfo__cell_voltages,  // assign(index, value) function pointer
    urc_msgs__msg__BatteryInfo__rosidl_typesupport_introspection_c__resize_function__BatteryInfo__cell_voltages  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers urc_msgs__msg__BatteryInfo__rosidl_typesupport_introspection_c__BatteryInfo_message_members = {
  "urc_msgs__msg",  // message namespace
  "BatteryInfo",  // message name
  5,  // number of fields
  sizeof(urc_msgs__msg__BatteryInfo),
  urc_msgs__msg__BatteryInfo__rosidl_typesupport_introspection_c__BatteryInfo_message_member_array,  // message members
  urc_msgs__msg__BatteryInfo__rosidl_typesupport_introspection_c__BatteryInfo_init_function,  // function to initialize message memory (memory has to be allocated)
  urc_msgs__msg__BatteryInfo__rosidl_typesupport_introspection_c__BatteryInfo_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t urc_msgs__msg__BatteryInfo__rosidl_typesupport_introspection_c__BatteryInfo_message_type_support_handle = {
  0,
  &urc_msgs__msg__BatteryInfo__rosidl_typesupport_introspection_c__BatteryInfo_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_urc_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, urc_msgs, msg, BatteryInfo)() {
  if (!urc_msgs__msg__BatteryInfo__rosidl_typesupport_introspection_c__BatteryInfo_message_type_support_handle.typesupport_identifier) {
    urc_msgs__msg__BatteryInfo__rosidl_typesupport_introspection_c__BatteryInfo_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &urc_msgs__msg__BatteryInfo__rosidl_typesupport_introspection_c__BatteryInfo_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
