// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from urc_msgs:srv/GenerateSpiralSearch.idl
// generated code does not contain a copyright notice

#ifndef URC_MSGS__SRV__DETAIL__GENERATE_SPIRAL_SEARCH__FUNCTIONS_H_
#define URC_MSGS__SRV__DETAIL__GENERATE_SPIRAL_SEARCH__FUNCTIONS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdlib.h>

#include "rosidl_runtime_c/visibility_control.h"
#include "urc_msgs/msg/rosidl_generator_c__visibility_control.h"

#include "urc_msgs/srv/detail/generate_spiral_search__struct.h"

/// Initialize srv/GenerateSpiralSearch message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * urc_msgs__srv__GenerateSpiralSearch_Request
 * )) before or use
 * urc_msgs__srv__GenerateSpiralSearch_Request__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_urc_msgs
bool
urc_msgs__srv__GenerateSpiralSearch_Request__init(urc_msgs__srv__GenerateSpiralSearch_Request * msg);

/// Finalize srv/GenerateSpiralSearch message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_urc_msgs
void
urc_msgs__srv__GenerateSpiralSearch_Request__fini(urc_msgs__srv__GenerateSpiralSearch_Request * msg);

/// Create srv/GenerateSpiralSearch message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * urc_msgs__srv__GenerateSpiralSearch_Request__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_urc_msgs
urc_msgs__srv__GenerateSpiralSearch_Request *
urc_msgs__srv__GenerateSpiralSearch_Request__create();

