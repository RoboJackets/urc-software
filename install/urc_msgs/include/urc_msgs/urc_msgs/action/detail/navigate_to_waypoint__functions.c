// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from urc_msgs:action/NavigateToWaypoint.idl
// generated code does not contain a copyright notice
#include "urc_msgs/action/detail/navigate_to_waypoint__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `path`
#include "nav_msgs/msg/detail/path__functions.h"
// Member `goal`
#include "geometry_msgs/msg/detail/pose_stamped__functions.h"

bool
urc_msgs__action__NavigateToWaypoint_Goal__init(urc_msgs__action__NavigateToWaypoint_Goal * msg)
{
  if (!msg) {
    return false;
  }
  // path
  if (!nav_msgs__msg__Path__init(&msg->path)) {
    urc_msgs__action__NavigateToWaypoint_Goal__fini(msg);
    return false;
  }
  // goal
  if (!geometry_msgs__msg__PoseStamped__init(&msg->goal)) {
    urc_msgs__action__NavigateToWaypoint_Goal__fini(msg);
    return false;
  }
  // has_path
  // has_goal
  // enforce_goal_heading
  return true;
}

void
urc_msgs__action__NavigateToWaypoint_Goal__fini(urc_msgs__action__NavigateToWaypoint_Goal * msg)
{
  if (!msg) {
    return;
  }
  // path
  nav_msgs__msg__Path__fini(&msg->path);
  // goal
  geometry_msgs__msg__PoseStamped__fini(&msg->goal);
  // has_path
  // has_goal
  // enforce_goal_heading
}

bool
urc_msgs__action__NavigateToWaypoint_Goal__are_equal(const urc_msgs__action__NavigateToWaypoint_Goal * lhs, const urc_msgs__action__NavigateToWaypoint_Goal * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // path
  if (!nav_msgs__msg__Path__are_equal(
      &(lhs->path), &(rhs->path)))
  {
    return false;
  }
  // goal
  if (!geometry_msgs__msg__PoseStamped__are_equal(
      &(lhs->goal), &(rhs->goal)))
  {
    return false;
  }
  // has_path
  if (lhs->has_path != rhs->has_path) {
    return false;
  }
  // has_goal
  if (lhs->has_goal != rhs->has_goal) {
    return false;
  }
  // enforce_goal_heading
  if (lhs->enforce_goal_heading != rhs->enforce_goal_heading) {
    return false;
  }
  return true;
}

bool
urc_msgs__action__NavigateToWaypoint_Goal__copy(
  const urc_msgs__action__NavigateToWaypoint_Goal * input,
  urc_msgs__action__NavigateToWaypoint_Goal * output)
{
  if (!input || !output) {
    return false;
  }
  // path
  if (!nav_msgs__msg__Path__copy(
      &(input->path), &(output->path)))
  {
    return false;
  }
  // goal
  if (!geometry_msgs__msg__PoseStamped__copy(
      &(input->goal), &(output->goal)))
  {
    return false;
  }
  // has_path
  output->has_path = input->has_path;
  // has_goal
  output->has_goal = input->has_goal;
  // enforce_goal_heading
  output->enforce_goal_heading = input->enforce_goal_heading;
  return true;
}

urc_msgs__action__NavigateToWaypoint_Goal *
urc_msgs__action__NavigateToWaypoint_Goal__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  urc_msgs__action__NavigateToWaypoint_Goal * msg = (urc_msgs__action__NavigateToWaypoint_Goal *)allocator.allocate(sizeof(urc_msgs__action__NavigateToWaypoint_Goal), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(urc_msgs__action__NavigateToWaypoint_Goal));
  bool success = urc_msgs__action__NavigateToWaypoint_Goal__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
