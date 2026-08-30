// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from vectornav_msgs:msg/TimeUTC.idl
// generated code does not contain a copyright notice
#include "vectornav_msgs/msg/detail/time_utc__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


bool
vectornav_msgs__msg__TimeUTC__init(vectornav_msgs__msg__TimeUTC * msg)
{
  if (!msg) {
    return false;
  }
  // year
  // month
  // day
  // hour
  // min
  // sec
  // ms
  return true;
}

void
vectornav_msgs__msg__TimeUTC__fini(vectornav_msgs__msg__TimeUTC * msg)
{
  if (!msg) {
    return;
  }
  // year
  // month
  // day
  // hour
  // min
  // sec
  // ms
}

bool
vectornav_msgs__msg__TimeUTC__are_equal(const vectornav_msgs__msg__TimeUTC * lhs, const vectornav_msgs__msg__TimeUTC * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // year
  if (lhs->year != rhs->year) {
    return false;
  }
  // month
  if (lhs->month != rhs->month) {
    return false;
  }
  // day
  if (lhs->day != rhs->day) {
    return false;
  }
  // hour
  if (lhs->hour != rhs->hour) {
    return false;
  }
  // min
  if (lhs->min != rhs->min) {
    return false;
  }
  // sec
  if (lhs->sec != rhs->sec) {
    return false;
  }
  // ms
  if (lhs->ms != rhs->ms) {
    return false;
  }
  return true;
}

bool
vectornav_msgs__msg__TimeUTC__copy(
  const vectornav_msgs__msg__TimeUTC * input,
  vectornav_msgs__msg__TimeUTC * output)
{
  if (!input || !output) {
    return false;
  }
  // year
  output->year = input->year;
  // month
  output->month = input->month;
  // day
  output->day = input->day;
  // hour
  output->hour = input->hour;
  // min
  output->min = input->min;
  // sec
  output->sec = input->sec;
  // ms
  output->ms = input->ms;
  return true;
}

vectornav_msgs__msg__TimeUTC *
vectornav_msgs__msg__TimeUTC__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  vectornav_msgs__msg__TimeUTC * msg = (vectornav_msgs__msg__TimeUTC *)allocator.allocate(sizeof(vectornav_msgs__msg__TimeUTC), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(vectornav_msgs__msg__TimeUTC));
  bool success = vectornav_msgs__msg__TimeUTC__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
vectornav_msgs__msg__TimeUTC__destroy(vectornav_msgs__msg__TimeUTC * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    vectornav_msgs__msg__TimeUTC__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
vectornav_msgs__msg__TimeUTC__Sequence__init(vectornav_msgs__msg__TimeUTC__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  vectornav_msgs__msg__TimeUTC * data = NULL;

  if (size) {
    data = (vectornav_msgs__msg__TimeUTC *)allocator.zero_allocate(size, sizeof(vectornav_msgs__msg__TimeUTC), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = vectornav_msgs__msg__TimeUTC__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        vectornav_msgs__msg__TimeUTC__fini(&data[i - 1]);
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
vectornav_msgs__msg__TimeUTC__Sequence__fini(vectornav_msgs__msg__TimeUTC__Sequence * array)
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
      vectornav_msgs__msg__TimeUTC__fini(&array->data[i]);
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

vectornav_msgs__msg__TimeUTC__Sequence *
vectornav_msgs__msg__TimeUTC__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  vectornav_msgs__msg__TimeUTC__Sequence * array = (vectornav_msgs__msg__TimeUTC__Sequence *)allocator.allocate(sizeof(vectornav_msgs__msg__TimeUTC__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = vectornav_msgs__msg__TimeUTC__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
vectornav_msgs__msg__TimeUTC__Sequence__destroy(vectornav_msgs__msg__TimeUTC__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    vectornav_msgs__msg__TimeUTC__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
vectornav_msgs__msg__TimeUTC__Sequence__are_equal(const vectornav_msgs__msg__TimeUTC__Sequence * lhs, const vectornav_msgs__msg__TimeUTC__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!vectornav_msgs__msg__TimeUTC__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
vectornav_msgs__msg__TimeUTC__Sequence__copy(
  const vectornav_msgs__msg__TimeUTC__Sequence * input,
  vectornav_msgs__msg__TimeUTC__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(vectornav_msgs__msg__TimeUTC);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    vectornav_msgs__msg__TimeUTC * data =
      (vectornav_msgs__msg__TimeUTC *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!vectornav_msgs__msg__TimeUTC__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          vectornav_msgs__msg__TimeUTC__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!vectornav_msgs__msg__TimeUTC__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