/// Destroy srv/GenerateSpiralSearch message.
/**
 * It calls
 * urc_msgs__srv__GenerateSpiralSearch_Request__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_urc_msgs
void
urc_msgs__srv__GenerateSpiralSearch_Request__destroy(urc_msgs__srv__GenerateSpiralSearch_Request * msg);

/// Check for srv/GenerateSpiralSearch message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_urc_msgs
bool
urc_msgs__srv__GenerateSpiralSearch_Request__are_equal(const urc_msgs__srv__GenerateSpiralSearch_Request * lhs, const urc_msgs__srv__GenerateSpiralSearch_Request * rhs);

/// Copy a srv/GenerateSpiralSearch message.
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
urc_msgs__srv__GenerateSpiralSearch_Request__copy(
  const urc_msgs__srv__GenerateSpiralSearch_Request * input,
  urc_msgs__srv__GenerateSpiralSearch_Request * output);

/// Initialize array of srv/GenerateSpiralSearch messages.
/**
 * It allocates the memory for the number of elements and calls
 * urc_msgs__srv__GenerateSpiralSearch_Request__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_urc_msgs
bool
urc_msgs__srv__GenerateSpiralSearch_Request__Sequence__init(urc_msgs__srv__GenerateSpiralSearch_Request__Sequence * array, size_t size);

/// Finalize array of srv/GenerateSpiralSearch messages.
/**
 * It calls
 * urc_msgs__srv__GenerateSpiralSearch_Request__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_urc_msgs
void
urc_msgs__srv__GenerateSpiralSearch_Request__Sequence__fini(urc_msgs__srv__GenerateSpiralSearch_Request__Sequence * array);

/// Create array of srv/GenerateSpiralSearch messages.
/**
 * It allocates the memory for the array and calls
 * urc_msgs__srv__GenerateSpiralSearch_Request__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_urc_msgs
urc_msgs__srv__GenerateSpiralSearch_Request__Sequence *
urc_msgs__srv__GenerateSpiralSearch_Request__Sequence__create(size_t size);

/// Destroy array of srv/GenerateSpiralSearch messages.
/**
 * It calls
 * urc_msgs__srv__GenerateSpiralSearch_Request__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_urc_msgs
void
urc_msgs__srv__GenerateSpiralSearch_Request__Sequence__destroy(urc_msgs__srv__GenerateSpiralSearch_Request__Sequence * array);

/// Check for srv/GenerateSpiralSearch message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_urc_msgs
bool
urc_msgs__srv__GenerateSpiralSearch_Request__Sequence__are_equal(const urc_msgs__srv__GenerateSpiralSearch_Request__Sequence * lhs, const urc_msgs__srv__GenerateSpiralSearch_Request__Sequence * rhs);

/// Copy an array of srv/GenerateSpiralSearch messages.
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
urc_msgs__srv__GenerateSpiralSearch_Request__Sequence__copy(
  const urc_msgs__srv__GenerateSpiralSearch_Request__Sequence * input,
  urc_msgs__srv__GenerateSpiralSearch_Request__Sequence * output);

/// Initialize srv/GenerateSpiralSearch message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * urc_msgs__srv__GenerateSpiralSearch_Response
 * )) before or use
 * urc_msgs__srv__GenerateSpiralSearch_Response__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_urc_msgs
bool
urc_msgs__srv__GenerateSpiralSearch_Response__init(urc_msgs__srv__GenerateSpiralSearch_Response * msg);

/// Finalize srv/GenerateSpiralSearch message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_urc_msgs
void
urc_msgs__srv__GenerateSpiralSearch_Response__fini(urc_msgs__srv__GenerateSpiralSearch_Response * msg);

/// Create srv/GenerateSpiralSearch message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * urc_msgs__srv__GenerateSpiralSearch_Response__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_urc_msgs
urc_msgs__srv__GenerateSpiralSearch_Response *
urc_msgs__srv__GenerateSpiralSearch_Response__create();

/// Destroy srv/GenerateSpiralSearch message.
/**
 * It calls
 * urc_msgs__srv__GenerateSpiralSearch_Response__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_urc_msgs
void
urc_msgs__srv__GenerateSpiralSearch_Response__destroy(urc_msgs__srv__GenerateSpiralSearch_Response * msg);

/// Check for srv/GenerateSpiralSearch message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_urc_msgs
bool
urc_msgs__srv__GenerateSpiralSearch_Response__are_equal(const urc_msgs__srv__GenerateSpiralSearch_Response * lhs, const urc_msgs__srv__GenerateSpiralSearch_Response * rhs);

/// Copy a srv/GenerateSpiralSearch message.
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
urc_msgs__srv__GenerateSpiralSearch_Response__copy(
  const urc_msgs__srv__GenerateSpiralSearch_Response * input,
  urc_msgs__srv__GenerateSpiralSearch_Response * output);

/// Initialize array of srv/GenerateSpiralSearch messages.
/**
 * It allocates the memory for the number of elements and calls
 * urc_msgs__srv__GenerateSpiralSearch_Response__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_urc_msgs
bool
urc_msgs__srv__GenerateSpiralSearch_Response__Sequence__init(urc_msgs__srv__GenerateSpiralSearch_Response__Sequence * array, size_t size);

/// Finalize array of srv/GenerateSpiralSearch messages.
/**
 * It calls
 * urc_msgs__srv__GenerateSpiralSearch_Response__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_urc_msgs
void
urc_msgs__srv__GenerateSpiralSearch_Response__Sequence__fini(urc_msgs__srv__GenerateSpiralSearch_Response__Sequence * array);

/// Create array of srv/GenerateSpiralSearch messages.
/**
 * It allocates the memory for the array and calls
 * urc_msgs__srv__GenerateSpiralSearch_Response__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_urc_msgs
urc_msgs__srv__GenerateSpiralSearch_Response__Sequence *
urc_msgs__srv__GenerateSpiralSearch_Response__Sequence__create(size_t size);

/// Destroy array of srv/GenerateSpiralSearch messages.
/**
 * It calls
 * urc_msgs__srv__GenerateSpiralSearch_Response__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_urc_msgs
void
urc_msgs__srv__GenerateSpiralSearch_Response__Sequence__destroy(urc_msgs__srv__GenerateSpiralSearch_Response__Sequence * array);

/// Check for srv/GenerateSpiralSearch message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_urc_msgs
bool
urc_msgs__srv__GenerateSpiralSearch_Response__Sequence__are_equal(const urc_msgs__srv__GenerateSpiralSearch_Response__Sequence * lhs, const urc_msgs__srv__GenerateSpiralSearch_Response__Sequence * rhs);

/// Copy an array of srv/GenerateSpiralSearch messages.
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
urc_msgs__srv__GenerateSpiralSearch_Response__Sequence__copy(
  const urc_msgs__srv__GenerateSpiralSearch_Response__Sequence * input,
  urc_msgs__srv__GenerateSpiralSearch_Response__Sequence * output);

#ifdef __cplusplus
}
#endif

#endif  // URC_MSGS__SRV__DETAIL__GENERATE_SPIRAL_SEARCH__FUNCTIONS_H_
