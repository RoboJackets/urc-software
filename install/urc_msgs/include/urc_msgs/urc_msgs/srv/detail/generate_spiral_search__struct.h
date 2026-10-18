// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from urc_msgs:srv/GenerateSpiralSearch.idl
// generated code does not contain a copyright notice

#ifndef URC_MSGS__SRV__DETAIL__GENERATE_SPIRAL_SEARCH__STRUCT_H_
#define URC_MSGS__SRV__DETAIL__GENERATE_SPIRAL_SEARCH__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'center'
#include "geometry_msgs/msg/detail/pose_stamped__struct.h"

/// Struct defined in srv/GenerateSpiralSearch in the package urc_msgs.
typedef struct urc_msgs__srv__GenerateSpiralSearch_Request
{
  geometry_msgs__msg__PoseStamped center;
  double search_radius;
  double track_spacing;
  double waypoint_spacing;
} urc_msgs__srv__GenerateSpiralSearch_Request;

// Struct for a sequence of urc_msgs__srv__GenerateSpiralSearch_Request.
typedef struct urc_msgs__srv__GenerateSpiralSearch_Request__Sequence
{
  urc_msgs__srv__GenerateSpiralSearch_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} urc_msgs__srv__GenerateSpiralSearch_Request__Sequence;


// Constants defined in the message

/// Constant 'SUCCESS'.
enum
{
  urc_msgs__srv__GenerateSpiralSearch_Response__SUCCESS = 0
};

/// Constant 'INVALID_REQUEST'.
enum
{
  urc_msgs__srv__GenerateSpiralSearch_Response__INVALID_REQUEST = 1
};

/// Constant 'FAILURE'.
enum
{
  urc_msgs__srv__GenerateSpiralSearch_Response__FAILURE = 2
};

/// Constant 'MAP_UNAVAILABLE'.
/**
  * No fresh traversability map was available and the server requires one.
 */
enum
{
  urc_msgs__srv__GenerateSpiralSearch_Response__MAP_UNAVAILABLE = 3
};

/// Constant 'NO_TRAVERSABLE_PATH'.
/**
  * Every spiral waypoint was blocked or unreachable on the traversability map.
 */
enum
{
  urc_msgs__srv__GenerateSpiralSearch_Response__NO_TRAVERSABLE_PATH = 4
};

// Include directives for member types
// Member 'path'
#include "nav_msgs/msg/detail/path__struct.h"

/// Struct defined in srv/GenerateSpiralSearch in the package urc_msgs.
typedef struct urc_msgs__srv__GenerateSpiralSearch_Response
{
  nav_msgs__msg__Path path;
  double track_spacing;
  double path_length;
  /// True when the path was routed against the traversability map.
  bool traversability_checked;
  /// True when the outer part of the spiral was dropped because no safe route reached it.
  bool truncated;
  /// Spiral waypoints left out of the path because they were blocked or unreachable.
  uint32_t skipped_waypoints;
  uint16_t error_code;
} urc_msgs__srv__GenerateSpiralSearch_Response;

// Struct for a sequence of urc_msgs__srv__GenerateSpiralSearch_Response.
typedef struct urc_msgs__srv__GenerateSpiralSearch_Response__Sequence
{
  urc_msgs__srv__GenerateSpiralSearch_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} urc_msgs__srv__GenerateSpiralSearch_Response__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // URC_MSGS__SRV__DETAIL__GENERATE_SPIRAL_SEARCH__STRUCT_H_
