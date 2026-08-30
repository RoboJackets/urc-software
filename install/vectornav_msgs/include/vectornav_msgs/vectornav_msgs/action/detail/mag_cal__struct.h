// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from vectornav_msgs:action/MagCal.idl
// generated code does not contain a copyright notice

#ifndef VECTORNAV_MSGS__ACTION__DETAIL__MAG_CAL__STRUCT_H_
#define VECTORNAV_MSGS__ACTION__DETAIL__MAG_CAL__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in action/MagCal in the package vectornav_msgs.
typedef struct vectornav_msgs__action__MagCal_Goal
{
  uint8_t structure_needs_at_least_one_member;
} vectornav_msgs__action__MagCal_Goal;

// Struct for a sequence of vectornav_msgs__action__MagCal_Goal.
typedef struct vectornav_msgs__action__MagCal_Goal__Sequence
{
  vectornav_msgs__action__MagCal_Goal * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} vectornav_msgs__action__MagCal_Goal__Sequence;


// Constants defined in the message

/// Struct defined in action/MagCal in the package vectornav_msgs.
typedef struct vectornav_msgs__action__MagCal_Result
{
  float avg_dev[12];
  float calib[12];
} vectornav_msgs__action__MagCal_Result;

// Struct for a sequence of vectornav_msgs__action__MagCal_Result.
typedef struct vectornav_msgs__action__MagCal_Result__Sequence
{
  vectornav_msgs__action__MagCal_Result * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} vectornav_msgs__action__MagCal_Result__Sequence;


// Constants defined in the message

/// Struct defined in action/MagCal in the package vectornav_msgs.
typedef struct vectornav_msgs__action__MagCal_Feedback
{
  float curr_avg_dev[12];
  float curr_calib[12];
  uint32_t samples;
} vectornav_msgs__action__MagCal_Feedback;

// Struct for a sequence of vectornav_msgs__action__MagCal_Feedback.
typedef struct vectornav_msgs__action__MagCal_Feedback__Sequence
{
  vectornav_msgs__action__MagCal_Feedback * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} vectornav_msgs__action__MagCal_Feedback__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'goal_id'
#include "unique_identifier_msgs/msg/detail/uuid__struct.h"
// Member 'goal'
#include "vectornav_msgs/action/detail/mag_cal__struct.h"

/// Struct defined in action/MagCal in the package vectornav_msgs.
typedef struct vectornav_msgs__action__MagCal_SendGoal_Request
{
  unique_identifier_msgs__msg__UUID goal_id;
  vectornav_msgs__action__MagCal_Goal goal;
} vectornav_msgs__action__MagCal_SendGoal_Request;

// Struct for a sequence of vectornav_msgs__action__MagCal_SendGoal_Request.
typedef struct vectornav_msgs__action__MagCal_SendGoal_Request__Sequence
{
  vectornav_msgs__action__MagCal_SendGoal_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} vectornav_msgs__action__MagCal_SendGoal_Request__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'stamp'
#include "builtin_interfaces/msg/detail/time__struct.h"

/// Struct defined in action/MagCal in the package vectornav_msgs.
typedef struct vectornav_msgs__action__MagCal_SendGoal_Response
{
  bool accepted;
  builtin_interfaces__msg__Time stamp;
} vectornav_msgs__action__MagCal_SendGoal_Response;

// Struct for a sequence of vectornav_msgs__action__MagCal_SendGoal_Response.
typedef struct vectornav_msgs__action__MagCal_SendGoal_Response__Sequence
{
  vectornav_msgs__action__MagCal_SendGoal_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} vectornav_msgs__action__MagCal_SendGoal_Response__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'goal_id'
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__struct.h"

/// Struct defined in action/MagCal in the package vectornav_msgs.
typedef struct vectornav_msgs__action__MagCal_GetResult_Request
{
  unique_identifier_msgs__msg__UUID goal_id;
} vectornav_msgs__action__MagCal_GetResult_Request;

// Struct for a sequence of vectornav_msgs__action__MagCal_GetResult_Request.
typedef struct vectornav_msgs__action__MagCal_GetResult_Request__Sequence
{
  vectornav_msgs__action__MagCal_GetResult_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} vectornav_msgs__action__MagCal_GetResult_Request__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'result'
// already included above
// #include "vectornav_msgs/action/detail/mag_cal__struct.h"

/// Struct defined in action/MagCal in the package vectornav_msgs.
typedef struct vectornav_msgs__action__MagCal_GetResult_Response
{
  int8_t status;
  vectornav_msgs__action__MagCal_Result result;
} vectornav_msgs__action__MagCal_GetResult_Response;

// Struct for a sequence of vectornav_msgs__action__MagCal_GetResult_Response.
typedef struct vectornav_msgs__action__MagCal_GetResult_Response__Sequence
{
  vectornav_msgs__action__MagCal_GetResult_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} vectornav_msgs__action__MagCal_GetResult_Response__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'goal_id'
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__struct.h"
// Member 'feedback'
// already included above
// #include "vectornav_msgs/action/detail/mag_cal__struct.h"

/// Struct defined in action/MagCal in the package vectornav_msgs.
typedef struct vectornav_msgs__action__MagCal_FeedbackMessage
{
  unique_identifier_msgs__msg__UUID goal_id;
  vectornav_msgs__action__MagCal_Feedback feedback;
} vectornav_msgs__action__MagCal_FeedbackMessage;

// Struct for a sequence of vectornav_msgs__action__MagCal_FeedbackMessage.
typedef struct vectornav_msgs__action__MagCal_FeedbackMessage__Sequence
{
  vectornav_msgs__action__MagCal_FeedbackMessage * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} vectornav_msgs__action__MagCal_FeedbackMessage__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // VECTORNAV_MSGS__ACTION__DETAIL__MAG_CAL__STRUCT_H_
