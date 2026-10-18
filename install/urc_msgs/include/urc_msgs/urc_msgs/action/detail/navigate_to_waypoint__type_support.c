// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from urc_msgs:action/NavigateToWaypoint.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "urc_msgs/action/detail/navigate_to_waypoint__rosidl_typesupport_introspection_c.h"
#include "urc_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "urc_msgs/action/detail/navigate_to_waypoint__functions.h"
#include "urc_msgs/action/detail/navigate_to_waypoint__struct.h"


// Include directives for member types
// Member `path`
#include "nav_msgs/msg/path.h"
// Member `path`
#include "nav_msgs/msg/detail/path__rosidl_typesupport_introspection_c.h"
// Member `goal`
#include "geometry_msgs/msg/pose_stamped.h"
// Member `goal`
#include "geometry_msgs/msg/detail/pose_stamped__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void urc_msgs__action__NavigateToWaypoint_Goal__rosidl_typesupport_introspection_c__NavigateToWaypoint_Goal_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  urc_msgs__action__NavigateToWaypoint_Goal__init(message_memory);
}

void urc_msgs__action__NavigateToWaypoint_Goal__rosidl_typesupport_introspection_c__NavigateToWaypoint_Goal_fini_function(void * message_memory)
{
  urc_msgs__action__NavigateToWaypoint_Goal__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember urc_msgs__action__NavigateToWaypoint_Goal__rosidl_typesupport_introspection_c__NavigateToWaypoint_Goal_message_member_array[5] = {
  {
    "path",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(urc_msgs__action__NavigateToWaypoint_Goal, path),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "goal",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(urc_msgs__action__NavigateToWaypoint_Goal, goal),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "has_path",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(urc_msgs__action__NavigateToWaypoint_Goal, has_path),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "has_goal",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(urc_msgs__action__NavigateToWaypoint_Goal, has_goal),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "enforce_goal_heading",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(urc_msgs__action__NavigateToWaypoint_Goal, enforce_goal_heading),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers urc_msgs__action__NavigateToWaypoint_Goal__rosidl_typesupport_introspection_c__NavigateToWaypoint_Goal_message_members = {
  "urc_msgs__action",  // message namespace
  "NavigateToWaypoint_Goal",  // message name
  5,  // number of fields
  sizeof(urc_msgs__action__NavigateToWaypoint_Goal),
  urc_msgs__action__NavigateToWaypoint_Goal__rosidl_typesupport_introspection_c__NavigateToWaypoint_Goal_message_member_array,  // message members
  urc_msgs__action__NavigateToWaypoint_Goal__rosidl_typesupport_introspection_c__NavigateToWaypoint_Goal_init_function,  // function to initialize message memory (memory has to be allocated)
  urc_msgs__action__NavigateToWaypoint_Goal__rosidl_typesupport_introspection_c__NavigateToWaypoint_Goal_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t urc_msgs__action__NavigateToWaypoint_Goal__rosidl_typesupport_introspection_c__NavigateToWaypoint_Goal_message_type_support_handle = {
  0,
  &urc_msgs__action__NavigateToWaypoint_Goal__rosidl_typesupport_introspection_c__NavigateToWaypoint_Goal_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_urc_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, urc_msgs, action, NavigateToWaypoint_Goal)() {
  urc_msgs__action__NavigateToWaypoint_Goal__rosidl_typesupport_introspection_c__NavigateToWaypoint_Goal_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, nav_msgs, msg, Path)();
  urc_msgs__action__NavigateToWaypoint_Goal__rosidl_typesupport_introspection_c__NavigateToWaypoint_Goal_message_member_array[1].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, geometry_msgs, msg, PoseStamped)();
  if (!urc_msgs__action__NavigateToWaypoint_Goal__rosidl_typesupport_introspection_c__NavigateToWaypoint_Goal_message_type_support_handle.typesupport_identifier) {
    urc_msgs__action__NavigateToWaypoint_Goal__rosidl_typesupport_introspection_c__NavigateToWaypoint_Goal_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &urc_msgs__action__NavigateToWaypoint_Goal__rosidl_typesupport_introspection_c__NavigateToWaypoint_Goal_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

// already included above
// #include <stddef.h>
// already included above
// #include "urc_msgs/action/detail/navigate_to_waypoint__rosidl_typesupport_introspection_c.h"
// already included above
// #include "urc_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "urc_msgs/action/detail/navigate_to_waypoint__functions.h"
// already included above
// #include "urc_msgs/action/detail/navigate_to_waypoint__struct.h"


// Include directives for member types
// Member `result`
#include "std_msgs/msg/empty.h"
// Member `result`
#include "std_msgs/msg/detail/empty__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void urc_msgs__action__NavigateToWaypoint_Result__rosidl_typesupport_introspection_c__NavigateToWaypoint_Result_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  urc_msgs__action__NavigateToWaypoint_Result__init(message_memory);
}

void urc_msgs__action__NavigateToWaypoint_Result__rosidl_typesupport_introspection_c__NavigateToWaypoint_Result_fini_function(void * message_memory)
{
  urc_msgs__action__NavigateToWaypoint_Result__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember urc_msgs__action__NavigateToWaypoint_Result__rosidl_typesupport_introspection_c__NavigateToWaypoint_Result_message_member_array[2] = {
  {
    "result",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(urc_msgs__action__NavigateToWaypoint_Result, result),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "error_code",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT16,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(urc_msgs__action__NavigateToWaypoint_Result, error_code),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers urc_msgs__action__NavigateToWaypoint_Result__rosidl_typesupport_introspection_c__NavigateToWaypoint_Result_message_members = {
  "urc_msgs__action",  // message namespace
  "NavigateToWaypoint_Result",  // message name
  2,  // number of fields
  sizeof(urc_msgs__action__NavigateToWaypoint_Result),
  urc_msgs__action__NavigateToWaypoint_Result__rosidl_typesupport_introspection_c__NavigateToWaypoint_Result_message_member_array,  // message members
  urc_msgs__action__NavigateToWaypoint_Result__rosidl_typesupport_introspection_c__NavigateToWaypoint_Result_init_function,  // function to initialize message memory (memory has to be allocated)
  urc_msgs__action__NavigateToWaypoint_Result__rosidl_typesupport_introspection_c__NavigateToWaypoint_Result_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t urc_msgs__action__NavigateToWaypoint_Result__rosidl_typesupport_introspection_c__NavigateToWaypoint_Result_message_type_support_handle = {
  0,
  &urc_msgs__action__NavigateToWaypoint_Result__rosidl_typesupport_introspection_c__NavigateToWaypoint_Result_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_urc_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, urc_msgs, action, NavigateToWaypoint_Result)() {
  urc_msgs__action__NavigateToWaypoint_Result__rosidl_typesupport_introspection_c__NavigateToWaypoint_Result_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, std_msgs, msg, Empty)();
  if (!urc_msgs__action__NavigateToWaypoint_Result__rosidl_typesupport_introspection_c__NavigateToWaypoint_Result_message_type_support_handle.typesupport_identifier) {
    urc_msgs__action__NavigateToWaypoint_Result__rosidl_typesupport_introspection_c__NavigateToWaypoint_Result_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &urc_msgs__action__NavigateToWaypoint_Result__rosidl_typesupport_introspection_c__NavigateToWaypoint_Result_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

// already included above
// #include <stddef.h>
// already included above
// #include "urc_msgs/action/detail/navigate_to_waypoint__rosidl_typesupport_introspection_c.h"
// already included above
// #include "urc_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "urc_msgs/action/detail/navigate_to_waypoint__functions.h"
// already included above
// #include "urc_msgs/action/detail/navigate_to_waypoint__struct.h"


#ifdef __cplusplus
extern "C"
{
#endif

void urc_msgs__action__NavigateToWaypoint_Feedback__rosidl_typesupport_introspection_c__NavigateToWaypoint_Feedback_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  urc_msgs__action__NavigateToWaypoint_Feedback__init(message_memory);
}

void urc_msgs__action__NavigateToWaypoint_Feedback__rosidl_typesupport_introspection_c__NavigateToWaypoint_Feedback_fini_function(void * message_memory)
{
  urc_msgs__action__NavigateToWaypoint_Feedback__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember urc_msgs__action__NavigateToWaypoint_Feedback__rosidl_typesupport_introspection_c__NavigateToWaypoint_Feedback_message_member_array[3] = {
  {
    "distance_to_goal",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(urc_msgs__action__NavigateToWaypoint_Feedback, distance_to_goal),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "is_planning",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(urc_msgs__action__NavigateToWaypoint_Feedback, is_planning),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "replan_count",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT16,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(urc_msgs__action__NavigateToWaypoint_Feedback, replan_count),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers urc_msgs__action__NavigateToWaypoint_Feedback__rosidl_typesupport_introspection_c__NavigateToWaypoint_Feedback_message_members = {
  "urc_msgs__action",  // message namespace
  "NavigateToWaypoint_Feedback",  // message name
  3,  // number of fields
  sizeof(urc_msgs__action__NavigateToWaypoint_Feedback),
  urc_msgs__action__NavigateToWaypoint_Feedback__rosidl_typesupport_introspection_c__NavigateToWaypoint_Feedback_message_member_array,  // message members
  urc_msgs__action__NavigateToWaypoint_Feedback__rosidl_typesupport_introspection_c__NavigateToWaypoint_Feedback_init_function,  // function to initialize message memory (memory has to be allocated)
  urc_msgs__action__NavigateToWaypoint_Feedback__rosidl_typesupport_introspection_c__NavigateToWaypoint_Feedback_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t urc_msgs__action__NavigateToWaypoint_Feedback__rosidl_typesupport_introspection_c__NavigateToWaypoint_Feedback_message_type_support_handle = {
  0,
  &urc_msgs__action__NavigateToWaypoint_Feedback__rosidl_typesupport_introspection_c__NavigateToWaypoint_Feedback_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_urc_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, urc_msgs, action, NavigateToWaypoint_Feedback)() {
  if (!urc_msgs__action__NavigateToWaypoint_Feedback__rosidl_typesupport_introspection_c__NavigateToWaypoint_Feedback_message_type_support_handle.typesupport_identifier) {
    urc_msgs__action__NavigateToWaypoint_Feedback__rosidl_typesupport_introspection_c__NavigateToWaypoint_Feedback_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &urc_msgs__action__NavigateToWaypoint_Feedback__rosidl_typesupport_introspection_c__NavigateToWaypoint_Feedback_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

// already included above
// #include <stddef.h>
// already included above
// #include "urc_msgs/action/detail/navigate_to_waypoint__rosidl_typesupport_introspection_c.h"
// already included above
// #include "urc_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "urc_msgs/action/detail/navigate_to_waypoint__functions.h"
// already included above
// #include "urc_msgs/action/detail/navigate_to_waypoint__struct.h"


// Include directives for member types
// Member `goal_id`
#include "unique_identifier_msgs/msg/uuid.h"
// Member `goal_id`
#include "unique_identifier_msgs/msg/detail/uuid__rosidl_typesupport_introspection_c.h"
// Member `goal`
#include "urc_msgs/action/navigate_to_waypoint.h"
// Member `goal`
// already included above
// #include "urc_msgs/action/detail/navigate_to_waypoint__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void urc_msgs__action__NavigateToWaypoint_SendGoal_Request__rosidl_typesupport_introspection_c__NavigateToWaypoint_SendGoal_Request_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  urc_msgs__action__NavigateToWaypoint_SendGoal_Request__init(message_memory);
}

void urc_msgs__action__NavigateToWaypoint_SendGoal_Request__rosidl_typesupport_introspection_c__NavigateToWaypoint_SendGoal_Request_fini_function(void * message_memory)
{
  urc_msgs__action__NavigateToWaypoint_SendGoal_Request__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember urc_msgs__action__NavigateToWaypoint_SendGoal_Request__rosidl_typesupport_introspection_c__NavigateToWaypoint_SendGoal_Request_message_member_array[2] = {
  {
    "goal_id",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(urc_msgs__action__NavigateToWaypoint_SendGoal_Request, goal_id),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "goal",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(urc_msgs__action__NavigateToWaypoint_SendGoal_Request, goal),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers urc_msgs__action__NavigateToWaypoint_SendGoal_Request__rosidl_typesupport_introspection_c__NavigateToWaypoint_SendGoal_Request_message_members = {
  "urc_msgs__action",  // message namespace
  "NavigateToWaypoint_SendGoal_Request",  // message name
  2,  // number of fields
  sizeof(urc_msgs__action__NavigateToWaypoint_SendGoal_Request),
  urc_msgs__action__NavigateToWaypoint_SendGoal_Request__rosidl_typesupport_introspection_c__NavigateToWaypoint_SendGoal_Request_message_member_array,  // message members
  urc_msgs__action__NavigateToWaypoint_SendGoal_Request__rosidl_typesupport_introspection_c__NavigateToWaypoint_SendGoal_Request_init_function,  // function to initialize message memory (memory has to be allocated)
  urc_msgs__action__NavigateToWaypoint_SendGoal_Request__rosidl_typesupport_introspection_c__NavigateToWaypoint_SendGoal_Request_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t urc_msgs__action__NavigateToWaypoint_SendGoal_Request__rosidl_typesupport_introspection_c__NavigateToWaypoint_SendGoal_Request_message_type_support_handle = {
  0,
  &urc_msgs__action__NavigateToWaypoint_SendGoal_Request__rosidl_typesupport_introspection_c__NavigateToWaypoint_SendGoal_Request_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_urc_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, urc_msgs, action, NavigateToWaypoint_SendGoal_Request)() {
  urc_msgs__action__NavigateToWaypoint_SendGoal_Request__rosidl_typesupport_introspection_c__NavigateToWaypoint_SendGoal_Request_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, unique_identifier_msgs, msg, UUID)();
  urc_msgs__action__NavigateToWaypoint_SendGoal_Request__rosidl_typesupport_introspection_c__NavigateToWaypoint_SendGoal_Request_message_member_array[1].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, urc_msgs, action, NavigateToWaypoint_Goal)();
  if (!urc_msgs__action__NavigateToWaypoint_SendGoal_Request__rosidl_typesupport_introspection_c__NavigateToWaypoint_SendGoal_Request_message_type_support_handle.typesupport_identifier) {
    urc_msgs__action__NavigateToWaypoint_SendGoal_Request__rosidl_typesupport_introspection_c__NavigateToWaypoint_SendGoal_Request_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &urc_msgs__action__NavigateToWaypoint_SendGoal_Request__rosidl_typesupport_introspection_c__NavigateToWaypoint_SendGoal_Request_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

// already included above
// #include <stddef.h>
// already included above
// #include "urc_msgs/action/detail/navigate_to_waypoint__rosidl_typesupport_introspection_c.h"
// already included above
// #include "urc_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "urc_msgs/action/detail/navigate_to_waypoint__functions.h"
// already included above
// #include "urc_msgs/action/detail/navigate_to_waypoint__struct.h"


// Include directives for member types
// Member `stamp`
#include "builtin_interfaces/msg/time.h"
// Member `stamp`
#include "builtin_interfaces/msg/detail/time__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void urc_msgs__action__NavigateToWaypoint_SendGoal_Response__rosidl_typesupport_introspection_c__NavigateToWaypoint_SendGoal_Response_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  urc_msgs__action__NavigateToWaypoint_SendGoal_Response__init(message_memory);
}

void urc_msgs__action__NavigateToWaypoint_SendGoal_Response__rosidl_typesupport_introspection_c__NavigateToWaypoint_SendGoal_Response_fini_function(void * message_memory)
{
  urc_msgs__action__NavigateToWaypoint_SendGoal_Response__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember urc_msgs__action__NavigateToWaypoint_SendGoal_Response__rosidl_typesupport_introspection_c__NavigateToWaypoint_SendGoal_Response_message_member_array[2] = {
  {
    "accepted",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(urc_msgs__action__NavigateToWaypoint_SendGoal_Response, accepted),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "stamp",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(urc_msgs__action__NavigateToWaypoint_SendGoal_Response, stamp),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers urc_msgs__action__NavigateToWaypoint_SendGoal_Response__rosidl_typesupport_introspection_c__NavigateToWaypoint_SendGoal_Response_message_members = {
  "urc_msgs__action",  // message namespace
  "NavigateToWaypoint_SendGoal_Response",  // message name
  2,  // number of fields
  sizeof(urc_msgs__action__NavigateToWaypoint_SendGoal_Response),
  urc_msgs__action__NavigateToWaypoint_SendGoal_Response__rosidl_typesupport_introspection_c__NavigateToWaypoint_SendGoal_Response_message_member_array,  // message members
  urc_msgs__action__NavigateToWaypoint_SendGoal_Response__rosidl_typesupport_introspection_c__NavigateToWaypoint_SendGoal_Response_init_function,  // function to initialize message memory (memory has to be allocated)
  urc_msgs__action__NavigateToWaypoint_SendGoal_Response__rosidl_typesupport_introspection_c__NavigateToWaypoint_SendGoal_Response_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t urc_msgs__action__NavigateToWaypoint_SendGoal_Response__rosidl_typesupport_introspection_c__NavigateToWaypoint_SendGoal_Response_message_type_support_handle = {
  0,
  &urc_msgs__action__NavigateToWaypoint_SendGoal_Response__rosidl_typesupport_introspection_c__NavigateToWaypoint_SendGoal_Response_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_urc_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, urc_msgs, action, NavigateToWaypoint_SendGoal_Response)() {
  urc_msgs__action__NavigateToWaypoint_SendGoal_Response__rosidl_typesupport_introspection_c__NavigateToWaypoint_SendGoal_Response_message_member_array[1].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, builtin_interfaces, msg, Time)();
  if (!urc_msgs__action__NavigateToWaypoint_SendGoal_Response__rosidl_typesupport_introspection_c__NavigateToWaypoint_SendGoal_Response_message_type_support_handle.typesupport_identifier) {
    urc_msgs__action__NavigateToWaypoint_SendGoal_Response__rosidl_typesupport_introspection_c__NavigateToWaypoint_SendGoal_Response_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &urc_msgs__action__NavigateToWaypoint_SendGoal_Response__rosidl_typesupport_introspection_c__NavigateToWaypoint_SendGoal_Response_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

#include "rosidl_runtime_c/service_type_support_struct.h"
// already included above
// #include "urc_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "urc_msgs/action/detail/navigate_to_waypoint__rosidl_typesupport_introspection_c.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/service_introspection.h"

// this is intentionally not const to allow initialization later to prevent an initialization race
static rosidl_typesupport_introspection_c__ServiceMembers urc_msgs__action__detail__navigate_to_waypoint__rosidl_typesupport_introspection_c__NavigateToWaypoint_SendGoal_service_members = {
  "urc_msgs__action",  // service namespace
  "NavigateToWaypoint_SendGoal",  // service name
  // these two fields are initialized below on the first access
  NULL,  // request message
  // urc_msgs__action__detail__navigate_to_waypoint__rosidl_typesupport_introspection_c__NavigateToWaypoint_SendGoal_Request_message_type_support_handle,
  NULL  // response message
  // urc_msgs__action__detail__navigate_to_waypoint__rosidl_typesupport_introspection_c__NavigateToWaypoint_SendGoal_Response_message_type_support_handle
};

static rosidl_service_type_support_t urc_msgs__action__detail__navigate_to_waypoint__rosidl_typesupport_introspection_c__NavigateToWaypoint_SendGoal_service_type_support_handle = {
  0,
  &urc_msgs__action__detail__navigate_to_waypoint__rosidl_typesupport_introspection_c__NavigateToWaypoint_SendGoal_service_members,
  get_service_typesupport_handle_function,
};

// Forward declaration of request/response type support functions
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, urc_msgs, action, NavigateToWaypoint_SendGoal_Request)();

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, urc_msgs, action, NavigateToWaypoint_SendGoal_Response)();

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_urc_msgs
const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_introspection_c, urc_msgs, action, NavigateToWaypoint_SendGoal)() {
  if (!urc_msgs__action__detail__navigate_to_waypoint__rosidl_typesupport_introspection_c__NavigateToWaypoint_SendGoal_service_type_support_handle.typesupport_identifier) {
    urc_msgs__action__detail__navigate_to_waypoint__rosidl_typesupport_introspection_c__NavigateToWaypoint_SendGoal_service_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  rosidl_typesupport_introspection_c__ServiceMembers * service_members =
    (rosidl_typesupport_introspection_c__ServiceMembers *)urc_msgs__action__detail__navigate_to_waypoint__rosidl_typesupport_introspection_c__NavigateToWaypoint_SendGoal_service_type_support_handle.data;

  if (!service_members->request_members_) {
    service_members->request_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, urc_msgs, action, NavigateToWaypoint_SendGoal_Request)()->data;
  }
  if (!service_members->response_members_) {
    service_members->response_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, urc_msgs, action, NavigateToWaypoint_SendGoal_Response)()->data;
  }

  return &urc_msgs__action__detail__navigate_to_waypoint__rosidl_typesupport_introspection_c__NavigateToWaypoint_SendGoal_service_type_support_handle;
}

// already included above
// #include <stddef.h>
// already included above
// #include "urc_msgs/action/detail/navigate_to_waypoint__rosidl_typesupport_introspection_c.h"
// already included above
// #include "urc_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "urc_msgs/action/detail/navigate_to_waypoint__functions.h"
// already included above
// #include "urc_msgs/action/detail/navigate_to_waypoint__struct.h"


// Include directives for member types
// Member `goal_id`
// already included above
// #include "unique_identifier_msgs/msg/uuid.h"
// Member `goal_id`
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void urc_msgs__action__NavigateToWaypoint_GetResult_Request__rosidl_typesupport_introspection_c__NavigateToWaypoint_GetResult_Request_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  urc_msgs__action__NavigateToWaypoint_GetResult_Request__init(message_memory);
}

void urc_msgs__action__NavigateToWaypoint_GetResult_Request__rosidl_typesupport_introspection_c__NavigateToWaypoint_GetResult_Request_fini_function(void * message_memory)
{
  urc_msgs__action__NavigateToWaypoint_GetResult_Request__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember urc_msgs__action__NavigateToWaypoint_GetResult_Request__rosidl_typesupport_introspection_c__NavigateToWaypoint_GetResult_Request_message_member_array[1] = {
  {
    "goal_id",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(urc_msgs__action__NavigateToWaypoint_GetResult_Request, goal_id),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers urc_msgs__action__NavigateToWaypoint_GetResult_Request__rosidl_typesupport_introspection_c__NavigateToWaypoint_GetResult_Request_message_members = {
  "urc_msgs__action",  // message namespace
  "NavigateToWaypoint_GetResult_Request",  // message name
  1,  // number of fields
  sizeof(urc_msgs__action__NavigateToWaypoint_GetResult_Request),
  urc_msgs__action__NavigateToWaypoint_GetResult_Request__rosidl_typesupport_introspection_c__NavigateToWaypoint_GetResult_Request_message_member_array,  // message members
  urc_msgs__action__NavigateToWaypoint_GetResult_Request__rosidl_typesupport_introspection_c__NavigateToWaypoint_GetResult_Request_init_function,  // function to initialize message memory (memory has to be allocated)
  urc_msgs__action__NavigateToWaypoint_GetResult_Request__rosidl_typesupport_introspection_c__NavigateToWaypoint_GetResult_Request_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t urc_msgs__action__NavigateToWaypoint_GetResult_Request__rosidl_typesupport_introspection_c__NavigateToWaypoint_GetResult_Request_message_type_support_handle = {
  0,
  &urc_msgs__action__NavigateToWaypoint_GetResult_Request__rosidl_typesupport_introspection_c__NavigateToWaypoint_GetResult_Request_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_urc_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, urc_msgs, action, NavigateToWaypoint_GetResult_Request)() {
  urc_msgs__action__NavigateToWaypoint_GetResult_Request__rosidl_typesupport_introspection_c__NavigateToWaypoint_GetResult_Request_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, unique_identifier_msgs, msg, UUID)();
  if (!urc_msgs__action__NavigateToWaypoint_GetResult_Request__rosidl_typesupport_introspection_c__NavigateToWaypoint_GetResult_Request_message_type_support_handle.typesupport_identifier) {
    urc_msgs__action__NavigateToWaypoint_GetResult_Request__rosidl_typesupport_introspection_c__NavigateToWaypoint_GetResult_Request_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &urc_msgs__action__NavigateToWaypoint_GetResult_Request__rosidl_typesupport_introspection_c__NavigateToWaypoint_GetResult_Request_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

// already included above
// #include <stddef.h>
// already included above
// #include "urc_msgs/action/detail/navigate_to_waypoint__rosidl_typesupport_introspection_c.h"
// already included above
// #include "urc_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "urc_msgs/action/detail/navigate_to_waypoint__functions.h"
// already included above
// #include "urc_msgs/action/detail/navigate_to_waypoint__struct.h"


// Include directives for member types
// Member `result`
// already included above
// #include "urc_msgs/action/navigate_to_waypoint.h"
// Member `result`
// already included above
// #include "urc_msgs/action/detail/navigate_to_waypoint__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void urc_msgs__action__NavigateToWaypoint_GetResult_Response__rosidl_typesupport_introspection_c__NavigateToWaypoint_GetResult_Response_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  urc_msgs__action__NavigateToWaypoint_GetResult_Response__init(message_memory);
}

void urc_msgs__action__NavigateToWaypoint_GetResult_Response__rosidl_typesupport_introspection_c__NavigateToWaypoint_GetResult_Response_fini_function(void * message_memory)
{
  urc_msgs__action__NavigateToWaypoint_GetResult_Response__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember urc_msgs__action__NavigateToWaypoint_GetResult_Response__rosidl_typesupport_introspection_c__NavigateToWaypoint_GetResult_Response_message_member_array[2] = {
  {
    "status",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT8,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(urc_msgs__action__NavigateToWaypoint_GetResult_Response, status),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "result",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(urc_msgs__action__NavigateToWaypoint_GetResult_Response, result),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers urc_msgs__action__NavigateToWaypoint_GetResult_Response__rosidl_typesupport_introspection_c__NavigateToWaypoint_GetResult_Response_message_members = {
  "urc_msgs__action",  // message namespace
  "NavigateToWaypoint_GetResult_Response",  // message name
  2,  // number of fields
  sizeof(urc_msgs__action__NavigateToWaypoint_GetResult_Response),
  urc_msgs__action__NavigateToWaypoint_GetResult_Response__rosidl_typesupport_introspection_c__NavigateToWaypoint_GetResult_Response_message_member_array,  // message members
  urc_msgs__action__NavigateToWaypoint_GetResult_Response__rosidl_typesupport_introspection_c__NavigateToWaypoint_GetResult_Response_init_function,  // function to initialize message memory (memory has to be allocated)
  urc_msgs__action__NavigateToWaypoint_GetResult_Response__rosidl_typesupport_introspection_c__NavigateToWaypoint_GetResult_Response_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t urc_msgs__action__NavigateToWaypoint_GetResult_Response__rosidl_typesupport_introspection_c__NavigateToWaypoint_GetResult_Response_message_type_support_handle = {
  0,
  &urc_msgs__action__NavigateToWaypoint_GetResult_Response__rosidl_typesupport_introspection_c__NavigateToWaypoint_GetResult_Response_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_urc_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, urc_msgs, action, NavigateToWaypoint_GetResult_Response)() {
  urc_msgs__action__NavigateToWaypoint_GetResult_Response__rosidl_typesupport_introspection_c__NavigateToWaypoint_GetResult_Response_message_member_array[1].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, urc_msgs, action, NavigateToWaypoint_Result)();
  if (!urc_msgs__action__NavigateToWaypoint_GetResult_Response__rosidl_typesupport_introspection_c__NavigateToWaypoint_GetResult_Response_message_type_support_handle.typesupport_identifier) {
    urc_msgs__action__NavigateToWaypoint_GetResult_Response__rosidl_typesupport_introspection_c__NavigateToWaypoint_GetResult_Response_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &urc_msgs__action__NavigateToWaypoint_GetResult_Response__rosidl_typesupport_introspection_c__NavigateToWaypoint_GetResult_Response_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

// already included above
// #include "rosidl_runtime_c/service_type_support_struct.h"
// already included above
// #include "urc_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "urc_msgs/action/detail/navigate_to_waypoint__rosidl_typesupport_introspection_c.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/service_introspection.h"

// this is intentionally not const to allow initialization later to prevent an initialization race
static rosidl_typesupport_introspection_c__ServiceMembers urc_msgs__action__detail__navigate_to_waypoint__rosidl_typesupport_introspection_c__NavigateToWaypoint_GetResult_service_members = {
  "urc_msgs__action",  // service namespace
  "NavigateToWaypoint_GetResult",  // service name
  // these two fields are initialized below on the first access
  NULL,  // request message
  // urc_msgs__action__detail__navigate_to_waypoint__rosidl_typesupport_introspection_c__NavigateToWaypoint_GetResult_Request_message_type_support_handle,
  NULL  // response message
  // urc_msgs__action__detail__navigate_to_waypoint__rosidl_typesupport_introspection_c__NavigateToWaypoint_GetResult_Response_message_type_support_handle
};

static rosidl_service_type_support_t urc_msgs__action__detail__navigate_to_waypoint__rosidl_typesupport_introspection_c__NavigateToWaypoint_GetResult_service_type_support_handle = {
  0,
  &urc_msgs__action__detail__navigate_to_waypoint__rosidl_typesupport_introspection_c__NavigateToWaypoint_GetResult_service_members,
  get_service_typesupport_handle_function,
};

// Forward declaration of request/response type support functions
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, urc_msgs, action, NavigateToWaypoint_GetResult_Request)();

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, urc_msgs, action, NavigateToWaypoint_GetResult_Response)();

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_urc_msgs
const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_introspection_c, urc_msgs, action, NavigateToWaypoint_GetResult)() {
  if (!urc_msgs__action__detail__navigate_to_waypoint__rosidl_typesupport_introspection_c__NavigateToWaypoint_GetResult_service_type_support_handle.typesupport_identifier) {
    urc_msgs__action__detail__navigate_to_waypoint__rosidl_typesupport_introspection_c__NavigateToWaypoint_GetResult_service_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  rosidl_typesupport_introspection_c__ServiceMembers * service_members =
    (rosidl_typesupport_introspection_c__ServiceMembers *)urc_msgs__action__detail__navigate_to_waypoint__rosidl_typesupport_introspection_c__NavigateToWaypoint_GetResult_service_type_support_handle.data;

  if (!service_members->request_members_) {
    service_members->request_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, urc_msgs, action, NavigateToWaypoint_GetResult_Request)()->data;
  }
  if (!service_members->response_members_) {
    service_members->response_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, urc_msgs, action, NavigateToWaypoint_GetResult_Response)()->data;
  }

  return &urc_msgs__action__detail__navigate_to_waypoint__rosidl_typesupport_introspection_c__NavigateToWaypoint_GetResult_service_type_support_handle;
}

// already included above
// #include <stddef.h>
// already included above
// #include "urc_msgs/action/detail/navigate_to_waypoint__rosidl_typesupport_introspection_c.h"
// already included above
// #include "urc_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "urc_msgs/action/detail/navigate_to_waypoint__functions.h"
// already included above
// #include "urc_msgs/action/detail/navigate_to_waypoint__struct.h"


// Include directives for member types
// Member `goal_id`
// already included above
// #include "unique_identifier_msgs/msg/uuid.h"
// Member `goal_id`
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__rosidl_typesupport_introspection_c.h"
// Member `feedback`
// already included above
// #include "urc_msgs/action/navigate_to_waypoint.h"
// Member `feedback`
// already included above
// #include "urc_msgs/action/detail/navigate_to_waypoint__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void urc_msgs__action__NavigateToWaypoint_FeedbackMessage__rosidl_typesupport_introspection_c__NavigateToWaypoint_FeedbackMessage_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  urc_msgs__action__NavigateToWaypoint_FeedbackMessage__init(message_memory);
}

void urc_msgs__action__NavigateToWaypoint_FeedbackMessage__rosidl_typesupport_introspection_c__NavigateToWaypoint_FeedbackMessage_fini_function(void * message_memory)
{
  urc_msgs__action__NavigateToWaypoint_FeedbackMessage__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember urc_msgs__action__NavigateToWaypoint_FeedbackMessage__rosidl_typesupport_introspection_c__NavigateToWaypoint_FeedbackMessage_message_member_array[2] = {
  {
    "goal_id",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(urc_msgs__action__NavigateToWaypoint_FeedbackMessage, goal_id),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "feedback",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(urc_msgs__action__NavigateToWaypoint_FeedbackMessage, feedback),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers urc_msgs__action__NavigateToWaypoint_FeedbackMessage__rosidl_typesupport_introspection_c__NavigateToWaypoint_FeedbackMessage_message_members = {
  "urc_msgs__action",  // message namespace
  "NavigateToWaypoint_FeedbackMessage",  // message name
  2,  // number of fields
  sizeof(urc_msgs__action__NavigateToWaypoint_FeedbackMessage),
  urc_msgs__action__NavigateToWaypoint_FeedbackMessage__rosidl_typesupport_introspection_c__NavigateToWaypoint_FeedbackMessage_message_member_array,  // message members
  urc_msgs__action__NavigateToWaypoint_FeedbackMessage__rosidl_typesupport_introspection_c__NavigateToWaypoint_FeedbackMessage_init_function,  // function to initialize message memory (memory has to be allocated)
  urc_msgs__action__NavigateToWaypoint_FeedbackMessage__rosidl_typesupport_introspection_c__NavigateToWaypoint_FeedbackMessage_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t urc_msgs__action__NavigateToWaypoint_FeedbackMessage__rosidl_typesupport_introspection_c__NavigateToWaypoint_FeedbackMessage_message_type_support_handle = {
  0,
  &urc_msgs__action__NavigateToWaypoint_FeedbackMessage__rosidl_typesupport_introspection_c__NavigateToWaypoint_FeedbackMessage_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_urc_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, urc_msgs, action, NavigateToWaypoint_FeedbackMessage)() {
  urc_msgs__action__NavigateToWaypoint_FeedbackMessage__rosidl_typesupport_introspection_c__NavigateToWaypoint_FeedbackMessage_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, unique_identifier_msgs, msg, UUID)();
  urc_msgs__action__NavigateToWaypoint_FeedbackMessage__rosidl_typesupport_introspection_c__NavigateToWaypoint_FeedbackMessage_message_member_array[1].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, urc_msgs, action, NavigateToWaypoint_Feedback)();
  if (!urc_msgs__action__NavigateToWaypoint_FeedbackMessage__rosidl_typesupport_introspection_c__NavigateToWaypoint_FeedbackMessage_message_type_support_handle.typesupport_identifier) {
    urc_msgs__action__NavigateToWaypoint_FeedbackMessage__rosidl_typesupport_introspection_c__NavigateToWaypoint_FeedbackMessage_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &urc_msgs__action__NavigateToWaypoint_FeedbackMessage__rosidl_typesupport_introspection_c__NavigateToWaypoint_FeedbackMessage_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
