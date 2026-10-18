// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from vectornav_msgs:msg/TimeGroup.idl
// generated code does not contain a copyright notice

#ifndef VECTORNAV_MSGS__MSG__DETAIL__TIME_GROUP__STRUCT_H_
#define VECTORNAV_MSGS__MSG__DETAIL__TIME_GROUP__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Constant 'TIMEGROUP_TIMESTARTUP'.
enum
{
  vectornav_msgs__msg__TimeGroup__TIMEGROUP_TIMESTARTUP = 1
};

/// Constant 'TIMEGROUP_TIMEGPS'.
enum
{
  vectornav_msgs__msg__TimeGroup__TIMEGROUP_TIMEGPS = 2
};

/// Constant 'TIMEGROUP_GPSTOW'.
enum
{
  vectornav_msgs__msg__TimeGroup__TIMEGROUP_GPSTOW = 4
};

/// Constant 'TIMEGROUP_GPSWEEK'.
enum
{
  vectornav_msgs__msg__TimeGroup__TIMEGROUP_GPSWEEK = 8
};

/// Constant 'TIMEGROUP_TIMESYNCIN'.
enum
{
  vectornav_msgs__msg__TimeGroup__TIMEGROUP_TIMESYNCIN = 16
};

/// Constant 'TIMEGROUP_TIMEGPSPPS'.
enum
{
  vectornav_msgs__msg__TimeGroup__TIMEGROUP_TIMEGPSPPS = 32
};

/// Constant 'TIMEGROUP_TIMEUTC'.
enum
{
  vectornav_msgs__msg__TimeGroup__TIMEGROUP_TIMEUTC = 64
};

/// Constant 'TIMEGROUP_SYNCINCNT'.
enum
{
  vectornav_msgs__msg__TimeGroup__TIMEGROUP_SYNCINCNT = 128
};

/// Constant 'TIMEGROUP_SYNCOUTCNT'.
enum
{
  vectornav_msgs__msg__TimeGroup__TIMEGROUP_SYNCOUTCNT = 256
};

/// Constant 'TIMEGROUP_TIMESTATUS'.
enum
{
  vectornav_msgs__msg__TimeGroup__TIMEGROUP_TIMESTATUS = 512
};

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__struct.h"
// Member 'timeutc'
#include "vectornav_msgs/msg/detail/time_utc__struct.h"
// Member 'timestatus'
#include "vectornav_msgs/msg/detail/time_status__struct.h"

/// Struct defined in msg/TimeGroup in the package vectornav_msgs.
/**
  * VectorNav Composite Data Packet
  *
  * Only the enabled fields will be populated with data and only the fields
  * you require for your application should be enabled to conserve bandwidth
  * and increase the update rate.
  *
  * TODO Requires rosidl patches
 */
typedef struct vectornav_msgs__msg__TimeGroup
{
  /// Data Received (ROS Time)
  std_msgs__msg__Header header;
  /// Field Enable Bits
  uint16_t group_fields;
  /// Fields
  uint64_t timestartup;
  uint64_t timegps;
  uint64_t gpstow;
  uint16_t gpsweek;
  uint64_t timesyncin;
  uint64_t timegpspps;
  vectornav_msgs__msg__TimeUTC timeutc;
  uint32_t syncincnt;
  uint32_t syncoutcnt;
  vectornav_msgs__msg__TimeStatus timestatus;
} vectornav_msgs__msg__TimeGroup;

// Struct for a sequence of vectornav_msgs__msg__TimeGroup.
typedef struct vectornav_msgs__msg__TimeGroup__Sequence
{
  vectornav_msgs__msg__TimeGroup * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} vectornav_msgs__msg__TimeGroup__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // VECTORNAV_MSGS__MSG__DETAIL__TIME_GROUP__STRUCT_H_
