// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from urc_msgs:msg/LandingLocations.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "urc_msgs/msg/detail/landing_locations__rosidl_typesupport_introspection_c.h"
#include "urc_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "urc_msgs/msg/detail/landing_locations__functions.h"
#include "urc_msgs/msg/detail/landing_locations__struct.h"


// Include directives for member types
// Member `header`
#include "std_msgs/msg/header.h"
// Member `header`
#include "std_msgs/msg/detail/header__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void urc_msgs__msg__LandingLocations__rosidl_typesupport_introspection_c__LandingLocations_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  urc_msgs__msg__LandingLocations__init(message_memory);
}

void urc_msgs__msg__LandingLocations__rosidl_typesupport_introspection_c__LandingLocations_fini_function(void * message_memory)
{
  urc_msgs__msg__LandingLocations__fini(message_memory);
}

size_t urc_msgs__msg__LandingLocations__rosidl_typesupport_introspection_c__size_function__LandingLocations__latitudes(
  const void * untyped_member)
{
  (void)untyped_member;
  return 100;
}

const void * urc_msgs__msg__LandingLocations__rosidl_typesupport_introspection_c__get_const_function__LandingLocations__latitudes(
  const void * untyped_member, size_t index)
{
  const double * member =
    (const double *)(untyped_member);
  return &member[index];
}

void * urc_msgs__msg__LandingLocations__rosidl_typesupport_introspection_c__get_function__LandingLocations__latitudes(
  void * untyped_member, size_t index)
{
  double * member =
    (double *)(untyped_member);
  return &member[index];
}

void urc_msgs__msg__LandingLocations__rosidl_typesupport_introspection_c__fetch_function__LandingLocations__latitudes(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const double * item =
    ((const double *)
    urc_msgs__msg__LandingLocations__rosidl_typesupport_introspection_c__get_const_function__LandingLocations__latitudes(untyped_member, index));
  double * value =
    (double *)(untyped_value);
  *value = *item;
}

void urc_msgs__msg__LandingLocations__rosidl_typesupport_introspection_c__assign_function__LandingLocations__latitudes(
  void * untyped_member, size_t index, const void * untyped_value)
{
  double * item =
    ((double *)
    urc_msgs__msg__LandingLocations__rosidl_typesupport_introspection_c__get_function__LandingLocations__latitudes(untyped_member, index));
  const double * value =
    (const double *)(untyped_value);
  *item = *value;
}

size_t urc_msgs__msg__LandingLocations__rosidl_typesupport_introspection_c__size_function__LandingLocations__longitudes(
  const void * untyped_member)
{
  (void)untyped_member;
  return 100;
}

const void * urc_msgs__msg__LandingLocations__rosidl_typesupport_introspection_c__get_const_function__LandingLocations__longitudes(
  const void * untyped_member, size_t index)
{
  const double * member =
    (const double *)(untyped_member);
  return &member[index];
}

void * urc_msgs__msg__LandingLocations__rosidl_typesupport_introspection_c__get_function__LandingLocations__longitudes(
  void * untyped_member, size_t index)
{
  double * member =
    (double *)(untyped_member);
  return &member[index];
}

void urc_msgs__msg__LandingLocations__rosidl_typesupport_introspection_c__fetch_function__LandingLocations__longitudes(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const double * item =
    ((const double *)
    urc_msgs__msg__LandingLocations__rosidl_typesupport_introspection_c__get_const_function__LandingLocations__longitudes(untyped_member, index));
  double * value =
    (double *)(untyped_value);
  *value = *item;
}

void urc_msgs__msg__LandingLocations__rosidl_typesupport_introspection_c__assign_function__LandingLocations__longitudes(
  void * untyped_member, size_t index, const void * untyped_value)
{
  double * item =
    ((double *)
    urc_msgs__msg__LandingLocations__rosidl_typesupport_introspection_c__get_function__LandingLocations__longitudes(untyped_member, index));
  const double * value =
    (const double *)(untyped_value);
  *item = *value;
}

