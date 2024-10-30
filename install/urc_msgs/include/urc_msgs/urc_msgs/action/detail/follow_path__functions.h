// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from urc_msgs:action/FollowPath.idl
// generated code does not contain a copyright notice

#ifndef URC_MSGS__ACTION__DETAIL__FOLLOW_PATH__FUNCTIONS_H_
#define URC_MSGS__ACTION__DETAIL__FOLLOW_PATH__FUNCTIONS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdlib.h>

#include "rosidl_runtime_c/visibility_control.h"
#include "urc_msgs/msg/rosidl_generator_c__visibility_control.h"

#include "urc_msgs/action/detail/follow_path__struct.h"

/// Initialize action/FollowPath message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * urc_msgs__action__FollowPath_Goal
 * )) before or use
 * urc_msgs__action__FollowPath_Goal__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_urc_msgs
bool
urc_msgs__action__FollowPath_Goal__init(urc_msgs__action__FollowPath_Goal * msg);

/// Finalize action/FollowPath message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_urc_msgs
void
urc_msgs__action__FollowPath_Goal__fini(urc_msgs__action__FollowPath_Goal * msg);

/// Create action/FollowPath message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * urc_msgs__action__FollowPath_Goal__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_urc_msgs
urc_msgs__action__FollowPath_Goal *
urc_msgs__action__FollowPath_Goal__create();

