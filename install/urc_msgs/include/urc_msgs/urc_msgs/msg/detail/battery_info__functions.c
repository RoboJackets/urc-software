// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from urc_msgs:msg/BatteryInfo.idl
// generated code does not contain a copyright notice
#include "urc_msgs/msg/detail/battery_info__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `cell_voltages`
#include "rosidl_runtime_c/primitives_sequence_functions.h"

bool
urc_msgs__msg__BatteryInfo__init(urc_msgs__msg__BatteryInfo * msg)
{
  if (!msg) {
    return false;
  }
  // cell_voltage
  // cell_charge_percentage
  // cell_discharge_current
  // cell_temperature
  // cell_voltages
  if (!rosidl_runtime_c__float__Sequence__init(&msg->cell_voltages, 0)) {
    urc_msgs__msg__BatteryInfo__fini(msg);
    return false;
  }
  return true;
}

void
urc_msgs__msg__BatteryInfo__fini(urc_msgs__msg__BatteryInfo * msg)
{
  if (!msg) {
    return;
  }
  // cell_voltage
  // cell_charge_percentage
  // cell_discharge_current
  // cell_temperature
  // cell_voltages
  rosidl_runtime_c__float__Sequence__fini(&msg->cell_voltages);
}

bool
urc_msgs__msg__BatteryInfo__are_equal(const urc_msgs__msg__BatteryInfo * lhs, const urc_msgs__msg__BatteryInfo * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // cell_voltage
  if (lhs->cell_voltage != rhs->cell_voltage) {
    return false;
  }
  // cell_charge_percentage
  if (lhs->cell_charge_percentage != rhs->cell_charge_percentage) {
    return false;
  }
  // cell_discharge_current
  if (lhs->cell_discharge_current != rhs->cell_discharge_current) {
    return false;
  }
  // cell_temperature
  if (lhs->cell_temperature != rhs->cell_temperature) {
    return false;
  }
  // cell_voltages
  if (!rosidl_runtime_c__float__Sequence__are_equal(
      &(lhs->cell_voltages), &(rhs->cell_voltages)))
  {
    return false;
  }
  return true;
}

bool
urc_msgs__msg__BatteryInfo__copy(
  const urc_msgs__msg__BatteryInfo * input,
  urc_msgs__msg__BatteryInfo * output)
{
  if (!input || !output) {
    return false;
  }
  // cell_voltage
  output->cell_voltage = input->cell_voltage;
  // cell_charge_percentage
  output->cell_charge_percentage = input->cell_charge_percentage;
  // cell_discharge_current
  output->cell_discharge_current = input->cell_discharge_current;
  // cell_temperature
  output->cell_temperature = input->cell_temperature;
  // cell_voltages
  if (!rosidl_runtime_c__float__Sequence__copy(
      &(input->cell_voltages), &(output->cell_voltages)))
  {
    return false;
  }
  return true;
}

urc_msgs__msg__BatteryInfo *
urc_msgs__msg__BatteryInfo__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  urc_msgs__msg__BatteryInfo * msg = (urc_msgs__msg__BatteryInfo *)allocator.allocate(sizeof(urc_msgs__msg__BatteryInfo), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(urc_msgs__msg__BatteryInfo));
  bool success = urc_msgs__msg__BatteryInfo__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
urc_msgs__msg__BatteryInfo__destroy(urc_msgs__msg__BatteryInfo * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    urc_msgs__msg__BatteryInfo__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
urc_msgs__msg__BatteryInfo__Sequence__init(urc_msgs__msg__BatteryInfo__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  urc_msgs__msg__BatteryInfo * data = NULL;

  if (size) {
    data = (urc_msgs__msg__BatteryInfo *)allocator.zero_allocate(size, sizeof(urc_msgs__msg__BatteryInfo), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = urc_msgs__msg__BatteryInfo__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        urc_msgs__msg__BatteryInfo__fini(&data[i - 1]);
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
urc_msgs__msg__BatteryInfo__Sequence__fini(urc_msgs__msg__BatteryInfo__Sequence * array)
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
      urc_msgs__msg__BatteryInfo__fini(&array->data[i]);
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

urc_msgs__msg__BatteryInfo__Sequence *
urc_msgs__msg__BatteryInfo__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  urc_msgs__msg__BatteryInfo__Sequence * array = (urc_msgs__msg__BatteryInfo__Sequence *)allocator.allocate(sizeof(urc_msgs__msg__BatteryInfo__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = urc_msgs__msg__BatteryInfo__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
urc_msgs__msg__BatteryInfo__Sequence__destroy(urc_msgs__msg__BatteryInfo__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    urc_msgs__msg__BatteryInfo__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
urc_msgs__msg__BatteryInfo__Sequence__are_equal(const urc_msgs__msg__BatteryInfo__Sequence * lhs, const urc_msgs__msg__BatteryInfo__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!urc_msgs__msg__BatteryInfo__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
urc_msgs__msg__BatteryInfo__Sequence__copy(
  const urc_msgs__msg__BatteryInfo__Sequence * input,
  urc_msgs__msg__BatteryInfo__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(urc_msgs__msg__BatteryInfo);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    urc_msgs__msg__BatteryInfo * data =
      (urc_msgs__msg__BatteryInfo *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!urc_msgs__msg__BatteryInfo__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          urc_msgs__msg__BatteryInfo__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!urc_msgs__msg__BatteryInfo__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
