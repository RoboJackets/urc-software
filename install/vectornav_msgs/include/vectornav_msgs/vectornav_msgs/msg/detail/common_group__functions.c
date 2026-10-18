// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from vectornav_msgs:msg/CommonGroup.idl
// generated code does not contain a copyright notice
#include "vectornav_msgs/msg/detail/common_group__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `header`
#include "std_msgs/msg/detail/header__functions.h"
// Member `yawpitchroll`
// Member `angularrate`
// Member `velocity`
// Member `accel`
// Member `imu_accel`
// Member `imu_rate`
// Member `magpres_mag`
// Member `deltatheta_dtheta`
// Member `deltatheta_dvel`
#include "geometry_msgs/msg/detail/vector3__functions.h"
// Member `quaternion`
#include "geometry_msgs/msg/detail/quaternion__functions.h"
// Member `position`
#include "geometry_msgs/msg/detail/point__functions.h"
// Member `insstatus`
#include "vectornav_msgs/msg/detail/ins_status__functions.h"

bool
vectornav_msgs__msg__CommonGroup__init(vectornav_msgs__msg__CommonGroup * msg)
{
  if (!msg) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__init(&msg->header)) {
    vectornav_msgs__msg__CommonGroup__fini(msg);
    return false;
  }
  // group_fields
  // timestartup
  // timegps
  // timesyncin
  // yawpitchroll
  if (!geometry_msgs__msg__Vector3__init(&msg->yawpitchroll)) {
    vectornav_msgs__msg__CommonGroup__fini(msg);
    return false;
  }
  // quaternion
  if (!geometry_msgs__msg__Quaternion__init(&msg->quaternion)) {
    vectornav_msgs__msg__CommonGroup__fini(msg);
    return false;
  }
  // angularrate
  if (!geometry_msgs__msg__Vector3__init(&msg->angularrate)) {
    vectornav_msgs__msg__CommonGroup__fini(msg);
    return false;
  }
  // position
  if (!geometry_msgs__msg__Point__init(&msg->position)) {
    vectornav_msgs__msg__CommonGroup__fini(msg);
    return false;
  }
  // velocity
  if (!geometry_msgs__msg__Vector3__init(&msg->velocity)) {
    vectornav_msgs__msg__CommonGroup__fini(msg);
    return false;
  }
  // accel
  if (!geometry_msgs__msg__Vector3__init(&msg->accel)) {
    vectornav_msgs__msg__CommonGroup__fini(msg);
    return false;
  }
  // imu_accel
  if (!geometry_msgs__msg__Vector3__init(&msg->imu_accel)) {
    vectornav_msgs__msg__CommonGroup__fini(msg);
    return false;
  }
  // imu_rate
  if (!geometry_msgs__msg__Vector3__init(&msg->imu_rate)) {
    vectornav_msgs__msg__CommonGroup__fini(msg);
    return false;
  }
  // magpres_mag
  if (!geometry_msgs__msg__Vector3__init(&msg->magpres_mag)) {
    vectornav_msgs__msg__CommonGroup__fini(msg);
    return false;
  }
  // magpres_temp
  // magpres_pres
  // deltatheta_dtime
  // deltatheta_dtheta
  if (!geometry_msgs__msg__Vector3__init(&msg->deltatheta_dtheta)) {
    vectornav_msgs__msg__CommonGroup__fini(msg);
    return false;
  }
  // deltatheta_dvel
  if (!geometry_msgs__msg__Vector3__init(&msg->deltatheta_dvel)) {
    vectornav_msgs__msg__CommonGroup__fini(msg);
    return false;
  }
  // insstatus
  if (!vectornav_msgs__msg__InsStatus__init(&msg->insstatus)) {
    vectornav_msgs__msg__CommonGroup__fini(msg);
    return false;
  }
  // syncincnt
  // timegpspps
  return true;
}

