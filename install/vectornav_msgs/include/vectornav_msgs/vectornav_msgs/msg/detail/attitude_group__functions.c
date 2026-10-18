// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from vectornav_msgs:msg/AttitudeGroup.idl
// generated code does not contain a copyright notice
#include "vectornav_msgs/msg/detail/attitude_group__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `header`
#include "std_msgs/msg/detail/header__functions.h"
// Member `vpestatus`
#include "vectornav_msgs/msg/detail/vpe_status__functions.h"
// Member `yawpitchroll`
// Member `magned`
// Member `accelned`
// Member `linearaccelbody`
// Member `linearaccelned`
// Member `ypru`
#include "geometry_msgs/msg/detail/vector3__functions.h"
// Member `quaternion`
#include "geometry_msgs/msg/detail/quaternion__functions.h"

bool
vectornav_msgs__msg__AttitudeGroup__init(vectornav_msgs__msg__AttitudeGroup * msg)
{
  if (!msg) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__init(&msg->header)) {
    vectornav_msgs__msg__AttitudeGroup__fini(msg);
    return false;
  }
  // group_fields
  // vpestatus
  if (!vectornav_msgs__msg__VpeStatus__init(&msg->vpestatus)) {
    vectornav_msgs__msg__AttitudeGroup__fini(msg);
    return false;
  }
  // yawpitchroll
  if (!geometry_msgs__msg__Vector3__init(&msg->yawpitchroll)) {
    vectornav_msgs__msg__AttitudeGroup__fini(msg);
    return false;
  }
  // quaternion
  if (!geometry_msgs__msg__Quaternion__init(&msg->quaternion)) {
    vectornav_msgs__msg__AttitudeGroup__fini(msg);
    return false;
  }
  // dcm
  // magned
  if (!geometry_msgs__msg__Vector3__init(&msg->magned)) {
    vectornav_msgs__msg__AttitudeGroup__fini(msg);
    return false;
  }
  // accelned
  if (!geometry_msgs__msg__Vector3__init(&msg->accelned)) {
    vectornav_msgs__msg__AttitudeGroup__fini(msg);
    return false;
  }
  // linearaccelbody
  if (!geometry_msgs__msg__Vector3__init(&msg->linearaccelbody)) {
    vectornav_msgs__msg__AttitudeGroup__fini(msg);
    return false;
  }
  // linearaccelned
  if (!geometry_msgs__msg__Vector3__init(&msg->linearaccelned)) {
    vectornav_msgs__msg__AttitudeGroup__fini(msg);
    return false;
  }
  // ypru
  if (!geometry_msgs__msg__Vector3__init(&msg->ypru)) {
    vectornav_msgs__msg__AttitudeGroup__fini(msg);
    return false;
  }
  return true;
}

void
vectornav_msgs__msg__AttitudeGroup__fini(vectornav_msgs__msg__AttitudeGroup * msg)
{
  if (!msg) {
    return;
  }
  // header
  std_msgs__msg__Header__fini(&msg->header);
  // group_fields
  // vpestatus
  vectornav_msgs__msg__VpeStatus__fini(&msg->vpestatus);
  // yawpitchroll
  geometry_msgs__msg__Vector3__fini(&msg->yawpitchroll);
  // quaternion
  geometry_msgs__msg__Quaternion__fini(&msg->quaternion);
  // dcm
  // magned
  geometry_msgs__msg__Vector3__fini(&msg->magned);
  // accelned
  geometry_msgs__msg__Vector3__fini(&msg->accelned);
  // linearaccelbody
  geometry_msgs__msg__Vector3__fini(&msg->linearaccelbody);
  // linearaccelned
  geometry_msgs__msg__Vector3__fini(&msg->linearaccelned);
  // ypru
  geometry_msgs__msg__Vector3__fini(&msg->ypru);
}

bool
vectornav_msgs__msg__AttitudeGroup__are_equal(const vectornav_msgs__msg__AttitudeGroup * lhs, const vectornav_msgs__msg__AttitudeGroup * rhs)
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
  // vpestatus
  if (!vectornav_msgs__msg__VpeStatus__are_equal(
      &(lhs->vpestatus), &(rhs->vpestatus)))
  {
    return false;
  }
  // yawpitchroll
  if (!geometry_msgs__msg__Vector3__are_equal(
      &(lhs->yawpitchroll), &(rhs->yawpitchroll)))
  {
    return false;
  }
  // quaternion
  if (!geometry_msgs__msg__Quaternion__are_equal(
      &(lhs->quaternion), &(rhs->quaternion)))
  {
    return false;
  }
  // dcm
  for (size_t i = 0; i < 9; ++i) {
    if (lhs->dcm[i] != rhs->dcm[i]) {
      return false;
    }
  }
  // magned
  if (!geometry_msgs__msg__Vector3__are_equal(
      &(lhs->magned), &(rhs->magned)))
  {
    return false;
  }
  // accelned
  if (!geometry_msgs__msg__Vector3__are_equal(
      &(lhs->accelned), &(rhs->accelned)))
  {
    return false;
  }
  // linearaccelbody
  if (!geometry_msgs__msg__Vector3__are_equal(
      &(lhs->linearaccelbody), &(rhs->linearaccelbody)))
  {
    return false;
  }
  // linearaccelned
  if (!geometry_msgs__msg__Vector3__are_equal(
      &(lhs->linearaccelned), &(rhs->linearaccelned)))
  {
    return false;
  }
  // ypru
  if (!geometry_msgs__msg__Vector3__are_equal(
      &(lhs->ypru), &(rhs->ypru)))
  {
    return false;
  }
  return true;
}

