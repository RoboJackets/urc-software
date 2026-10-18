// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from vectornav_msgs:msg/InsStatus.idl
// generated code does not contain a copyright notice
#include "vectornav_msgs/msg/detail/ins_status__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


bool
vectornav_msgs__msg__InsStatus__init(vectornav_msgs__msg__InsStatus * msg)
{
  if (!msg) {
    return false;
  }
  // mode
  // gps_fix
  // time_error
  // imu_error
  // mag_pres_error
  // gps_error
  // gps_heading_ins
  // gps_compass
  return true;
}

void
vectornav_msgs__msg__InsStatus__fini(vectornav_msgs__msg__InsStatus * msg)
{
  if (!msg) {
    return;
  }
  // mode
  // gps_fix
  // time_error
  // imu_error
  // mag_pres_error
  // gps_error
  // gps_heading_ins
  // gps_compass
}

bool
vectornav_msgs__msg__InsStatus__are_equal(const vectornav_msgs__msg__InsStatus * lhs, const vectornav_msgs__msg__InsStatus * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // mode
  if (lhs->mode != rhs->mode) {
    return false;
  }
  // gps_fix
  if (lhs->gps_fix != rhs->gps_fix) {
    return false;
  }
  // time_error
  if (lhs->time_error != rhs->time_error) {
    return false;
  }
  // imu_error
  if (lhs->imu_error != rhs->imu_error) {
    return false;
  }
  // mag_pres_error
  if (lhs->mag_pres_error != rhs->mag_pres_error) {
    return false;
  }
  // gps_error
  if (lhs->gps_error != rhs->gps_error) {
    return false;
  }
  // gps_heading_ins
  if (lhs->gps_heading_ins != rhs->gps_heading_ins) {
    return false;
  }
  // gps_compass
  if (lhs->gps_compass != rhs->gps_compass) {
    return false;
  }
  return true;
}

bool
vectornav_msgs__msg__InsStatus__copy(
  const vectornav_msgs__msg__InsStatus * input,
  vectornav_msgs__msg__InsStatus * output)
{
  if (!input || !output) {
    return false;
  }
  // mode
  output->mode = input->mode;
  // gps_fix
  output->gps_fix = input->gps_fix;
  // time_error
  output->time_error = input->time_error;
  // imu_error
  output->imu_error = input->imu_error;
  // mag_pres_error
  output->mag_pres_error = input->mag_pres_error;
  // gps_error
  output->gps_error = input->gps_error;
  // gps_heading_ins
  output->gps_heading_ins = input->gps_heading_ins;
  // gps_compass
  output->gps_compass = input->gps_compass;
  return true;
}

vectornav_msgs__msg__InsStatus *
vectornav_msgs__msg__InsStatus__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  vectornav_msgs__msg__InsStatus * msg = (vectornav_msgs__msg__InsStatus *)allocator.allocate(sizeof(vectornav_msgs__msg__InsStatus), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(vectornav_msgs__msg__InsStatus));
  bool success = vectornav_msgs__msg__InsStatus__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
vectornav_msgs__msg__InsStatus__destroy(vectornav_msgs__msg__InsStatus * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    vectornav_msgs__msg__InsStatus__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
vectornav_msgs__msg__InsStatus__Sequence__init(vectornav_msgs__msg__InsStatus__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  vectornav_msgs__msg__InsStatus * data = NULL;

  if (size) {
    data = (vectornav_msgs__msg__InsStatus *)allocator.zero_allocate(size, sizeof(vectornav_msgs__msg__InsStatus), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = vectornav_msgs__msg__InsStatus__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        vectornav_msgs__msg__InsStatus__fini(&data[i - 1]);
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
vectornav_msgs__msg__InsStatus__Sequence__fini(vectornav_msgs__msg__InsStatus__Sequence * array)
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
      vectornav_msgs__msg__InsStatus__fini(&array->data[i]);
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

vectornav_msgs__msg__InsStatus__Sequence *
vectornav_msgs__msg__InsStatus__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  vectornav_msgs__msg__InsStatus__Sequence * array = (vectornav_msgs__msg__InsStatus__Sequence *)allocator.allocate(sizeof(vectornav_msgs__msg__InsStatus__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = vectornav_msgs__msg__InsStatus__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
vectornav_msgs__msg__InsStatus__Sequence__destroy(vectornav_msgs__msg__InsStatus__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    vectornav_msgs__msg__InsStatus__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
vectornav_msgs__msg__InsStatus__Sequence__are_equal(const vectornav_msgs__msg__InsStatus__Sequence * lhs, const vectornav_msgs__msg__InsStatus__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!vectornav_msgs__msg__InsStatus__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
vectornav_msgs__msg__InsStatus__Sequence__copy(
  const vectornav_msgs__msg__InsStatus__Sequence * input,
  vectornav_msgs__msg__InsStatus__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(vectornav_msgs__msg__InsStatus);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    vectornav_msgs__msg__InsStatus * data =
      (vectornav_msgs__msg__InsStatus *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!vectornav_msgs__msg__InsStatus__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          vectornav_msgs__msg__InsStatus__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!vectornav_msgs__msg__InsStatus__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
