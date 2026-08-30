// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from vectornav_msgs:msg/TimeStatus.idl
// generated code does not contain a copyright notice

#ifndef VECTORNAV_MSGS__MSG__DETAIL__TIME_STATUS__STRUCT_H_
#define VECTORNAV_MSGS__MSG__DETAIL__TIME_STATUS__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in msg/TimeStatus in the package vectornav_msgs.
/**
  * VectorNav Time Status
  * UM001 - 4.7.1
 */
typedef struct vectornav_msgs__msg__TimeStatus
{
  bool time_ok;
  bool date_ok;
  bool utctime_ok;
} vectornav_msgs__msg__TimeStatus;

// Struct for a sequence of vectornav_msgs__msg__TimeStatus.
typedef struct vectornav_msgs__msg__TimeStatus__Sequence
{
  vectornav_msgs__msg__TimeStatus * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} vectornav_msgs__msg__TimeStatus__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // VECTORNAV_MSGS__MSG__DETAIL__TIME_STATUS__STRUCT_H_
