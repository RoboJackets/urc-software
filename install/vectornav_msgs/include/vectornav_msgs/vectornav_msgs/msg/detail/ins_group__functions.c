// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from vectornav_msgs:msg/InsGroup.idl
// generated code does not contain a copyright notice
#include "vectornav_msgs/msg/detail/ins_group__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `header`
#include "std_msgs/msg/detail/header__functions.h"
// Member `insstatus`
#include "vectornav_msgs/msg/detail/ins_status__functions.h"
// Member `poslla`
// Member `posecef`
#include "geometry_msgs/msg/detail/point__functions.h"
// Member `velbody`
// Member `velned`
// Member `velecef`
// Member `magecef`
// Member `accelecef`
// Member `linearaccelecef`
#include "geometry_msgs/msg/detail/vector3__functions.h"

bool
vectornav_msgs__msg__InsGroup__init(vectornav_msgs__msg__InsGroup * msg)
{
  if (!msg) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__init(&msg->header)) {
    vectornav_msgs__msg__InsGroup__fini(msg);
    return false;
  }
  // group_fields
  // insstatus
  if (!vectornav_msgs__msg__InsStatus__init(&msg->insstatus)) {
    vectornav_msgs__msg__InsGroup__fini(msg);
    return false;
  }
  // poslla
  if (!geometry_msgs__msg__Point__init(&msg->poslla)) {
    vectornav_msgs__msg__InsGroup__fini(msg);
    return false;
  }
  // posecef
  if (!geometry_msgs__msg__Point__init(&msg->posecef)) {
    vectornav_msgs__msg__InsGroup__fini(msg);
    return false;
  }
  // velbody
  if (!geometry_msgs__msg__Vector3__init(&msg->velbody)) {
    vectornav_msgs__msg__InsGroup__fini(msg);
    return false;
  }
  // velned
  if (!geometry_msgs__msg__Vector3__init(&msg->velned)) {
    vectornav_msgs__msg__InsGroup__fini(msg);
    return false;
  }
  // velecef
  if (!geometry_msgs__msg__Vector3__init(&msg->velecef)) {
    vectornav_msgs__msg__InsGroup__fini(msg);
    return false;
  }
  // magecef
  if (!geometry_msgs__msg__Vector3__init(&msg->magecef)) {
    vectornav_msgs__msg__InsGroup__fini(msg);
    return false;
  }
  // accelecef
  if (!geometry_msgs__msg__Vector3__init(&msg->accelecef)) {
    vectornav_msgs__msg__InsGroup__fini(msg);
    return false;
  }
  // linearaccelecef
  if (!geometry_msgs__msg__Vector3__init(&msg->linearaccelecef)) {
    vectornav_msgs__msg__InsGroup__fini(msg);
    return false;
  }
  // posu
  // velu
  return true;
}

void
vectornav_msgs__msg__InsGroup__fini(vectornav_msgs__msg__InsGroup * msg)
{
  if (!msg) {
    return;
  }
  // header
  std_msgs__msg__Header__fini(&msg->header);
  // group_fields
  // insstatus
  vectornav_msgs__msg__InsStatus__fini(&msg->insstatus);
  // poslla
  geometry_msgs__msg__Point__fini(&msg->poslla);
  // posecef
  geometry_msgs__msg__Point__fini(&msg->posecef);
  // velbody
  geometry_msgs__msg__Vector3__fini(&msg->velbody);
  // velned
  geometry_msgs__msg__Vector3__fini(&msg->velned);
  // velecef
  geometry_msgs__msg__Vector3__fini(&msg->velecef);
  // magecef
  geometry_msgs__msg__Vector3__fini(&msg->magecef);
  // accelecef
  geometry_msgs__msg__Vector3__fini(&msg->accelecef);
  // linearaccelecef
  geometry_msgs__msg__Vector3__fini(&msg->linearaccelecef);
  // posu
  // velu
}

