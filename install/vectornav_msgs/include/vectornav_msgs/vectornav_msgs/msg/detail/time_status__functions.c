// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from vectornav_msgs:msg/TimeStatus.idl
// generated code does not contain a copyright notice
#include "vectornav_msgs/msg/detail/time_status__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


bool
vectornav_msgs__msg__TimeStatus__init(vectornav_msgs__msg__TimeStatus * msg)
{
  if (!msg) {
    return false;
  }
  // time_ok
  // date_ok
  // utctime_ok
  return true;
}

void
vectornav_msgs__msg__TimeStatus__fini(vectornav_msgs__msg__TimeStatus * msg)
{
  if (!msg) {
    return;
  }
  // time_ok
  // date_ok
  // utctime_ok
}

bool
vectornav_msgs__msg__TimeStatus__are_equal(const vectornav_msgs__msg__TimeStatus * lhs, const vectornav_msgs__msg__TimeStatus * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // time_ok
  if (lhs->time_ok != rhs->time_ok) {
    return false;
  }
  // date_ok
  if (lhs->date_ok != rhs->date_ok) {
    return false;
  }
  // utctime_ok
  if (lhs->utctime_ok != rhs->utctime_ok) {
    return false;
  }
  return true;
}

bool
vectornav_msgs__msg__TimeStatus__copy(
  const vectornav_msgs__msg__TimeStatus * input,
  vectornav_msgs__msg__TimeStatus * output)
{
  if (!input || !output) {
    return false;
  }
  // time_ok
  output->time_ok = input->time_ok;
  // date_ok
  output->date_ok = input->date_ok;
  // utctime_ok
  output->utctime_ok = input->utctime_ok;
  return true;
}

vectornav_msgs__msg__TimeStatus *
vectornav_msgs__msg__TimeStatus__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  vectornav_msgs__msg__TimeStatus * msg = (vectornav_msgs__msg__TimeStatus *)allocator.allocate(sizeof(vectornav_msgs__msg__TimeStatus), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(vectornav_msgs__msg__TimeStatus));
  bool success = vectornav_msgs__msg__TimeStatus__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
vectornav_msgs__msg__TimeStatus__destroy(vectornav_msgs__msg__TimeStatus * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    vectornav_msgs__msg__TimeStatus__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
vectornav_msgs__msg__TimeStatus__Sequence__init(vectornav_msgs__msg__TimeStatus__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  vectornav_msgs__msg__TimeStatus * data = NULL;

  if (size) {
    data = (vectornav_msgs__msg__TimeStatus *)allocator.zero_allocate(size, sizeof(vectornav_msgs__msg__TimeStatus), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = vectornav_msgs__msg__TimeStatus__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        vectornav_msgs__msg__TimeStatus__fini(&data[i - 1]);
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
vectornav_msgs__msg__TimeStatus__Sequence__fini(vectornav_msgs__msg__TimeStatus__Sequence * array)
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
      vectornav_msgs__msg__TimeStatus__fini(&array->data[i]);
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

vectornav_msgs__msg__TimeStatus__Sequence *
vectornav_msgs__msg__TimeStatus__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  vectornav_msgs__msg__TimeStatus__Sequence * array = (vectornav_msgs__msg__TimeStatus__Sequence *)allocator.allocate(sizeof(vectornav_msgs__msg__TimeStatus__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = vectornav_msgs__msg__TimeStatus__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
vectornav_msgs__msg__TimeStatus__Sequence__destroy(vectornav_msgs__msg__TimeStatus__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    vectornav_msgs__msg__TimeStatus__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
vectornav_msgs__msg__TimeStatus__Sequence__are_equal(const vectornav_msgs__msg__TimeStatus__Sequence * lhs, const vectornav_msgs__msg__TimeStatus__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!vectornav_msgs__msg__TimeStatus__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
vectornav_msgs__msg__TimeStatus__Sequence__copy(
  const vectornav_msgs__msg__TimeStatus__Sequence * input,
  vectornav_msgs__msg__TimeStatus__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(vectornav_msgs__msg__TimeStatus);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    vectornav_msgs__msg__TimeStatus * data =
      (vectornav_msgs__msg__TimeStatus *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!vectornav_msgs__msg__TimeStatus__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          vectornav_msgs__msg__TimeStatus__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!vectornav_msgs__msg__TimeStatus__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