static rosidl_typesupport_introspection_c__MessageMember urc_msgs__msg__LandingLocations__rosidl_typesupport_introspection_c__LandingLocations_message_member_array[4] = {
  {
    "header",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(urc_msgs__msg__LandingLocations, header),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "num_locations",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT32,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(urc_msgs__msg__LandingLocations, num_locations),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "latitudes",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    true,  // is array
    100,  // array size
    false,  // is upper bound
    offsetof(urc_msgs__msg__LandingLocations, latitudes),  // bytes offset in struct
    NULL,  // default value
    urc_msgs__msg__LandingLocations__rosidl_typesupport_introspection_c__size_function__LandingLocations__latitudes,  // size() function pointer
    urc_msgs__msg__LandingLocations__rosidl_typesupport_introspection_c__get_const_function__LandingLocations__latitudes,  // get_const(index) function pointer
    urc_msgs__msg__LandingLocations__rosidl_typesupport_introspection_c__get_function__LandingLocations__latitudes,  // get(index) function pointer
    urc_msgs__msg__LandingLocations__rosidl_typesupport_introspection_c__fetch_function__LandingLocations__latitudes,  // fetch(index, &value) function pointer
    urc_msgs__msg__LandingLocations__rosidl_typesupport_introspection_c__assign_function__LandingLocations__latitudes,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "longitudes",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    true,  // is array
    100,  // array size
    false,  // is upper bound
    offsetof(urc_msgs__msg__LandingLocations, longitudes),  // bytes offset in struct
    NULL,  // default value
    urc_msgs__msg__LandingLocations__rosidl_typesupport_introspection_c__size_function__LandingLocations__longitudes,  // size() function pointer
    urc_msgs__msg__LandingLocations__rosidl_typesupport_introspection_c__get_const_function__LandingLocations__longitudes,  // get_const(index) function pointer
    urc_msgs__msg__LandingLocations__rosidl_typesupport_introspection_c__get_function__LandingLocations__longitudes,  // get(index) function pointer
    urc_msgs__msg__LandingLocations__rosidl_typesupport_introspection_c__fetch_function__LandingLocations__longitudes,  // fetch(index, &value) function pointer
    urc_msgs__msg__LandingLocations__rosidl_typesupport_introspection_c__assign_function__LandingLocations__longitudes,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers urc_msgs__msg__LandingLocations__rosidl_typesupport_introspection_c__LandingLocations_message_members = {
  "urc_msgs__msg",  // message namespace
  "LandingLocations",  // message name
  4,  // number of fields
  sizeof(urc_msgs__msg__LandingLocations),
  urc_msgs__msg__LandingLocations__rosidl_typesupport_introspection_c__LandingLocations_message_member_array,  // message members
  urc_msgs__msg__LandingLocations__rosidl_typesupport_introspection_c__LandingLocations_init_function,  // function to initialize message memory (memory has to be allocated)
  urc_msgs__msg__LandingLocations__rosidl_typesupport_introspection_c__LandingLocations_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t urc_msgs__msg__LandingLocations__rosidl_typesupport_introspection_c__LandingLocations_message_type_support_handle = {
  0,
  &urc_msgs__msg__LandingLocations__rosidl_typesupport_introspection_c__LandingLocations_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_urc_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, urc_msgs, msg, LandingLocations)() {
  urc_msgs__msg__LandingLocations__rosidl_typesupport_introspection_c__LandingLocations_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, std_msgs, msg, Header)();
  if (!urc_msgs__msg__LandingLocations__rosidl_typesupport_introspection_c__LandingLocations_message_type_support_handle.typesupport_identifier) {
    urc_msgs__msg__LandingLocations__rosidl_typesupport_introspection_c__LandingLocations_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &urc_msgs__msg__LandingLocations__rosidl_typesupport_introspection_c__LandingLocations_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
