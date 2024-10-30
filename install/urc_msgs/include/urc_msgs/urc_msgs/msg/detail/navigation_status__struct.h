// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from urc_msgs:msg/NavigationStatus.idl
// generated code does not contain a copyright notice

#ifndef URC_MSGS__MSG__DETAIL__NAVIGATION_STATUS__STRUCT_H_
#define URC_MSGS__MSG__DETAIL__NAVIGATION_STATUS__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'message'
#include "rosidl_runtime_c/string.h"

/// Struct defined in msg/NavigationStatus in the package urc_msgs.
typedef struct urc_msgs__msg__NavigationStatus
{
  rosidl_runtime_c__String message;
} urc_msgs__msg__NavigationStatus;

// Struct for a sequence of urc_msgs__msg__NavigationStatus.
typedef struct urc_msgs__msg__NavigationStatus__Sequence
{
  urc_msgs__msg__NavigationStatus * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} urc_msgs__msg__NavigationStatus__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // URC_MSGS__MSG__DETAIL__NAVIGATION_STATUS__STRUCT_H_
