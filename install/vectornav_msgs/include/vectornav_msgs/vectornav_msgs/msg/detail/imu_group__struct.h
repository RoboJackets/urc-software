// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from vectornav_msgs:msg/ImuGroup.idl
// generated code does not contain a copyright notice

#ifndef VECTORNAV_MSGS__MSG__DETAIL__IMU_GROUP__STRUCT_H_
#define VECTORNAV_MSGS__MSG__DETAIL__IMU_GROUP__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Constant 'IMUGROUP_IMUSTATUS'.
enum
{
  vectornav_msgs__msg__ImuGroup__IMUGROUP_IMUSTATUS = 1
};

/// Constant 'IMUGROUP_UNCOMPMAG'.
enum
{
  vectornav_msgs__msg__ImuGroup__IMUGROUP_UNCOMPMAG = 2
};

/// Constant 'IMUGROUP_UNCOMPACCEL'.
enum
{
  vectornav_msgs__msg__ImuGroup__IMUGROUP_UNCOMPACCEL = 4
};

/// Constant 'IMUGROUP_UNCOMPGYRO'.
enum
{
  vectornav_msgs__msg__ImuGroup__IMUGROUP_UNCOMPGYRO = 8
};

/// Constant 'IMUGROUP_TEMP'.
enum
{
  vectornav_msgs__msg__ImuGroup__IMUGROUP_TEMP = 16
};

/// Constant 'IMUGROUP_PRES'.
enum
{
  vectornav_msgs__msg__ImuGroup__IMUGROUP_PRES = 32
};

/// Constant 'IMUGROUP_DELTATHETA'.
enum
{
  vectornav_msgs__msg__ImuGroup__IMUGROUP_DELTATHETA = 64
};

/// Constant 'IMUGROUP_DELTAVEL'.
enum
{
  vectornav_msgs__msg__ImuGroup__IMUGROUP_DELTAVEL = 128
};

/// Constant 'IMUGROUP_MAG'.
enum
{
  vectornav_msgs__msg__ImuGroup__IMUGROUP_MAG = 256
};

/// Constant 'IMUGROUP_ACCEL'.
enum
{
  vectornav_msgs__msg__ImuGroup__IMUGROUP_ACCEL = 512
};

/// Constant 'IMUGROUP_ANGULARRATE'.
enum
{
  vectornav_msgs__msg__ImuGroup__IMUGROUP_ANGULARRATE = 1024
};

/// Constant 'IMUGROUP_SENSSAT'.
enum
{
  vectornav_msgs__msg__ImuGroup__IMUGROUP_SENSSAT = 2048
};

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__struct.h"
// Member 'uncompmag'
// Member 'uncompaccel'
// Member 'uncompgyro'
// Member 'deltatheta_dtheta'
// Member 'deltavel'
// Member 'mag'
// Member 'accel'
// Member 'angularrate'
#include "geometry_msgs/msg/detail/vector3__struct.h"

/// Struct defined in msg/ImuGroup in the package vectornav_msgs.
/**
  * VectorNav Composite Data Packet
  *
  * Only the enabled fields will be populated with data and only the fields
  * you require for your application should be enabled to conserve bandwidth
  * and increase the update rate.
  *
  * TODO Requires rosidl patches
 */
typedef struct vectornav_msgs__msg__ImuGroup
{
  /// Data Received (ROS Time)
  std_msgs__msg__Header header;
  /// Field Enable Bits
  uint16_t group_fields;
  /// TODO SENSSAT exists in the header, but not the manual...
  /// Fields
  uint16_t imustatus;
  geometry_msgs__msg__Vector3 uncompmag;
  geometry_msgs__msg__Vector3 uncompaccel;
  geometry_msgs__msg__Vector3 uncompgyro;
  float temp;
  float pres;
  float deltatheta_time;
  geometry_msgs__msg__Vector3 deltatheta_dtheta;
  geometry_msgs__msg__Vector3 deltavel;
  geometry_msgs__msg__Vector3 mag;
  geometry_msgs__msg__Vector3 accel;
  geometry_msgs__msg__Vector3 angularrate;
  uint16_t sensat;
} vectornav_msgs__msg__ImuGroup;

// Struct for a sequence of vectornav_msgs__msg__ImuGroup.
typedef struct vectornav_msgs__msg__ImuGroup__Sequence
{
  vectornav_msgs__msg__ImuGroup * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} vectornav_msgs__msg__ImuGroup__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // VECTORNAV_MSGS__MSG__DETAIL__IMU_GROUP__STRUCT_H_