bool
vectornav_msgs__msg__AttitudeGroup__copy(
  const vectornav_msgs__msg__AttitudeGroup * input,
  vectornav_msgs__msg__AttitudeGroup * output)
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
  // vpestatus
  if (!vectornav_msgs__msg__VpeStatus__copy(
      &(input->vpestatus), &(output->vpestatus)))
  {
    return false;
  }
  // yawpitchroll
  if (!geometry_msgs__msg__Vector3__copy(
      &(input->yawpitchroll), &(output->yawpitchroll)))
  {
    return false;
  }
  // quaternion
  if (!geometry_msgs__msg__Quaternion__copy(
      &(input->quaternion), &(output->quaternion)))
  {
    return false;
  }
  // dcm
  for (size_t i = 0; i < 9; ++i) {
    output->dcm[i] = input->dcm[i];
  }
  // magned
  if (!geometry_msgs__msg__Vector3__copy(
      &(input->magned), &(output->magned)))
  {
    return false;
  }
  // accelned
  if (!geometry_msgs__msg__Vector3__copy(
      &(input->accelned), &(output->accelned)))
  {
    return false;
  }
  // linearaccelbody
  if (!geometry_msgs__msg__Vector3__copy(
      &(input->linearaccelbody), &(output->linearaccelbody)))
  {
    return false;
  }
  // linearaccelned
  if (!geometry_msgs__msg__Vector3__copy(
      &(input->linearaccelned), &(output->linearaccelned)))
  {
    return false;
  }
  // ypru
  if (!geometry_msgs__msg__Vector3__copy(
      &(input->ypru), &(output->ypru)))
  {
    return false;
  }
  return true;
}

vectornav_msgs__msg__AttitudeGroup *
vectornav_msgs__msg__AttitudeGroup__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  vectornav_msgs__msg__AttitudeGroup * msg = (vectornav_msgs__msg__AttitudeGroup *)allocator.allocate(sizeof(vectornav_msgs__msg__AttitudeGroup), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(vectornav_msgs__msg__AttitudeGroup));
  bool success = vectornav_msgs__msg__AttitudeGroup__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
vectornav_msgs__msg__AttitudeGroup__destroy(vectornav_msgs__msg__AttitudeGroup * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    vectornav_msgs__msg__AttitudeGroup__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
vectornav_msgs__msg__AttitudeGroup__Sequence__init(vectornav_msgs__msg__AttitudeGroup__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  vectornav_msgs__msg__AttitudeGroup * data = NULL;

  if (size) {
    data = (vectornav_msgs__msg__AttitudeGroup *)allocator.zero_allocate(size, sizeof(vectornav_msgs__msg__AttitudeGroup), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = vectornav_msgs__msg__AttitudeGroup__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        vectornav_msgs__msg__AttitudeGroup__fini(&data[i - 1]);
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
vectornav_msgs__msg__AttitudeGroup__Sequence__fini(vectornav_msgs__msg__AttitudeGroup__Sequence * array)
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
      vectornav_msgs__msg__AttitudeGroup__fini(&array->data[i]);
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

vectornav_msgs__msg__AttitudeGroup__Sequence *
vectornav_msgs__msg__AttitudeGroup__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  vectornav_msgs__msg__AttitudeGroup__Sequence * array = (vectornav_msgs__msg__AttitudeGroup__Sequence *)allocator.allocate(sizeof(vectornav_msgs__msg__AttitudeGroup__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = vectornav_msgs__msg__AttitudeGroup__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
vectornav_msgs__msg__AttitudeGroup__Sequence__destroy(vectornav_msgs__msg__AttitudeGroup__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    vectornav_msgs__msg__AttitudeGroup__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
vectornav_msgs__msg__AttitudeGroup__Sequence__are_equal(const vectornav_msgs__msg__AttitudeGroup__Sequence * lhs, const vectornav_msgs__msg__AttitudeGroup__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!vectornav_msgs__msg__AttitudeGroup__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
vectornav_msgs__msg__AttitudeGroup__Sequence__copy(
  const vectornav_msgs__msg__AttitudeGroup__Sequence * input,
  vectornav_msgs__msg__AttitudeGroup__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(vectornav_msgs__msg__AttitudeGroup);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    vectornav_msgs__msg__AttitudeGroup * data =
      (vectornav_msgs__msg__AttitudeGroup *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!vectornav_msgs__msg__AttitudeGroup__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          vectornav_msgs__msg__AttitudeGroup__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!vectornav_msgs__msg__AttitudeGroup__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
