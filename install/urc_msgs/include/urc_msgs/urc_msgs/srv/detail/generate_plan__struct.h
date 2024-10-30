// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from urc_msgs:srv/GeneratePlan.idl
// generated code does not contain a copyright notice

#ifndef URC_MSGS__SRV__DETAIL__GENERATE_PLAN__STRUCT_H_
#define URC_MSGS__SRV__DETAIL__GENERATE_PLAN__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'goal'
// Member 'start'
#include "geometry_msgs/msg/detail/pose_stamped__struct.h"

/// Struct defined in srv/GeneratePlan in the package urc_msgs.
typedef struct urc_msgs__srv__GeneratePlan_Request
{
  geometry_msgs__msg__PoseStamped goal;
  geometry_msgs__msg__PoseStamped start;
} urc_msgs__srv__GeneratePlan_Request;

// Struct for a sequence of urc_msgs__srv__GeneratePlan_Request.
typedef struct urc_msgs__srv__GeneratePlan_Request__Sequence
{
  urc_msgs__srv__GeneratePlan_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} urc_msgs__srv__GeneratePlan_Request__Sequence;


// Constants defined in the message

/// Constant 'SUCCESS'.
enum
{
  urc_msgs__srv__GeneratePlan_Response__SUCCESS = 0
};

/// Constant 'FAILURE'.
enum
{
  urc_msgs__srv__GeneratePlan_Response__FAILURE = 1
};

// Include directives for member types
// Member 'path'
#include "nav_msgs/msg/detail/path__struct.h"

/// Struct defined in srv/GeneratePlan in the package urc_msgs.
typedef struct urc_msgs__srv__GeneratePlan_Response
{
  /// Response definition
  nav_msgs__msg__Path path;
  uint16_t error_code;
} urc_msgs__srv__GeneratePlan_Response;

// Struct for a sequence of urc_msgs__srv__GeneratePlan_Response.
typedef struct urc_msgs__srv__GeneratePlan_Response__Sequence
{
  urc_msgs__srv__GeneratePlan_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} urc_msgs__srv__GeneratePlan_Response__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // URC_MSGS__SRV__DETAIL__GENERATE_PLAN__STRUCT_H_