bool
vectornav_msgs__msg__InsGroup__are_equal(const vectornav_msgs__msg__InsGroup * lhs, const vectornav_msgs__msg__InsGroup * rhs)
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
  // insstatus
  if (!vectornav_msgs__msg__InsStatus__are_equal(
      &(lhs->insstatus), &(rhs->insstatus)))
  {
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
  // velbody
  if (!geometry_msgs__msg__Vector3__are_equal(
      &(lhs->velbody), &(rhs->velbody)))
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
  // magecef
  if (!geometry_msgs__msg__Vector3__are_equal(
      &(lhs->magecef), &(rhs->magecef)))
  {
    return false;
  }
  // accelecef
  if (!geometry_msgs__msg__Vector3__are_equal(
      &(lhs->accelecef), &(rhs->accelecef)))
  {
    return false;
  }
  // linearaccelecef
  if (!geometry_msgs__msg__Vector3__are_equal(
      &(lhs->linearaccelecef), &(rhs->linearaccelecef)))
  {
    return false;
  }
  // posu
  if (lhs->posu != rhs->posu) {
    return false;
  }
  // velu
  if (lhs->velu != rhs->velu) {
    return false;
  }
  return true;
}

bool
vectornav_msgs__msg__InsGroup__copy(
  const vectornav_msgs__msg__InsGroup * input,
  vectornav_msgs__msg__InsGroup * output)
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
  // insstatus
  if (!vectornav_msgs__msg__InsStatus__copy(
      &(input->insstatus), &(output->insstatus)))
  {
    return false;
  }
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
  // velbody
  if (!geometry_msgs__msg__Vector3__copy(
      &(input->velbody), &(output->velbody)))
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
  // magecef
  if (!geometry_msgs__msg__Vector3__copy(
      &(input->magecef), &(output->magecef)))
  {
    return false;
  }
  // accelecef
  if (!geometry_msgs__msg__Vector3__copy(
      &(input->accelecef), &(output->accelecef)))
  {
    return false;
  }
  // linearaccelecef
  if (!geometry_msgs__msg__Vector3__copy(
      &(input->linearaccelecef), &(output->linearaccelecef)))
  {
    return false;
  }
  // posu
  output->posu = input->posu;
  // velu
  output->velu = input->velu;
  return true;
}

vectornav_msgs__msg__InsGroup *
vectornav_msgs__msg__InsGroup__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  vectornav_msgs__msg__InsGroup * msg = (vectornav_msgs__msg__InsGroup *)allocator.allocate(sizeof(vectornav_msgs__msg__InsGroup), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(vectornav_msgs__msg__InsGroup));
  bool success = vectornav_msgs__msg__InsGroup__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
vectornav_msgs__msg__InsGroup__destroy(vectornav_msgs__msg__InsGroup * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    vectornav_msgs__msg__InsGroup__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
vectornav_msgs__msg__InsGroup__Sequence__init(vectornav_msgs__msg__InsGroup__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  vectornav_msgs__msg__InsGroup * data = NULL;

  if (size) {
    data = (vectornav_msgs__msg__InsGroup *)allocator.zero_allocate(size, sizeof(vectornav_msgs__msg__InsGroup), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = vectornav_msgs__msg__InsGroup__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        vectornav_msgs__msg__InsGroup__fini(&data[i - 1]);
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
vectornav_msgs__msg__InsGroup__Sequence__fini(vectornav_msgs__msg__InsGroup__Sequence * array)
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
      vectornav_msgs__msg__InsGroup__fini(&array->data[i]);
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

vectornav_msgs__msg__InsGroup__Sequence *
vectornav_msgs__msg__InsGroup__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  vectornav_msgs__msg__InsGroup__Sequence * array = (vectornav_msgs__msg__InsGroup__Sequence *)allocator.allocate(sizeof(vectornav_msgs__msg__InsGroup__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = vectornav_msgs__msg__InsGroup__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
vectornav_msgs__msg__InsGroup__Sequence__destroy(vectornav_msgs__msg__InsGroup__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    vectornav_msgs__msg__InsGroup__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
vectornav_msgs__msg__InsGroup__Sequence__are_equal(const vectornav_msgs__msg__InsGroup__Sequence * lhs, const vectornav_msgs__msg__InsGroup__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!vectornav_msgs__msg__InsGroup__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
vectornav_msgs__msg__InsGroup__Sequence__copy(
  const vectornav_msgs__msg__InsGroup__Sequence * input,
  vectornav_msgs__msg__InsGroup__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(vectornav_msgs__msg__InsGroup);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    vectornav_msgs__msg__InsGroup * data =
      (vectornav_msgs__msg__InsGroup *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!vectornav_msgs__msg__InsGroup__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          vectornav_msgs__msg__InsGroup__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!vectornav_msgs__msg__InsGroup__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
