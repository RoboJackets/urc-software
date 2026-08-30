// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from vectornav_msgs:msg/InsGroup.idl
// generated code does not contain a copyright notice

#ifndef VECTORNAV_MSGS__MSG__DETAIL__INS_GROUP__STRUCT_H_
#define VECTORNAV_MSGS__MSG__DETAIL__INS_GROUP__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Constant 'INSGROUP_INSSTATUS'.
enum
{
  vectornav_msgs__msg__InsGroup__INSGROUP_INSSTATUS = 1
};

/// Constant 'INSGROUP_POSLLA'.
enum
{
  vectornav_msgs__msg__InsGroup__INSGROUP_POSLLA = 2
};

/// Constant 'INSGROUP_POSECEF'.
enum
{
  vectornav_msgs__msg__InsGroup__INSGROUP_POSECEF = 4
};

/// Constant 'INSGROUP_VELBODY'.
enum
{
  vectornav_msgs__msg__InsGroup__INSGROUP_VELBODY = 8
};

/// Constant 'INSGROUP_VELNED'.
enum
{
  vectornav_msgs__msg__InsGroup__INSGROUP_VELNED = 16
};

/// Constant 'INSGROUP_VELECEF'.
enum
{
  vectornav_msgs__msg__InsGroup__INSGROUP_VELECEF = 32
};

/// Constant 'INSGROUP_MAGECEF'.
enum
{
  vectornav_msgs__msg__InsGroup__INSGROUP_MAGECEF = 64
};

/// Constant 'INSGROUP_ACCELECEF'.
enum
{
  vectornav_msgs__msg__InsGroup__INSGROUP_ACCELECEF = 128
};

/// Constant 'INSGROUP_LINEARACCELECEF'.
enum
{
  vectornav_msgs__msg__InsGroup__INSGROUP_LINEARACCELECEF = 256
};

/// Constant 'INSGROUP_POSU'.
enum
{
  vectornav_msgs__msg__InsGroup__INSGROUP_POSU = 512
};

/// Constant 'INSGROUP_VELU'.
enum
{
  vectornav_msgs__msg__InsGroup__INSGROUP_VELU = 1024
};

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__struct.h"
// Member 'insstatus'
#include "vectornav_msgs/msg/detail/ins_status__struct.h"
// Member 'poslla'
// Member 'posecef'
#include "geometry_msgs/msg/detail/point__struct.h"
// Member 'velbody'
// Member 'velned'
// Member 'velecef'
// Member 'magecef'
// Member 'accelecef'
// Member 'linearaccelecef'
#include "geometry_msgs/msg/detail/vector3__struct.h"

/// Struct defined in msg/InsGroup in the package vectornav_msgs.
/**
  * VectorNav Composite Data Packet
  *
  * Only the enabled fields will be populated with data and only the fields
  * you require for your application should be enabled to conserve bandwidth
  * and increase the update rate.
  *
  * TODO Requires rosidl patches
 */
typedef struct vectornav_msgs__msg__InsGroup
{
  /// Data Received (ROS Time)
  std_msgs__msg__Header header;
  /// Field Enable Bits
  uint16_t group_fields;
  /// Fields
  vectornav_msgs__msg__InsStatus insstatus;
  geometry_msgs__msg__Point poslla;
  geometry_msgs__msg__Point posecef;
  geometry_msgs__msg__Vector3 velbody;
  geometry_msgs__msg__Vector3 velned;
  geometry_msgs__msg__Vector3 velecef;
  geometry_msgs__msg__Vector3 magecef;
  geometry_msgs__msg__Vector3 accelecef;
  geometry_msgs__msg__Vector3 linearaccelecef;
  float posu;
  float velu;
} vectornav_msgs__msg__InsGroup;

// Struct for a sequence of vectornav_msgs__msg__InsGroup.
typedef struct vectornav_msgs__msg__InsGroup__Sequence
{
  vectornav_msgs__msg__InsGroup * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} vectornav_msgs__msg__InsGroup__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // VECTORNAV_MSGS__MSG__DETAIL__INS_GROUP__STRUCT_H_
