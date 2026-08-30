// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from vectornav_msgs:msg/VpeStatus.idl
// generated code does not contain a copyright notice

#ifndef VECTORNAV_MSGS__MSG__DETAIL__VPE_STATUS__STRUCT_H_
#define VECTORNAV_MSGS__MSG__DETAIL__VPE_STATUS__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in msg/VpeStatus in the package vectornav_msgs.
/**
  * VectorNav VPE Status
  * UM001 - 4.7.1
 */
typedef struct vectornav_msgs__msg__VpeStatus
{
  uint8_t attitude_quality;
  bool gyro_saturation;
  bool gyro_saturation_recovery;
  uint8_t mag_disturbance;
  bool mag_saturation;
  uint8_t acc_disturbance;
  bool acc_saturation;
  bool known_mag_disturbance;
  bool known_accel_disturbance;
} vectornav_msgs__msg__VpeStatus;

// Struct for a sequence of vectornav_msgs__msg__VpeStatus.
typedef struct vectornav_msgs__msg__VpeStatus__Sequence
{
  vectornav_msgs__msg__VpeStatus * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} vectornav_msgs__msg__VpeStatus__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // VECTORNAV_MSGS__MSG__DETAIL__VPE_STATUS__STRUCT_H_
