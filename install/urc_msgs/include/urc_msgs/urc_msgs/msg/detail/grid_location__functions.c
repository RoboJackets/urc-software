// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from urc_msgs:msg/GridLocation.idl
// generated code does not contain a copyright notice
#include "urc_msgs/msg/detail/grid_location__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


bool
urc_msgs__msg__GridLocation__init(urc_msgs__msg__GridLocation * msg)
{
  if (!msg) {
    return false;
  }
  // x
  // y
  return true;
}

void
urc_msgs__msg__GridLocation__fini(urc_msgs__msg__GridLocation * msg)
{
  if (!msg) {
    return;
  }
  // x
  // y
}

bool
urc_msgs__msg__GridLocation__are_equal(const urc_msgs__msg__GridLocation * lhs, const urc_msgs__msg__GridLocation * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // x
  if (lhs->x != rhs->x) {
    return false;
  }
  // y
  if (lhs->y != rhs->y) {
    return false;
  }
  return true;
}

bool
urc_msgs__msg__GridLocation__copy(
  const urc_msgs__msg__GridLocation * input,
  urc_msgs__msg__GridLocation * output)
{
  if (!input || !output) {
    return false;
  }
  // x
  output->x = input->x;
  // y
  output->y = input->y;
  return true;
}

urc_msgs__msg__GridLocation *
urc_msgs__msg__GridLocation__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  urc_msgs__msg__GridLocation * msg = (urc_msgs__msg__GridLocation *)allocator.allocate(sizeof(urc_msgs__msg__GridLocation), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(urc_msgs__msg__GridLocation));
  bool success = urc_msgs__msg__GridLocation__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
urc_msgs__msg__GridLocation__destroy(urc_msgs__msg__GridLocation * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    urc_msgs__msg__GridLocation__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
urc_msgs__msg__GridLocation__Sequence__init(urc_msgs__msg__GridLocation__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  urc_msgs__msg__GridLocation * data = NULL;

  if (size) {
    data = (urc_msgs__msg__GridLocation *)allocator.zero_allocate(size, sizeof(urc_msgs__msg__GridLocation), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = urc_msgs__msg__GridLocation__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        urc_msgs__msg__GridLocation__fini(&data[i - 1]);
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
urc_msgs__msg__GridLocation__Sequence__fini(urc_msgs__msg__GridLocation__Sequence * array)
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
      urc_msgs__msg__GridLocation__fini(&array->data[i]);
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

urc_msgs__msg__GridLocation__Sequence *
urc_msgs__msg__GridLocation__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  urc_msgs__msg__GridLocation__Sequence * array = (urc_msgs__msg__GridLocation__Sequence *)allocator.allocate(sizeof(urc_msgs__msg__GridLocation__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = urc_msgs__msg__GridLocation__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
urc_msgs__msg__GridLocation__Sequence__destroy(urc_msgs__msg__GridLocation__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    urc_msgs__msg__GridLocation__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
urc_msgs__msg__GridLocation__Sequence__are_equal(const urc_msgs__msg__GridLocation__Sequence * lhs, const urc_msgs__msg__GridLocation__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!urc_msgs__msg__GridLocation__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
urc_msgs__msg__GridLocation__Sequence__copy(
  const urc_msgs__msg__GridLocation__Sequence * input,
  urc_msgs__msg__GridLocation__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(urc_msgs__msg__GridLocation);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    urc_msgs__msg__GridLocation * data =
      (urc_msgs__msg__GridLocation *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!urc_msgs__msg__GridLocation__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          urc_msgs__msg__GridLocation__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!urc_msgs__msg__GridLocation__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
