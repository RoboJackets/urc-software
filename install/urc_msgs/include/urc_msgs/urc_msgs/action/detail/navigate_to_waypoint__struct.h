// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from urc_msgs:action/NavigateToWaypoint.idl
// generated code does not contain a copyright notice

#ifndef URC_MSGS__ACTION__DETAIL__NAVIGATE_TO_WAYPOINT__STRUCT_H_
#define URC_MSGS__ACTION__DETAIL__NAVIGATE_TO_WAYPOINT__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'path'
#include "nav_msgs/msg/detail/path__struct.h"
// Member 'goal'
#include "geometry_msgs/msg/detail/pose_stamped__struct.h"

/// Struct defined in action/NavigateToWaypoint in the package urc_msgs.
typedef struct urc_msgs__action__NavigateToWaypoint_Goal
{
  nav_msgs__msg__Path path;
  geometry_msgs__msg__PoseStamped goal;
  bool has_path;
  bool has_goal;
  bool enforce_goal_heading;
} urc_msgs__action__NavigateToWaypoint_Goal;

// Struct for a sequence of urc_msgs__action__NavigateToWaypoint_Goal.
typedef struct urc_msgs__action__NavigateToWaypoint_Goal__Sequence
{
  urc_msgs__action__NavigateToWaypoint_Goal * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} urc_msgs__action__NavigateToWaypoint_Goal__Sequence;


// Constants defined in the message

/// Constant 'SUCCESS'.
enum
{
  urc_msgs__action__NavigateToWaypoint_Result__SUCCESS = 0
};

/// Constant 'FAILURE'.
enum
{
  urc_msgs__action__NavigateToWaypoint_Result__FAILURE = 1
};

/// Constant 'OBSTACLE_DETECTED'.
enum
{
  urc_msgs__action__NavigateToWaypoint_Result__OBSTACLE_DETECTED = 2
};

/// Constant 'PLANNING_FAILED'.
enum
{
  urc_msgs__action__NavigateToWaypoint_Result__PLANNING_FAILED = 3
};

// Include directives for member types
// Member 'result'
#include "std_msgs/msg/detail/empty__struct.h"

/// Struct defined in action/NavigateToWaypoint in the package urc_msgs.
typedef struct urc_msgs__action__NavigateToWaypoint_Result
{
  std_msgs__msg__Empty result;
  uint16_t error_code;
} urc_msgs__action__NavigateToWaypoint_Result;

// Struct for a sequence of urc_msgs__action__NavigateToWaypoint_Result.
typedef struct urc_msgs__action__NavigateToWaypoint_Result__Sequence
{
  urc_msgs__action__NavigateToWaypoint_Result * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} urc_msgs__action__NavigateToWaypoint_Result__Sequence;


// Constants defined in the message

/// Struct defined in action/NavigateToWaypoint in the package urc_msgs.
typedef struct urc_msgs__action__NavigateToWaypoint_Feedback
{
  float distance_to_goal;
  bool is_planning;
  uint16_t replan_count;
} urc_msgs__action__NavigateToWaypoint_Feedback;

// Struct for a sequence of urc_msgs__action__NavigateToWaypoint_Feedback.
typedef struct urc_msgs__action__NavigateToWaypoint_Feedback__Sequence
{
  urc_msgs__action__NavigateToWaypoint_Feedback * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} urc_msgs__action__NavigateToWaypoint_Feedback__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'goal_id'
#include "unique_identifier_msgs/msg/detail/uuid__struct.h"
// Member 'goal'
#include "urc_msgs/action/detail/navigate_to_waypoint__struct.h"

/// Struct defined in action/NavigateToWaypoint in the package urc_msgs.
typedef struct urc_msgs__action__NavigateToWaypoint_SendGoal_Request
{
  unique_identifier_msgs__msg__UUID goal_id;
  urc_msgs__action__NavigateToWaypoint_Goal goal;
} urc_msgs__action__NavigateToWaypoint_SendGoal_Request;

// Struct for a sequence of urc_msgs__action__NavigateToWaypoint_SendGoal_Request.
typedef struct urc_msgs__action__NavigateToWaypoint_SendGoal_Request__Sequence
{
  urc_msgs__action__NavigateToWaypoint_SendGoal_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} urc_msgs__action__NavigateToWaypoint_SendGoal_Request__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'stamp'
#include "builtin_interfaces/msg/detail/time__struct.h"

/// Struct defined in action/NavigateToWaypoint in the package urc_msgs.
typedef struct urc_msgs__action__NavigateToWaypoint_SendGoal_Response
{
  bool accepted;
  builtin_interfaces__msg__Time stamp;
} urc_msgs__action__NavigateToWaypoint_SendGoal_Response;

// Struct for a sequence of urc_msgs__action__NavigateToWaypoint_SendGoal_Response.
typedef struct urc_msgs__action__NavigateToWaypoint_SendGoal_Response__Sequence
{
  urc_msgs__action__NavigateToWaypoint_SendGoal_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} urc_msgs__action__NavigateToWaypoint_SendGoal_Response__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'goal_id'
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__struct.h"

/// Struct defined in action/NavigateToWaypoint in the package urc_msgs.
typedef struct urc_msgs__action__NavigateToWaypoint_GetResult_Request
{
  unique_identifier_msgs__msg__UUID goal_id;
} urc_msgs__action__NavigateToWaypoint_GetResult_Request;

// Struct for a sequence of urc_msgs__action__NavigateToWaypoint_GetResult_Request.
typedef struct urc_msgs__action__NavigateToWaypoint_GetResult_Request__Sequence
{
  urc_msgs__action__NavigateToWaypoint_GetResult_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} urc_msgs__action__NavigateToWaypoint_GetResult_Request__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'result'
// already included above
// #include "urc_msgs/action/detail/navigate_to_waypoint__struct.h"

/// Struct defined in action/NavigateToWaypoint in the package urc_msgs.
typedef struct urc_msgs__action__NavigateToWaypoint_GetResult_Response
{
  int8_t status;
  urc_msgs__action__NavigateToWaypoint_Result result;
} urc_msgs__action__NavigateToWaypoint_GetResult_Response;

// Struct for a sequence of urc_msgs__action__NavigateToWaypoint_GetResult_Response.
typedef struct urc_msgs__action__NavigateToWaypoint_GetResult_Response__Sequence
{
  urc_msgs__action__NavigateToWaypoint_GetResult_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} urc_msgs__action__NavigateToWaypoint_GetResult_Response__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'goal_id'
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__struct.h"
// Member 'feedback'
// already included above
// #include "urc_msgs/action/detail/navigate_to_waypoint__struct.h"

/// Struct defined in action/NavigateToWaypoint in the package urc_msgs.
typedef struct urc_msgs__action__NavigateToWaypoint_FeedbackMessage
{
  unique_identifier_msgs__msg__UUID goal_id;
  urc_msgs__action__NavigateToWaypoint_Feedback feedback;
} urc_msgs__action__NavigateToWaypoint_FeedbackMessage;

// Struct for a sequence of urc_msgs__action__NavigateToWaypoint_FeedbackMessage.
typedef struct urc_msgs__action__NavigateToWaypoint_FeedbackMessage__Sequence
{
  urc_msgs__action__NavigateToWaypoint_FeedbackMessage * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} urc_msgs__action__NavigateToWaypoint_FeedbackMessage__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // URC_MSGS__ACTION__DETAIL__NAVIGATE_TO_WAYPOINT__STRUCT_H_
