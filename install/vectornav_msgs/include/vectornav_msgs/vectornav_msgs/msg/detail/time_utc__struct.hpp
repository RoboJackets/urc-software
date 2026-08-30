// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from vectornav_msgs:msg/TimeUTC.idl
// generated code does not contain a copyright notice

#ifndef VECTORNAV_MSGS__MSG__DETAIL__TIME_UTC__STRUCT_HPP_
#define VECTORNAV_MSGS__MSG__DETAIL__TIME_UTC__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__vectornav_msgs__msg__TimeUTC __attribute__((deprecated))
#else
# define DEPRECATED__vectornav_msgs__msg__TimeUTC __declspec(deprecated)
#endif

namespace vectornav_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct TimeUTC_
{
  using Type = TimeUTC_<ContainerAllocator>;

  explicit TimeUTC_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->year = 0;
      this->month = 0;
      this->day = 0;
      this->hour = 0;
      this->min = 0;
      this->sec = 0;
      this->ms = 0;
    }
  }

  explicit TimeUTC_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->year = 0;
      this->month = 0;
      this->day = 0;
      this->hour = 0;
      this->min = 0;
      this->sec = 0;
      this->ms = 0;
    }
  }

  // field types and members
  using _year_type =
    uint8_t;
  _year_type year;
  using _month_type =
    uint8_t;
  _month_type month;
  using _day_type =
    uint8_t;
  _day_type day;
  using _hour_type =
    uint8_t;
  _hour_type hour;
  using _min_type =
    uint8_t;
  _min_type min;
  using _sec_type =
    uint8_t;
  _sec_type sec;
  using _ms_type =
    uint16_t;
  _ms_type ms;

  // setters for named parameter idiom
  Type & set__year(
    const uint8_t & _arg)
  {
    this->year = _arg;
    return *this;
  }
  Type & set__month(
    const uint8_t & _arg)
  {
    this->month = _arg;
    return *this;
  }
  Type & set__day(
    const uint8_t & _arg)
  {
    this->day = _arg;
    return *this;
  }
  Type & set__hour(
    const uint8_t & _arg)
  {
    this->hour = _arg;
    return *this;
  }
  Type & set__min(
    const uint8_t & _arg)
  {
    this->min = _arg;
    return *this;
  }
  Type & set__sec(
    const uint8_t & _arg)
  {
    this->sec = _arg;
    return *this;
  }
  Type & set__ms(
    const uint16_t & _arg)
  {
    this->ms = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    vectornav_msgs::msg::TimeUTC_<ContainerAllocator> *;
  using ConstRawPtr =
    const vectornav_msgs::msg::TimeUTC_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<vectornav_msgs::msg::TimeUTC_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<vectornav_msgs::msg::TimeUTC_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      vectornav_msgs::msg::TimeUTC_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<vectornav_msgs::msg::TimeUTC_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      vectornav_msgs::msg::TimeUTC_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<vectornav_msgs::msg::TimeUTC_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<vectornav_msgs::msg::TimeUTC_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<vectornav_msgs::msg::TimeUTC_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__vectornav_msgs__msg__TimeUTC
    std::shared_ptr<vectornav_msgs::msg::TimeUTC_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__vectornav_msgs__msg__TimeUTC
    std::shared_ptr<vectornav_msgs::msg::TimeUTC_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const TimeUTC_ & other) const
  {
    if (this->year != other.year) {
      return false;
    }
    if (this->month != other.month) {
      return false;
    }
    if (this->day != other.day) {
      return false;
    }
    if (this->hour != other.hour) {
      return false;
    }
    if (this->min != other.min) {
      return false;
    }
    if (this->sec != other.sec) {
      return false;
    }
    if (this->ms != other.ms) {
      return false;
    }
    return true;
  }
  bool operator!=(const TimeUTC_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct TimeUTC_

// alias to use template instance with default allocator
using TimeUTC =
  vectornav_msgs::msg::TimeUTC_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace vectornav_msgs

#endif  // VECTORNAV_MSGS__MSG__DETAIL__TIME_UTC__STRUCT_HPP_
