// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from urc_msgs:srv/UpdateBehaviorTree.idl
// generated code does not contain a copyright notice
#include "urc_msgs/srv/detail/update_behavior_tree__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"

// Include directives for member types
// Member `tree_content`
// Member `tree_dir`
#include "rosidl_runtime_c/string_functions.h"

bool
urc_msgs__srv__UpdateBehaviorTree_Request__init(urc_msgs__srv__UpdateBehaviorTree_Request * msg)
{
  if (!msg) {
    return false;
  }
  // tree_content
  if (!rosidl_runtime_c__String__init(&msg->tree_content)) {
    urc_msgs__srv__UpdateBehaviorTree_Request__fini(msg);
    return false;
  }
  // tree_dir
  if (!rosidl_runtime_c__String__init(&msg->tree_dir)) {
    urc_msgs__srv__UpdateBehaviorTree_Request__fini(msg);
    return false;
  }
  // use_dir
  return true;
}

void
urc_msgs__srv__UpdateBehaviorTree_Request__fini(urc_msgs__srv__UpdateBehaviorTree_Request * msg)
{
  if (!msg) {
    return;
  }
  // tree_content
  rosidl_runtime_c__String__fini(&msg->tree_content);
  // tree_dir
  rosidl_runtime_c__String__fini(&msg->tree_dir);
  // use_dir
}

bool
urc_msgs__srv__UpdateBehaviorTree_Request__are_equal(const urc_msgs__srv__UpdateBehaviorTree_Request * lhs, const urc_msgs__srv__UpdateBehaviorTree_Request * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // tree_content
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->tree_content), &(rhs->tree_content)))
  {
    return false;
  }
  // tree_dir
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->tree_dir), &(rhs->tree_dir)))
  {
    return false;
  }
  // use_dir
  if (lhs->use_dir != rhs->use_dir) {
    return false;
  }
  return true;
}

bool
urc_msgs__srv__UpdateBehaviorTree_Request__copy(
  const urc_msgs__srv__UpdateBehaviorTree_Request * input,
  urc_msgs__srv__UpdateBehaviorTree_Request * output)
{
  if (!input || !output) {
    return false;
  }
  // tree_content
  if (!rosidl_runtime_c__String__copy(
      &(input->tree_content), &(output->tree_content)))
  {
    return false;
  }
  // tree_dir
  if (!rosidl_runtime_c__String__copy(
      &(input->tree_dir), &(output->tree_dir)))
  {
    return false;
  }
  // use_dir
  output->use_dir = input->use_dir;
  return true;
}

urc_msgs__srv__UpdateBehaviorTree_Request *
urc_msgs__srv__UpdateBehaviorTree_Request__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  urc_msgs__srv__UpdateBehaviorTree_Request * msg = (urc_msgs__srv__UpdateBehaviorTree_Request *)allocator.allocate(sizeof(urc_msgs__srv__UpdateBehaviorTree_Request), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(urc_msgs__srv__UpdateBehaviorTree_Request));
  bool success = urc_msgs__srv__UpdateBehaviorTree_Request__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
