// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from vectornav_msgs:msg/TimeStatus.idl
// generated code does not contain a copyright notice

#ifndef VECTORNAV_MSGS__MSG__DETAIL__TIME_STATUS__STRUCT_HPP_
#define VECTORNAV_MSGS__MSG__DETAIL__TIME_STATUS__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__vectornav_msgs__msg__TimeStatus __attribute__((deprecated))
#else
# define DEPRECATED__vectornav_msgs__msg__TimeStatus __declspec(deprecated)
#endif

namespace vectornav_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct TimeStatus_
{
  using Type = TimeStatus_<ContainerAllocator>;

  explicit TimeStatus_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->time_ok = false;
      this->date_ok = false;
      this->utctime_ok = false;
    }
  }

  explicit TimeStatus_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->time_ok = false;
      this->date_ok = false;
      this->utctime_ok = false;
    }
  }

  // field types and members
  using _time_ok_type =
    bool;
  _time_ok_type time_ok;
  using _date_ok_type =
    bool;
  _date_ok_type date_ok;
  using _utctime_ok_type =
    bool;
  _utctime_ok_type utctime_ok;

  // setters for named parameter idiom
  Type & set__time_ok(
    const bool & _arg)
  {
    this->time_ok = _arg;
    return *this;
  }
  Type & set__date_ok(
    const bool & _arg)
  {
    this->date_ok = _arg;
    return *this;
  }
  Type & set__utctime_ok(
    const bool & _arg)
  {
    this->utctime_ok = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    vectornav_msgs::msg::TimeStatus_<ContainerAllocator> *;
  using ConstRawPtr =
    const vectornav_msgs::msg::TimeStatus_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<vectornav_msgs::msg::TimeStatus_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<vectornav_msgs::msg::TimeStatus_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      vectornav_msgs::msg::TimeStatus_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<vectornav_msgs::msg::TimeStatus_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      vectornav_msgs::msg::TimeStatus_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<vectornav_msgs::msg::TimeStatus_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<vectornav_msgs::msg::TimeStatus_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<vectornav_msgs::msg::TimeStatus_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__vectornav_msgs__msg__TimeStatus
    std::shared_ptr<vectornav_msgs::msg::TimeStatus_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__vectornav_msgs__msg__TimeStatus
    std::shared_ptr<vectornav_msgs::msg::TimeStatus_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const TimeStatus_ & other) const
  {
    if (this->time_ok != other.time_ok) {
      return false;
    }
    if (this->date_ok != other.date_ok) {
      return false;
    }
    if (this->utctime_ok != other.utctime_ok) {
      return false;
    }
    return true;
  }
  bool operator!=(const TimeStatus_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct TimeStatus_

// alias to use template instance with default allocator
using TimeStatus =
  vectornav_msgs::msg::TimeStatus_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace vectornav_msgs

#endif  // VECTORNAV_MSGS__MSG__DETAIL__TIME_STATUS__STRUCT_HPP_
