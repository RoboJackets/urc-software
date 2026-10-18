// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from vectornav_msgs:msg/ImuGroup.idl
// generated code does not contain a copyright notice

#ifndef VECTORNAV_MSGS__MSG__DETAIL__IMU_GROUP__STRUCT_HPP_
#define VECTORNAV_MSGS__MSG__DETAIL__IMU_GROUP__STRUCT_HPP_

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
// Member 'uncompmag'
// Member 'uncompaccel'
// Member 'uncompgyro'
// Member 'deltatheta_dtheta'
// Member 'deltavel'
// Member 'mag'
// Member 'accel'
// Member 'angularrate'
#include "geometry_msgs/msg/detail/vector3__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__vectornav_msgs__msg__ImuGroup __attribute__((deprecated))
#else
# define DEPRECATED__vectornav_msgs__msg__ImuGroup __declspec(deprecated)
#endif

namespace vectornav_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct ImuGroup_
{
  using Type = ImuGroup_<ContainerAllocator>;

  explicit ImuGroup_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_init),
    uncompmag(_init),
    uncompaccel(_init),
    uncompgyro(_init),
    deltatheta_dtheta(_init),
    deltavel(_init),
    mag(_init),
    accel(_init),
    angularrate(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->group_fields = 0;
      this->imustatus = 0;
      this->temp = 0.0f;
      this->pres = 0.0f;
      this->deltatheta_time = 0.0f;
      this->sensat = 0;
    }
  }

  explicit ImuGroup_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_alloc, _init),
    uncompmag(_alloc, _init),
    uncompaccel(_alloc, _init),
    uncompgyro(_alloc, _init),
    deltatheta_dtheta(_alloc, _init),
    deltavel(_alloc, _init),
    mag(_alloc, _init),
    accel(_alloc, _init),
    angularrate(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->group_fields = 0;
      this->imustatus = 0;
      this->temp = 0.0f;
      this->pres = 0.0f;
      this->deltatheta_time = 0.0f;
      this->sensat = 0;
    }
  }

  // field types and members
  using _header_type =
    std_msgs::msg::Header_<ContainerAllocator>;
  _header_type header;
  using _group_fields_type =
    uint16_t;
  _group_fields_type group_fields;
  using _imustatus_type =
    uint16_t;
  _imustatus_type imustatus;
  using _uncompmag_type =
    geometry_msgs::msg::Vector3_<ContainerAllocator>;
  _uncompmag_type uncompmag;
  using _uncompaccel_type =
    geometry_msgs::msg::Vector3_<ContainerAllocator>;
  _uncompaccel_type uncompaccel;
  using _uncompgyro_type =
    geometry_msgs::msg::Vector3_<ContainerAllocator>;
  _uncompgyro_type uncompgyro;
  using _temp_type =
    float;
  _temp_type temp;
  using _pres_type =
    float;
  _pres_type pres;
  using _deltatheta_time_type =
    float;
  _deltatheta_time_type deltatheta_time;
  using _deltatheta_dtheta_type =
    geometry_msgs::msg::Vector3_<ContainerAllocator>;
  _deltatheta_dtheta_type deltatheta_dtheta;
  using _deltavel_type =
    geometry_msgs::msg::Vector3_<ContainerAllocator>;
  _deltavel_type deltavel;
  using _mag_type =
    geometry_msgs::msg::Vector3_<ContainerAllocator>;
  _mag_type mag;
  using _accel_type =
    geometry_msgs::msg::Vector3_<ContainerAllocator>;
  _accel_type accel;
  using _angularrate_type =
    geometry_msgs::msg::Vector3_<ContainerAllocator>;
  _angularrate_type angularrate;
  using _sensat_type =
    uint16_t;
  _sensat_type sensat;

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
  Type & set__imustatus(
    const uint16_t & _arg)
  {
    this->imustatus = _arg;
    return *this;
  }
  Type & set__uncompmag(
    const geometry_msgs::msg::Vector3_<ContainerAllocator> & _arg)
  {
    this->uncompmag = _arg;
    return *this;
  }
  Type & set__uncompaccel(
    const geometry_msgs::msg::Vector3_<ContainerAllocator> & _arg)
  {
    this->uncompaccel = _arg;
    return *this;
  }
  Type & set__uncompgyro(
    const geometry_msgs::msg::Vector3_<ContainerAllocator> & _arg)
  {
    this->uncompgyro = _arg;
    return *this;
  }
  Type & set__temp(
    const float & _arg)
  {
    this->temp = _arg;
    return *this;
  }
  Type & set__pres(
    const float & _arg)
  {
    this->pres = _arg;
    return *this;
  }
  Type & set__deltatheta_time(
    const float & _arg)
  {
    this->deltatheta_time = _arg;
    return *this;
  }
  Type & set__deltatheta_dtheta(
    const geometry_msgs::msg::Vector3_<ContainerAllocator> & _arg)
  {
    this->deltatheta_dtheta = _arg;
    return *this;
  }
  Type & set__deltavel(
    const geometry_msgs::msg::Vector3_<ContainerAllocator> & _arg)
  {
    this->deltavel = _arg;
    return *this;
  }
  Type & set__mag(
    const geometry_msgs::msg::Vector3_<ContainerAllocator> & _arg)
  {
    this->mag = _arg;
    return *this;
  }
  Type & set__accel(
    const geometry_msgs::msg::Vector3_<ContainerAllocator> & _arg)
  {
    this->accel = _arg;
    return *this;
  }
  Type & set__angularrate(
    const geometry_msgs::msg::Vector3_<ContainerAllocator> & _arg)
  {
    this->angularrate = _arg;
    return *this;
  }
  Type & set__sensat(
    const uint16_t & _arg)
  {
    this->sensat = _arg;
    return *this;
  }

  // constant declarations
  static constexpr uint16_t IMUGROUP_IMUSTATUS =
    1u;
  static constexpr uint16_t IMUGROUP_UNCOMPMAG =
    2u;
  static constexpr uint16_t IMUGROUP_UNCOMPACCEL =
    4u;
  static constexpr uint16_t IMUGROUP_UNCOMPGYRO =
    8u;
  static constexpr uint16_t IMUGROUP_TEMP =
    16u;
  static constexpr uint16_t IMUGROUP_PRES =
    32u;
  static constexpr uint16_t IMUGROUP_DELTATHETA =
    64u;
  static constexpr uint16_t IMUGROUP_DELTAVEL =
    128u;
  static constexpr uint16_t IMUGROUP_MAG =
    256u;
  static constexpr uint16_t IMUGROUP_ACCEL =
    512u;
  static constexpr uint16_t IMUGROUP_ANGULARRATE =
    1024u;
  static constexpr uint16_t IMUGROUP_SENSSAT =
    2048u;

  // pointer types
  using RawPtr =
    vectornav_msgs::msg::ImuGroup_<ContainerAllocator> *;
  using ConstRawPtr =
    const vectornav_msgs::msg::ImuGroup_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<vectornav_msgs::msg::ImuGroup_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<vectornav_msgs::msg::ImuGroup_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      vectornav_msgs::msg::ImuGroup_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<vectornav_msgs::msg::ImuGroup_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      vectornav_msgs::msg::ImuGroup_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<vectornav_msgs::msg::ImuGroup_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<vectornav_msgs::msg::ImuGroup_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<vectornav_msgs::msg::ImuGroup_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__vectornav_msgs__msg__ImuGroup
    std::shared_ptr<vectornav_msgs::msg::ImuGroup_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__vectornav_msgs__msg__ImuGroup
    std::shared_ptr<vectornav_msgs::msg::ImuGroup_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const ImuGroup_ & other) const
  {
    if (this->header != other.header) {
      return false;
    }
    if (this->group_fields != other.group_fields) {
      return false;
    }
    if (this->imustatus != other.imustatus) {
      return false;
    }
    if (this->uncompmag != other.uncompmag) {
      return false;
    }
    if (this->uncompaccel != other.uncompaccel) {
      return false;
    }
    if (this->uncompgyro != other.uncompgyro) {
      return false;
    }
    if (this->temp != other.temp) {
      return false;
    }
    if (this->pres != other.pres) {
      return false;
    }
    if (this->deltatheta_time != other.deltatheta_time) {
      return false;
    }
    if (this->deltatheta_dtheta != other.deltatheta_dtheta) {
      return false;
    }
    if (this->deltavel != other.deltavel) {
      return false;
    }
    if (this->mag != other.mag) {
      return false;
    }
    if (this->accel != other.accel) {
      return false;
    }
    if (this->angularrate != other.angularrate) {
      return false;
    }
    if (this->sensat != other.sensat) {
      return false;
    }
    return true;
  }
  bool operator!=(const ImuGroup_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct ImuGroup_

// alias to use template instance with default allocator
using ImuGroup =
  vectornav_msgs::msg::ImuGroup_<std::allocator<void>>;

// constant definitions
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t ImuGroup_<ContainerAllocator>::IMUGROUP_IMUSTATUS;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t ImuGroup_<ContainerAllocator>::IMUGROUP_UNCOMPMAG;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t ImuGroup_<ContainerAllocator>::IMUGROUP_UNCOMPACCEL;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t ImuGroup_<ContainerAllocator>::IMUGROUP_UNCOMPGYRO;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t ImuGroup_<ContainerAllocator>::IMUGROUP_TEMP;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t ImuGroup_<ContainerAllocator>::IMUGROUP_PRES;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t ImuGroup_<ContainerAllocator>::IMUGROUP_DELTATHETA;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t ImuGroup_<ContainerAllocator>::IMUGROUP_DELTAVEL;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t ImuGroup_<ContainerAllocator>::IMUGROUP_MAG;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t ImuGroup_<ContainerAllocator>::IMUGROUP_ACCEL;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t ImuGroup_<ContainerAllocator>::IMUGROUP_ANGULARRATE;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t ImuGroup_<ContainerAllocator>::IMUGROUP_SENSSAT;
#endif  // __cplusplus < 201703L

}  // namespace msg

}  // namespace vectornav_msgs

#endif  // VECTORNAV_MSGS__MSG__DETAIL__IMU_GROUP__STRUCT_HPP_
