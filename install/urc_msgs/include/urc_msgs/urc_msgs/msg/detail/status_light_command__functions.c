// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from urc_msgs:msg/StatusLightCommand.idl
// generated code does not contain a copyright notice
#include "urc_msgs/msg/detail/status_light_command__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


bool
urc_msgs__msg__StatusLightCommand__init(urc_msgs__msg__StatusLightCommand * msg)
{
  if (!msg) {
    return false;
  }
  // color
  // state
  return true;
}

void
urc_msgs__msg__StatusLightCommand__fini(urc_msgs__msg__StatusLightCommand * msg)
{
  if (!msg) {
    return;
  }
  // color
  // state
}

bool
urc_msgs__msg__StatusLightCommand__are_equal(const urc_msgs__msg__StatusLightCommand * lhs, const urc_msgs__msg__StatusLightCommand * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // color
  if (lhs->color != rhs->color) {
    return false;
  }
  // state
  if (lhs->state != rhs->state) {
    return false;
  }
  return true;
}

bool
urc_msgs__msg__StatusLightCommand__copy(
  const urc_msgs__msg__StatusLightCommand * input,
  urc_msgs__msg__StatusLightCommand * output)
{
  if (!input || !output) {
    return false;
  }
  // color
  output->color = input->color;
  // state
  output->state = input->state;
  return true;
}

urc_msgs__msg__StatusLightCommand *
urc_msgs__msg__StatusLightCommand__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  urc_msgs__msg__StatusLightCommand * msg = (urc_msgs__msg__StatusLightCommand *)allocator.allocate(sizeof(urc_msgs__msg__StatusLightCommand), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(urc_msgs__msg__StatusLightCommand));
  bool success = urc_msgs__msg__StatusLightCommand__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
urc_msgs__msg__StatusLightCommand__destroy(urc_msgs__msg__StatusLightCommand * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    urc_msgs__msg__StatusLightCommand__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
urc_msgs__msg__StatusLightCommand__Sequence__init(urc_msgs__msg__StatusLightCommand__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  urc_msgs__msg__StatusLightCommand * data = NULL;

  if (size) {
    data = (urc_msgs__msg__StatusLightCommand *)allocator.zero_allocate(size, sizeof(urc_msgs__msg__StatusLightCommand), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = urc_msgs__msg__StatusLightCommand__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        urc_msgs__msg__StatusLightCommand__fini(&data[i - 1]);
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
urc_msgs__msg__StatusLightCommand__Sequence__fini(urc_msgs__msg__StatusLightCommand__Sequence * array)
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
      urc_msgs__msg__StatusLightCommand__fini(&array->data[i]);
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

urc_msgs__msg__StatusLightCommand__Sequence *
urc_msgs__msg__StatusLightCommand__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  urc_msgs__msg__StatusLightCommand__Sequence * array = (urc_msgs__msg__StatusLightCommand__Sequence *)allocator.allocate(sizeof(urc_msgs__msg__StatusLightCommand__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = urc_msgs__msg__StatusLightCommand__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
urc_msgs__msg__StatusLightCommand__Sequence__destroy(urc_msgs__msg__StatusLightCommand__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    urc_msgs__msg__StatusLightCommand__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
urc_msgs__msg__StatusLightCommand__Sequence__are_equal(const urc_msgs__msg__StatusLightCommand__Sequence * lhs, const urc_msgs__msg__StatusLightCommand__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!urc_msgs__msg__StatusLightCommand__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
urc_msgs__msg__StatusLightCommand__Sequence__copy(
  const urc_msgs__msg__StatusLightCommand__Sequence * input,
  urc_msgs__msg__StatusLightCommand__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(urc_msgs__msg__StatusLightCommand);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    urc_msgs__msg__StatusLightCommand * data =
      (urc_msgs__msg__StatusLightCommand *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!urc_msgs__msg__StatusLightCommand__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          urc_msgs__msg__StatusLightCommand__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!urc_msgs__msg__StatusLightCommand__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
