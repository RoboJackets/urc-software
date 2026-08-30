// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from vectornav_msgs:msg/InsStatus.idl
// generated code does not contain a copyright notice

#ifndef VECTORNAV_MSGS__MSG__DETAIL__INS_STATUS__STRUCT_H_
#define VECTORNAV_MSGS__MSG__DETAIL__INS_STATUS__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Constant 'MODE_NOT_TRACKING'.
enum
{
  vectornav_msgs__msg__InsStatus__MODE_NOT_TRACKING = 0
};

/// Constant 'MODE_ALIGNING'.
enum
{
  vectornav_msgs__msg__InsStatus__MODE_ALIGNING = 1
};

/// Constant 'MODE_TRACKING'.
enum
{
  vectornav_msgs__msg__InsStatus__MODE_TRACKING = 2
};

/// Constant 'MODE_NO_GPS'.
enum
{
  vectornav_msgs__msg__InsStatus__MODE_NO_GPS = 3
};

/// Struct defined in msg/InsStatus in the package vectornav_msgs.
/**
  * VectorNav Time Status
  * UM005 - 10.2.2
 */
typedef struct vectornav_msgs__msg__InsStatus
{
  /// TODO VNCXX does not match manual exactly
  uint8_t mode;
  bool gps_fix;
  bool time_error;
  bool imu_error;
  bool mag_pres_error;
  bool gps_error;
  bool gps_heading_ins;
  bool gps_compass;
} vectornav_msgs__msg__InsStatus;

// Struct for a sequence of vectornav_msgs__msg__InsStatus.
typedef struct vectornav_msgs__msg__InsStatus__Sequence
{
  vectornav_msgs__msg__InsStatus * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} vectornav_msgs__msg__InsStatus__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // VECTORNAV_MSGS__MSG__DETAIL__INS_STATUS__STRUCT_H_