urc_msgs__srv__UpdateBehaviorTree_Request__destroy(urc_msgs__srv__UpdateBehaviorTree_Request * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    urc_msgs__srv__UpdateBehaviorTree_Request__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
urc_msgs__srv__UpdateBehaviorTree_Request__Sequence__init(urc_msgs__srv__UpdateBehaviorTree_Request__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  urc_msgs__srv__UpdateBehaviorTree_Request * data = NULL;

  if (size) {
    data = (urc_msgs__srv__UpdateBehaviorTree_Request *)allocator.zero_allocate(size, sizeof(urc_msgs__srv__UpdateBehaviorTree_Request), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = urc_msgs__srv__UpdateBehaviorTree_Request__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        urc_msgs__srv__UpdateBehaviorTree_Request__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
urc_msgs__srv__UpdateBehaviorTree_Request__Sequence__fini(urc_msgs__srv__UpdateBehaviorTree_Request__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      urc_msgs__srv__UpdateBehaviorTree_Request__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

urc_msgs__srv__UpdateBehaviorTree_Request__Sequence *
urc_msgs__srv__UpdateBehaviorTree_Request__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  urc_msgs__srv__UpdateBehaviorTree_Request__Sequence * array = (urc_msgs__srv__UpdateBehaviorTree_Request__Sequence *)allocator.allocate(sizeof(urc_msgs__srv__UpdateBehaviorTree_Request__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = urc_msgs__srv__UpdateBehaviorTree_Request__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
urc_msgs__srv__UpdateBehaviorTree_Request__Sequence__destroy(urc_msgs__srv__UpdateBehaviorTree_Request__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    urc_msgs__srv__UpdateBehaviorTree_Request__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
urc_msgs__srv__UpdateBehaviorTree_Request__Sequence__are_equal(const urc_msgs__srv__UpdateBehaviorTree_Request__Sequence * lhs, const urc_msgs__srv__UpdateBehaviorTree_Request__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!urc_msgs__srv__UpdateBehaviorTree_Request__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
urc_msgs__srv__UpdateBehaviorTree_Request__Sequence__copy(
  const urc_msgs__srv__UpdateBehaviorTree_Request__Sequence * input,
  urc_msgs__srv__UpdateBehaviorTree_Request__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(urc_msgs__srv__UpdateBehaviorTree_Request);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    urc_msgs__srv__UpdateBehaviorTree_Request * data =
      (urc_msgs__srv__UpdateBehaviorTree_Request *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!urc_msgs__srv__UpdateBehaviorTree_Request__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          urc_msgs__srv__UpdateBehaviorTree_Request__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!urc_msgs__srv__UpdateBehaviorTree_Request__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


bool
urc_msgs__srv__UpdateBehaviorTree_Response__init(urc_msgs__srv__UpdateBehaviorTree_Response * msg)
{
  if (!msg) {
    return false;
  }
  // success
  return true;
}

void
urc_msgs__srv__UpdateBehaviorTree_Response__fini(urc_msgs__srv__UpdateBehaviorTree_Response * msg)
{
  if (!msg) {
    return;
  }
  // success
}

bool
urc_msgs__srv__UpdateBehaviorTree_Response__are_equal(const urc_msgs__srv__UpdateBehaviorTree_Response * lhs, const urc_msgs__srv__UpdateBehaviorTree_Response * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // success
  if (lhs->success != rhs->success) {
    return false;
  }
  return true;
}

bool
urc_msgs__srv__UpdateBehaviorTree_Response__copy(
  const urc_msgs__srv__UpdateBehaviorTree_Response * input,
  urc_msgs__srv__UpdateBehaviorTree_Response * output)
{
  if (!input || !output) {
    return false;
  }
  // success
  output->success = input->success;
  return true;
}

urc_msgs__srv__UpdateBehaviorTree_Response *
urc_msgs__srv__UpdateBehaviorTree_Response__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  urc_msgs__srv__UpdateBehaviorTree_Response * msg = (urc_msgs__srv__UpdateBehaviorTree_Response *)allocator.allocate(sizeof(urc_msgs__srv__UpdateBehaviorTree_Response), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(urc_msgs__srv__UpdateBehaviorTree_Response));
  bool success = urc_msgs__srv__UpdateBehaviorTree_Response__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
urc_msgs__srv__UpdateBehaviorTree_Response__destroy(urc_msgs__srv__UpdateBehaviorTree_Response * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    urc_msgs__srv__UpdateBehaviorTree_Response__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
urc_msgs__srv__UpdateBehaviorTree_Response__Sequence__init(urc_msgs__srv__UpdateBehaviorTree_Response__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  urc_msgs__srv__UpdateBehaviorTree_Response * data = NULL;

  if (size) {
    data = (urc_msgs__srv__UpdateBehaviorTree_Response *)allocator.zero_allocate(size, sizeof(urc_msgs__srv__UpdateBehaviorTree_Response), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = urc_msgs__srv__UpdateBehaviorTree_Response__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        urc_msgs__srv__UpdateBehaviorTree_Response__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
urc_msgs__srv__UpdateBehaviorTree_Response__Sequence__fini(urc_msgs__srv__UpdateBehaviorTree_Response__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      urc_msgs__srv__UpdateBehaviorTree_Response__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

urc_msgs__srv__UpdateBehaviorTree_Response__Sequence *
urc_msgs__srv__UpdateBehaviorTree_Response__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  urc_msgs__srv__UpdateBehaviorTree_Response__Sequence * array = (urc_msgs__srv__UpdateBehaviorTree_Response__Sequence *)allocator.allocate(sizeof(urc_msgs__srv__UpdateBehaviorTree_Response__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = urc_msgs__srv__UpdateBehaviorTree_Response__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
urc_msgs__srv__UpdateBehaviorTree_Response__Sequence__destroy(urc_msgs__srv__UpdateBehaviorTree_Response__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    urc_msgs__srv__UpdateBehaviorTree_Response__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
urc_msgs__srv__UpdateBehaviorTree_Response__Sequence__are_equal(const urc_msgs__srv__UpdateBehaviorTree_Response__Sequence * lhs, const urc_msgs__srv__UpdateBehaviorTree_Response__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!urc_msgs__srv__UpdateBehaviorTree_Response__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
urc_msgs__srv__UpdateBehaviorTree_Response__Sequence__copy(
  const urc_msgs__srv__UpdateBehaviorTree_Response__Sequence * input,
  urc_msgs__srv__UpdateBehaviorTree_Response__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(urc_msgs__srv__UpdateBehaviorTree_Response);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    urc_msgs__srv__UpdateBehaviorTree_Response * data =
      (urc_msgs__srv__UpdateBehaviorTree_Response *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!urc_msgs__srv__UpdateBehaviorTree_Response__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          urc_msgs__srv__UpdateBehaviorTree_Response__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!urc_msgs__srv__UpdateBehaviorTree_Response__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
