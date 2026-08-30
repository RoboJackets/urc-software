// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from vectornav_msgs:msg/GpsGroup.idl
// generated code does not contain a copyright notice
#include "vectornav_msgs/msg/detail/gps_group__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `header`
#include "std_msgs/msg/detail/header__functions.h"
// Member `utc`
#include "vectornav_msgs/msg/detail/time_utc__functions.h"
// Member `poslla`
// Member `posecef`
#include "geometry_msgs/msg/detail/point__functions.h"
// Member `velned`
// Member `velecef`
// Member `posu`
#include "geometry_msgs/msg/detail/vector3__functions.h"
// Member `dop`
#include "vectornav_msgs/msg/detail/dop__functions.h"

bool
vectornav_msgs__msg__GpsGroup__init(vectornav_msgs__msg__GpsGroup * msg)
{
  if (!msg) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__init(&msg->header)) {
    vectornav_msgs__msg__GpsGroup__fini(msg);
    return false;
  }
  // group_fields
  // utc
  if (!vectornav_msgs__msg__TimeUTC__init(&msg->utc)) {
    vectornav_msgs__msg__GpsGroup__fini(msg);
    return false;
  }
  // tow
  // week
  // numsats
  // fix
  // poslla
  if (!geometry_msgs__msg__Point__init(&msg->poslla)) {
    vectornav_msgs__msg__GpsGroup__fini(msg);
    return false;
  }
  // posecef
  if (!geometry_msgs__msg__Point__init(&msg->posecef)) {
    vectornav_msgs__msg__GpsGroup__fini(msg);
    return false;
  }
  // velned
  if (!geometry_msgs__msg__Vector3__init(&msg->velned)) {
    vectornav_msgs__msg__GpsGroup__fini(msg);
    return false;
  }
  // velecef
  if (!geometry_msgs__msg__Vector3__init(&msg->velecef)) {
    vectornav_msgs__msg__GpsGroup__fini(msg);
    return false;
  }
  // posu
  if (!geometry_msgs__msg__Vector3__init(&msg->posu)) {
    vectornav_msgs__msg__GpsGroup__fini(msg);
    return false;
  }
  // velu
  // timeu
  // timeinfo_status
  // timeinfo_leapseconds
  // dop
  if (!vectornav_msgs__msg__DOP__init(&msg->dop)) {
    vectornav_msgs__msg__GpsGroup__fini(msg);
    return false;
  }
  return true;
}

void
vectornav_msgs__msg__GpsGroup__fini(vectornav_msgs__msg__GpsGroup * msg)
{
  if (!msg) {
    return;
  }
  // header
  std_msgs__msg__Header__fini(&msg->header);
  // group_fields
  // utc
  vectornav_msgs__msg__TimeUTC__fini(&msg->utc);
  // tow
  // week
  // numsats
  // fix
  // poslla
  geometry_msgs__msg__Point__fini(&msg->poslla);
  // posecef
  geometry_msgs__msg__Point__fini(&msg->posecef);
  // velned
  geometry_msgs__msg__Vector3__fini(&msg->velned);
  // velecef
  geometry_msgs__msg__Vector3__fini(&msg->velecef);
  // posu
  geometry_msgs__msg__Vector3__fini(&msg->posu);
  // velu
  // timeu
  // timeinfo_status
  // timeinfo_leapseconds
  // dop
  vectornav_msgs__msg__DOP__fini(&msg->dop);
}

bool
vectornav_msgs__msg__GpsGroup__are_equal(const vectornav_msgs__msg__GpsGroup * lhs, const vectornav_msgs__msg__GpsGroup * rhs)
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
  // utc
  if (!vectornav_msgs__msg__TimeUTC__are_equal(
      &(lhs->utc), &(rhs->utc)))
  {
    return false;
  }
  // tow
  if (lhs->tow != rhs->tow) {
    return false;
  }
  // week
  if (lhs->week != rhs->week) {
    return false;
  }
  // numsats
  if (lhs->numsats != rhs->numsats) {
    return false;
  }
  // fix
  if (lhs->fix != rhs->fix) {
    return false;
  }
  // poslla
  if (!geometry_msgs__msg__Point__are_equal(
      &(lhs->poslla), &(rhs->poslla)))
  {
    return false;
  }
  // posecef
  if (!geometry_msgs__msg__Point__are_equal(
      &(lhs->posecef), &(rhs->posecef)))
  {
    return false;
  }
  // velned
  if (!geometry_msgs__msg__Vector3__are_equal(
      &(lhs->velned), &(rhs->velned)))
  {
    return false;
  }
  // velecef
  if (!geometry_msgs__msg__Vector3__are_equal(
      &(lhs->velecef), &(rhs->velecef)))
  {
    return false;
  }
  // posu
  if (!geometry_msgs__msg__Vector3__are_equal(
      &(lhs->posu), &(rhs->posu)))
  {
    return false;
  }
  // velu
  if (lhs->velu != rhs->velu) {
    return false;
  }
  // timeu
  if (lhs->timeu != rhs->timeu) {
    return false;
  }
  // timeinfo_status
  if (lhs->timeinfo_status != rhs->timeinfo_status) {
    return false;
  }
  // timeinfo_leapseconds
  if (lhs->timeinfo_leapseconds != rhs->timeinfo_leapseconds) {
    return false;
  }
  // dop
  if (!vectornav_msgs__msg__DOP__are_equal(
      &(lhs->dop), &(rhs->dop)))
  {
    return false;
  }
  return true;
}

