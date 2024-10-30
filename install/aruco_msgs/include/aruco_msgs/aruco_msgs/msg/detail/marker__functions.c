// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from aruco_msgs:msg/Marker.idl
// generated code does not contain a copyright notice
#include "aruco_msgs/msg/detail/marker__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `header`
#include "std_msgs/msg/detail/header__functions.h"
// Member `pose`
#include "geometry_msgs/msg/detail/pose_with_covariance__functions.h"

bool
aruco_msgs__msg__Marker__init(aruco_msgs__msg__Marker * msg)
{
  if (!msg) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__init(&msg->header)) {
    aruco_msgs__msg__Marker__fini(msg);
    return false;
  }
  // id
  // pose
  if (!geometry_msgs__msg__PoseWithCovariance__init(&msg->pose)) {
    aruco_msgs__msg__Marker__fini(msg);
    return false;
  }
  // confidence
  return true;
}

void
aruco_msgs__msg__Marker__fini(aruco_msgs__msg__Marker * msg)
{
  if (!msg) {
    return;
  }
  // header
  std_msgs__msg__Header__fini(&msg->header);
  // id
  // pose
  geometry_msgs__msg__PoseWithCovariance__fini(&msg->pose);
  // confidence
}

bool
aruco_msgs__msg__Marker__are_equal(const aruco_msgs__msg__Marker * lhs, const aruco_msgs__msg__Marker * rhs)
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
  // id
  if (lhs->id != rhs->id) {
    return false;
  }
  // pose
  if (!geometry_msgs__msg__PoseWithCovariance__are_equal(
      &(lhs->pose), &(rhs->pose)))
  {
    return false;
  }
  // confidence
  if (lhs->confidence != rhs->confidence) {
    return false;
  }
  return true;
}

bool
aruco_msgs__msg__Marker__copy(
  const aruco_msgs__msg__Marker * input,
  aruco_msgs__msg__Marker * output)
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
  // id
  output->id = input->id;
  // pose
  if (!geometry_msgs__msg__PoseWithCovariance__copy(
      &(input->pose), &(output->pose)))
  {
    return false;
  }
  // confidence
  output->confidence = input->confidence;
  return true;
}

aruco_msgs__msg__Marker *
aruco_msgs__msg__Marker__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  aruco_msgs__msg__Marker * msg = (aruco_msgs__msg__Marker *)allocator.allocate(sizeof(aruco_msgs__msg__Marker), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(aruco_msgs__msg__Marker));
  bool success = aruco_msgs__msg__Marker__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
aruco_msgs__msg__Marker__destroy(aruco_msgs__msg__Marker * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    aruco_msgs__msg__Marker__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
aruco_msgs__msg__Marker__Sequence__init(aruco_msgs__msg__Marker__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  aruco_msgs__msg__Marker * data = NULL;

  if (size) {
    data = (aruco_msgs__msg__Marker *)allocator.zero_allocate(size, sizeof(aruco_msgs__msg__Marker), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = aruco_msgs__msg__Marker__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        aruco_msgs__msg__Marker__fini(&data[i - 1]);
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
aruco_msgs__msg__Marker__Sequence__fini(aruco_msgs__msg__Marker__Sequence * array)
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
      aruco_msgs__msg__Marker__fini(&array->data[i]);
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

aruco_msgs__msg__Marker__Sequence *
aruco_msgs__msg__Marker__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  aruco_msgs__msg__Marker__Sequence * array = (aruco_msgs__msg__Marker__Sequence *)allocator.allocate(sizeof(aruco_msgs__msg__Marker__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = aruco_msgs__msg__Marker__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
aruco_msgs__msg__Marker__Sequence__destroy(aruco_msgs__msg__Marker__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    aruco_msgs__msg__Marker__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
aruco_msgs__msg__Marker__Sequence__are_equal(const aruco_msgs__msg__Marker__Sequence * lhs, const aruco_msgs__msg__Marker__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!aruco_msgs__msg__Marker__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
aruco_msgs__msg__Marker__Sequence__copy(
  const aruco_msgs__msg__Marker__Sequence * input,
  aruco_msgs__msg__Marker__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(aruco_msgs__msg__Marker);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    aruco_msgs__msg__Marker * data =
      (aruco_msgs__msg__Marker *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!aruco_msgs__msg__Marker__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          aruco_msgs__msg__Marker__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!aruco_msgs__msg__Marker__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
