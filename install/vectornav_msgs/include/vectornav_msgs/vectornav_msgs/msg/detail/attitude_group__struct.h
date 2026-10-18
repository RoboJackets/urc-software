// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from vectornav_msgs:msg/AttitudeGroup.idl
// generated code does not contain a copyright notice

#ifndef VECTORNAV_MSGS__MSG__DETAIL__ATTITUDE_GROUP__STRUCT_H_
#define VECTORNAV_MSGS__MSG__DETAIL__ATTITUDE_GROUP__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Constant 'ATTITUDEGROUP_VPESTATUS'.
enum
{
  vectornav_msgs__msg__AttitudeGroup__ATTITUDEGROUP_VPESTATUS = 1
};

/// Constant 'ATTITUDEGROUP_YAWPITCHROLL'.
enum
{
  vectornav_msgs__msg__AttitudeGroup__ATTITUDEGROUP_YAWPITCHROLL = 2
};

/// Constant 'ATTITUDEGROUP_QUATERNION'.
enum
{
  vectornav_msgs__msg__AttitudeGroup__ATTITUDEGROUP_QUATERNION = 4
};

/// Constant 'ATTITUDEGROUP_DCM'.
enum
{
  vectornav_msgs__msg__AttitudeGroup__ATTITUDEGROUP_DCM = 8
};

/// Constant 'ATTITUDEGROUP_MAGNED'.
enum
{
  vectornav_msgs__msg__AttitudeGroup__ATTITUDEGROUP_MAGNED = 16
};

/// Constant 'ATTITUDEGROUP_ACCELNED'.
enum
{
  vectornav_msgs__msg__AttitudeGroup__ATTITUDEGROUP_ACCELNED = 32
};

/// Constant 'ATTITUDEGROUP_LINEARACCELBODY'.
enum
{
  vectornav_msgs__msg__AttitudeGroup__ATTITUDEGROUP_LINEARACCELBODY = 64
};

/// Constant 'ATTITUDEGROUP_LINEARACCELNED'.
enum
{
  vectornav_msgs__msg__AttitudeGroup__ATTITUDEGROUP_LINEARACCELNED = 128
};

/// Constant 'ATTITUDEGROUP_YPRU'.
enum
{
  vectornav_msgs__msg__AttitudeGroup__ATTITUDEGROUP_YPRU = 256
};

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__struct.h"
// Member 'vpestatus'
#include "vectornav_msgs/msg/detail/vpe_status__struct.h"
// Member 'yawpitchroll'
// Member 'magned'
// Member 'accelned'
// Member 'linearaccelbody'
// Member 'linearaccelned'
// Member 'ypru'
#include "geometry_msgs/msg/detail/vector3__struct.h"
// Member 'quaternion'
#include "geometry_msgs/msg/detail/quaternion__struct.h"

/// Struct defined in msg/AttitudeGroup in the package vectornav_msgs.
/**
  * VectorNav Composite Data Packet
  *
  * Only the enabled fields will be populated with data and only the fields 
  * you require for your application should be enabled to conserve bandwidth
  * and increase the update rate.
  *
  * TODO Requires rosidl patches
 */
typedef struct vectornav_msgs__msg__AttitudeGroup
{
  /// Data Received (ROS Time)
  std_msgs__msg__Header header;
  /// Field Enable Bits
  uint16_t group_fields;
  /// Fields
  vectornav_msgs__msg__VpeStatus vpestatus;
  geometry_msgs__msg__Vector3 yawpitchroll;
  geometry_msgs__msg__Quaternion quaternion;
  float dcm[9];
  geometry_msgs__msg__Vector3 magned;
  geometry_msgs__msg__Vector3 accelned;
  geometry_msgs__msg__Vector3 linearaccelbody;
  geometry_msgs__msg__Vector3 linearaccelned;
  geometry_msgs__msg__Vector3 ypru;
} vectornav_msgs__msg__AttitudeGroup;

// Struct for a sequence of vectornav_msgs__msg__AttitudeGroup.
typedef struct vectornav_msgs__msg__AttitudeGroup__Sequence
{
  vectornav_msgs__msg__AttitudeGroup * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} vectornav_msgs__msg__AttitudeGroup__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // VECTORNAV_MSGS__MSG__DETAIL__ATTITUDE_GROUP__STRUCT_H_
