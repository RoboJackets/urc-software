// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from urc_msgs:msg/NavigationStatus.idl
// generated code does not contain a copyright notice

#ifndef URC_MSGS__MSG__DETAIL__NAVIGATION_STATUS__FUNCTIONS_H_
#define URC_MSGS__MSG__DETAIL__NAVIGATION_STATUS__FUNCTIONS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdlib.h>

#include "rosidl_runtime_c/visibility_control.h"
#include "urc_msgs/msg/rosidl_generator_c__visibility_control.h"

#include "urc_msgs/msg/detail/navigation_status__struct.h"

/// Initialize msg/NavigationStatus message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * urc_msgs__msg__NavigationStatus
 * )) before or use
 * urc_msgs__msg__NavigationStatus__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_urc_msgs
bool
urc_msgs__msg__NavigationStatus__init(urc_msgs__msg__NavigationStatus * msg);

/// Finalize msg/NavigationStatus message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_urc_msgs
void
urc_msgs__msg__NavigationStatus__fini(urc_msgs__msg__NavigationStatus * msg);

/// Create msg/NavigationStatus message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * urc_msgs__msg__NavigationStatus__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_urc_msgs
urc_msgs__msg__NavigationStatus *
urc_msgs__msg__NavigationStatus__create();

/// Destroy msg/NavigationStatus message.
/**
 * It calls
 * urc_msgs__msg__NavigationStatus__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_urc_msgs
void
urc_msgs__msg__NavigationStatus__destroy(urc_msgs__msg__NavigationStatus * msg);

/// Check for msg/NavigationStatus message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_urc_msgs
bool
urc_msgs__msg__NavigationStatus__are_equal(const urc_msgs__msg__NavigationStatus * lhs, const urc_msgs__msg__NavigationStatus * rhs);

/// Copy a msg/NavigationStatus message.
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
urc_msgs__msg__NavigationStatus__copy(
  const urc_msgs__msg__NavigationStatus * input,
  urc_msgs__msg__NavigationStatus * output);

/// Initialize array of msg/NavigationStatus messages.
/**
 * It allocates the memory for the number of elements and calls
 * urc_msgs__msg__NavigationStatus__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_urc_msgs
bool
urc_msgs__msg__NavigationStatus__Sequence__init(urc_msgs__msg__NavigationStatus__Sequence * array, size_t size);

/// Finalize array of msg/NavigationStatus messages.
/**
 * It calls
 * urc_msgs__msg__NavigationStatus__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_urc_msgs
void
urc_msgs__msg__NavigationStatus__Sequence__fini(urc_msgs__msg__NavigationStatus__Sequence * array);

/// Create array of msg/NavigationStatus messages.
/**
 * It allocates the memory for the array and calls
 * urc_msgs__msg__NavigationStatus__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_urc_msgs
urc_msgs__msg__NavigationStatus__Sequence *
urc_msgs__msg__NavigationStatus__Sequence__create(size_t size);

/// Destroy array of msg/NavigationStatus messages.
/**
 * It calls
 * urc_msgs__msg__NavigationStatus__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_urc_msgs
void
urc_msgs__msg__NavigationStatus__Sequence__destroy(urc_msgs__msg__NavigationStatus__Sequence * array);

/// Check for msg/NavigationStatus message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_urc_msgs
bool
urc_msgs__msg__NavigationStatus__Sequence__are_equal(const urc_msgs__msg__NavigationStatus__Sequence * lhs, const urc_msgs__msg__NavigationStatus__Sequence * rhs);

/// Copy an array of msg/NavigationStatus messages.
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
urc_msgs__msg__NavigationStatus__Sequence__copy(
  const urc_msgs__msg__NavigationStatus__Sequence * input,
  urc_msgs__msg__NavigationStatus__Sequence * output);

#ifdef __cplusplus
}
#endif

#endif  // URC_MSGS__MSG__DETAIL__NAVIGATION_STATUS__FUNCTIONS_H_
