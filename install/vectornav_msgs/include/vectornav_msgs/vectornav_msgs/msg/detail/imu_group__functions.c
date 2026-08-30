// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from vectornav_msgs:msg/ImuGroup.idl
// generated code does not contain a copyright notice
#include "vectornav_msgs/msg/detail/imu_group__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `header`
#include "std_msgs/msg/detail/header__functions.h"
// Member `uncompmag`
// Member `uncompaccel`
// Member `uncompgyro`
// Member `deltatheta_dtheta`
// Member `deltavel`
// Member `mag`
// Member `accel`
// Member `angularrate`
#include "geometry_msgs/msg/detail/vector3__functions.h"

bool
vectornav_msgs__msg__ImuGroup__init(vectornav_msgs__msg__ImuGroup * msg)
{
  if (!msg) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__init(&msg->header)) {
    vectornav_msgs__msg__ImuGroup__fini(msg);
    return false;
  }
  // group_fields
  // imustatus
  // uncompmag
  if (!geometry_msgs__msg__Vector3__init(&msg->uncompmag)) {
    vectornav_msgs__msg__ImuGroup__fini(msg);
    return false;
  }
  // uncompaccel
  if (!geometry_msgs__msg__Vector3__init(&msg->uncompaccel)) {
    vectornav_msgs__msg__ImuGroup__fini(msg);
    return false;
  }
  // uncompgyro
  if (!geometry_msgs__msg__Vector3__init(&msg->uncompgyro)) {
    vectornav_msgs__msg__ImuGroup__fini(msg);
    return false;
  }
  // temp
  // pres
  // deltatheta_time
  // deltatheta_dtheta
  if (!geometry_msgs__msg__Vector3__init(&msg->deltatheta_dtheta)) {
    vectornav_msgs__msg__ImuGroup__fini(msg);
    return false;
  }
  // deltavel
  if (!geometry_msgs__msg__Vector3__init(&msg->deltavel)) {
    vectornav_msgs__msg__ImuGroup__fini(msg);
    return false;
  }
  // mag
  if (!geometry_msgs__msg__Vector3__init(&msg->mag)) {
    vectornav_msgs__msg__ImuGroup__fini(msg);
    return false;
  }
  // accel
  if (!geometry_msgs__msg__Vector3__init(&msg->accel)) {
    vectornav_msgs__msg__ImuGroup__fini(msg);
    return false;
  }
  // angularrate
  if (!geometry_msgs__msg__Vector3__init(&msg->angularrate)) {
    vectornav_msgs__msg__ImuGroup__fini(msg);
    return false;
  }
  // sensat
  return true;
}

void
vectornav_msgs__msg__ImuGroup__fini(vectornav_msgs__msg__ImuGroup * msg)
{
  if (!msg) {
    return;
  }
  // header
  std_msgs__msg__Header__fini(&msg->header);
  // group_fields
  // imustatus
  // uncompmag
  geometry_msgs__msg__Vector3__fini(&msg->uncompmag);
  // uncompaccel
  geometry_msgs__msg__Vector3__fini(&msg->uncompaccel);
  // uncompgyro
  geometry_msgs__msg__Vector3__fini(&msg->uncompgyro);
  // temp
  // pres
  // deltatheta_time
  // deltatheta_dtheta
  geometry_msgs__msg__Vector3__fini(&msg->deltatheta_dtheta);
  // deltavel
  geometry_msgs__msg__Vector3__fini(&msg->deltavel);
  // mag
  geometry_msgs__msg__Vector3__fini(&msg->mag);
  // accel
  geometry_msgs__msg__Vector3__fini(&msg->accel);
  // angularrate
  geometry_msgs__msg__Vector3__fini(&msg->angularrate);
  // sensat
}

bool
vectornav_msgs__msg__ImuGroup__are_equal(const vectornav_msgs__msg__ImuGroup * lhs, const vectornav_msgs__msg__ImuGroup * rhs)
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
  // imustatus
  if (lhs->imustatus != rhs->imustatus) {
    return false;
  }
  // uncompmag
  if (!geometry_msgs__msg__Vector3__are_equal(
      &(lhs->uncompmag), &(rhs->uncompmag)))
  {
    return false;
  }
  // uncompaccel
  if (!geometry_msgs__msg__Vector3__are_equal(
      &(lhs->uncompaccel), &(rhs->uncompaccel)))
  {
    return false;
  }
  // uncompgyro
  if (!geometry_msgs__msg__Vector3__are_equal(
      &(lhs->uncompgyro), &(rhs->uncompgyro)))
  {
    return false;
  }
  // temp
  if (lhs->temp != rhs->temp) {
    return false;
  }
  // pres
  if (lhs->pres != rhs->pres) {
    return false;
  }
  // deltatheta_time
  if (lhs->deltatheta_time != rhs->deltatheta_time) {
    return false;
  }
  // deltatheta_dtheta
  if (!geometry_msgs__msg__Vector3__are_equal(
      &(lhs->deltatheta_dtheta), &(rhs->deltatheta_dtheta)))
  {
    return false;
  }
  // deltavel
  if (!geometry_msgs__msg__Vector3__are_equal(
      &(lhs->deltavel), &(rhs->deltavel)))
  {
    return false;
  }
  // mag
  if (!geometry_msgs__msg__Vector3__are_equal(
      &(lhs->mag), &(rhs->mag)))
  {
    return false;
  }
  // accel
  if (!geometry_msgs__msg__Vector3__are_equal(
      &(lhs->accel), &(rhs->accel)))
  {
    return false;
  }
  // angularrate
  if (!geometry_msgs__msg__Vector3__are_equal(
      &(lhs->angularrate), &(rhs->angularrate)))
  {
    return false;
  }
  // sensat
  if (lhs->sensat != rhs->sensat) {
    return false;
  }
  return true;
}