urc_msgs__action__NavigateToWaypoint_Goal__destroy(urc_msgs__action__NavigateToWaypoint_Goal * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    urc_msgs__action__NavigateToWaypoint_Goal__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
urc_msgs__action__NavigateToWaypoint_Goal__Sequence__init(urc_msgs__action__NavigateToWaypoint_Goal__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  urc_msgs__action__NavigateToWaypoint_Goal * data = NULL;

  if (size) {
    data = (urc_msgs__action__NavigateToWaypoint_Goal *)allocator.zero_allocate(size, sizeof(urc_msgs__action__NavigateToWaypoint_Goal), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = urc_msgs__action__NavigateToWaypoint_Goal__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        urc_msgs__action__NavigateToWaypoint_Goal__fini(&data[i - 1]);
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
urc_msgs__action__NavigateToWaypoint_Goal__Sequence__fini(urc_msgs__action__NavigateToWaypoint_Goal__Sequence * array)
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
      urc_msgs__action__NavigateToWaypoint_Goal__fini(&array->data[i]);
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

urc_msgs__action__NavigateToWaypoint_Goal__Sequence *
urc_msgs__action__NavigateToWaypoint_Goal__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  urc_msgs__action__NavigateToWaypoint_Goal__Sequence * array = (urc_msgs__action__NavigateToWaypoint_Goal__Sequence *)allocator.allocate(sizeof(urc_msgs__action__NavigateToWaypoint_Goal__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = urc_msgs__action__NavigateToWaypoint_Goal__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
urc_msgs__action__NavigateToWaypoint_Goal__Sequence__destroy(urc_msgs__action__NavigateToWaypoint_Goal__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    urc_msgs__action__NavigateToWaypoint_Goal__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
urc_msgs__action__NavigateToWaypoint_Goal__Sequence__are_equal(const urc_msgs__action__NavigateToWaypoint_Goal__Sequence * lhs, const urc_msgs__action__NavigateToWaypoint_Goal__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!urc_msgs__action__NavigateToWaypoint_Goal__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
urc_msgs__action__NavigateToWaypoint_Goal__Sequence__copy(
  const urc_msgs__action__NavigateToWaypoint_Goal__Sequence * input,
  urc_msgs__action__NavigateToWaypoint_Goal__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(urc_msgs__action__NavigateToWaypoint_Goal);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    urc_msgs__action__NavigateToWaypoint_Goal * data =
      (urc_msgs__action__NavigateToWaypoint_Goal *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!urc_msgs__action__NavigateToWaypoint_Goal__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          urc_msgs__action__NavigateToWaypoint_Goal__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!urc_msgs__action__NavigateToWaypoint_Goal__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


// Include directives for member types
// Member `result`
#include "std_msgs/msg/detail/empty__functions.h"

bool
urc_msgs__action__NavigateToWaypoint_Result__init(urc_msgs__action__NavigateToWaypoint_Result * msg)
{
  if (!msg) {
    return false;
  }
  // result
  if (!std_msgs__msg__Empty__init(&msg->result)) {
    urc_msgs__action__NavigateToWaypoint_Result__fini(msg);
    return false;
  }
  // error_code
  return true;
}

void
urc_msgs__action__NavigateToWaypoint_Result__fini(urc_msgs__action__NavigateToWaypoint_Result * msg)
{
  if (!msg) {
    return;
  }
  // result
  std_msgs__msg__Empty__fini(&msg->result);
  // error_code
}

bool
urc_msgs__action__NavigateToWaypoint_Result__are_equal(const urc_msgs__action__NavigateToWaypoint_Result * lhs, const urc_msgs__action__NavigateToWaypoint_Result * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // result
  if (!std_msgs__msg__Empty__are_equal(
      &(lhs->result), &(rhs->result)))
  {
    return false;
  }
  // error_code
  if (lhs->error_code != rhs->error_code) {
    return false;
  }
  return true;
}

bool
urc_msgs__action__NavigateToWaypoint_Result__copy(
  const urc_msgs__action__NavigateToWaypoint_Result * input,
  urc_msgs__action__NavigateToWaypoint_Result * output)
{
  if (!input || !output) {
    return false;
  }
  // result
  if (!std_msgs__msg__Empty__copy(
      &(input->result), &(output->result)))
  {
    return false;
  }
  // error_code
  output->error_code = input->error_code;
  return true;
}

urc_msgs__action__NavigateToWaypoint_Result *
urc_msgs__action__NavigateToWaypoint_Result__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  urc_msgs__action__NavigateToWaypoint_Result * msg = (urc_msgs__action__NavigateToWaypoint_Result *)allocator.allocate(sizeof(urc_msgs__action__NavigateToWaypoint_Result), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(urc_msgs__action__NavigateToWaypoint_Result));
  bool success = urc_msgs__action__NavigateToWaypoint_Result__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
urc_msgs__action__NavigateToWaypoint_Result__destroy(urc_msgs__action__NavigateToWaypoint_Result * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    urc_msgs__action__NavigateToWaypoint_Result__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
urc_msgs__action__NavigateToWaypoint_Result__Sequence__init(urc_msgs__action__NavigateToWaypoint_Result__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  urc_msgs__action__NavigateToWaypoint_Result * data = NULL;

  if (size) {
    data = (urc_msgs__action__NavigateToWaypoint_Result *)allocator.zero_allocate(size, sizeof(urc_msgs__action__NavigateToWaypoint_Result), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = urc_msgs__action__NavigateToWaypoint_Result__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        urc_msgs__action__NavigateToWaypoint_Result__fini(&data[i - 1]);
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
urc_msgs__action__NavigateToWaypoint_Result__Sequence__fini(urc_msgs__action__NavigateToWaypoint_Result__Sequence * array)
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
      urc_msgs__action__NavigateToWaypoint_Result__fini(&array->data[i]);
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

urc_msgs__action__NavigateToWaypoint_Result__Sequence *
urc_msgs__action__NavigateToWaypoint_Result__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  urc_msgs__action__NavigateToWaypoint_Result__Sequence * array = (urc_msgs__action__NavigateToWaypoint_Result__Sequence *)allocator.allocate(sizeof(urc_msgs__action__NavigateToWaypoint_Result__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = urc_msgs__action__NavigateToWaypoint_Result__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
urc_msgs__action__NavigateToWaypoint_Result__Sequence__destroy(urc_msgs__action__NavigateToWaypoint_Result__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    urc_msgs__action__NavigateToWaypoint_Result__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
urc_msgs__action__NavigateToWaypoint_Result__Sequence__are_equal(const urc_msgs__action__NavigateToWaypoint_Result__Sequence * lhs, const urc_msgs__action__NavigateToWaypoint_Result__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!urc_msgs__action__NavigateToWaypoint_Result__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
urc_msgs__action__NavigateToWaypoint_Result__Sequence__copy(
  const urc_msgs__action__NavigateToWaypoint_Result__Sequence * input,
  urc_msgs__action__NavigateToWaypoint_Result__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(urc_msgs__action__NavigateToWaypoint_Result);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    urc_msgs__action__NavigateToWaypoint_Result * data =
      (urc_msgs__action__NavigateToWaypoint_Result *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!urc_msgs__action__NavigateToWaypoint_Result__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          urc_msgs__action__NavigateToWaypoint_Result__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!urc_msgs__action__NavigateToWaypoint_Result__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


bool
urc_msgs__action__NavigateToWaypoint_Feedback__init(urc_msgs__action__NavigateToWaypoint_Feedback * msg)
{
  if (!msg) {
    return false;
  }
  // distance_to_goal
  // is_planning
  // replan_count
  return true;
}

void
urc_msgs__action__NavigateToWaypoint_Feedback__fini(urc_msgs__action__NavigateToWaypoint_Feedback * msg)
{
  if (!msg) {
    return;
  }
  // distance_to_goal
  // is_planning
  // replan_count
}

bool
urc_msgs__action__NavigateToWaypoint_Feedback__are_equal(const urc_msgs__action__NavigateToWaypoint_Feedback * lhs, const urc_msgs__action__NavigateToWaypoint_Feedback * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // distance_to_goal
  if (lhs->distance_to_goal != rhs->distance_to_goal) {
    return false;
  }
  // is_planning
  if (lhs->is_planning != rhs->is_planning) {
    return false;
  }
  // replan_count
  if (lhs->replan_count != rhs->replan_count) {
    return false;
  }
  return true;
}

bool
urc_msgs__action__NavigateToWaypoint_Feedback__copy(
  const urc_msgs__action__NavigateToWaypoint_Feedback * input,
  urc_msgs__action__NavigateToWaypoint_Feedback * output)
{
  if (!input || !output) {
    return false;
  }
  // distance_to_goal
  output->distance_to_goal = input->distance_to_goal;
  // is_planning
  output->is_planning = input->is_planning;
  // replan_count
  output->replan_count = input->replan_count;
  return true;
}

urc_msgs__action__NavigateToWaypoint_Feedback *
urc_msgs__action__NavigateToWaypoint_Feedback__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  urc_msgs__action__NavigateToWaypoint_Feedback * msg = (urc_msgs__action__NavigateToWaypoint_Feedback *)allocator.allocate(sizeof(urc_msgs__action__NavigateToWaypoint_Feedback), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(urc_msgs__action__NavigateToWaypoint_Feedback));
  bool success = urc_msgs__action__NavigateToWaypoint_Feedback__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
urc_msgs__action__NavigateToWaypoint_Feedback__destroy(urc_msgs__action__NavigateToWaypoint_Feedback * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    urc_msgs__action__NavigateToWaypoint_Feedback__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
urc_msgs__action__NavigateToWaypoint_Feedback__Sequence__init(urc_msgs__action__NavigateToWaypoint_Feedback__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  urc_msgs__action__NavigateToWaypoint_Feedback * data = NULL;

  if (size) {
    data = (urc_msgs__action__NavigateToWaypoint_Feedback *)allocator.zero_allocate(size, sizeof(urc_msgs__action__NavigateToWaypoint_Feedback), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = urc_msgs__action__NavigateToWaypoint_Feedback__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        urc_msgs__action__NavigateToWaypoint_Feedback__fini(&data[i - 1]);
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
urc_msgs__action__NavigateToWaypoint_Feedback__Sequence__fini(urc_msgs__action__NavigateToWaypoint_Feedback__Sequence * array)
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
      urc_msgs__action__NavigateToWaypoint_Feedback__fini(&array->data[i]);
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

urc_msgs__action__NavigateToWaypoint_Feedback__Sequence *
urc_msgs__action__NavigateToWaypoint_Feedback__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  urc_msgs__action__NavigateToWaypoint_Feedback__Sequence * array = (urc_msgs__action__NavigateToWaypoint_Feedback__Sequence *)allocator.allocate(sizeof(urc_msgs__action__NavigateToWaypoint_Feedback__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = urc_msgs__action__NavigateToWaypoint_Feedback__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
urc_msgs__action__NavigateToWaypoint_Feedback__Sequence__destroy(urc_msgs__action__NavigateToWaypoint_Feedback__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    urc_msgs__action__NavigateToWaypoint_Feedback__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
urc_msgs__action__NavigateToWaypoint_Feedback__Sequence__are_equal(const urc_msgs__action__NavigateToWaypoint_Feedback__Sequence * lhs, const urc_msgs__action__NavigateToWaypoint_Feedback__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!urc_msgs__action__NavigateToWaypoint_Feedback__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
urc_msgs__action__NavigateToWaypoint_Feedback__Sequence__copy(
  const urc_msgs__action__NavigateToWaypoint_Feedback__Sequence * input,
  urc_msgs__action__NavigateToWaypoint_Feedback__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(urc_msgs__action__NavigateToWaypoint_Feedback);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    urc_msgs__action__NavigateToWaypoint_Feedback * data =
      (urc_msgs__action__NavigateToWaypoint_Feedback *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!urc_msgs__action__NavigateToWaypoint_Feedback__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          urc_msgs__action__NavigateToWaypoint_Feedback__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!urc_msgs__action__NavigateToWaypoint_Feedback__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


// Include directives for member types
// Member `goal_id`
#include "unique_identifier_msgs/msg/detail/uuid__functions.h"
// Member `goal`
// already included above
// #include "urc_msgs/action/detail/navigate_to_waypoint__functions.h"

bool
urc_msgs__action__NavigateToWaypoint_SendGoal_Request__init(urc_msgs__action__NavigateToWaypoint_SendGoal_Request * msg)
{
  if (!msg) {
    return false;
  }
  // goal_id
  if (!unique_identifier_msgs__msg__UUID__init(&msg->goal_id)) {
    urc_msgs__action__NavigateToWaypoint_SendGoal_Request__fini(msg);
    return false;
  }
  // goal
  if (!urc_msgs__action__NavigateToWaypoint_Goal__init(&msg->goal)) {
    urc_msgs__action__NavigateToWaypoint_SendGoal_Request__fini(msg);
    return false;
  }
  return true;
}

void
urc_msgs__action__NavigateToWaypoint_SendGoal_Request__fini(urc_msgs__action__NavigateToWaypoint_SendGoal_Request * msg)
{
  if (!msg) {
    return;
  }
  // goal_id
  unique_identifier_msgs__msg__UUID__fini(&msg->goal_id);
  // goal
  urc_msgs__action__NavigateToWaypoint_Goal__fini(&msg->goal);
}

bool
urc_msgs__action__NavigateToWaypoint_SendGoal_Request__are_equal(const urc_msgs__action__NavigateToWaypoint_SendGoal_Request * lhs, const urc_msgs__action__NavigateToWaypoint_SendGoal_Request * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // goal_id
  if (!unique_identifier_msgs__msg__UUID__are_equal(
      &(lhs->goal_id), &(rhs->goal_id)))
  {
    return false;
  }
  // goal
  if (!urc_msgs__action__NavigateToWaypoint_Goal__are_equal(
      &(lhs->goal), &(rhs->goal)))
  {
    return false;
  }
  return true;
}

bool
urc_msgs__action__NavigateToWaypoint_SendGoal_Request__copy(
  const urc_msgs__action__NavigateToWaypoint_SendGoal_Request * input,
  urc_msgs__action__NavigateToWaypoint_SendGoal_Request * output)
{
  if (!input || !output) {
    return false;
  }
  // goal_id
  if (!unique_identifier_msgs__msg__UUID__copy(
      &(input->goal_id), &(output->goal_id)))
  {
    return false;
  }
  // goal
  if (!urc_msgs__action__NavigateToWaypoint_Goal__copy(
      &(input->goal), &(output->goal)))
  {
    return false;
  }
  return true;
}

urc_msgs__action__NavigateToWaypoint_SendGoal_Request *
urc_msgs__action__NavigateToWaypoint_SendGoal_Request__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  urc_msgs__action__NavigateToWaypoint_SendGoal_Request * msg = (urc_msgs__action__NavigateToWaypoint_SendGoal_Request *)allocator.allocate(sizeof(urc_msgs__action__NavigateToWaypoint_SendGoal_Request), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(urc_msgs__action__NavigateToWaypoint_SendGoal_Request));
  bool success = urc_msgs__action__NavigateToWaypoint_SendGoal_Request__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
urc_msgs__action__NavigateToWaypoint_SendGoal_Request__destroy(urc_msgs__action__NavigateToWaypoint_SendGoal_Request * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    urc_msgs__action__NavigateToWaypoint_SendGoal_Request__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
urc_msgs__action__NavigateToWaypoint_SendGoal_Request__Sequence__init(urc_msgs__action__NavigateToWaypoint_SendGoal_Request__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  urc_msgs__action__NavigateToWaypoint_SendGoal_Request * data = NULL;

  if (size) {
    data = (urc_msgs__action__NavigateToWaypoint_SendGoal_Request *)allocator.zero_allocate(size, sizeof(urc_msgs__action__NavigateToWaypoint_SendGoal_Request), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = urc_msgs__action__NavigateToWaypoint_SendGoal_Request__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        urc_msgs__action__NavigateToWaypoint_SendGoal_Request__fini(&data[i - 1]);
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
urc_msgs__action__NavigateToWaypoint_SendGoal_Request__Sequence__fini(urc_msgs__action__NavigateToWaypoint_SendGoal_Request__Sequence * array)
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
      urc_msgs__action__NavigateToWaypoint_SendGoal_Request__fini(&array->data[i]);
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

urc_msgs__action__NavigateToWaypoint_SendGoal_Request__Sequence *
urc_msgs__action__NavigateToWaypoint_SendGoal_Request__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  urc_msgs__action__NavigateToWaypoint_SendGoal_Request__Sequence * array = (urc_msgs__action__NavigateToWaypoint_SendGoal_Request__Sequence *)allocator.allocate(sizeof(urc_msgs__action__NavigateToWaypoint_SendGoal_Request__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = urc_msgs__action__NavigateToWaypoint_SendGoal_Request__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
urc_msgs__action__NavigateToWaypoint_SendGoal_Request__Sequence__destroy(urc_msgs__action__NavigateToWaypoint_SendGoal_Request__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    urc_msgs__action__NavigateToWaypoint_SendGoal_Request__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
urc_msgs__action__NavigateToWaypoint_SendGoal_Request__Sequence__are_equal(const urc_msgs__action__NavigateToWaypoint_SendGoal_Request__Sequence * lhs, const urc_msgs__action__NavigateToWaypoint_SendGoal_Request__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!urc_msgs__action__NavigateToWaypoint_SendGoal_Request__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
urc_msgs__action__NavigateToWaypoint_SendGoal_Request__Sequence__copy(
  const urc_msgs__action__NavigateToWaypoint_SendGoal_Request__Sequence * input,
  urc_msgs__action__NavigateToWaypoint_SendGoal_Request__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(urc_msgs__action__NavigateToWaypoint_SendGoal_Request);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    urc_msgs__action__NavigateToWaypoint_SendGoal_Request * data =
      (urc_msgs__action__NavigateToWaypoint_SendGoal_Request *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!urc_msgs__action__NavigateToWaypoint_SendGoal_Request__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          urc_msgs__action__NavigateToWaypoint_SendGoal_Request__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!urc_msgs__action__NavigateToWaypoint_SendGoal_Request__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


// Include directives for member types
// Member `stamp`
#include "builtin_interfaces/msg/detail/time__functions.h"

bool
urc_msgs__action__NavigateToWaypoint_SendGoal_Response__init(urc_msgs__action__NavigateToWaypoint_SendGoal_Response * msg)
{
  if (!msg) {
    return false;
  }
  // accepted
  // stamp
  if (!builtin_interfaces__msg__Time__init(&msg->stamp)) {
    urc_msgs__action__NavigateToWaypoint_SendGoal_Response__fini(msg);
    return false;
  }
  return true;
}

void
urc_msgs__action__NavigateToWaypoint_SendGoal_Response__fini(urc_msgs__action__NavigateToWaypoint_SendGoal_Response * msg)
{
  if (!msg) {
    return;
  }
  // accepted
  // stamp
  builtin_interfaces__msg__Time__fini(&msg->stamp);
}

bool
urc_msgs__action__NavigateToWaypoint_SendGoal_Response__are_equal(const urc_msgs__action__NavigateToWaypoint_SendGoal_Response * lhs, const urc_msgs__action__NavigateToWaypoint_SendGoal_Response * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // accepted
  if (lhs->accepted != rhs->accepted) {
    return false;
  }
  // stamp
  if (!builtin_interfaces__msg__Time__are_equal(
      &(lhs->stamp), &(rhs->stamp)))
  {
    return false;
  }
  return true;
}

bool
urc_msgs__action__NavigateToWaypoint_SendGoal_Response__copy(
  const urc_msgs__action__NavigateToWaypoint_SendGoal_Response * input,
  urc_msgs__action__NavigateToWaypoint_SendGoal_Response * output)
{
  if (!input || !output) {
    return false;
  }
  // accepted
  output->accepted = input->accepted;
  // stamp
  if (!builtin_interfaces__msg__Time__copy(
      &(input->stamp), &(output->stamp)))
  {
    return false;
  }
  return true;
}

urc_msgs__action__NavigateToWaypoint_SendGoal_Response *
urc_msgs__action__NavigateToWaypoint_SendGoal_Response__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  urc_msgs__action__NavigateToWaypoint_SendGoal_Response * msg = (urc_msgs__action__NavigateToWaypoint_SendGoal_Response *)allocator.allocate(sizeof(urc_msgs__action__NavigateToWaypoint_SendGoal_Response), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(urc_msgs__action__NavigateToWaypoint_SendGoal_Response));
  bool success = urc_msgs__action__NavigateToWaypoint_SendGoal_Response__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
urc_msgs__action__NavigateToWaypoint_SendGoal_Response__destroy(urc_msgs__action__NavigateToWaypoint_SendGoal_Response * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    urc_msgs__action__NavigateToWaypoint_SendGoal_Response__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
urc_msgs__action__NavigateToWaypoint_SendGoal_Response__Sequence__init(urc_msgs__action__NavigateToWaypoint_SendGoal_Response__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  urc_msgs__action__NavigateToWaypoint_SendGoal_Response * data = NULL;

  if (size) {
    data = (urc_msgs__action__NavigateToWaypoint_SendGoal_Response *)allocator.zero_allocate(size, sizeof(urc_msgs__action__NavigateToWaypoint_SendGoal_Response), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = urc_msgs__action__NavigateToWaypoint_SendGoal_Response__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        urc_msgs__action__NavigateToWaypoint_SendGoal_Response__fini(&data[i - 1]);
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
urc_msgs__action__NavigateToWaypoint_SendGoal_Response__Sequence__fini(urc_msgs__action__NavigateToWaypoint_SendGoal_Response__Sequence * array)
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
      urc_msgs__action__NavigateToWaypoint_SendGoal_Response__fini(&array->data[i]);
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

urc_msgs__action__NavigateToWaypoint_SendGoal_Response__Sequence *
urc_msgs__action__NavigateToWaypoint_SendGoal_Response__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  urc_msgs__action__NavigateToWaypoint_SendGoal_Response__Sequence * array = (urc_msgs__action__NavigateToWaypoint_SendGoal_Response__Sequence *)allocator.allocate(sizeof(urc_msgs__action__NavigateToWaypoint_SendGoal_Response__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = urc_msgs__action__NavigateToWaypoint_SendGoal_Response__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
urc_msgs__action__NavigateToWaypoint_SendGoal_Response__Sequence__destroy(urc_msgs__action__NavigateToWaypoint_SendGoal_Response__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    urc_msgs__action__NavigateToWaypoint_SendGoal_Response__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
urc_msgs__action__NavigateToWaypoint_SendGoal_Response__Sequence__are_equal(const urc_msgs__action__NavigateToWaypoint_SendGoal_Response__Sequence * lhs, const urc_msgs__action__NavigateToWaypoint_SendGoal_Response__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!urc_msgs__action__NavigateToWaypoint_SendGoal_Response__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
urc_msgs__action__NavigateToWaypoint_SendGoal_Response__Sequence__copy(
  const urc_msgs__action__NavigateToWaypoint_SendGoal_Response__Sequence * input,
  urc_msgs__action__NavigateToWaypoint_SendGoal_Response__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(urc_msgs__action__NavigateToWaypoint_SendGoal_Response);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    urc_msgs__action__NavigateToWaypoint_SendGoal_Response * data =
      (urc_msgs__action__NavigateToWaypoint_SendGoal_Response *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!urc_msgs__action__NavigateToWaypoint_SendGoal_Response__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          urc_msgs__action__NavigateToWaypoint_SendGoal_Response__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!urc_msgs__action__NavigateToWaypoint_SendGoal_Response__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


// Include directives for member types
// Member `goal_id`
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__functions.h"

bool
urc_msgs__action__NavigateToWaypoint_GetResult_Request__init(urc_msgs__action__NavigateToWaypoint_GetResult_Request * msg)
{
  if (!msg) {
    return false;
  }
  // goal_id
  if (!unique_identifier_msgs__msg__UUID__init(&msg->goal_id)) {
    urc_msgs__action__NavigateToWaypoint_GetResult_Request__fini(msg);
    return false;
  }
  return true;
}

void
urc_msgs__action__NavigateToWaypoint_GetResult_Request__fini(urc_msgs__action__NavigateToWaypoint_GetResult_Request * msg)
{
  if (!msg) {
    return;
  }
  // goal_id
  unique_identifier_msgs__msg__UUID__fini(&msg->goal_id);
}

bool
urc_msgs__action__NavigateToWaypoint_GetResult_Request__are_equal(const urc_msgs__action__NavigateToWaypoint_GetResult_Request * lhs, const urc_msgs__action__NavigateToWaypoint_GetResult_Request * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // goal_id
  if (!unique_identifier_msgs__msg__UUID__are_equal(
      &(lhs->goal_id), &(rhs->goal_id)))
  {
    return false;
  }
  return true;
}

bool
urc_msgs__action__NavigateToWaypoint_GetResult_Request__copy(
  const urc_msgs__action__NavigateToWaypoint_GetResult_Request * input,
  urc_msgs__action__NavigateToWaypoint_GetResult_Request * output)
{
  if (!input || !output) {
    return false;
  }
  // goal_id
  if (!unique_identifier_msgs__msg__UUID__copy(
      &(input->goal_id), &(output->goal_id)))
  {
    return false;
  }
  return true;
}

urc_msgs__action__NavigateToWaypoint_GetResult_Request *
urc_msgs__action__NavigateToWaypoint_GetResult_Request__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  urc_msgs__action__NavigateToWaypoint_GetResult_Request * msg = (urc_msgs__action__NavigateToWaypoint_GetResult_Request *)allocator.allocate(sizeof(urc_msgs__action__NavigateToWaypoint_GetResult_Request), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(urc_msgs__action__NavigateToWaypoint_GetResult_Request));
  bool success = urc_msgs__action__NavigateToWaypoint_GetResult_Request__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
urc_msgs__action__NavigateToWaypoint_GetResult_Request__destroy(urc_msgs__action__NavigateToWaypoint_GetResult_Request * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    urc_msgs__action__NavigateToWaypoint_GetResult_Request__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
urc_msgs__action__NavigateToWaypoint_GetResult_Request__Sequence__init(urc_msgs__action__NavigateToWaypoint_GetResult_Request__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  urc_msgs__action__NavigateToWaypoint_GetResult_Request * data = NULL;

  if (size) {
    data = (urc_msgs__action__NavigateToWaypoint_GetResult_Request *)allocator.zero_allocate(size, sizeof(urc_msgs__action__NavigateToWaypoint_GetResult_Request), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = urc_msgs__action__NavigateToWaypoint_GetResult_Request__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        urc_msgs__action__NavigateToWaypoint_GetResult_Request__fini(&data[i - 1]);
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
urc_msgs__action__NavigateToWaypoint_GetResult_Request__Sequence__fini(urc_msgs__action__NavigateToWaypoint_GetResult_Request__Sequence * array)
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
      urc_msgs__action__NavigateToWaypoint_GetResult_Request__fini(&array->data[i]);
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

urc_msgs__action__NavigateToWaypoint_GetResult_Request__Sequence *
urc_msgs__action__NavigateToWaypoint_GetResult_Request__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  urc_msgs__action__NavigateToWaypoint_GetResult_Request__Sequence * array = (urc_msgs__action__NavigateToWaypoint_GetResult_Request__Sequence *)allocator.allocate(sizeof(urc_msgs__action__NavigateToWaypoint_GetResult_Request__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = urc_msgs__action__NavigateToWaypoint_GetResult_Request__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
urc_msgs__action__NavigateToWaypoint_GetResult_Request__Sequence__destroy(urc_msgs__action__NavigateToWaypoint_GetResult_Request__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    urc_msgs__action__NavigateToWaypoint_GetResult_Request__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
urc_msgs__action__NavigateToWaypoint_GetResult_Request__Sequence__are_equal(const urc_msgs__action__NavigateToWaypoint_GetResult_Request__Sequence * lhs, const urc_msgs__action__NavigateToWaypoint_GetResult_Request__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!urc_msgs__action__NavigateToWaypoint_GetResult_Request__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
urc_msgs__action__NavigateToWaypoint_GetResult_Request__Sequence__copy(
  const urc_msgs__action__NavigateToWaypoint_GetResult_Request__Sequence * input,
  urc_msgs__action__NavigateToWaypoint_GetResult_Request__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(urc_msgs__action__NavigateToWaypoint_GetResult_Request);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    urc_msgs__action__NavigateToWaypoint_GetResult_Request * data =
      (urc_msgs__action__NavigateToWaypoint_GetResult_Request *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!urc_msgs__action__NavigateToWaypoint_GetResult_Request__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          urc_msgs__action__NavigateToWaypoint_GetResult_Request__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!urc_msgs__action__NavigateToWaypoint_GetResult_Request__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


// Include directives for member types
// Member `result`
// already included above
// #include "urc_msgs/action/detail/navigate_to_waypoint__functions.h"

bool
urc_msgs__action__NavigateToWaypoint_GetResult_Response__init(urc_msgs__action__NavigateToWaypoint_GetResult_Response * msg)
{
  if (!msg) {
    return false;
  }
  // status
  // result
  if (!urc_msgs__action__NavigateToWaypoint_Result__init(&msg->result)) {
    urc_msgs__action__NavigateToWaypoint_GetResult_Response__fini(msg);
    return false;
  }
  return true;
}

void
urc_msgs__action__NavigateToWaypoint_GetResult_Response__fini(urc_msgs__action__NavigateToWaypoint_GetResult_Response * msg)
{
  if (!msg) {
    return;
  }
  // status
  // result
  urc_msgs__action__NavigateToWaypoint_Result__fini(&msg->result);
}

bool
urc_msgs__action__NavigateToWaypoint_GetResult_Response__are_equal(const urc_msgs__action__NavigateToWaypoint_GetResult_Response * lhs, const urc_msgs__action__NavigateToWaypoint_GetResult_Response * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // status
  if (lhs->status != rhs->status) {
    return false;
  }
  // result
  if (!urc_msgs__action__NavigateToWaypoint_Result__are_equal(
      &(lhs->result), &(rhs->result)))
  {
    return false;
  }
  return true;
}

bool
urc_msgs__action__NavigateToWaypoint_GetResult_Response__copy(
  const urc_msgs__action__NavigateToWaypoint_GetResult_Response * input,
  urc_msgs__action__NavigateToWaypoint_GetResult_Response * output)
{
  if (!input || !output) {
    return false;
  }
  // status
  output->status = input->status;
  // result
  if (!urc_msgs__action__NavigateToWaypoint_Result__copy(
      &(input->result), &(output->result)))
  {
    return false;
  }
  return true;
}

urc_msgs__action__NavigateToWaypoint_GetResult_Response *
urc_msgs__action__NavigateToWaypoint_GetResult_Response__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  urc_msgs__action__NavigateToWaypoint_GetResult_Response * msg = (urc_msgs__action__NavigateToWaypoint_GetResult_Response *)allocator.allocate(sizeof(urc_msgs__action__NavigateToWaypoint_GetResult_Response), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(urc_msgs__action__NavigateToWaypoint_GetResult_Response));
  bool success = urc_msgs__action__NavigateToWaypoint_GetResult_Response__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
urc_msgs__action__NavigateToWaypoint_GetResult_Response__destroy(urc_msgs__action__NavigateToWaypoint_GetResult_Response * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    urc_msgs__action__NavigateToWaypoint_GetResult_Response__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
urc_msgs__action__NavigateToWaypoint_GetResult_Response__Sequence__init(urc_msgs__action__NavigateToWaypoint_GetResult_Response__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  urc_msgs__action__NavigateToWaypoint_GetResult_Response * data = NULL;

  if (size) {
    data = (urc_msgs__action__NavigateToWaypoint_GetResult_Response *)allocator.zero_allocate(size, sizeof(urc_msgs__action__NavigateToWaypoint_GetResult_Response), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = urc_msgs__action__NavigateToWaypoint_GetResult_Response__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        urc_msgs__action__NavigateToWaypoint_GetResult_Response__fini(&data[i - 1]);
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
urc_msgs__action__NavigateToWaypoint_GetResult_Response__Sequence__fini(urc_msgs__action__NavigateToWaypoint_GetResult_Response__Sequence * array)
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
      urc_msgs__action__NavigateToWaypoint_GetResult_Response__fini(&array->data[i]);
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

urc_msgs__action__NavigateToWaypoint_GetResult_Response__Sequence *
urc_msgs__action__NavigateToWaypoint_GetResult_Response__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  urc_msgs__action__NavigateToWaypoint_GetResult_Response__Sequence * array = (urc_msgs__action__NavigateToWaypoint_GetResult_Response__Sequence *)allocator.allocate(sizeof(urc_msgs__action__NavigateToWaypoint_GetResult_Response__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = urc_msgs__action__NavigateToWaypoint_GetResult_Response__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
urc_msgs__action__NavigateToWaypoint_GetResult_Response__Sequence__destroy(urc_msgs__action__NavigateToWaypoint_GetResult_Response__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    urc_msgs__action__NavigateToWaypoint_GetResult_Response__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
urc_msgs__action__NavigateToWaypoint_GetResult_Response__Sequence__are_equal(const urc_msgs__action__NavigateToWaypoint_GetResult_Response__Sequence * lhs, const urc_msgs__action__NavigateToWaypoint_GetResult_Response__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!urc_msgs__action__NavigateToWaypoint_GetResult_Response__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
urc_msgs__action__NavigateToWaypoint_GetResult_Response__Sequence__copy(
  const urc_msgs__action__NavigateToWaypoint_GetResult_Response__Sequence * input,
  urc_msgs__action__NavigateToWaypoint_GetResult_Response__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(urc_msgs__action__NavigateToWaypoint_GetResult_Response);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    urc_msgs__action__NavigateToWaypoint_GetResult_Response * data =
      (urc_msgs__action__NavigateToWaypoint_GetResult_Response *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!urc_msgs__action__NavigateToWaypoint_GetResult_Response__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          urc_msgs__action__NavigateToWaypoint_GetResult_Response__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!urc_msgs__action__NavigateToWaypoint_GetResult_Response__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


// Include directives for member types
// Member `goal_id`
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__functions.h"
// Member `feedback`
// already included above
// #include "urc_msgs/action/detail/navigate_to_waypoint__functions.h"

bool
urc_msgs__action__NavigateToWaypoint_FeedbackMessage__init(urc_msgs__action__NavigateToWaypoint_FeedbackMessage * msg)
{
  if (!msg) {
    return false;
  }
  // goal_id
  if (!unique_identifier_msgs__msg__UUID__init(&msg->goal_id)) {
    urc_msgs__action__NavigateToWaypoint_FeedbackMessage__fini(msg);
    return false;
  }
  // feedback
  if (!urc_msgs__action__NavigateToWaypoint_Feedback__init(&msg->feedback)) {
    urc_msgs__action__NavigateToWaypoint_FeedbackMessage__fini(msg);
    return false;
  }
  return true;
}

void
urc_msgs__action__NavigateToWaypoint_FeedbackMessage__fini(urc_msgs__action__NavigateToWaypoint_FeedbackMessage * msg)
{
  if (!msg) {
    return;
  }
  // goal_id
  unique_identifier_msgs__msg__UUID__fini(&msg->goal_id);
  // feedback
  urc_msgs__action__NavigateToWaypoint_Feedback__fini(&msg->feedback);
}

bool
urc_msgs__action__NavigateToWaypoint_FeedbackMessage__are_equal(const urc_msgs__action__NavigateToWaypoint_FeedbackMessage * lhs, const urc_msgs__action__NavigateToWaypoint_FeedbackMessage * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // goal_id
  if (!unique_identifier_msgs__msg__UUID__are_equal(
      &(lhs->goal_id), &(rhs->goal_id)))
  {
    return false;
  }
  // feedback
  if (!urc_msgs__action__NavigateToWaypoint_Feedback__are_equal(
      &(lhs->feedback), &(rhs->feedback)))
  {
    return false;
  }
  return true;
}

bool
urc_msgs__action__NavigateToWaypoint_FeedbackMessage__copy(
  const urc_msgs__action__NavigateToWaypoint_FeedbackMessage * input,
  urc_msgs__action__NavigateToWaypoint_FeedbackMessage * output)
{
  if (!input || !output) {
    return false;
  }
  // goal_id
  if (!unique_identifier_msgs__msg__UUID__copy(
      &(input->goal_id), &(output->goal_id)))
  {
    return false;
  }
  // feedback
  if (!urc_msgs__action__NavigateToWaypoint_Feedback__copy(
      &(input->feedback), &(output->feedback)))
  {
    return false;
  }
  return true;
}

urc_msgs__action__NavigateToWaypoint_FeedbackMessage *
urc_msgs__action__NavigateToWaypoint_FeedbackMessage__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  urc_msgs__action__NavigateToWaypoint_FeedbackMessage * msg = (urc_msgs__action__NavigateToWaypoint_FeedbackMessage *)allocator.allocate(sizeof(urc_msgs__action__NavigateToWaypoint_FeedbackMessage), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(urc_msgs__action__NavigateToWaypoint_FeedbackMessage));
  bool success = urc_msgs__action__NavigateToWaypoint_FeedbackMessage__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
urc_msgs__action__NavigateToWaypoint_FeedbackMessage__destroy(urc_msgs__action__NavigateToWaypoint_FeedbackMessage * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    urc_msgs__action__NavigateToWaypoint_FeedbackMessage__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
urc_msgs__action__NavigateToWaypoint_FeedbackMessage__Sequence__init(urc_msgs__action__NavigateToWaypoint_FeedbackMessage__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  urc_msgs__action__NavigateToWaypoint_FeedbackMessage * data = NULL;

  if (size) {
    data = (urc_msgs__action__NavigateToWaypoint_FeedbackMessage *)allocator.zero_allocate(size, sizeof(urc_msgs__action__NavigateToWaypoint_FeedbackMessage), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = urc_msgs__action__NavigateToWaypoint_FeedbackMessage__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        urc_msgs__action__NavigateToWaypoint_FeedbackMessage__fini(&data[i - 1]);
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
urc_msgs__action__NavigateToWaypoint_FeedbackMessage__Sequence__fini(urc_msgs__action__NavigateToWaypoint_FeedbackMessage__Sequence * array)
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
      urc_msgs__action__NavigateToWaypoint_FeedbackMessage__fini(&array->data[i]);
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

urc_msgs__action__NavigateToWaypoint_FeedbackMessage__Sequence *
urc_msgs__action__NavigateToWaypoint_FeedbackMessage__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  urc_msgs__action__NavigateToWaypoint_FeedbackMessage__Sequence * array = (urc_msgs__action__NavigateToWaypoint_FeedbackMessage__Sequence *)allocator.allocate(sizeof(urc_msgs__action__NavigateToWaypoint_FeedbackMessage__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = urc_msgs__action__NavigateToWaypoint_FeedbackMessage__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
urc_msgs__action__NavigateToWaypoint_FeedbackMessage__Sequence__destroy(urc_msgs__action__NavigateToWaypoint_FeedbackMessage__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    urc_msgs__action__NavigateToWaypoint_FeedbackMessage__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
urc_msgs__action__NavigateToWaypoint_FeedbackMessage__Sequence__are_equal(const urc_msgs__action__NavigateToWaypoint_FeedbackMessage__Sequence * lhs, const urc_msgs__action__NavigateToWaypoint_FeedbackMessage__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!urc_msgs__action__NavigateToWaypoint_FeedbackMessage__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
urc_msgs__action__NavigateToWaypoint_FeedbackMessage__Sequence__copy(
  const urc_msgs__action__NavigateToWaypoint_FeedbackMessage__Sequence * input,
  urc_msgs__action__NavigateToWaypoint_FeedbackMessage__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(urc_msgs__action__NavigateToWaypoint_FeedbackMessage);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    urc_msgs__action__NavigateToWaypoint_FeedbackMessage * data =
      (urc_msgs__action__NavigateToWaypoint_FeedbackMessage *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!urc_msgs__action__NavigateToWaypoint_FeedbackMessage__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          urc_msgs__action__NavigateToWaypoint_FeedbackMessage__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!urc_msgs__action__NavigateToWaypoint_FeedbackMessage__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
