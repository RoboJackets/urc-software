// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from vectornav_msgs:msg/ImuGroup.idl
// generated code does not contain a copyright notice

#ifndef VECTORNAV_MSGS__MSG__DETAIL__IMU_GROUP__FUNCTIONS_H_
#define VECTORNAV_MSGS__MSG__DETAIL__IMU_GROUP__FUNCTIONS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdlib.h>

#include "rosidl_runtime_c/visibility_control.h"
#include "vectornav_msgs/msg/rosidl_generator_c__visibility_control.h"

#include "vectornav_msgs/msg/detail/imu_group__struct.h"

/// Initialize msg/ImuGroup message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * vectornav_msgs__msg__ImuGroup
 * )) before or use
 * vectornav_msgs__msg__ImuGroup__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_vectornav_msgs
bool
vectornav_msgs__msg__ImuGroup__init(vectornav_msgs__msg__ImuGroup * msg);

/// Finalize msg/ImuGroup message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_vectornav_msgs
void
vectornav_msgs__msg__ImuGroup__fini(vectornav_msgs__msg__ImuGroup * msg);

/// Create msg/ImuGroup message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * vectornav_msgs__msg__ImuGroup__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_vectornav_msgs
vectornav_msgs__msg__ImuGroup *
vectornav_msgs__msg__ImuGroup__create();

/// Destroy msg/ImuGroup message.
/**
 * It calls
 * vectornav_msgs__msg__ImuGroup__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_vectornav_msgs
void
vectornav_msgs__msg__ImuGroup__destroy(vectornav_msgs__msg__ImuGroup * msg);

/// Check for msg/ImuGroup message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_vectornav_msgs
bool
vectornav_msgs__msg__ImuGroup__are_equal(const vectornav_msgs__msg__ImuGroup * lhs, const vectornav_msgs__msg__ImuGroup * rhs);

/// Copy a msg/ImuGroup message.
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
ROSIDL_GENERATOR_C_PUBLIC_vectornav_msgs
bool
vectornav_msgs__msg__ImuGroup__copy(
  const vectornav_msgs__msg__ImuGroup * input,
  vectornav_msgs__msg__ImuGroup * output);

/// Initialize array of msg/ImuGroup messages.
/**
 * It allocates the memory for the number of elements and calls
 * vectornav_msgs__msg__ImuGroup__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_vectornav_msgs
bool
vectornav_msgs__msg__ImuGroup__Sequence__init(vectornav_msgs__msg__ImuGroup__Sequence * array, size_t size);

/// Finalize array of msg/ImuGroup messages.
/**
 * It calls
 * vectornav_msgs__msg__ImuGroup__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_vectornav_msgs
void
vectornav_msgs__msg__ImuGroup__Sequence__fini(vectornav_msgs__msg__ImuGroup__Sequence * array);

/// Create array of msg/ImuGroup messages.
/**
 * It allocates the memory for the array and calls
 * vectornav_msgs__msg__ImuGroup__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_vectornav_msgs
vectornav_msgs__msg__ImuGroup__Sequence *
vectornav_msgs__msg__ImuGroup__Sequence__create(size_t size);

/// Destroy array of msg/ImuGroup messages.
/**
 * It calls
 * vectornav_msgs__msg__ImuGroup__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_vectornav_msgs
void
vectornav_msgs__msg__ImuGroup__Sequence__destroy(vectornav_msgs__msg__ImuGroup__Sequence * array);

/// Check for msg/ImuGroup message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_vectornav_msgs
bool
vectornav_msgs__msg__ImuGroup__Sequence__are_equal(const vectornav_msgs__msg__ImuGroup__Sequence * lhs, const vectornav_msgs__msg__ImuGroup__Sequence * rhs);

/// Copy an array of msg/ImuGroup messages.
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
ROSIDL_GENERATOR_C_PUBLIC_vectornav_msgs
bool
vectornav_msgs__msg__ImuGroup__Sequence__copy(
  const vectornav_msgs__msg__ImuGroup__Sequence * input,
  vectornav_msgs__msg__ImuGroup__Sequence * output);

#ifdef __cplusplus
}
#endif

#endif  // VECTORNAV_MSGS__MSG__DETAIL__IMU_GROUP__FUNCTIONS_H_
