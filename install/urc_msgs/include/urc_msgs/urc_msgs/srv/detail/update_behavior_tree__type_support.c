// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from urc_msgs:srv/UpdateBehaviorTree.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "urc_msgs/srv/detail/update_behavior_tree__rosidl_typesupport_introspection_c.h"
#include "urc_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "urc_msgs/srv/detail/update_behavior_tree__functions.h"
#include "urc_msgs/srv/detail/update_behavior_tree__struct.h"


// Include directives for member types
// Member `tree_content`
// Member `tree_dir`
#include "rosidl_runtime_c/string_functions.h"

#ifdef __cplusplus
extern "C"
{
#endif

void urc_msgs__srv__UpdateBehaviorTree_Request__rosidl_typesupport_introspection_c__UpdateBehaviorTree_Request_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  urc_msgs__srv__UpdateBehaviorTree_Request__init(message_memory);
}

void urc_msgs__srv__UpdateBehaviorTree_Request__rosidl_typesupport_introspection_c__UpdateBehaviorTree_Request_fini_function(void * message_memory)
{
  urc_msgs__srv__UpdateBehaviorTree_Request__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember urc_msgs__srv__UpdateBehaviorTree_Request__rosidl_typesupport_introspection_c__UpdateBehaviorTree_Request_message_member_array[3] = {
  {
    "tree_content",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(urc_msgs__srv__UpdateBehaviorTree_Request, tree_content),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "tree_dir",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(urc_msgs__srv__UpdateBehaviorTree_Request, tree_dir),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "use_dir",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(urc_msgs__srv__UpdateBehaviorTree_Request, use_dir),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers urc_msgs__srv__UpdateBehaviorTree_Request__rosidl_typesupport_introspection_c__UpdateBehaviorTree_Request_message_members = {
  "urc_msgs__srv",  // message namespace
  "UpdateBehaviorTree_Request",  // message name
  3,  // number of fields
  sizeof(urc_msgs__srv__UpdateBehaviorTree_Request),
  urc_msgs__srv__UpdateBehaviorTree_Request__rosidl_typesupport_introspection_c__UpdateBehaviorTree_Request_message_member_array,  // message members
  urc_msgs__srv__UpdateBehaviorTree_Request__rosidl_typesupport_introspection_c__UpdateBehaviorTree_Request_init_function,  // function to initialize message memory (memory has to be allocated)
  urc_msgs__srv__UpdateBehaviorTree_Request__rosidl_typesupport_introspection_c__UpdateBehaviorTree_Request_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t urc_msgs__srv__UpdateBehaviorTree_Request__rosidl_typesupport_introspection_c__UpdateBehaviorTree_Request_message_type_support_handle = {
  0,
  &urc_msgs__srv__UpdateBehaviorTree_Request__rosidl_typesupport_introspection_c__UpdateBehaviorTree_Request_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_urc_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, urc_msgs, srv, UpdateBehaviorTree_Request)() {
  if (!urc_msgs__srv__UpdateBehaviorTree_Request__rosidl_typesupport_introspection_c__UpdateBehaviorTree_Request_message_type_support_handle.typesupport_identifier) {
    urc_msgs__srv__UpdateBehaviorTree_Request__rosidl_typesupport_introspection_c__UpdateBehaviorTree_Request_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &urc_msgs__srv__UpdateBehaviorTree_Request__rosidl_typesupport_introspection_c__UpdateBehaviorTree_Request_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

// already included above
// #include <stddef.h>
// already included above
// #include "urc_msgs/srv/detail/update_behavior_tree__rosidl_typesupport_introspection_c.h"
// already included above
// #include "urc_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "urc_msgs/srv/detail/update_behavior_tree__functions.h"
// already included above
// #include "urc_msgs/srv/detail/update_behavior_tree__struct.h"


#ifdef __cplusplus
extern "C"
{
#endif

void urc_msgs__srv__UpdateBehaviorTree_Response__rosidl_typesupport_introspection_c__UpdateBehaviorTree_Response_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  urc_msgs__srv__UpdateBehaviorTree_Response__init(message_memory);
}

void urc_msgs__srv__UpdateBehaviorTree_Response__rosidl_typesupport_introspection_c__UpdateBehaviorTree_Response_fini_function(void * message_memory)
{
  urc_msgs__srv__UpdateBehaviorTree_Response__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember urc_msgs__srv__UpdateBehaviorTree_Response__rosidl_typesupport_introspection_c__UpdateBehaviorTree_Response_message_member_array[1] = {
  {
    "success",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(urc_msgs__srv__UpdateBehaviorTree_Response, success),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers urc_msgs__srv__UpdateBehaviorTree_Response__rosidl_typesupport_introspection_c__UpdateBehaviorTree_Response_message_members = {
  "urc_msgs__srv",  // message namespace
  "UpdateBehaviorTree_Response",  // message name
  1,  // number of fields
  sizeof(urc_msgs__srv__UpdateBehaviorTree_Response),
  urc_msgs__srv__UpdateBehaviorTree_Response__rosidl_typesupport_introspection_c__UpdateBehaviorTree_Response_message_member_array,  // message members
  urc_msgs__srv__UpdateBehaviorTree_Response__rosidl_typesupport_introspection_c__UpdateBehaviorTree_Response_init_function,  // function to initialize message memory (memory has to be allocated)
  urc_msgs__srv__UpdateBehaviorTree_Response__rosidl_typesupport_introspection_c__UpdateBehaviorTree_Response_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t urc_msgs__srv__UpdateBehaviorTree_Response__rosidl_typesupport_introspection_c__UpdateBehaviorTree_Response_message_type_support_handle = {
  0,
  &urc_msgs__srv__UpdateBehaviorTree_Response__rosidl_typesupport_introspection_c__UpdateBehaviorTree_Response_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_urc_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, urc_msgs, srv, UpdateBehaviorTree_Response)() {
  if (!urc_msgs__srv__UpdateBehaviorTree_Response__rosidl_typesupport_introspection_c__UpdateBehaviorTree_Response_message_type_support_handle.typesupport_identifier) {
    urc_msgs__srv__UpdateBehaviorTree_Response__rosidl_typesupport_introspection_c__UpdateBehaviorTree_Response_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &urc_msgs__srv__UpdateBehaviorTree_Response__rosidl_typesupport_introspection_c__UpdateBehaviorTree_Response_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

#include "rosidl_runtime_c/service_type_support_struct.h"
// already included above
// #include "urc_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "urc_msgs/srv/detail/update_behavior_tree__rosidl_typesupport_introspection_c.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/service_introspection.h"

// this is intentionally not const to allow initialization later to prevent an initialization race
static rosidl_typesupport_introspection_c__ServiceMembers urc_msgs__srv__detail__update_behavior_tree__rosidl_typesupport_introspection_c__UpdateBehaviorTree_service_members = {
  "urc_msgs__srv",  // service namespace
  "UpdateBehaviorTree",  // service name
  // these two fields are initialized below on the first access
  NULL,  // request message
  // urc_msgs__srv__detail__update_behavior_tree__rosidl_typesupport_introspection_c__UpdateBehaviorTree_Request_message_type_support_handle,
  NULL  // response message
  // urc_msgs__srv__detail__update_behavior_tree__rosidl_typesupport_introspection_c__UpdateBehaviorTree_Response_message_type_support_handle
};

static rosidl_service_type_support_t urc_msgs__srv__detail__update_behavior_tree__rosidl_typesupport_introspection_c__UpdateBehaviorTree_service_type_support_handle = {
  0,
  &urc_msgs__srv__detail__update_behavior_tree__rosidl_typesupport_introspection_c__UpdateBehaviorTree_service_members,
  get_service_typesupport_handle_function,
};

// Forward declaration of request/response type support functions
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, urc_msgs, srv, UpdateBehaviorTree_Request)();

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, urc_msgs, srv, UpdateBehaviorTree_Response)();

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_urc_msgs
const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_introspection_c, urc_msgs, srv, UpdateBehaviorTree)() {
  if (!urc_msgs__srv__detail__update_behavior_tree__rosidl_typesupport_introspection_c__UpdateBehaviorTree_service_type_support_handle.typesupport_identifier) {
    urc_msgs__srv__detail__update_behavior_tree__rosidl_typesupport_introspection_c__UpdateBehaviorTree_service_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  rosidl_typesupport_introspection_c__ServiceMembers * service_members =
    (rosidl_typesupport_introspection_c__ServiceMembers *)urc_msgs__srv__detail__update_behavior_tree__rosidl_typesupport_introspection_c__UpdateBehaviorTree_service_type_support_handle.data;

  if (!service_members->request_members_) {
    service_members->request_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, urc_msgs, srv, UpdateBehaviorTree_Request)()->data;
  }
  if (!service_members->response_members_) {
    service_members->response_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, urc_msgs, srv, UpdateBehaviorTree_Response)()->data;
  }

  return &urc_msgs__srv__detail__update_behavior_tree__rosidl_typesupport_introspection_c__UpdateBehaviorTree_service_type_support_handle;
}
