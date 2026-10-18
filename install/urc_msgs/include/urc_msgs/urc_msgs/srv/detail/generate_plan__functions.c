// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from urc_msgs:srv/GeneratePlan.idl
// generated code does not contain a copyright notice
#include "urc_msgs/srv/detail/generate_plan__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"

// Include directives for member types
// Member `goal`
// Member `start`
#include "geometry_msgs/msg/detail/pose_stamped__functions.h"

bool
urc_msgs__srv__GeneratePlan_Request__init(urc_msgs__srv__GeneratePlan_Request * msg)
{
  if (!msg) {
    return false;
  }
  // goal
  if (!geometry_msgs__msg__PoseStamped__init(&msg->goal)) {
    urc_msgs__srv__GeneratePlan_Request__fini(msg);
    return false;
  }
  // start
  if (!geometry_msgs__msg__PoseStamped__init(&msg->start)) {
    urc_msgs__srv__GeneratePlan_Request__fini(msg);
    return false;
  }
  return true;
}

void
urc_msgs__srv__GeneratePlan_Request__fini(urc_msgs__srv__GeneratePlan_Request * msg)
{
  if (!msg) {
    return;
  }
  // goal
  geometry_msgs__msg__PoseStamped__fini(&msg->goal);
  // start
  geometry_msgs__msg__PoseStamped__fini(&msg->start);
}

bool
urc_msgs__srv__GeneratePlan_Request__are_equal(const urc_msgs__srv__GeneratePlan_Request * lhs, const urc_msgs__srv__GeneratePlan_Request * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // goal
  if (!geometry_msgs__msg__PoseStamped__are_equal(
      &(lhs->goal), &(rhs->goal)))
  {
    return false;
  }
  // start
  if (!geometry_msgs__msg__PoseStamped__are_equal(
      &(lhs->start), &(rhs->start)))
  {
    return false;
  }
  return true;
}

bool
urc_msgs__srv__GeneratePlan_Request__copy(
  const urc_msgs__srv__GeneratePlan_Request * input,
  urc_msgs__srv__GeneratePlan_Request * output)
{
  if (!input || !output) {
    return false;
  }
  // goal
  if (!geometry_msgs__msg__PoseStamped__copy(
      &(input->goal), &(output->goal)))
  {
    return false;
  }
  // start
  if (!geometry_msgs__msg__PoseStamped__copy(
      &(input->start), &(output->start)))
  {
    return false;
  }
  return true;
}

urc_msgs__srv__GeneratePlan_Request *
urc_msgs__srv__GeneratePlan_Request__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  urc_msgs__srv__GeneratePlan_Request * msg = (urc_msgs__srv__GeneratePlan_Request *)allocator.allocate(sizeof(urc_msgs__srv__GeneratePlan_Request), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(urc_msgs__srv__GeneratePlan_Request));
  bool success = urc_msgs__srv__GeneratePlan_Request__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