void
vectornav_msgs__msg__CommonGroup__fini(vectornav_msgs__msg__CommonGroup * msg)
{
  if (!msg) {
    return;
  }
  // header
  std_msgs__msg__Header__fini(&msg->header);
  // group_fields
  // timestartup
  // timegps
  // timesyncin
  // yawpitchroll
  geometry_msgs__msg__Vector3__fini(&msg->yawpitchroll);
  // quaternion
  geometry_msgs__msg__Quaternion__fini(&msg->quaternion);
  // angularrate
  geometry_msgs__msg__Vector3__fini(&msg->angularrate);
  // position
  geometry_msgs__msg__Point__fini(&msg->position);
  // velocity
  geometry_msgs__msg__Vector3__fini(&msg->velocity);
  // accel
  geometry_msgs__msg__Vector3__fini(&msg->accel);
  // imu_accel
  geometry_msgs__msg__Vector3__fini(&msg->imu_accel);
  // imu_rate
  geometry_msgs__msg__Vector3__fini(&msg->imu_rate);
  // magpres_mag
  geometry_msgs__msg__Vector3__fini(&msg->magpres_mag);
  // magpres_temp
  // magpres_pres
  // deltatheta_dtime
  // deltatheta_dtheta
  geometry_msgs__msg__Vector3__fini(&msg->deltatheta_dtheta);
  // deltatheta_dvel
  geometry_msgs__msg__Vector3__fini(&msg->deltatheta_dvel);
  // insstatus
  vectornav_msgs__msg__InsStatus__fini(&msg->insstatus);
  // syncincnt
  // timegpspps
}

bool
vectornav_msgs__msg__CommonGroup__are_equal(const vectornav_msgs__msg__CommonGroup * lhs, const vectornav_msgs__msg__CommonGroup * rhs)
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
  // timesyncin
  if (lhs->timesyncin != rhs->timesyncin) {
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
  // angularrate
  if (!geometry_msgs__msg__Vector3__are_equal(
      &(lhs->angularrate), &(rhs->angularrate)))
  {
    return false;
  }
  // position
  if (!geometry_msgs__msg__Point__are_equal(
      &(lhs->position), &(rhs->position)))
  {
    return false;
  }
  // velocity
  if (!geometry_msgs__msg__Vector3__are_equal(
      &(lhs->velocity), &(rhs->velocity)))
  {
    return false;
  }
  // accel
  if (!geometry_msgs__msg__Vector3__are_equal(
      &(lhs->accel), &(rhs->accel)))
  {
    return false;
  }
  // imu_accel
  if (!geometry_msgs__msg__Vector3__are_equal(
      &(lhs->imu_accel), &(rhs->imu_accel)))
  {
    return false;
  }
  // imu_rate
  if (!geometry_msgs__msg__Vector3__are_equal(
      &(lhs->imu_rate), &(rhs->imu_rate)))
  {
    return false;
  }
  // magpres_mag
  if (!geometry_msgs__msg__Vector3__are_equal(
      &(lhs->magpres_mag), &(rhs->magpres_mag)))
  {
    return false;
  }
  // magpres_temp
  if (lhs->magpres_temp != rhs->magpres_temp) {
    return false;
  }
  // magpres_pres
  if (lhs->magpres_pres != rhs->magpres_pres) {
    return false;
  }
  // deltatheta_dtime
  if (lhs->deltatheta_dtime != rhs->deltatheta_dtime) {
    return false;
  }
  // deltatheta_dtheta
  if (!geometry_msgs__msg__Vector3__are_equal(
      &(lhs->deltatheta_dtheta), &(rhs->deltatheta_dtheta)))
  {
    return false;
  }
  // deltatheta_dvel
  if (!geometry_msgs__msg__Vector3__are_equal(
      &(lhs->deltatheta_dvel), &(rhs->deltatheta_dvel)))
  {
    return false;
  }
  // insstatus
  if (!vectornav_msgs__msg__InsStatus__are_equal(
      &(lhs->insstatus), &(rhs->insstatus)))
  {
    return false;
  }
  // syncincnt
  if (lhs->syncincnt != rhs->syncincnt) {
    return false;
  }
  // timegpspps
  if (lhs->timegpspps != rhs->timegpspps) {
    return false;
  }
  return true;
}

