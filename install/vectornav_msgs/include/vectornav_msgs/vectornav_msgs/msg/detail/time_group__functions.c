// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from vectornav_msgs:msg/TimeGroup.idl
// generated code does not contain a copyright notice
#include "vectornav_msgs/msg/detail/time_group__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `header`
#include "std_msgs/msg/detail/header__functions.h"
// Member `timeutc`
#include "vectornav_msgs/msg/detail/time_utc__functions.h"
// Member `timestatus`
#include "vectornav_msgs/msg/detail/time_status__functions.h"

bool
vectornav_msgs__msg__TimeGroup__init(vectornav_msgs__msg__TimeGroup * msg)
{
  if (!msg) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__init(&msg->header)) {
    vectornav_msgs__msg__TimeGroup__fini(msg);
    return false;
  }
  // group_fields
  // timestartup
  // timegps
  // gpstow
  // gpsweek
  // timesyncin
  // timegpspps
  // timeutc
  if (!vectornav_msgs__msg__TimeUTC__init(&msg->timeutc)) {
    vectornav_msgs__msg__TimeGroup__fini(msg);
    return false;
  }
  // syncincnt
  // syncoutcnt
  // timestatus
  if (!vectornav_msgs__msg__TimeStatus__init(&msg->timestatus)) {
    vectornav_msgs__msg__TimeGroup__fini(msg);
    return false;
  }
  return true;
}

void
vectornav_msgs__msg__TimeGroup__fini(vectornav_msgs__msg__TimeGroup * msg)
{
  if (!msg) {
    return;
  }
  // header
  std_msgs__msg__Header__fini(&msg->header);
  // group_fields
  // timestartup
  // timegps
  // gpstow
  // gpsweek
  // timesyncin
  // timegpspps
  // timeutc
  vectornav_msgs__msg__TimeUTC__fini(&msg->timeutc);
  // syncincnt
  // syncoutcnt
  // timestatus
  vectornav_msgs__msg__TimeStatus__fini(&msg->timestatus);
}

bool
vectornav_msgs__msg__TimeGroup__are_equal(const vectornav_msgs__msg__TimeGroup * lhs, const vectornav_msgs__msg__TimeGroup * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__are_equal(
      &(lhs->header), &(rhs->header)))
  {
    return false;
  }
  // group_fields
  if (lhs->group_fields != rhs->group_fields) {
    return false;
  }
  // timestartup
  if (lhs->timestartup != rhs->timestartup) {
    return false;
  }
  // timegps
  if (lhs->timegps != rhs->timegps) {
    return false;
  }
  // gpstow
  if (lhs->gpstow != rhs->gpstow) {
    return false;
  }
  // gpsweek
  if (lhs->gpsweek != rhs->gpsweek) {
    return false;
  }
  // timesyncin
  if (lhs->timesyncin != rhs->timesyncin) {
    return false;
  }
  // timegpspps
  if (lhs->timegpspps != rhs->timegpspps) {
    return false;
  }
  // timeutc
  if (!vectornav_msgs__msg__TimeUTC__are_equal(
      &(lhs->timeutc), &(rhs->timeutc)))
  {
    return false;
  }
  // syncincnt
  if (lhs->syncincnt != rhs->syncincnt) {
    return false;
  }
  // syncoutcnt
  if (lhs->syncoutcnt != rhs->syncoutcnt) {
    return false;
  }
  // timestatus
  if (!vectornav_msgs__msg__TimeStatus__are_equal(
      &(lhs->timestatus), &(rhs->timestatus)))
  {
    return false;
  }
  return true;
}

bool
vectornav_msgs__msg__TimeGroup__copy(
  const vectornav_msgs__msg__TimeGroup * input,
  vectornav_msgs__msg__TimeGroup * output)
{
  if (!input || !output) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__copy(
      &(input->header), &(output->header)))
  {
    return false;
  }
  // group_fields
  output->group_fields = input->group_fields;
  // timestartup
  output->timestartup = input->timestartup;
  // timegps
  output->timegps = input->timegps;
  // gpstow
  output->gpstow = input->gpstow;
  // gpsweek
  output->gpsweek = input->gpsweek;
  // timesyncin
  output->timesyncin = input->timesyncin;
  // timegpspps
  output->timegpspps = input->timegpspps;
  // timeutc
  if (!vectornav_msgs__msg__TimeUTC__copy(
      &(input->timeutc), &(output->timeutc)))
  {
    return false;
  }
  // syncincnt
  output->syncincnt = input->syncincnt;
  // syncoutcnt
  output->syncoutcnt = input->syncoutcnt;
  // timestatus
  if (!vectornav_msgs__msg__TimeStatus__copy(
      &(input->timestatus), &(output->timestatus)))
  {
    return false;
  }
  return true;
}

vectornav_msgs__msg__TimeGroup *
vectornav_msgs__msg__TimeGroup__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  vectornav_msgs__msg__TimeGroup * msg = (vectornav_msgs__msg__TimeGroup *)allocator.allocate(sizeof(vectornav_msgs__msg__TimeGroup), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(vectornav_msgs__msg__TimeGroup));
  bool success = vectornav_msgs__msg__TimeGroup__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
vectornav_msgs__msg__TimeGroup__destroy(vectornav_msgs__msg__TimeGroup * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    vectornav_msgs__msg__TimeGroup__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
vectornav_msgs__msg__TimeGroup__Sequence__init(vectornav_msgs__msg__TimeGroup__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  vectornav_msgs__msg__TimeGroup * data = NULL;

  if (size) {
    data = (vectornav_msgs__msg__TimeGroup *)allocator.zero_allocate(size, sizeof(vectornav_msgs__msg__TimeGroup), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = vectornav_msgs__msg__TimeGroup__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        vectornav_msgs__msg__TimeGroup__fini(&data[i - 1]);
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
vectornav_msgs__msg__TimeGroup__Sequence__fini(vectornav_msgs__msg__TimeGroup__Sequence * array)
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
      vectornav_msgs__msg__TimeGroup__fini(&array->data[i]);
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

vectornav_msgs__msg__TimeGroup__Sequence *
vectornav_msgs__msg__TimeGroup__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  vectornav_msgs__msg__TimeGroup__Sequence * array = (vectornav_msgs__msg__TimeGroup__Sequence *)allocator.allocate(sizeof(vectornav_msgs__msg__TimeGroup__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = vectornav_msgs__msg__TimeGroup__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
vectornav_msgs__msg__TimeGroup__Sequence__destroy(vectornav_msgs__msg__TimeGroup__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    vectornav_msgs__msg__TimeGroup__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
vectornav_msgs__msg__TimeGroup__Sequence__are_equal(const vectornav_msgs__msg__TimeGroup__Sequence * lhs, const vectornav_msgs__msg__TimeGroup__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!vectornav_msgs__msg__TimeGroup__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
vectornav_msgs__msg__TimeGroup__Sequence__copy(
  const vectornav_msgs__msg__TimeGroup__Sequence * input,
  vectornav_msgs__msg__TimeGroup__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(vectornav_msgs__msg__TimeGroup);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    vectornav_msgs__msg__TimeGroup * data =
      (vectornav_msgs__msg__TimeGroup *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!vectornav_msgs__msg__TimeGroup__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          vectornav_msgs__msg__TimeGroup__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!vectornav_msgs__msg__TimeGroup__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
