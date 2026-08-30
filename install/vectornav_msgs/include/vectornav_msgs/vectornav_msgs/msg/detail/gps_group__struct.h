// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from vectornav_msgs:msg/GpsGroup.idl
// generated code does not contain a copyright notice

#ifndef VECTORNAV_MSGS__MSG__DETAIL__GPS_GROUP__STRUCT_H_
#define VECTORNAV_MSGS__MSG__DETAIL__GPS_GROUP__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Constant 'GPSGROUP_UTC'.
enum
{
  vectornav_msgs__msg__GpsGroup__GPSGROUP_UTC = 1
};

/// Constant 'GPSGROUP_TOW'.
enum
{
  vectornav_msgs__msg__GpsGroup__GPSGROUP_TOW = 2
};

/// Constant 'GPSGROUP_WEEK'.
enum
{
  vectornav_msgs__msg__GpsGroup__GPSGROUP_WEEK = 4
};

/// Constant 'GPSGROUP_NUMSATS'.
enum
{
  vectornav_msgs__msg__GpsGroup__GPSGROUP_NUMSATS = 8
};

/// Constant 'GPSGROUP_FIX'.
enum
{
  vectornav_msgs__msg__GpsGroup__GPSGROUP_FIX = 16
};

/// Constant 'GPSGROUP_POSLLA'.
enum
{
  vectornav_msgs__msg__GpsGroup__GPSGROUP_POSLLA = 32
};

/// Constant 'GPSGROUP_POSECEF'.
enum
{
  vectornav_msgs__msg__GpsGroup__GPSGROUP_POSECEF = 64
};

/// Constant 'GPSGROUP_VELNED'.
enum
{
  vectornav_msgs__msg__GpsGroup__GPSGROUP_VELNED = 128
};

/// Constant 'GPSGROUP_VELECEF'.
enum
{
  vectornav_msgs__msg__GpsGroup__GPSGROUP_VELECEF = 256
};

/// Constant 'GPSGROUP_POSU'.
enum
{
  vectornav_msgs__msg__GpsGroup__GPSGROUP_POSU = 512
};

/// Constant 'GPSGROUP_VELU'.
enum
{
  vectornav_msgs__msg__GpsGroup__GPSGROUP_VELU = 1024
};

/// Constant 'GPSGROUP_TIMEU'.
enum
{
  vectornav_msgs__msg__GpsGroup__GPSGROUP_TIMEU = 2048
};

/// Constant 'GPSGROUP_TIMEINFO'.
enum
{
  vectornav_msgs__msg__GpsGroup__GPSGROUP_TIMEINFO = 4096
};

/// Constant 'GPSGROUP_DOP'.
enum
{
  vectornav_msgs__msg__GpsGroup__GPSGROUP_DOP = 8192
};

/// Constant 'GPSFIX_NOFIX'.
enum
{
  vectornav_msgs__msg__GpsGroup__GPSFIX_NOFIX = 0
};

/// Constant 'GPSFIX_TIMEONLY'.
enum
{
  vectornav_msgs__msg__GpsGroup__GPSFIX_TIMEONLY = 1
};

/// Constant 'GPSFIX_2D'.
enum
{
  vectornav_msgs__msg__GpsGroup__GPSFIX_2D = 2
};

/// Constant 'GPSFIX_3D'.
enum
{
  vectornav_msgs__msg__GpsGroup__GPSFIX_3D = 3
};

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__struct.h"
// Member 'utc'
#include "vectornav_msgs/msg/detail/time_utc__struct.h"
// Member 'poslla'
// Member 'posecef'
#include "geometry_msgs/msg/detail/point__struct.h"
// Member 'velned'
// Member 'velecef'
// Member 'posu'
#include "geometry_msgs/msg/detail/vector3__struct.h"
// Member 'dop'
#include "vectornav_msgs/msg/detail/dop__struct.h"

/// Struct defined in msg/GpsGroup in the package vectornav_msgs.
/**
  * VectorNav Composite Data Packet
  *
  * Only the enabled fields will be populated with data and only the fields
  * you require for your application should be enabled to conserve bandwidth
  * and increase the update rate.
  *
  * TODO Requires rosidl patches
 */
typedef struct vectornav_msgs__msg__GpsGroup
{
  /// Data Received (ROS Time)
  std_msgs__msg__Header header;
  /// Field Enable Bits
  uint16_t group_fields;
  /// TODO vncxx does not support SatInfo or RawMeas
  /// Fields
  vectornav_msgs__msg__TimeUTC utc;
  uint64_t tow;
  uint16_t week;
  uint8_t numsats;
  uint8_t fix;
  geometry_msgs__msg__Point poslla;
  geometry_msgs__msg__Point posecef;
  geometry_msgs__msg__Vector3 velned;
  geometry_msgs__msg__Vector3 velecef;
  geometry_msgs__msg__Vector3 posu;
  float velu;
  uint32_t timeu;
  uint8_t timeinfo_status;
  int8_t timeinfo_leapseconds;
  vectornav_msgs__msg__DOP dop;
} vectornav_msgs__msg__GpsGroup;

// Struct for a sequence of vectornav_msgs__msg__GpsGroup.
typedef struct vectornav_msgs__msg__GpsGroup__Sequence
{
  vectornav_msgs__msg__GpsGroup * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} vectornav_msgs__msg__GpsGroup__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // VECTORNAV_MSGS__MSG__DETAIL__GPS_GROUP__STRUCT_H_
