// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from vectornav_msgs:msg/TimeGroup.idl
// generated code does not contain a copyright notice

#ifndef VECTORNAV_MSGS__MSG__DETAIL__TIME_GROUP__STRUCT_HPP_
#define VECTORNAV_MSGS__MSG__DETAIL__TIME_GROUP__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__struct.hpp"
// Member 'timeutc'
#include "vectornav_msgs/msg/detail/time_utc__struct.hpp"
// Member 'timestatus'
#include "vectornav_msgs/msg/detail/time_status__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__vectornav_msgs__msg__TimeGroup __attribute__((deprecated))
#else
# define DEPRECATED__vectornav_msgs__msg__TimeGroup __declspec(deprecated)
#endif

namespace vectornav_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct TimeGroup_
{
  using Type = TimeGroup_<ContainerAllocator>;

  explicit TimeGroup_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_init),
    timeutc(_init),
    timestatus(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->group_fields = 0;
      this->timestartup = 0ull;
      this->timegps = 0ull;
      this->gpstow = 0ull;
      this->gpsweek = 0;
      this->timesyncin = 0ull;
      this->timegpspps = 0ull;
      this->syncincnt = 0ul;
      this->syncoutcnt = 0ul;
    }
  }

  explicit TimeGroup_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_alloc, _init),
    timeutc(_alloc, _init),
    timestatus(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->group_fields = 0;
      this->timestartup = 0ull;
      this->timegps = 0ull;
      this->gpstow = 0ull;
      this->gpsweek = 0;
      this->timesyncin = 0ull;
      this->timegpspps = 0ull;
      this->syncincnt = 0ul;
      this->syncoutcnt = 0ul;
    }
  }

  // field types and members
  using _header_type =
    std_msgs::msg::Header_<ContainerAllocator>;
  _header_type header;
  using _group_fields_type =
    uint16_t;
  _group_fields_type group_fields;
  using _timestartup_type =
    uint64_t;
  _timestartup_type timestartup;
  using _timegps_type =
    uint64_t;
  _timegps_type timegps;
  using _gpstow_type =
    uint64_t;
  _gpstow_type gpstow;
  using _gpsweek_type =
    uint16_t;
  _gpsweek_type gpsweek;
  using _timesyncin_type =
    uint64_t;
  _timesyncin_type timesyncin;
  using _timegpspps_type =
    uint64_t;
  _timegpspps_type timegpspps;
  using _timeutc_type =
    vectornav_msgs::msg::TimeUTC_<ContainerAllocator>;
  _timeutc_type timeutc;
  using _syncincnt_type =
    uint32_t;
  _syncincnt_type syncincnt;
  using _syncoutcnt_type =
    uint32_t;
  _syncoutcnt_type syncoutcnt;
  using _timestatus_type =
    vectornav_msgs::msg::TimeStatus_<ContainerAllocator>;
  _timestatus_type timestatus;

  // setters for named parameter idiom
  Type & set__header(
    const std_msgs::msg::Header_<ContainerAllocator> & _arg)
  {
    this->header = _arg;
    return *this;
  }
  Type & set__group_fields(
    const uint16_t & _arg)
  {
    this->group_fields = _arg;
    return *this;
  }
  Type & set__timestartup(
    const uint64_t & _arg)
  {
    this->timestartup = _arg;
    return *this;
  }
  Type & set__timegps(
    const uint64_t & _arg)
  {
    this->timegps = _arg;
    return *this;
  }
  Type & set__gpstow(
    const uint64_t & _arg)
  {
    this->gpstow = _arg;
    return *this;
  }
  Type & set__gpsweek(
    const uint16_t & _arg)
  {
    this->gpsweek = _arg;
    return *this;
  }
  Type & set__timesyncin(
    const uint64_t & _arg)
  {
    this->timesyncin = _arg;
    return *this;
  }
  Type & set__timegpspps(
    const uint64_t & _arg)
  {
    this->timegpspps = _arg;
    return *this;
  }
  Type & set__timeutc(
    const vectornav_msgs::msg::TimeUTC_<ContainerAllocator> & _arg)
  {
    this->timeutc = _arg;
    return *this;
  }
  Type & set__syncincnt(
    const uint32_t & _arg)
  {
    this->syncincnt = _arg;
    return *this;
  }
  Type & set__syncoutcnt(
    const uint32_t & _arg)
  {
    this->syncoutcnt = _arg;
    return *this;
  }
  Type & set__timestatus(
    const vectornav_msgs::msg::TimeStatus_<ContainerAllocator> & _arg)
  {
    this->timestatus = _arg;
    return *this;
  }

  // constant declarations
  static constexpr uint16_t TIMEGROUP_TIMESTARTUP =
    1u;
  static constexpr uint16_t TIMEGROUP_TIMEGPS =
    2u;
  static constexpr uint16_t TIMEGROUP_GPSTOW =
    4u;
  static constexpr uint16_t TIMEGROUP_GPSWEEK =
    8u;
  static constexpr uint16_t TIMEGROUP_TIMESYNCIN =
    16u;
  static constexpr uint16_t TIMEGROUP_TIMEGPSPPS =
    32u;
  static constexpr uint16_t TIMEGROUP_TIMEUTC =
    64u;
  static constexpr uint16_t TIMEGROUP_SYNCINCNT =
    128u;
  static constexpr uint16_t TIMEGROUP_SYNCOUTCNT =
    256u;
  static constexpr uint16_t TIMEGROUP_TIMESTATUS =
    512u;

  // pointer types
  using RawPtr =
    vectornav_msgs::msg::TimeGroup_<ContainerAllocator> *;
  using ConstRawPtr =
    const vectornav_msgs::msg::TimeGroup_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<vectornav_msgs::msg::TimeGroup_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<vectornav_msgs::msg::TimeGroup_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      vectornav_msgs::msg::TimeGroup_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<vectornav_msgs::msg::TimeGroup_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      vectornav_msgs::msg::TimeGroup_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<vectornav_msgs::msg::TimeGroup_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<vectornav_msgs::msg::TimeGroup_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<vectornav_msgs::msg::TimeGroup_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__vectornav_msgs__msg__TimeGroup
    std::shared_ptr<vectornav_msgs::msg::TimeGroup_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__vectornav_msgs__msg__TimeGroup
    std::shared_ptr<vectornav_msgs::msg::TimeGroup_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const TimeGroup_ & other) const
  {
    if (this->header != other.header) {
      return false;
    }
    if (this->group_fields != other.group_fields) {
      return false;
    }
    if (this->timestartup != other.timestartup) {
      return false;
    }
    if (this->timegps != other.timegps) {
      return false;
    }
    if (this->gpstow != other.gpstow) {
      return false;
    }
    if (this->gpsweek != other.gpsweek) {
      return false;
    }
    if (this->timesyncin != other.timesyncin) {
      return false;
    }
    if (this->timegpspps != other.timegpspps) {
      return false;
    }
    if (this->timeutc != other.timeutc) {
      return false;
    }
    if (this->syncincnt != other.syncincnt) {
      return false;
    }
    if (this->syncoutcnt != other.syncoutcnt) {
      return false;
    }
    if (this->timestatus != other.timestatus) {
      return false;
    }
    return true;
  }
  bool operator!=(const TimeGroup_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct TimeGroup_

// alias to use template instance with default allocator
using TimeGroup =
  vectornav_msgs::msg::TimeGroup_<std::allocator<void>>;

// constant definitions
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t TimeGroup_<ContainerAllocator>::TIMEGROUP_TIMESTARTUP;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t TimeGroup_<ContainerAllocator>::TIMEGROUP_TIMEGPS;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t TimeGroup_<ContainerAllocator>::TIMEGROUP_GPSTOW;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t TimeGroup_<ContainerAllocator>::TIMEGROUP_GPSWEEK;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t TimeGroup_<ContainerAllocator>::TIMEGROUP_TIMESYNCIN;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t TimeGroup_<ContainerAllocator>::TIMEGROUP_TIMEGPSPPS;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t TimeGroup_<ContainerAllocator>::TIMEGROUP_TIMEUTC;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t TimeGroup_<ContainerAllocator>::TIMEGROUP_SYNCINCNT;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t TimeGroup_<ContainerAllocator>::TIMEGROUP_SYNCOUTCNT;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t TimeGroup_<ContainerAllocator>::TIMEGROUP_TIMESTATUS;
#endif  // __cplusplus < 201703L

}  // namespace msg

}  // namespace vectornav_msgs

#endif  // VECTORNAV_MSGS__MSG__DETAIL__TIME_GROUP__STRUCT_HPP_
