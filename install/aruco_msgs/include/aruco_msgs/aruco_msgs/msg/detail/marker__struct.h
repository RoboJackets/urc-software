// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from aruco_msgs:msg/Marker.idl
// generated code does not contain a copyright notice

#ifndef ARUCO_MSGS__MSG__DETAIL__MARKER__STRUCT_H_
#define ARUCO_MSGS__MSG__DETAIL__MARKER__STRUCT_H_

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
// Member 'pose'
#include "geometry_msgs/msg/detail/pose_with_covariance__struct.h"

/// Struct defined in msg/Marker in the package aruco_msgs.
typedef struct aruco_msgs__msg__Marker
{
  std_msgs__msg__Header header;
  uint32_t id;
  geometry_msgs__msg__PoseWithCovariance pose;
  double confidence;
} aruco_msgs__msg__Marker;

// Struct for a sequence of aruco_msgs__msg__Marker.
typedef struct aruco_msgs__msg__Marker__Sequence
{
  aruco_msgs__msg__Marker * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} aruco_msgs__msg__Marker__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // ARUCO_MSGS__MSG__DETAIL__MARKER__STRUCT_H_
