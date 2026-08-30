// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from vectornav_msgs:msg/InsStatus.idl
// generated code does not contain a copyright notice

#ifndef VECTORNAV_MSGS__MSG__DETAIL__INS_STATUS__STRUCT_HPP_
#define VECTORNAV_MSGS__MSG__DETAIL__INS_STATUS__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__vectornav_msgs__msg__InsStatus __attribute__((deprecated))
#else
# define DEPRECATED__vectornav_msgs__msg__InsStatus __declspec(deprecated)
#endif

namespace vectornav_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct InsStatus_
{
  using Type = InsStatus_<ContainerAllocator>;

  explicit InsStatus_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->mode = 0;
      this->gps_fix = false;
      this->time_error = false;
      this->imu_error = false;
      this->mag_pres_error = false;
      this->gps_error = false;
      this->gps_heading_ins = false;
      this->gps_compass = false;
    }
  }

  explicit InsStatus_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->mode = 0;
      this->gps_fix = false;
      this->time_error = false;
      this->imu_error = false;
      this->mag_pres_error = false;
      this->gps_error = false;
      this->gps_heading_ins = false;
      this->gps_compass = false;
    }
  }

  // field types and members
  using _mode_type =
    uint8_t;
  _mode_type mode;
  using _gps_fix_type =
    bool;
  _gps_fix_type gps_fix;
  using _time_error_type =
    bool;
  _time_error_type time_error;
  using _imu_error_type =
    bool;
  _imu_error_type imu_error;
  using _mag_pres_error_type =
    bool;
  _mag_pres_error_type mag_pres_error;
  using _gps_error_type =
    bool;
  _gps_error_type gps_error;
  using _gps_heading_ins_type =
    bool;
  _gps_heading_ins_type gps_heading_ins;
  using _gps_compass_type =
    bool;
  _gps_compass_type gps_compass;

  // setters for named parameter idiom
  Type & set__mode(
    const uint8_t & _arg)
  {
    this->mode = _arg;
    return *this;
  }
  Type & set__gps_fix(
    const bool & _arg)
  {
    this->gps_fix = _arg;
    return *this;
  }
  Type & set__time_error(
    const bool & _arg)
  {
    this->time_error = _arg;
    return *this;
  }
  Type & set__imu_error(
    const bool & _arg)
  {
    this->imu_error = _arg;
    return *this;
  }
  Type & set__mag_pres_error(
    const bool & _arg)
  {
    this->mag_pres_error = _arg;
    return *this;
  }
  Type & set__gps_error(
    const bool & _arg)
  {
    this->gps_error = _arg;
    return *this;
  }
  Type & set__gps_heading_ins(
    const bool & _arg)
  {
    this->gps_heading_ins = _arg;
    return *this;
  }
  Type & set__gps_compass(
    const bool & _arg)
  {
    this->gps_compass = _arg;
    return *this;
  }

  // constant declarations
  static constexpr uint8_t MODE_NOT_TRACKING =
    0u;
  static constexpr uint8_t MODE_ALIGNING =
    1u;
  static constexpr uint8_t MODE_TRACKING =
    2u;
  static constexpr uint8_t MODE_NO_GPS =
    3u;

  // pointer types
  using RawPtr =
    vectornav_msgs::msg::InsStatus_<ContainerAllocator> *;
  using ConstRawPtr =
    const vectornav_msgs::msg::InsStatus_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<vectornav_msgs::msg::InsStatus_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<vectornav_msgs::msg::InsStatus_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      vectornav_msgs::msg::InsStatus_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<vectornav_msgs::msg::InsStatus_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      vectornav_msgs::msg::InsStatus_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<vectornav_msgs::msg::InsStatus_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<vectornav_msgs::msg::InsStatus_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<vectornav_msgs::msg::InsStatus_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__vectornav_msgs__msg__InsStatus
    std::shared_ptr<vectornav_msgs::msg::InsStatus_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__vectornav_msgs__msg__InsStatus
    std::shared_ptr<vectornav_msgs::msg::InsStatus_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const InsStatus_ & other) const
  {
    if (this->mode != other.mode) {
      return false;
    }
    if (this->gps_fix != other.gps_fix) {
      return false;
    }
    if (this->time_error != other.time_error) {
      return false;
    }
    if (this->imu_error != other.imu_error) {
      return false;
    }
    if (this->mag_pres_error != other.mag_pres_error) {
      return false;
    }
    if (this->gps_error != other.gps_error) {
      return false;
    }
    if (this->gps_heading_ins != other.gps_heading_ins) {
      return false;
    }
    if (this->gps_compass != other.gps_compass) {
      return false;
    }
    return true;
  }
  bool operator!=(const InsStatus_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct InsStatus_

// alias to use template instance with default allocator
using InsStatus =
  vectornav_msgs::msg::InsStatus_<std::allocator<void>>;

// constant definitions
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t InsStatus_<ContainerAllocator>::MODE_NOT_TRACKING;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t InsStatus_<ContainerAllocator>::MODE_ALIGNING;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t InsStatus_<ContainerAllocator>::MODE_TRACKING;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t InsStatus_<ContainerAllocator>::MODE_NO_GPS;
#endif  // __cplusplus < 201703L

}  // namespace msg

}  // namespace vectornav_msgs

#endif  // VECTORNAV_MSGS__MSG__DETAIL__INS_STATUS__STRUCT_HPP_