bool
vectornav_msgs__msg__GpsGroup__copy(
  const vectornav_msgs__msg__GpsGroup * input,
  vectornav_msgs__msg__GpsGroup * output)
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
  // utc
  if (!vectornav_msgs__msg__TimeUTC__copy(
      &(input->utc), &(output->utc)))
  {
    return false;
  }
  // tow
  output->tow = input->tow;
  // week
  output->week = input->week;
  // numsats
  output->numsats = input->numsats;
  // fix
  output->fix = input->fix;
  // poslla
  if (!geometry_msgs__msg__Point__copy(
      &(input->poslla), &(output->poslla)))
  {
    return false;
  }
  // posecef
  if (!geometry_msgs__msg__Point__copy(
      &(input->posecef), &(output->posecef)))
  {
    return false;
  }
  // velned
  if (!geometry_msgs__msg__Vector3__copy(
      &(input->velned), &(output->velned)))
  {
    return false;
  }
  // velecef
  if (!geometry_msgs__msg__Vector3__copy(
      &(input->velecef), &(output->velecef)))
  {
    return false;
  }
  // posu
  if (!geometry_msgs__msg__Vector3__copy(
      &(input->posu), &(output->posu)))
  {
    return false;
  }
  // velu
  output->velu = input->velu;
  // timeu
  output->timeu = input->timeu;
  // timeinfo_status
  output->timeinfo_status = input->timeinfo_status;
  // timeinfo_leapseconds
  output->timeinfo_leapseconds = input->timeinfo_leapseconds;
  // dop
  if (!vectornav_msgs__msg__DOP__copy(
      &(input->dop), &(output->dop)))
  {
    return false;
  }
  return true;
}

vectornav_msgs__msg__GpsGroup *
vectornav_msgs__msg__GpsGroup__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  vectornav_msgs__msg__GpsGroup * msg = (vectornav_msgs__msg__GpsGroup *)allocator.allocate(sizeof(vectornav_msgs__msg__GpsGroup), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(vectornav_msgs__msg__GpsGroup));
  bool success = vectornav_msgs__msg__GpsGroup__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
vectornav_msgs__msg__GpsGroup__destroy(vectornav_msgs__msg__GpsGroup * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    vectornav_msgs__msg__GpsGroup__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
vectornav_msgs__msg__GpsGroup__Sequence__init(vectornav_msgs__msg__GpsGroup__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  vectornav_msgs__msg__GpsGroup * data = NULL;

  if (size) {
    data = (vectornav_msgs__msg__GpsGroup *)allocator.zero_allocate(size, sizeof(vectornav_msgs__msg__GpsGroup), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = vectornav_msgs__msg__GpsGroup__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        vectornav_msgs__msg__GpsGroup__fini(&data[i - 1]);
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
vectornav_msgs__msg__GpsGroup__Sequence__fini(vectornav_msgs__msg__GpsGroup__Sequence * array)
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
      vectornav_msgs__msg__GpsGroup__fini(&array->data[i]);
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

vectornav_msgs__msg__GpsGroup__Sequence *
vectornav_msgs__msg__GpsGroup__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  vectornav_msgs__msg__GpsGroup__Sequence * array = (vectornav_msgs__msg__GpsGroup__Sequence *)allocator.allocate(sizeof(vectornav_msgs__msg__GpsGroup__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = vectornav_msgs__msg__GpsGroup__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
vectornav_msgs__msg__GpsGroup__Sequence__destroy(vectornav_msgs__msg__GpsGroup__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    vectornav_msgs__msg__GpsGroup__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
vectornav_msgs__msg__GpsGroup__Sequence__are_equal(const vectornav_msgs__msg__GpsGroup__Sequence * lhs, const vectornav_msgs__msg__GpsGroup__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!vectornav_msgs__msg__GpsGroup__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
vectornav_msgs__msg__GpsGroup__Sequence__copy(
  const vectornav_msgs__msg__GpsGroup__Sequence * input,
  vectornav_msgs__msg__GpsGroup__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(vectornav_msgs__msg__GpsGroup);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    vectornav_msgs__msg__GpsGroup * data =
      (vectornav_msgs__msg__GpsGroup *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!vectornav_msgs__msg__GpsGroup__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          vectornav_msgs__msg__GpsGroup__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!vectornav_msgs__msg__GpsGroup__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
