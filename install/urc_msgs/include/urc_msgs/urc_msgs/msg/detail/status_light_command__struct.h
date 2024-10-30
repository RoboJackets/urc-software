// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from urc_msgs:msg/StatusLightCommand.idl
// generated code does not contain a copyright notice

#ifndef URC_MSGS__MSG__DETAIL__STATUS_LIGHT_COMMAND__STRUCT_H_
#define URC_MSGS__MSG__DETAIL__STATUS_LIGHT_COMMAND__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Constant 'RED'.
enum
{
  urc_msgs__msg__StatusLightCommand__RED = 0
};

/// Constant 'GREEN'.
enum
{
  urc_msgs__msg__StatusLightCommand__GREEN = 1
};

/// Constant 'BLUE'.
enum
{
  urc_msgs__msg__StatusLightCommand__BLUE = 2
};

/// Constant 'OFF'.
enum
{
  urc_msgs__msg__StatusLightCommand__OFF = 0
};

/// Constant 'ON'.
enum
{
  urc_msgs__msg__StatusLightCommand__ON = 1
};

/// Constant 'BLINK'.
enum
{
  urc_msgs__msg__StatusLightCommand__BLINK = 2
};

/// Struct defined in msg/StatusLightCommand in the package urc_msgs.
typedef struct urc_msgs__msg__StatusLightCommand
{
  uint8_t color;
  uint8_t state;
} urc_msgs__msg__StatusLightCommand;

// Struct for a sequence of urc_msgs__msg__StatusLightCommand.
typedef struct urc_msgs__msg__StatusLightCommand__Sequence
{
  urc_msgs__msg__StatusLightCommand * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} urc_msgs__msg__StatusLightCommand__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // URC_MSGS__MSG__DETAIL__STATUS_LIGHT_COMMAND__STRUCT_H_
