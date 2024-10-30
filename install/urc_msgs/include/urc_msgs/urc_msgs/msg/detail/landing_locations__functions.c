// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from urc_msgs:msg/LandingLocations.idl
// generated code does not contain a copyright notice
#include "urc_msgs/msg/detail/landing_locations__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `header`
#include "std_msgs/msg/detail/header__functions.h"

bool
urc_msgs__msg__LandingLocations__init(urc_msgs__msg__LandingLocations * msg)
{
  if (!msg) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__init(&msg->header)) {
    urc_msgs__msg__LandingLocations__fini(msg);
    return false;
  }
  // num_locations
  // latitudes
  // longitudes
  return true;
}

void
urc_msgs__msg__LandingLocations__fini(urc_msgs__msg__LandingLocations * msg)
{
  if (!msg) {
    return;
  }
  // header
  std_msgs__msg__Header__fini(&msg->header);
  // num_locations
  // latitudes
  // longitudes
}

bool
urc_msgs__msg__LandingLocations__are_equal(const urc_msgs__msg__LandingLocations * lhs, const urc_msgs__msg__LandingLocations * rhs)
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
  // num_locations
  if (lhs->num_locations != rhs->num_locations) {
    return false;
  }
  // latitudes
  for (size_t i = 0; i < 100; ++i) {
    if (lhs->latitudes[i] != rhs->latitudes[i]) {
      return false;
    }
  }
  // longitudes
  for (size_t i = 0; i < 100; ++i) {
    if (lhs->longitudes[i] != rhs->longitudes[i]) {
      return false;
    }
  }
  return true;
}

bool
urc_msgs__msg__LandingLocations__copy(
  const urc_msgs__msg__LandingLocations * input,
  urc_msgs__msg__LandingLocations * output)
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
  // num_locations
  output->num_locations = input->num_locations;
  // latitudes
  for (size_t i = 0; i < 100; ++i) {
    output->latitudes[i] = input->latitudes[i];
  }
  // longitudes
  for (size_t i = 0; i < 100; ++i) {
    output->longitudes[i] = input->longitudes[i];
  }
  return true;
}

urc_msgs__msg__LandingLocations *
urc_msgs__msg__LandingLocations__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  urc_msgs__msg__LandingLocations * msg = (urc_msgs__msg__LandingLocations *)allocator.allocate(sizeof(urc_msgs__msg__LandingLocations), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(urc_msgs__msg__LandingLocations));
  bool success = urc_msgs__msg__LandingLocations__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
urc_msgs__msg__LandingLocations__destroy(urc_msgs__msg__LandingLocations * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    urc_msgs__msg__LandingLocations__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
urc_msgs__msg__LandingLocations__Sequence__init(urc_msgs__msg__LandingLocations__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  urc_msgs__msg__LandingLocations * data = NULL;

  if (size) {
    data = (urc_msgs__msg__LandingLocations *)allocator.zero_allocate(size, sizeof(urc_msgs__msg__LandingLocations), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = urc_msgs__msg__LandingLocations__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        urc_msgs__msg__LandingLocations__fini(&data[i - 1]);
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
urc_msgs__msg__LandingLocations__Sequence__fini(urc_msgs__msg__LandingLocations__Sequence * array)
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
      urc_msgs__msg__LandingLocations__fini(&array->data[i]);
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

urc_msgs__msg__LandingLocations__Sequence *
urc_msgs__msg__LandingLocations__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  urc_msgs__msg__LandingLocations__Sequence * array = (urc_msgs__msg__LandingLocations__Sequence *)allocator.allocate(sizeof(urc_msgs__msg__LandingLocations__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = urc_msgs__msg__LandingLocations__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
urc_msgs__msg__LandingLocations__Sequence__destroy(urc_msgs__msg__LandingLocations__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    urc_msgs__msg__LandingLocations__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
urc_msgs__msg__LandingLocations__Sequence__are_equal(const urc_msgs__msg__LandingLocations__Sequence * lhs, const urc_msgs__msg__LandingLocations__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!urc_msgs__msg__LandingLocations__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
urc_msgs__msg__LandingLocations__Sequence__copy(
  const urc_msgs__msg__LandingLocations__Sequence * input,
  urc_msgs__msg__LandingLocations__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(urc_msgs__msg__LandingLocations);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    urc_msgs__msg__LandingLocations * data =
      (urc_msgs__msg__LandingLocations *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!urc_msgs__msg__LandingLocations__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          urc_msgs__msg__LandingLocations__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!urc_msgs__msg__LandingLocations__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
