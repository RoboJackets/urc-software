// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from vectornav_msgs:msg/CommonGroup.idl
// generated code does not contain a copyright notice

#ifndef VECTORNAV_MSGS__MSG__DETAIL__COMMON_GROUP__STRUCT_H_
#define VECTORNAV_MSGS__MSG__DETAIL__COMMON_GROUP__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Constant 'COMMONGROUP_TIMESTARTUP'.
enum
{
  vectornav_msgs__msg__CommonGroup__COMMONGROUP_TIMESTARTUP = 1
};

/// Constant 'COMMONGROUP_TIMEGPS'.
enum
{
  vectornav_msgs__msg__CommonGroup__COMMONGROUP_TIMEGPS = 2
};

/// Constant 'COMMONGROUP_TIMESYNCIN'.
enum
{
  vectornav_msgs__msg__CommonGroup__COMMONGROUP_TIMESYNCIN = 4
};

/// Constant 'COMMONGROUP_YAWPITCHROLL'.
enum
{
  vectornav_msgs__msg__CommonGroup__COMMONGROUP_YAWPITCHROLL = 8
};

/// Constant 'COMMONGROUP_QUATERNION'.
enum
{
  vectornav_msgs__msg__CommonGroup__COMMONGROUP_QUATERNION = 16
};

/// Constant 'COMMONGROUP_ANGULARRATE'.
enum
{
  vectornav_msgs__msg__CommonGroup__COMMONGROUP_ANGULARRATE = 32
};

/// Constant 'COMMONGROUP_POSITION'.
enum
{
  vectornav_msgs__msg__CommonGroup__COMMONGROUP_POSITION = 64
};

/// Constant 'COMMONGROUP_VELOCITY'.
enum
{
  vectornav_msgs__msg__CommonGroup__COMMONGROUP_VELOCITY = 128
};

/// Constant 'COMMONGROUP_ACCEL'.
enum
{
  vectornav_msgs__msg__CommonGroup__COMMONGROUP_ACCEL = 256
};

/// Constant 'COMMONGROUP_IMU'.
enum
{
  vectornav_msgs__msg__CommonGroup__COMMONGROUP_IMU = 512
};

/// Constant 'COMMONGROUP_MAGPRES'.
enum
{
  vectornav_msgs__msg__CommonGroup__COMMONGROUP_MAGPRES = 1024
};

/// Constant 'COMMONGROUP_DELTATHETA'.
enum
{
  vectornav_msgs__msg__CommonGroup__COMMONGROUP_DELTATHETA = 2048
};

/// Constant 'COMMONGROUP_INSSTATUS'.
enum
{
  vectornav_msgs__msg__CommonGroup__COMMONGROUP_INSSTATUS = 4096
};

/// Constant 'COMMONGROUP_SYNCINCNT'.
enum
{
  vectornav_msgs__msg__CommonGroup__COMMONGROUP_SYNCINCNT = 8192
};

/// Constant 'COMMONGROUP_TIMEGPSPPS'.
enum
{
  vectornav_msgs__msg__CommonGroup__COMMONGROUP_TIMEGPSPPS = 16384
};

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__struct.h"
// Member 'yawpitchroll'
// Member 'angularrate'
// Member 'velocity'
// Member 'accel'
// Member 'imu_accel'
// Member 'imu_rate'
// Member 'magpres_mag'
// Member 'deltatheta_dtheta'
// Member 'deltatheta_dvel'
#include "geometry_msgs/msg/detail/vector3__struct.h"
// Member 'quaternion'
#include "geometry_msgs/msg/detail/quaternion__struct.h"
// Member 'position'
#include "geometry_msgs/msg/detail/point__struct.h"
// Member 'insstatus'
#include "vectornav_msgs/msg/detail/ins_status__struct.h"

/// Struct defined in msg/CommonGroup in the package vectornav_msgs.
/**
  * VectorNav Composite Data Packet
  *
  * Only the enabled fields will be populated with data and only the fields
  * you require for your application should be enabled to conserve bandwidth
  * and increase the update rate.
  *
  * TODO Requires rosidl patches
 */
typedef struct vectornav_msgs__msg__CommonGroup
{
  /// Data Received (ROS Time)
  std_msgs__msg__Header header;
  /// Field Enable Bits
  uint16_t group_fields;
  /// Common
  uint64_t timestartup;
  uint64_t timegps;
  uint64_t timesyncin;
  geometry_msgs__msg__Vector3 yawpitchroll;
  geometry_msgs__msg__Quaternion quaternion;
  geometry_msgs__msg__Vector3 angularrate;
  geometry_msgs__msg__Point position;
  geometry_msgs__msg__Vector3 velocity;
  geometry_msgs__msg__Vector3 accel;
  geometry_msgs__msg__Vector3 imu_accel;
  geometry_msgs__msg__Vector3 imu_rate;
  geometry_msgs__msg__Vector3 magpres_mag;
  float magpres_temp;
  float magpres_pres;
  float deltatheta_dtime;
  geometry_msgs__msg__Vector3 deltatheta_dtheta;
  geometry_msgs__msg__Vector3 deltatheta_dvel;
  vectornav_msgs__msg__InsStatus insstatus;
  uint32_t syncincnt;
  uint16_t timegpspps;
} vectornav_msgs__msg__CommonGroup;

// Struct for a sequence of vectornav_msgs__msg__CommonGroup.
typedef struct vectornav_msgs__msg__CommonGroup__Sequence
{
  vectornav_msgs__msg__CommonGroup * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} vectornav_msgs__msg__CommonGroup__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // VECTORNAV_MSGS__MSG__DETAIL__COMMON_GROUP__STRUCT_H_
