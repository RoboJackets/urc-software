// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from urc_msgs:msg/BatteryInfo.idl
// generated code does not contain a copyright notice

#ifndef URC_MSGS__MSG__DETAIL__BATTERY_INFO__STRUCT_H_
#define URC_MSGS__MSG__DETAIL__BATTERY_INFO__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'cell_voltages'
#include "rosidl_runtime_c/primitives_sequence.h"

/// Struct defined in msg/BatteryInfo in the package urc_msgs.
typedef struct urc_msgs__msg__BatteryInfo
{
  float cell_voltage;
  float cell_charge_percentage;
  float cell_discharge_current;
  float cell_temperature;
  rosidl_runtime_c__float__Sequence cell_voltages;
} urc_msgs__msg__BatteryInfo;

// Struct for a sequence of urc_msgs__msg__BatteryInfo.
typedef struct urc_msgs__msg__BatteryInfo__Sequence
{
  urc_msgs__msg__BatteryInfo * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} urc_msgs__msg__BatteryInfo__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // URC_MSGS__MSG__DETAIL__BATTERY_INFO__STRUCT_H_
