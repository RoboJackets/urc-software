// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from urc_msgs:msg/GridLocation.idl
// generated code does not contain a copyright notice

#ifndef URC_MSGS__MSG__DETAIL__GRID_LOCATION__STRUCT_H_
#define URC_MSGS__MSG__DETAIL__GRID_LOCATION__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in msg/GridLocation in the package urc_msgs.
typedef struct urc_msgs__msg__GridLocation
{
  uint16_t x;
  uint16_t y;
} urc_msgs__msg__GridLocation;

// Struct for a sequence of urc_msgs__msg__GridLocation.
typedef struct urc_msgs__msg__GridLocation__Sequence
{
  urc_msgs__msg__GridLocation * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} urc_msgs__msg__GridLocation__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // URC_MSGS__MSG__DETAIL__GRID_LOCATION__STRUCT_H_
