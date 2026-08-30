// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from vectornav_msgs:msg/VpeStatus.idl
// generated code does not contain a copyright notice

#ifndef VECTORNAV_MSGS__MSG__DETAIL__VPE_STATUS__STRUCT_HPP_
#define VECTORNAV_MSGS__MSG__DETAIL__VPE_STATUS__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__vectornav_msgs__msg__VpeStatus __attribute__((deprecated))
#else
# define DEPRECATED__vectornav_msgs__msg__VpeStatus __declspec(deprecated)
#endif

namespace vectornav_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct VpeStatus_
{
  using Type = VpeStatus_<ContainerAllocator>;

  explicit VpeStatus_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->attitude_quality = 0;
      this->gyro_saturation = false;
      this->gyro_saturation_recovery = false;
      this->mag_disturbance = 0;
      this->mag_saturation = false;
      this->acc_disturbance = 0;
      this->acc_saturation = false;
      this->known_mag_disturbance = false;
      this->known_accel_disturbance = false;
    }
  }

  explicit VpeStatus_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->attitude_quality = 0;
      this->gyro_saturation = false;
      this->gyro_saturation_recovery = false;
      this->mag_disturbance = 0;
      this->mag_saturation = false;
      this->acc_disturbance = 0;
      this->acc_saturation = false;
      this->known_mag_disturbance = false;
      this->known_accel_disturbance = false;
    }
  }

  // field types and members
  using _attitude_quality_type =
    uint8_t;
  _attitude_quality_type attitude_quality;
  using _gyro_saturation_type =
    bool;
  _gyro_saturation_type gyro_saturation;
  using _gyro_saturation_recovery_type =
    bool;
  _gyro_saturation_recovery_type gyro_saturation_recovery;
  using _mag_disturbance_type =
    uint8_t;
  _mag_disturbance_type mag_disturbance;
  using _mag_saturation_type =
    bool;
  _mag_saturation_type mag_saturation;
  using _acc_disturbance_type =
    uint8_t;
  _acc_disturbance_type acc_disturbance;
  using _acc_saturation_type =
    bool;
  _acc_saturation_type acc_saturation;
  using _known_mag_disturbance_type =
    bool;
  _known_mag_disturbance_type known_mag_disturbance;
  using _known_accel_disturbance_type =
    bool;
  _known_accel_disturbance_type known_accel_disturbance;

  // setters for named parameter idiom
  Type & set__attitude_quality(
    const uint8_t & _arg)
  {
    this->attitude_quality = _arg;
    return *this;
  }
  Type & set__gyro_saturation(
    const bool & _arg)
  {
    this->gyro_saturation = _arg;
    return *this;
  }
  Type & set__gyro_saturation_recovery(
    const bool & _arg)
  {
    this->gyro_saturation_recovery = _arg;
    return *this;
  }
  Type & set__mag_disturbance(
    const uint8_t & _arg)
  {
    this->mag_disturbance = _arg;
    return *this;
  }
  Type & set__mag_saturation(
    const bool & _arg)
  {
    this->mag_saturation = _arg;
    return *this;
  }
  Type & set__acc_disturbance(
    const uint8_t & _arg)
  {
    this->acc_disturbance = _arg;
    return *this;
  }
  Type & set__acc_saturation(
    const bool & _arg)
  {
    this->acc_saturation = _arg;
    return *this;
  }
  Type & set__known_mag_disturbance(
    const bool & _arg)
  {
    this->known_mag_disturbance = _arg;
    return *this;
  }
  Type & set__known_accel_disturbance(
    const bool & _arg)
  {
    this->known_accel_disturbance = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    vectornav_msgs::msg::VpeStatus_<ContainerAllocator> *;
  using ConstRawPtr =
    const vectornav_msgs::msg::VpeStatus_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<vectornav_msgs::msg::VpeStatus_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<vectornav_msgs::msg::VpeStatus_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      vectornav_msgs::msg::VpeStatus_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<vectornav_msgs::msg::VpeStatus_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      vectornav_msgs::msg::VpeStatus_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<vectornav_msgs::msg::VpeStatus_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<vectornav_msgs::msg::VpeStatus_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<vectornav_msgs::msg::VpeStatus_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__vectornav_msgs__msg__VpeStatus
    std::shared_ptr<vectornav_msgs::msg::VpeStatus_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__vectornav_msgs__msg__VpeStatus
    std::shared_ptr<vectornav_msgs::msg::VpeStatus_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const VpeStatus_ & other) const
  {
    if (this->attitude_quality != other.attitude_quality) {
      return false;
    }
    if (this->gyro_saturation != other.gyro_saturation) {
      return false;
    }
    if (this->gyro_saturation_recovery != other.gyro_saturation_recovery) {
      return false;
    }
    if (this->mag_disturbance != other.mag_disturbance) {
      return false;
    }
    if (this->mag_saturation != other.mag_saturation) {
      return false;
    }
    if (this->acc_disturbance != other.acc_disturbance) {
      return false;
    }
    if (this->acc_saturation != other.acc_saturation) {
      return false;
    }
    if (this->known_mag_disturbance != other.known_mag_disturbance) {
      return false;
    }
    if (this->known_accel_disturbance != other.known_accel_disturbance) {
      return false;
    }
    return true;
  }
  bool operator!=(const VpeStatus_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct VpeStatus_

// alias to use template instance with default allocator
using VpeStatus =
  vectornav_msgs::msg::VpeStatus_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace vectornav_msgs

#endif  // VECTORNAV_MSGS__MSG__DETAIL__VPE_STATUS__STRUCT_HPP_