bool
vectornav_msgs__msg__ImuGroup__copy(
  const vectornav_msgs__msg__ImuGroup * input,
  vectornav_msgs__msg__ImuGroup * output)
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
  // imustatus
  output->imustatus = input->imustatus;
  // uncompmag
  if (!geometry_msgs__msg__Vector3__copy(
      &(input->uncompmag), &(output->uncompmag)))
  {
    return false;
  }
  // uncompaccel
  if (!geometry_msgs__msg__Vector3__copy(
      &(input->uncompaccel), &(output->uncompaccel)))
  {
    return false;
  }
  // uncompgyro
  if (!geometry_msgs__msg__Vector3__copy(
      &(input->uncompgyro), &(output->uncompgyro)))
  {
    return false;
  }
  // temp
  output->temp = input->temp;
  // pres
  output->pres = input->pres;
  // deltatheta_time
  output->deltatheta_time = input->deltatheta_time;
  // deltatheta_dtheta
  if (!geometry_msgs__msg__Vector3__copy(
      &(input->deltatheta_dtheta), &(output->deltatheta_dtheta)))
  {
    return false;
  }
  // deltavel
  if (!geometry_msgs__msg__Vector3__copy(
      &(input->deltavel), &(output->deltavel)))
  {
    return false;
  }
  // mag
  if (!geometry_msgs__msg__Vector3__copy(
      &(input->mag), &(output->mag)))
  {
    return false;
  }
  // accel
  if (!geometry_msgs__msg__Vector3__copy(
      &(input->accel), &(output->accel)))
  {
    return false;
  }
  // angularrate
  if (!geometry_msgs__msg__Vector3__copy(
      &(input->angularrate), &(output->angularrate)))
  {
    return false;
  }
  // sensat
  output->sensat = input->sensat;
  return true;
}

vectornav_msgs__msg__ImuGroup *
vectornav_msgs__msg__ImuGroup__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  vectornav_msgs__msg__ImuGroup * msg = (vectornav_msgs__msg__ImuGroup *)allocator.allocate(sizeof(vectornav_msgs__msg__ImuGroup), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(vectornav_msgs__msg__ImuGroup));
  bool success = vectornav_msgs__msg__ImuGroup__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
vectornav_msgs__msg__ImuGroup__destroy(vectornav_msgs__msg__ImuGroup * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    vectornav_msgs__msg__ImuGroup__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
vectornav_msgs__msg__ImuGroup__Sequence__init(vectornav_msgs__msg__ImuGroup__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  vectornav_msgs__msg__ImuGroup * data = NULL;

  if (size) {
    data = (vectornav_msgs__msg__ImuGroup *)allocator.zero_allocate(size, sizeof(vectornav_msgs__msg__ImuGroup), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = vectornav_msgs__msg__ImuGroup__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        vectornav_msgs__msg__ImuGroup__fini(&data[i - 1]);
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
vectornav_msgs__msg__ImuGroup__Sequence__fini(vectornav_msgs__msg__ImuGroup__Sequence * array)
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
      vectornav_msgs__msg__ImuGroup__fini(&array->data[i]);
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

vectornav_msgs__msg__ImuGroup__Sequence *
vectornav_msgs__msg__ImuGroup__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  vectornav_msgs__msg__ImuGroup__Sequence * array = (vectornav_msgs__msg__ImuGroup__Sequence *)allocator.allocate(sizeof(vectornav_msgs__msg__ImuGroup__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = vectornav_msgs__msg__ImuGroup__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
vectornav_msgs__msg__ImuGroup__Sequence__destroy(vectornav_msgs__msg__ImuGroup__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    vectornav_msgs__msg__ImuGroup__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
vectornav_msgs__msg__ImuGroup__Sequence__are_equal(const vectornav_msgs__msg__ImuGroup__Sequence * lhs, const vectornav_msgs__msg__ImuGroup__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!vectornav_msgs__msg__ImuGroup__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
vectornav_msgs__msg__ImuGroup__Sequence__copy(
  const vectornav_msgs__msg__ImuGroup__Sequence * input,
  vectornav_msgs__msg__ImuGroup__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(vectornav_msgs__msg__ImuGroup);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    vectornav_msgs__msg__ImuGroup * data =
      (vectornav_msgs__msg__ImuGroup *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!vectornav_msgs__msg__ImuGroup__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          vectornav_msgs__msg__ImuGroup__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!vectornav_msgs__msg__ImuGroup__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