bool
vectornav_msgs__msg__CommonGroup__copy(
  const vectornav_msgs__msg__CommonGroup * input,
  vectornav_msgs__msg__CommonGroup * output)
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
  // timesyncin
  output->timesyncin = input->timesyncin;
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
  // angularrate
  if (!geometry_msgs__msg__Vector3__copy(
      &(input->angularrate), &(output->angularrate)))
  {
    return false;
  }
  // position
  if (!geometry_msgs__msg__Point__copy(
      &(input->position), &(output->position)))
  {
    return false;
  }
  // velocity
  if (!geometry_msgs__msg__Vector3__copy(
      &(input->velocity), &(output->velocity)))
  {
    return false;
  }
  // accel
  if (!geometry_msgs__msg__Vector3__copy(
      &(input->accel), &(output->accel)))
  {
    return false;
  }
  // imu_accel
  if (!geometry_msgs__msg__Vector3__copy(
      &(input->imu_accel), &(output->imu_accel)))
  {
    return false;
  }
  // imu_rate
  if (!geometry_msgs__msg__Vector3__copy(
      &(input->imu_rate), &(output->imu_rate)))
  {
    return false;
  }
  // magpres_mag
  if (!geometry_msgs__msg__Vector3__copy(
      &(input->magpres_mag), &(output->magpres_mag)))
  {
    return false;
  }
  // magpres_temp
  output->magpres_temp = input->magpres_temp;
  // magpres_pres
  output->magpres_pres = input->magpres_pres;
  // deltatheta_dtime
  output->deltatheta_dtime = input->deltatheta_dtime;
  // deltatheta_dtheta
  if (!geometry_msgs__msg__Vector3__copy(
      &(input->deltatheta_dtheta), &(output->deltatheta_dtheta)))
  {
    return false;
  }
  // deltatheta_dvel
  if (!geometry_msgs__msg__Vector3__copy(
      &(input->deltatheta_dvel), &(output->deltatheta_dvel)))
  {
    return false;
  }
  // insstatus
  if (!vectornav_msgs__msg__InsStatus__copy(
      &(input->insstatus), &(output->insstatus)))
  {
    return false;
  }
  // syncincnt
  output->syncincnt = input->syncincnt;
  // timegpspps
  output->timegpspps = input->timegpspps;
  return true;
}

vectornav_msgs__msg__CommonGroup *
vectornav_msgs__msg__CommonGroup__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  vectornav_msgs__msg__CommonGroup * msg = (vectornav_msgs__msg__CommonGroup *)allocator.allocate(sizeof(vectornav_msgs__msg__CommonGroup), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(vectornav_msgs__msg__CommonGroup));
  bool success = vectornav_msgs__msg__CommonGroup__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
vectornav_msgs__msg__CommonGroup__destroy(vectornav_msgs__msg__CommonGroup * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    vectornav_msgs__msg__CommonGroup__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
vectornav_msgs__msg__CommonGroup__Sequence__init(vectornav_msgs__msg__CommonGroup__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  vectornav_msgs__msg__CommonGroup * data = NULL;

  if (size) {
    data = (vectornav_msgs__msg__CommonGroup *)allocator.zero_allocate(size, sizeof(vectornav_msgs__msg__CommonGroup), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = vectornav_msgs__msg__CommonGroup__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        vectornav_msgs__msg__CommonGroup__fini(&data[i - 1]);
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
vectornav_msgs__msg__CommonGroup__Sequence__fini(vectornav_msgs__msg__CommonGroup__Sequence * array)
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
      vectornav_msgs__msg__CommonGroup__fini(&array->data[i]);
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

vectornav_msgs__msg__CommonGroup__Sequence *
vectornav_msgs__msg__CommonGroup__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  vectornav_msgs__msg__CommonGroup__Sequence * array = (vectornav_msgs__msg__CommonGroup__Sequence *)allocator.allocate(sizeof(vectornav_msgs__msg__CommonGroup__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = vectornav_msgs__msg__CommonGroup__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
vectornav_msgs__msg__CommonGroup__Sequence__destroy(vectornav_msgs__msg__CommonGroup__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    vectornav_msgs__msg__CommonGroup__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
vectornav_msgs__msg__CommonGroup__Sequence__are_equal(const vectornav_msgs__msg__CommonGroup__Sequence * lhs, const vectornav_msgs__msg__CommonGroup__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!vectornav_msgs__msg__CommonGroup__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
vectornav_msgs__msg__CommonGroup__Sequence__copy(
  const vectornav_msgs__msg__CommonGroup__Sequence * input,
  vectornav_msgs__msg__CommonGroup__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(vectornav_msgs__msg__CommonGroup);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    vectornav_msgs__msg__CommonGroup * data =
      (vectornav_msgs__msg__CommonGroup *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!vectornav_msgs__msg__CommonGroup__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          vectornav_msgs__msg__CommonGroup__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!vectornav_msgs__msg__CommonGroup__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