urc_msgs__srv__GeneratePlan_Request__destroy(urc_msgs__srv__GeneratePlan_Request * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    urc_msgs__srv__GeneratePlan_Request__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
urc_msgs__srv__GeneratePlan_Request__Sequence__init(urc_msgs__srv__GeneratePlan_Request__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  urc_msgs__srv__GeneratePlan_Request * data = NULL;

  if (size) {
    data = (urc_msgs__srv__GeneratePlan_Request *)allocator.zero_allocate(size, sizeof(urc_msgs__srv__GeneratePlan_Request), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = urc_msgs__srv__GeneratePlan_Request__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        urc_msgs__srv__GeneratePlan_Request__fini(&data[i - 1]);
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
urc_msgs__srv__GeneratePlan_Request__Sequence__fini(urc_msgs__srv__GeneratePlan_Request__Sequence * array)
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
      urc_msgs__srv__GeneratePlan_Request__fini(&array->data[i]);
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

urc_msgs__srv__GeneratePlan_Request__Sequence *
urc_msgs__srv__GeneratePlan_Request__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  urc_msgs__srv__GeneratePlan_Request__Sequence * array = (urc_msgs__srv__GeneratePlan_Request__Sequence *)allocator.allocate(sizeof(urc_msgs__srv__GeneratePlan_Request__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = urc_msgs__srv__GeneratePlan_Request__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
urc_msgs__srv__GeneratePlan_Request__Sequence__destroy(urc_msgs__srv__GeneratePlan_Request__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    urc_msgs__srv__GeneratePlan_Request__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
urc_msgs__srv__GeneratePlan_Request__Sequence__are_equal(const urc_msgs__srv__GeneratePlan_Request__Sequence * lhs, const urc_msgs__srv__GeneratePlan_Request__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!urc_msgs__srv__GeneratePlan_Request__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
urc_msgs__srv__GeneratePlan_Request__Sequence__copy(
  const urc_msgs__srv__GeneratePlan_Request__Sequence * input,
  urc_msgs__srv__GeneratePlan_Request__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(urc_msgs__srv__GeneratePlan_Request);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    urc_msgs__srv__GeneratePlan_Request * data =
      (urc_msgs__srv__GeneratePlan_Request *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!urc_msgs__srv__GeneratePlan_Request__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          urc_msgs__srv__GeneratePlan_Request__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!urc_msgs__srv__GeneratePlan_Request__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


// Include directives for member types
// Member `path`
#include "nav_msgs/msg/detail/path__functions.h"

bool
urc_msgs__srv__GeneratePlan_Response__init(urc_msgs__srv__GeneratePlan_Response * msg)
{
  if (!msg) {
    return false;
  }
  // path
  if (!nav_msgs__msg__Path__init(&msg->path)) {
    urc_msgs__srv__GeneratePlan_Response__fini(msg);
    return false;
  }
  // error_code
  return true;
}

void
urc_msgs__srv__GeneratePlan_Response__fini(urc_msgs__srv__GeneratePlan_Response * msg)
{
  if (!msg) {
    return;
  }
  // path
  nav_msgs__msg__Path__fini(&msg->path);
  // error_code
}

bool
urc_msgs__srv__GeneratePlan_Response__are_equal(const urc_msgs__srv__GeneratePlan_Response * lhs, const urc_msgs__srv__GeneratePlan_Response * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // path
  if (!nav_msgs__msg__Path__are_equal(
      &(lhs->path), &(rhs->path)))
  {
    return false;
  }
  // error_code
  if (lhs->error_code != rhs->error_code) {
    return false;
  }
  return true;
}

bool
urc_msgs__srv__GeneratePlan_Response__copy(
  const urc_msgs__srv__GeneratePlan_Response * input,
  urc_msgs__srv__GeneratePlan_Response * output)
{
  if (!input || !output) {
    return false;
  }
  // path
  if (!nav_msgs__msg__Path__copy(
      &(input->path), &(output->path)))
  {
    return false;
  }
  // error_code
  output->error_code = input->error_code;
  return true;
}

urc_msgs__srv__GeneratePlan_Response *
urc_msgs__srv__GeneratePlan_Response__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  urc_msgs__srv__GeneratePlan_Response * msg = (urc_msgs__srv__GeneratePlan_Response *)allocator.allocate(sizeof(urc_msgs__srv__GeneratePlan_Response), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(urc_msgs__srv__GeneratePlan_Response));
  bool success = urc_msgs__srv__GeneratePlan_Response__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
urc_msgs__srv__GeneratePlan_Response__destroy(urc_msgs__srv__GeneratePlan_Response * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    urc_msgs__srv__GeneratePlan_Response__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
urc_msgs__srv__GeneratePlan_Response__Sequence__init(urc_msgs__srv__GeneratePlan_Response__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  urc_msgs__srv__GeneratePlan_Response * data = NULL;

  if (size) {
    data = (urc_msgs__srv__GeneratePlan_Response *)allocator.zero_allocate(size, sizeof(urc_msgs__srv__GeneratePlan_Response), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = urc_msgs__srv__GeneratePlan_Response__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        urc_msgs__srv__GeneratePlan_Response__fini(&data[i - 1]);
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
urc_msgs__srv__GeneratePlan_Response__Sequence__fini(urc_msgs__srv__GeneratePlan_Response__Sequence * array)
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
      urc_msgs__srv__GeneratePlan_Response__fini(&array->data[i]);
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

urc_msgs__srv__GeneratePlan_Response__Sequence *
urc_msgs__srv__GeneratePlan_Response__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  urc_msgs__srv__GeneratePlan_Response__Sequence * array = (urc_msgs__srv__GeneratePlan_Response__Sequence *)allocator.allocate(sizeof(urc_msgs__srv__GeneratePlan_Response__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = urc_msgs__srv__GeneratePlan_Response__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
urc_msgs__srv__GeneratePlan_Response__Sequence__destroy(urc_msgs__srv__GeneratePlan_Response__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    urc_msgs__srv__GeneratePlan_Response__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
urc_msgs__srv__GeneratePlan_Response__Sequence__are_equal(const urc_msgs__srv__GeneratePlan_Response__Sequence * lhs, const urc_msgs__srv__GeneratePlan_Response__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!urc_msgs__srv__GeneratePlan_Response__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
urc_msgs__srv__GeneratePlan_Response__Sequence__copy(
  const urc_msgs__srv__GeneratePlan_Response__Sequence * input,
  urc_msgs__srv__GeneratePlan_Response__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(urc_msgs__srv__GeneratePlan_Response);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    urc_msgs__srv__GeneratePlan_Response * data =
      (urc_msgs__srv__GeneratePlan_Response *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!urc_msgs__srv__GeneratePlan_Response__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          urc_msgs__srv__GeneratePlan_Response__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!urc_msgs__srv__GeneratePlan_Response__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
