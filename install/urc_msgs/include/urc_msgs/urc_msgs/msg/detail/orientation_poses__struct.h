// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from urc_msgs:msg/OrientationPoses.idl
// generated code does not contain a copyright notice

#ifndef URC_MSGS__MSG__DETAIL__ORIENTATION_POSES__STRUCT_H_
#define URC_MSGS__MSG__DETAIL__ORIENTATION_POSES__STRUCT_H_

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
// Member 'names'
#include "rosidl_runtime_c/string.h"
// Member 'poses'
#include "geometry_msgs/msg/detail/pose__struct.h"

/// Struct defined in msg/OrientationPoses in the package urc_msgs.
typedef struct urc_msgs__msg__OrientationPoses
{
  std_msgs__msg__Header header;
  rosidl_runtime_c__String__Sequence names;
  geometry_msgs__msg__Pose__Sequence poses;
} urc_msgs__msg__OrientationPoses;

// Struct for a sequence of urc_msgs__msg__OrientationPoses.
typedef struct urc_msgs__msg__OrientationPoses__Sequence
{
  urc_msgs__msg__OrientationPoses * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} urc_msgs__msg__OrientationPoses__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // URC_MSGS__MSG__DETAIL__ORIENTATION_POSES__STRUCT_H_
