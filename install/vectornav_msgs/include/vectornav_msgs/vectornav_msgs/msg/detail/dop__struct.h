// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from vectornav_msgs:msg/DOP.idl
// generated code does not contain a copyright notice

#ifndef VECTORNAV_MSGS__MSG__DETAIL__DOP__STRUCT_H_
#define VECTORNAV_MSGS__MSG__DETAIL__DOP__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in msg/DOP in the package vectornav_msgs.
/**
  * VectorNav Dilution of Precision
  * UM005 - 5.7.14
 */
typedef struct vectornav_msgs__msg__DOP
{
  float g;
  float p;
  float t;
  float v;
  float h;
  float n;
  float e;
} vectornav_msgs__msg__DOP;

// Struct for a sequence of vectornav_msgs__msg__DOP.
typedef struct vectornav_msgs__msg__DOP__Sequence
{
  vectornav_msgs__msg__DOP * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} vectornav_msgs__msg__DOP__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // VECTORNAV_MSGS__MSG__DETAIL__DOP__STRUCT_H_
