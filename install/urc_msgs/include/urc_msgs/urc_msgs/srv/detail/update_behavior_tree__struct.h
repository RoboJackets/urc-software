// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from urc_msgs:srv/UpdateBehaviorTree.idl
// generated code does not contain a copyright notice

#ifndef URC_MSGS__SRV__DETAIL__UPDATE_BEHAVIOR_TREE__STRUCT_H_
#define URC_MSGS__SRV__DETAIL__UPDATE_BEHAVIOR_TREE__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'tree_content'
// Member 'tree_dir'
#include "rosidl_runtime_c/string.h"

/// Struct defined in srv/UpdateBehaviorTree in the package urc_msgs.
typedef struct urc_msgs__srv__UpdateBehaviorTree_Request
{
  rosidl_runtime_c__String tree_content;
  rosidl_runtime_c__String tree_dir;
  bool use_dir;
} urc_msgs__srv__UpdateBehaviorTree_Request;

// Struct for a sequence of urc_msgs__srv__UpdateBehaviorTree_Request.
typedef struct urc_msgs__srv__UpdateBehaviorTree_Request__Sequence
{
  urc_msgs__srv__UpdateBehaviorTree_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} urc_msgs__srv__UpdateBehaviorTree_Request__Sequence;


// Constants defined in the message

/// Struct defined in srv/UpdateBehaviorTree in the package urc_msgs.
typedef struct urc_msgs__srv__UpdateBehaviorTree_Response
{
  bool success;
} urc_msgs__srv__UpdateBehaviorTree_Response;

// Struct for a sequence of urc_msgs__srv__UpdateBehaviorTree_Response.
typedef struct urc_msgs__srv__UpdateBehaviorTree_Response__Sequence
{
  urc_msgs__srv__UpdateBehaviorTree_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} urc_msgs__srv__UpdateBehaviorTree_Response__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // URC_MSGS__SRV__DETAIL__UPDATE_BEHAVIOR_TREE__STRUCT_H_