/// Destroy action/FollowPath message.
/**
 * It calls
 * urc_msgs__action__FollowPath_Goal__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_urc_msgs
void
urc_msgs__action__FollowPath_Goal__destroy(urc_msgs__action__FollowPath_Goal * msg);

/// Check for action/FollowPath message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_urc_msgs
bool
urc_msgs__action__FollowPath_Goal__are_equal(const urc_msgs__action__FollowPath_Goal * lhs, const urc_msgs__action__FollowPath_Goal * rhs);

/// Copy a action/FollowPath message.
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
urc_msgs__action__FollowPath_Goal__copy(
  const urc_msgs__action__FollowPath_Goal * input,
  urc_msgs__action__FollowPath_Goal * output);

/// Initialize array of action/FollowPath messages.
/**
 * It allocates the memory for the number of elements and calls
 * urc_msgs__action__FollowPath_Goal__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_urc_msgs
bool
urc_msgs__action__FollowPath_Goal__Sequence__init(urc_msgs__action__FollowPath_Goal__Sequence * array, size_t size);

/// Finalize array of action/FollowPath messages.
/**
 * It calls
 * urc_msgs__action__FollowPath_Goal__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_urc_msgs
void
urc_msgs__action__FollowPath_Goal__Sequence__fini(urc_msgs__action__FollowPath_Goal__Sequence * array);

/// Create array of action/FollowPath messages.
/**
 * It allocates the memory for the array and calls
 * urc_msgs__action__FollowPath_Goal__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_urc_msgs
urc_msgs__action__FollowPath_Goal__Sequence *
urc_msgs__action__FollowPath_Goal__Sequence__create(size_t size);

/// Destroy array of action/FollowPath messages.
/**
 * It calls
 * urc_msgs__action__FollowPath_Goal__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_urc_msgs
void
urc_msgs__action__FollowPath_Goal__Sequence__destroy(urc_msgs__action__FollowPath_Goal__Sequence * array);

/// Check for action/FollowPath message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_urc_msgs
bool
urc_msgs__action__FollowPath_Goal__Sequence__are_equal(const urc_msgs__action__FollowPath_Goal__Sequence * lhs, const urc_msgs__action__FollowPath_Goal__Sequence * rhs);

/// Copy an array of action/FollowPath messages.
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
urc_msgs__action__FollowPath_Goal__Sequence__copy(
  const urc_msgs__action__FollowPath_Goal__Sequence * input,
  urc_msgs__action__FollowPath_Goal__Sequence * output);

/// Initialize action/FollowPath message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * urc_msgs__action__FollowPath_Result
 * )) before or use
 * urc_msgs__action__FollowPath_Result__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_urc_msgs
bool
urc_msgs__action__FollowPath_Result__init(urc_msgs__action__FollowPath_Result * msg);

/// Finalize action/FollowPath message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_urc_msgs
void
urc_msgs__action__FollowPath_Result__fini(urc_msgs__action__FollowPath_Result * msg);

/// Create action/FollowPath message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * urc_msgs__action__FollowPath_Result__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_urc_msgs
urc_msgs__action__FollowPath_Result *
urc_msgs__action__FollowPath_Result__create();

/// Destroy action/FollowPath message.
/**
 * It calls
 * urc_msgs__action__FollowPath_Result__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_urc_msgs
void
urc_msgs__action__FollowPath_Result__destroy(urc_msgs__action__FollowPath_Result * msg);

/// Check for action/FollowPath message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_urc_msgs
bool
urc_msgs__action__FollowPath_Result__are_equal(const urc_msgs__action__FollowPath_Result * lhs, const urc_msgs__action__FollowPath_Result * rhs);

/// Copy a action/FollowPath message.
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
urc_msgs__action__FollowPath_Result__copy(
  const urc_msgs__action__FollowPath_Result * input,
  urc_msgs__action__FollowPath_Result * output);

/// Initialize array of action/FollowPath messages.
/**
 * It allocates the memory for the number of elements and calls
 * urc_msgs__action__FollowPath_Result__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_urc_msgs
bool
urc_msgs__action__FollowPath_Result__Sequence__init(urc_msgs__action__FollowPath_Result__Sequence * array, size_t size);

/// Finalize array of action/FollowPath messages.
/**
 * It calls
 * urc_msgs__action__FollowPath_Result__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_urc_msgs
void
urc_msgs__action__FollowPath_Result__Sequence__fini(urc_msgs__action__FollowPath_Result__Sequence * array);

/// Create array of action/FollowPath messages.
/**
 * It allocates the memory for the array and calls
 * urc_msgs__action__FollowPath_Result__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_urc_msgs
urc_msgs__action__FollowPath_Result__Sequence *
urc_msgs__action__FollowPath_Result__Sequence__create(size_t size);

/// Destroy array of action/FollowPath messages.
/**
 * It calls
 * urc_msgs__action__FollowPath_Result__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_urc_msgs
void
urc_msgs__action__FollowPath_Result__Sequence__destroy(urc_msgs__action__FollowPath_Result__Sequence * array);

/// Check for action/FollowPath message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_urc_msgs
bool
urc_msgs__action__FollowPath_Result__Sequence__are_equal(const urc_msgs__action__FollowPath_Result__Sequence * lhs, const urc_msgs__action__FollowPath_Result__Sequence * rhs);

/// Copy an array of action/FollowPath messages.
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
urc_msgs__action__FollowPath_Result__Sequence__copy(
  const urc_msgs__action__FollowPath_Result__Sequence * input,
  urc_msgs__action__FollowPath_Result__Sequence * output);

/// Initialize action/FollowPath message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * urc_msgs__action__FollowPath_Feedback
 * )) before or use
 * urc_msgs__action__FollowPath_Feedback__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_urc_msgs
bool
urc_msgs__action__FollowPath_Feedback__init(urc_msgs__action__FollowPath_Feedback * msg);

/// Finalize action/FollowPath message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_urc_msgs
void
urc_msgs__action__FollowPath_Feedback__fini(urc_msgs__action__FollowPath_Feedback * msg);

/// Create action/FollowPath message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * urc_msgs__action__FollowPath_Feedback__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_urc_msgs
urc_msgs__action__FollowPath_Feedback *
urc_msgs__action__FollowPath_Feedback__create();

/// Destroy action/FollowPath message.
/**
 * It calls
 * urc_msgs__action__FollowPath_Feedback__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_urc_msgs
void
urc_msgs__action__FollowPath_Feedback__destroy(urc_msgs__action__FollowPath_Feedback * msg);

/// Check for action/FollowPath message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_urc_msgs
bool
urc_msgs__action__FollowPath_Feedback__are_equal(const urc_msgs__action__FollowPath_Feedback * lhs, const urc_msgs__action__FollowPath_Feedback * rhs);

/// Copy a action/FollowPath message.
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
urc_msgs__action__FollowPath_Feedback__copy(
  const urc_msgs__action__FollowPath_Feedback * input,
  urc_msgs__action__FollowPath_Feedback * output);

/// Initialize array of action/FollowPath messages.
/**
 * It allocates the memory for the number of elements and calls
 * urc_msgs__action__FollowPath_Feedback__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_urc_msgs
bool
urc_msgs__action__FollowPath_Feedback__Sequence__init(urc_msgs__action__FollowPath_Feedback__Sequence * array, size_t size);

/// Finalize array of action/FollowPath messages.
/**
 * It calls
 * urc_msgs__action__FollowPath_Feedback__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_urc_msgs
void
urc_msgs__action__FollowPath_Feedback__Sequence__fini(urc_msgs__action__FollowPath_Feedback__Sequence * array);

/// Create array of action/FollowPath messages.
/**
 * It allocates the memory for the array and calls
 * urc_msgs__action__FollowPath_Feedback__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_urc_msgs
urc_msgs__action__FollowPath_Feedback__Sequence *
urc_msgs__action__FollowPath_Feedback__Sequence__create(size_t size);

/// Destroy array of action/FollowPath messages.
/**
 * It calls
 * urc_msgs__action__FollowPath_Feedback__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_urc_msgs
void
urc_msgs__action__FollowPath_Feedback__Sequence__destroy(urc_msgs__action__FollowPath_Feedback__Sequence * array);

/// Check for action/FollowPath message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_urc_msgs
bool
urc_msgs__action__FollowPath_Feedback__Sequence__are_equal(const urc_msgs__action__FollowPath_Feedback__Sequence * lhs, const urc_msgs__action__FollowPath_Feedback__Sequence * rhs);

/// Copy an array of action/FollowPath messages.
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
urc_msgs__action__FollowPath_Feedback__Sequence__copy(
  const urc_msgs__action__FollowPath_Feedback__Sequence * input,
  urc_msgs__action__FollowPath_Feedback__Sequence * output);

/// Initialize action/FollowPath message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * urc_msgs__action__FollowPath_SendGoal_Request
 * )) before or use
 * urc_msgs__action__FollowPath_SendGoal_Request__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_urc_msgs
bool
urc_msgs__action__FollowPath_SendGoal_Request__init(urc_msgs__action__FollowPath_SendGoal_Request * msg);

/// Finalize action/FollowPath message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_urc_msgs
void
urc_msgs__action__FollowPath_SendGoal_Request__fini(urc_msgs__action__FollowPath_SendGoal_Request * msg);

/// Create action/FollowPath message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * urc_msgs__action__FollowPath_SendGoal_Request__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_urc_msgs
urc_msgs__action__FollowPath_SendGoal_Request *
urc_msgs__action__FollowPath_SendGoal_Request__create();

/// Destroy action/FollowPath message.
/**
 * It calls
 * urc_msgs__action__FollowPath_SendGoal_Request__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_urc_msgs
void
urc_msgs__action__FollowPath_SendGoal_Request__destroy(urc_msgs__action__FollowPath_SendGoal_Request * msg);

/// Check for action/FollowPath message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_urc_msgs
bool
urc_msgs__action__FollowPath_SendGoal_Request__are_equal(const urc_msgs__action__FollowPath_SendGoal_Request * lhs, const urc_msgs__action__FollowPath_SendGoal_Request * rhs);

/// Copy a action/FollowPath message.
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
urc_msgs__action__FollowPath_SendGoal_Request__copy(
  const urc_msgs__action__FollowPath_SendGoal_Request * input,
  urc_msgs__action__FollowPath_SendGoal_Request * output);

/// Initialize array of action/FollowPath messages.
/**
 * It allocates the memory for the number of elements and calls
 * urc_msgs__action__FollowPath_SendGoal_Request__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_urc_msgs
bool
urc_msgs__action__FollowPath_SendGoal_Request__Sequence__init(urc_msgs__action__FollowPath_SendGoal_Request__Sequence * array, size_t size);

/// Finalize array of action/FollowPath messages.
/**
 * It calls
 * urc_msgs__action__FollowPath_SendGoal_Request__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_urc_msgs
void
urc_msgs__action__FollowPath_SendGoal_Request__Sequence__fini(urc_msgs__action__FollowPath_SendGoal_Request__Sequence * array);

/// Create array of action/FollowPath messages.
/**
 * It allocates the memory for the array and calls
 * urc_msgs__action__FollowPath_SendGoal_Request__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_urc_msgs
urc_msgs__action__FollowPath_SendGoal_Request__Sequence *
urc_msgs__action__FollowPath_SendGoal_Request__Sequence__create(size_t size);

/// Destroy array of action/FollowPath messages.
/**
 * It calls
 * urc_msgs__action__FollowPath_SendGoal_Request__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_urc_msgs
void
urc_msgs__action__FollowPath_SendGoal_Request__Sequence__destroy(urc_msgs__action__FollowPath_SendGoal_Request__Sequence * array);

/// Check for action/FollowPath message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_urc_msgs
bool
urc_msgs__action__FollowPath_SendGoal_Request__Sequence__are_equal(const urc_msgs__action__FollowPath_SendGoal_Request__Sequence * lhs, const urc_msgs__action__FollowPath_SendGoal_Request__Sequence * rhs);

/// Copy an array of action/FollowPath messages.
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
urc_msgs__action__FollowPath_SendGoal_Request__Sequence__copy(
  const urc_msgs__action__FollowPath_SendGoal_Request__Sequence * input,
  urc_msgs__action__FollowPath_SendGoal_Request__Sequence * output);

/// Initialize action/FollowPath message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * urc_msgs__action__FollowPath_SendGoal_Response
 * )) before or use
 * urc_msgs__action__FollowPath_SendGoal_Response__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_urc_msgs
bool
urc_msgs__action__FollowPath_SendGoal_Response__init(urc_msgs__action__FollowPath_SendGoal_Response * msg);

/// Finalize action/FollowPath message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_urc_msgs
void
urc_msgs__action__FollowPath_SendGoal_Response__fini(urc_msgs__action__FollowPath_SendGoal_Response * msg);

/// Create action/FollowPath message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * urc_msgs__action__FollowPath_SendGoal_Response__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_urc_msgs
urc_msgs__action__FollowPath_SendGoal_Response *
urc_msgs__action__FollowPath_SendGoal_Response__create();

/// Destroy action/FollowPath message.
/**
 * It calls
 * urc_msgs__action__FollowPath_SendGoal_Response__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_urc_msgs
void
urc_msgs__action__FollowPath_SendGoal_Response__destroy(urc_msgs__action__FollowPath_SendGoal_Response * msg);

/// Check for action/FollowPath message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_urc_msgs
bool
urc_msgs__action__FollowPath_SendGoal_Response__are_equal(const urc_msgs__action__FollowPath_SendGoal_Response * lhs, const urc_msgs__action__FollowPath_SendGoal_Response * rhs);

/// Copy a action/FollowPath message.
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
urc_msgs__action__FollowPath_SendGoal_Response__copy(
  const urc_msgs__action__FollowPath_SendGoal_Response * input,
  urc_msgs__action__FollowPath_SendGoal_Response * output);

/// Initialize array of action/FollowPath messages.
/**
 * It allocates the memory for the number of elements and calls
 * urc_msgs__action__FollowPath_SendGoal_Response__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_urc_msgs
bool
urc_msgs__action__FollowPath_SendGoal_Response__Sequence__init(urc_msgs__action__FollowPath_SendGoal_Response__Sequence * array, size_t size);

/// Finalize array of action/FollowPath messages.
/**
 * It calls
 * urc_msgs__action__FollowPath_SendGoal_Response__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_urc_msgs
void
urc_msgs__action__FollowPath_SendGoal_Response__Sequence__fini(urc_msgs__action__FollowPath_SendGoal_Response__Sequence * array);

/// Create array of action/FollowPath messages.
/**
 * It allocates the memory for the array and calls
 * urc_msgs__action__FollowPath_SendGoal_Response__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_urc_msgs
urc_msgs__action__FollowPath_SendGoal_Response__Sequence *
urc_msgs__action__FollowPath_SendGoal_Response__Sequence__create(size_t size);

/// Destroy array of action/FollowPath messages.
/**
 * It calls
 * urc_msgs__action__FollowPath_SendGoal_Response__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_urc_msgs
void
urc_msgs__action__FollowPath_SendGoal_Response__Sequence__destroy(urc_msgs__action__FollowPath_SendGoal_Response__Sequence * array);

/// Check for action/FollowPath message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_urc_msgs
bool
urc_msgs__action__FollowPath_SendGoal_Response__Sequence__are_equal(const urc_msgs__action__FollowPath_SendGoal_Response__Sequence * lhs, const urc_msgs__action__FollowPath_SendGoal_Response__Sequence * rhs);

/// Copy an array of action/FollowPath messages.
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
urc_msgs__action__FollowPath_SendGoal_Response__Sequence__copy(
  const urc_msgs__action__FollowPath_SendGoal_Response__Sequence * input,
  urc_msgs__action__FollowPath_SendGoal_Response__Sequence * output);

/// Initialize action/FollowPath message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * urc_msgs__action__FollowPath_GetResult_Request
 * )) before or use
 * urc_msgs__action__FollowPath_GetResult_Request__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_urc_msgs
bool
urc_msgs__action__FollowPath_GetResult_Request__init(urc_msgs__action__FollowPath_GetResult_Request * msg);

/// Finalize action/FollowPath message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_urc_msgs
void
urc_msgs__action__FollowPath_GetResult_Request__fini(urc_msgs__action__FollowPath_GetResult_Request * msg);

/// Create action/FollowPath message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * urc_msgs__action__FollowPath_GetResult_Request__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_urc_msgs
urc_msgs__action__FollowPath_GetResult_Request *
urc_msgs__action__FollowPath_GetResult_Request__create();

/// Destroy action/FollowPath message.
/**
 * It calls
 * urc_msgs__action__FollowPath_GetResult_Request__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_urc_msgs
void
urc_msgs__action__FollowPath_GetResult_Request__destroy(urc_msgs__action__FollowPath_GetResult_Request * msg);

/// Check for action/FollowPath message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_urc_msgs
bool
urc_msgs__action__FollowPath_GetResult_Request__are_equal(const urc_msgs__action__FollowPath_GetResult_Request * lhs, const urc_msgs__action__FollowPath_GetResult_Request * rhs);

/// Copy a action/FollowPath message.
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
urc_msgs__action__FollowPath_GetResult_Request__copy(
  const urc_msgs__action__FollowPath_GetResult_Request * input,
  urc_msgs__action__FollowPath_GetResult_Request * output);

/// Initialize array of action/FollowPath messages.
/**
 * It allocates the memory for the number of elements and calls
 * urc_msgs__action__FollowPath_GetResult_Request__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_urc_msgs
bool
urc_msgs__action__FollowPath_GetResult_Request__Sequence__init(urc_msgs__action__FollowPath_GetResult_Request__Sequence * array, size_t size);

/// Finalize array of action/FollowPath messages.
/**
 * It calls
 * urc_msgs__action__FollowPath_GetResult_Request__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_urc_msgs
void
urc_msgs__action__FollowPath_GetResult_Request__Sequence__fini(urc_msgs__action__FollowPath_GetResult_Request__Sequence * array);

/// Create array of action/FollowPath messages.
/**
 * It allocates the memory for the array and calls
 * urc_msgs__action__FollowPath_GetResult_Request__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_urc_msgs
urc_msgs__action__FollowPath_GetResult_Request__Sequence *
urc_msgs__action__FollowPath_GetResult_Request__Sequence__create(size_t size);

/// Destroy array of action/FollowPath messages.
/**
 * It calls
 * urc_msgs__action__FollowPath_GetResult_Request__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_urc_msgs
void
urc_msgs__action__FollowPath_GetResult_Request__Sequence__destroy(urc_msgs__action__FollowPath_GetResult_Request__Sequence * array);

/// Check for action/FollowPath message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_urc_msgs
bool
urc_msgs__action__FollowPath_GetResult_Request__Sequence__are_equal(const urc_msgs__action__FollowPath_GetResult_Request__Sequence * lhs, const urc_msgs__action__FollowPath_GetResult_Request__Sequence * rhs);

/// Copy an array of action/FollowPath messages.
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
urc_msgs__action__FollowPath_GetResult_Request__Sequence__copy(
  const urc_msgs__action__FollowPath_GetResult_Request__Sequence * input,
  urc_msgs__action__FollowPath_GetResult_Request__Sequence * output);

/// Initialize action/FollowPath message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * urc_msgs__action__FollowPath_GetResult_Response
 * )) before or use
 * urc_msgs__action__FollowPath_GetResult_Response__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_urc_msgs
bool
urc_msgs__action__FollowPath_GetResult_Response__init(urc_msgs__action__FollowPath_GetResult_Response * msg);

/// Finalize action/FollowPath message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_urc_msgs
void
urc_msgs__action__FollowPath_GetResult_Response__fini(urc_msgs__action__FollowPath_GetResult_Response * msg);

/// Create action/FollowPath message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * urc_msgs__action__FollowPath_GetResult_Response__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_urc_msgs
urc_msgs__action__FollowPath_GetResult_Response *
urc_msgs__action__FollowPath_GetResult_Response__create();

/// Destroy action/FollowPath message.
/**
 * It calls
 * urc_msgs__action__FollowPath_GetResult_Response__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_urc_msgs
void
urc_msgs__action__FollowPath_GetResult_Response__destroy(urc_msgs__action__FollowPath_GetResult_Response * msg);

/// Check for action/FollowPath message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_urc_msgs
bool
urc_msgs__action__FollowPath_GetResult_Response__are_equal(const urc_msgs__action__FollowPath_GetResult_Response * lhs, const urc_msgs__action__FollowPath_GetResult_Response * rhs);

/// Copy a action/FollowPath message.
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
urc_msgs__action__FollowPath_GetResult_Response__copy(
  const urc_msgs__action__FollowPath_GetResult_Response * input,
  urc_msgs__action__FollowPath_GetResult_Response * output);

/// Initialize array of action/FollowPath messages.
/**
 * It allocates the memory for the number of elements and calls
 * urc_msgs__action__FollowPath_GetResult_Response__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_urc_msgs
bool
urc_msgs__action__FollowPath_GetResult_Response__Sequence__init(urc_msgs__action__FollowPath_GetResult_Response__Sequence * array, size_t size);

/// Finalize array of action/FollowPath messages.
/**
 * It calls
 * urc_msgs__action__FollowPath_GetResult_Response__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_urc_msgs
void
urc_msgs__action__FollowPath_GetResult_Response__Sequence__fini(urc_msgs__action__FollowPath_GetResult_Response__Sequence * array);

/// Create array of action/FollowPath messages.
/**
 * It allocates the memory for the array and calls
 * urc_msgs__action__FollowPath_GetResult_Response__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_urc_msgs
urc_msgs__action__FollowPath_GetResult_Response__Sequence *
urc_msgs__action__FollowPath_GetResult_Response__Sequence__create(size_t size);

/// Destroy array of action/FollowPath messages.
/**
 * It calls
 * urc_msgs__action__FollowPath_GetResult_Response__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_urc_msgs
void
urc_msgs__action__FollowPath_GetResult_Response__Sequence__destroy(urc_msgs__action__FollowPath_GetResult_Response__Sequence * array);

/// Check for action/FollowPath message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_urc_msgs
bool
urc_msgs__action__FollowPath_GetResult_Response__Sequence__are_equal(const urc_msgs__action__FollowPath_GetResult_Response__Sequence * lhs, const urc_msgs__action__FollowPath_GetResult_Response__Sequence * rhs);

/// Copy an array of action/FollowPath messages.
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
urc_msgs__action__FollowPath_GetResult_Response__Sequence__copy(
  const urc_msgs__action__FollowPath_GetResult_Response__Sequence * input,
  urc_msgs__action__FollowPath_GetResult_Response__Sequence * output);

/// Initialize action/FollowPath message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * urc_msgs__action__FollowPath_FeedbackMessage
 * )) before or use
 * urc_msgs__action__FollowPath_FeedbackMessage__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_urc_msgs
bool
urc_msgs__action__FollowPath_FeedbackMessage__init(urc_msgs__action__FollowPath_FeedbackMessage * msg);

/// Finalize action/FollowPath message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_urc_msgs
void
urc_msgs__action__FollowPath_FeedbackMessage__fini(urc_msgs__action__FollowPath_FeedbackMessage * msg);

/// Create action/FollowPath message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * urc_msgs__action__FollowPath_FeedbackMessage__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_urc_msgs
urc_msgs__action__FollowPath_FeedbackMessage *
urc_msgs__action__FollowPath_FeedbackMessage__create();

/// Destroy action/FollowPath message.
/**
 * It calls
 * urc_msgs__action__FollowPath_FeedbackMessage__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_urc_msgs
void
urc_msgs__action__FollowPath_FeedbackMessage__destroy(urc_msgs__action__FollowPath_FeedbackMessage * msg);

/// Check for action/FollowPath message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_urc_msgs
bool
urc_msgs__action__FollowPath_FeedbackMessage__are_equal(const urc_msgs__action__FollowPath_FeedbackMessage * lhs, const urc_msgs__action__FollowPath_FeedbackMessage * rhs);

/// Copy a action/FollowPath message.
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
urc_msgs__action__FollowPath_FeedbackMessage__copy(
  const urc_msgs__action__FollowPath_FeedbackMessage * input,
  urc_msgs__action__FollowPath_FeedbackMessage * output);

/// Initialize array of action/FollowPath messages.
/**
 * It allocates the memory for the number of elements and calls
 * urc_msgs__action__FollowPath_FeedbackMessage__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_urc_msgs
bool
urc_msgs__action__FollowPath_FeedbackMessage__Sequence__init(urc_msgs__action__FollowPath_FeedbackMessage__Sequence * array, size_t size);

/// Finalize array of action/FollowPath messages.
/**
 * It calls
 * urc_msgs__action__FollowPath_FeedbackMessage__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_urc_msgs
void
urc_msgs__action__FollowPath_FeedbackMessage__Sequence__fini(urc_msgs__action__FollowPath_FeedbackMessage__Sequence * array);

/// Create array of action/FollowPath messages.
/**
 * It allocates the memory for the array and calls
 * urc_msgs__action__FollowPath_FeedbackMessage__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_urc_msgs
urc_msgs__action__FollowPath_FeedbackMessage__Sequence *
urc_msgs__action__FollowPath_FeedbackMessage__Sequence__create(size_t size);

/// Destroy array of action/FollowPath messages.
/**
 * It calls
 * urc_msgs__action__FollowPath_FeedbackMessage__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_urc_msgs
void
urc_msgs__action__FollowPath_FeedbackMessage__Sequence__destroy(urc_msgs__action__FollowPath_FeedbackMessage__Sequence * array);

/// Check for action/FollowPath message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_urc_msgs
bool
urc_msgs__action__FollowPath_FeedbackMessage__Sequence__are_equal(const urc_msgs__action__FollowPath_FeedbackMessage__Sequence * lhs, const urc_msgs__action__FollowPath_FeedbackMessage__Sequence * rhs);

/// Copy an array of action/FollowPath messages.
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
urc_msgs__action__FollowPath_FeedbackMessage__Sequence__copy(
  const urc_msgs__action__FollowPath_FeedbackMessage__Sequence * input,
  urc_msgs__action__FollowPath_FeedbackMessage__Sequence * output);

#ifdef __cplusplus
}
#endif

#endif  // URC_MSGS__ACTION__DETAIL__FOLLOW_PATH__FUNCTIONS_H_
