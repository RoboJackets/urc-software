// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from vectornav_msgs:msg/VpeStatus.idl
// generated code does not contain a copyright notice
#include "vectornav_msgs/msg/detail/vpe_status__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


bool
vectornav_msgs__msg__VpeStatus__init(vectornav_msgs__msg__VpeStatus * msg)
{
  if (!msg) {
    return false;
  }
  // attitude_quality
  // gyro_saturation
  // gyro_saturation_recovery
  // mag_disturbance
  // mag_saturation
  // acc_disturbance
  // acc_saturation
  // known_mag_disturbance
  // known_accel_disturbance
  return true;
}

void
vectornav_msgs__msg__VpeStatus__fini(vectornav_msgs__msg__VpeStatus * msg)
{
  if (!msg) {
    return;
  }
  // attitude_quality
  // gyro_saturation
  // gyro_saturation_recovery
  // mag_disturbance
  // mag_saturation
  // acc_disturbance
  // acc_saturation
  // known_mag_disturbance
  // known_accel_disturbance
}

bool
vectornav_msgs__msg__VpeStatus__are_equal(const vectornav_msgs__msg__VpeStatus * lhs, const vectornav_msgs__msg__VpeStatus * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // attitude_quality
  if (lhs->attitude_quality != rhs->attitude_quality) {
    return false;
  }
  // gyro_saturation
  if (lhs->gyro_saturation != rhs->gyro_saturation) {
    return false;
  }
  // gyro_saturation_recovery
  if (lhs->gyro_saturation_recovery != rhs->gyro_saturation_recovery) {
    return false;
  }
  // mag_disturbance
  if (lhs->mag_disturbance != rhs->mag_disturbance) {
    return false;
  }
  // mag_saturation
  if (lhs->mag_saturation != rhs->mag_saturation) {
    return false;
  }
  // acc_disturbance
  if (lhs->acc_disturbance != rhs->acc_disturbance) {
    return false;
  }
  // acc_saturation
  if (lhs->acc_saturation != rhs->acc_saturation) {
    return false;
  }
  // known_mag_disturbance
  if (lhs->known_mag_disturbance != rhs->known_mag_disturbance) {
    return false;
  }
  // known_accel_disturbance
  if (lhs->known_accel_disturbance != rhs->known_accel_disturbance) {
    return false;
  }
  return true;
}

bool
vectornav_msgs__msg__VpeStatus__copy(
  const vectornav_msgs__msg__VpeStatus * input,
  vectornav_msgs__msg__VpeStatus * output)
{
  if (!input || !output) {
    return false;
  }
  // attitude_quality
  output->attitude_quality = input->attitude_quality;
  // gyro_saturation
  output->gyro_saturation = input->gyro_saturation;
  // gyro_saturation_recovery
  output->gyro_saturation_recovery = input->gyro_saturation_recovery;
  // mag_disturbance
  output->mag_disturbance = input->mag_disturbance;
  // mag_saturation
  output->mag_saturation = input->mag_saturation;
  // acc_disturbance
  output->acc_disturbance = input->acc_disturbance;
  // acc_saturation
  output->acc_saturation = input->acc_saturation;
  // known_mag_disturbance
  output->known_mag_disturbance = input->known_mag_disturbance;
  // known_accel_disturbance
  output->known_accel_disturbance = input->known_accel_disturbance;
  return true;
}

vectornav_msgs__msg__VpeStatus *
vectornav_msgs__msg__VpeStatus__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  vectornav_msgs__msg__VpeStatus * msg = (vectornav_msgs__msg__VpeStatus *)allocator.allocate(sizeof(vectornav_msgs__msg__VpeStatus), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(vectornav_msgs__msg__VpeStatus));
  bool success = vectornav_msgs__msg__VpeStatus__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
vectornav_msgs__msg__VpeStatus__destroy(vectornav_msgs__msg__VpeStatus * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    vectornav_msgs__msg__VpeStatus__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
vectornav_msgs__msg__VpeStatus__Sequence__init(vectornav_msgs__msg__VpeStatus__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  vectornav_msgs__msg__VpeStatus * data = NULL;

  if (size) {
    data = (vectornav_msgs__msg__VpeStatus *)allocator.zero_allocate(size, sizeof(vectornav_msgs__msg__VpeStatus), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = vectornav_msgs__msg__VpeStatus__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        vectornav_msgs__msg__VpeStatus__fini(&data[i - 1]);
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
vectornav_msgs__msg__VpeStatus__Sequence__fini(vectornav_msgs__msg__VpeStatus__Sequence * array)
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
      vectornav_msgs__msg__VpeStatus__fini(&array->data[i]);
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

vectornav_msgs__msg__VpeStatus__Sequence *
vectornav_msgs__msg__VpeStatus__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  vectornav_msgs__msg__VpeStatus__Sequence * array = (vectornav_msgs__msg__VpeStatus__Sequence *)allocator.allocate(sizeof(vectornav_msgs__msg__VpeStatus__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = vectornav_msgs__msg__VpeStatus__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
vectornav_msgs__msg__VpeStatus__Sequence__destroy(vectornav_msgs__msg__VpeStatus__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    vectornav_msgs__msg__VpeStatus__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
vectornav_msgs__msg__VpeStatus__Sequence__are_equal(const vectornav_msgs__msg__VpeStatus__Sequence * lhs, const vectornav_msgs__msg__VpeStatus__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!vectornav_msgs__msg__VpeStatus__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
vectornav_msgs__msg__VpeStatus__Sequence__copy(
  const vectornav_msgs__msg__VpeStatus__Sequence * input,
  vectornav_msgs__msg__VpeStatus__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(vectornav_msgs__msg__VpeStatus);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    vectornav_msgs__msg__VpeStatus * data =
      (vectornav_msgs__msg__VpeStatus *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!vectornav_msgs__msg__VpeStatus__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          vectornav_msgs__msg__VpeStatus__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!vectornav_msgs__msg__VpeStatus__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
