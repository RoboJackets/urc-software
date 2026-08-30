// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from vectornav_msgs:msg/TimeUTC.idl
// generated code does not contain a copyright notice

#ifndef VECTORNAV_MSGS__MSG__DETAIL__TIME_UTC__STRUCT_H_
#define VECTORNAV_MSGS__MSG__DETAIL__TIME_UTC__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in msg/TimeUTC in the package vectornav_msgs.
/**
  * VectorNav Timestamp (UTC)
 */
typedef struct vectornav_msgs__msg__TimeUTC
{
  uint8_t year;
  uint8_t month;
  uint8_t day;
  uint8_t hour;
  uint8_t min;
  uint8_t sec;
  uint16_t ms;
} vectornav_msgs__msg__TimeUTC;

// Struct for a sequence of vectornav_msgs__msg__TimeUTC.
typedef struct vectornav_msgs__msg__TimeUTC__Sequence
{
  vectornav_msgs__msg__TimeUTC * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} vectornav_msgs__msg__TimeUTC__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // VECTORNAV_MSGS__MSG__DETAIL__TIME_UTC__STRUCT_H_
