// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from urc_msgs:msg/ArucoDetection.idl
// generated code does not contain a copyright notice

#ifndef URC_MSGS__MSG__DETAIL__ARUCO_DETECTION__FUNCTIONS_H_
#define URC_MSGS__MSG__DETAIL__ARUCO_DETECTION__FUNCTIONS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdlib.h>

#include "rosidl_runtime_c/visibility_control.h"
#include "urc_msgs/msg/rosidl_generator_c__visibility_control.h"

#include "urc_msgs/msg/detail/aruco_detection__struct.h"

/// Initialize msg/ArucoDetection message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * urc_msgs__msg__ArucoDetection
 * )) before or use
 * urc_msgs__msg__ArucoDetection__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_urc_msgs
bool
urc_msgs__msg__ArucoDetection__init(urc_msgs__msg__ArucoDetection * msg);

/// Finalize msg/ArucoDetection message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_urc_msgs
void
urc_msgs__msg__ArucoDetection__fini(urc_msgs__msg__ArucoDetection * msg);

/// Create msg/ArucoDetection message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * urc_msgs__msg__ArucoDetection__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_urc_msgs
urc_msgs__msg__ArucoDetection *
urc_msgs__msg__ArucoDetection__create();

/// Destroy msg/ArucoDetection message.
/**
 * It calls
 * urc_msgs__msg__ArucoDetection__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_urc_msgs
void
urc_msgs__msg__ArucoDetection__destroy(urc_msgs__msg__ArucoDetection * msg);

/// Check for msg/ArucoDetection message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_urc_msgs
bool
urc_msgs__msg__ArucoDetection__are_equal(const urc_msgs__msg__ArucoDetection * lhs, const urc_msgs__msg__ArucoDetection * rhs);

/// Copy a msg/ArucoDetection message.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source message pointer.
 * \param[out] output The target message pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer is null
 *   or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_urc_msgs
bool
urc_msgs__msg__ArucoDetection__copy(
  const urc_msgs__msg__ArucoDetection * input,
  urc_msgs__msg__ArucoDetection * output);

/// Initialize array of msg/ArucoDetection messages.
/**
 * It allocates the memory for the number of elements and calls
 * urc_msgs__msg__ArucoDetection__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_urc_msgs
bool
urc_msgs__msg__ArucoDetection__Sequence__init(urc_msgs__msg__ArucoDetection__Sequence * array, size_t size);

/// Finalize array of msg/ArucoDetection messages.
/**
 * It calls
 * urc_msgs__msg__ArucoDetection__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_urc_msgs
void
urc_msgs__msg__ArucoDetection__Sequence__fini(urc_msgs__msg__ArucoDetection__Sequence * array);

/// Create array of msg/ArucoDetection messages.
/**
 * It allocates the memory for the array and calls
 * urc_msgs__msg__ArucoDetection__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_urc_msgs
urc_msgs__msg__ArucoDetection__Sequence *
urc_msgs__msg__ArucoDetection__Sequence__create(size_t size);

/// Destroy array of msg/ArucoDetection messages.
/**
 * It calls
 * urc_msgs__msg__ArucoDetection__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_urc_msgs
void
urc_msgs__msg__ArucoDetection__Sequence__destroy(urc_msgs__msg__ArucoDetection__Sequence * array);

/// Check for msg/ArucoDetection message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_urc_msgs
bool
urc_msgs__msg__ArucoDetection__Sequence__are_equal(const urc_msgs__msg__ArucoDetection__Sequence * lhs, const urc_msgs__msg__ArucoDetection__Sequence * rhs);

/// Copy an array of msg/ArucoDetection messages.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source array pointer.
 * \param[out] output The target array pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer
 *   is null or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_urc_msgs
bool
urc_msgs__msg__ArucoDetection__Sequence__copy(
  const urc_msgs__msg__ArucoDetection__Sequence * input,
  urc_msgs__msg__ArucoDetection__Sequence * output);

#ifdef __cplusplus
}
#endif

#endif  // URC_MSGS__MSG__DETAIL__ARUCO_DETECTION__FUNCTIONS_H_
