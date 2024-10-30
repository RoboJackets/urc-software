// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from urc_msgs:msg/ArucoLocation.idl
// generated code does not contain a copyright notice

#ifndef URC_MSGS__MSG__DETAIL__ARUCO_LOCATION__STRUCT_H_
#define URC_MSGS__MSG__DETAIL__ARUCO_LOCATION__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__struct.h"
// Member 'which_camera'
#include "rosidl_runtime_c/string.h"

/// Struct defined in msg/ArucoLocation in the package urc_msgs.
typedef struct urc_msgs__msg__ArucoLocation
{
  std_msgs__msg__Header header;
  double lon;
  double lat;
  uint64_t id;
  rosidl_runtime_c__String which_camera;
} urc_msgs__msg__ArucoLocation;

// Struct for a sequence of urc_msgs__msg__ArucoLocation.
typedef struct urc_msgs__msg__ArucoLocation__Sequence
{
  urc_msgs__msg__ArucoLocation * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} urc_msgs__msg__ArucoLocation__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // URC_MSGS__MSG__DETAIL__ARUCO_LOCATION__STRUCT_H_
