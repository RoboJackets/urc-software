// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from vectornav_msgs:msg/CommonGroup.idl
// generated code does not contain a copyright notice

#ifndef VECTORNAV_MSGS__MSG__DETAIL__COMMON_GROUP__STRUCT_HPP_
#define VECTORNAV_MSGS__MSG__DETAIL__COMMON_GROUP__STRUCT_HPP_

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
// Member 'yawpitchroll'
// Member 'angularrate'
// Member 'velocity'
// Member 'accel'
// Member 'imu_accel'
// Member 'imu_rate'
// Member 'magpres_mag'
// Member 'deltatheta_dtheta'
// Member 'deltatheta_dvel'
#include "geometry_msgs/msg/detail/vector3__struct.hpp"
// Member 'quaternion'
#include "geometry_msgs/msg/detail/quaternion__struct.hpp"
// Member 'position'
#include "geometry_msgs/msg/detail/point__struct.hpp"
// Member 'insstatus'
#include "vectornav_msgs/msg/detail/ins_status__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__vectornav_msgs__msg__CommonGroup __attribute__((deprecated))
#else
# define DEPRECATED__vectornav_msgs__msg__CommonGroup __declspec(deprecated)
#endif

namespace vectornav_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct CommonGroup_
{
  using Type = CommonGroup_<ContainerAllocator>;

  explicit CommonGroup_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_init),
    yawpitchroll(_init),
    quaternion(_init),
    angularrate(_init),
    position(_init),
    velocity(_init),
    accel(_init),
    imu_accel(_init),
    imu_rate(_init),
    magpres_mag(_init),
    deltatheta_dtheta(_init),
    deltatheta_dvel(_init),
    insstatus(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->group_fields = 0;
      this->timestartup = 0ull;
      this->timegps = 0ull;
      this->timesyncin = 0ull;
      this->magpres_temp = 0.0f;
      this->magpres_pres = 0.0f;
      this->deltatheta_dtime = 0.0f;
      this->syncincnt = 0ul;
      this->timegpspps = 0;
    }
  }

  explicit CommonGroup_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_alloc, _init),
    yawpitchroll(_alloc, _init),
    quaternion(_alloc, _init),
    angularrate(_alloc, _init),
    position(_alloc, _init),
    velocity(_alloc, _init),
    accel(_alloc, _init),
    imu_accel(_alloc, _init),
    imu_rate(_alloc, _init),
    magpres_mag(_alloc, _init),
    deltatheta_dtheta(_alloc, _init),
    deltatheta_dvel(_alloc, _init),
    insstatus(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->group_fields = 0;
      this->timestartup = 0ull;
      this->timegps = 0ull;
      this->timesyncin = 0ull;
      this->magpres_temp = 0.0f;
      this->magpres_pres = 0.0f;
      this->deltatheta_dtime = 0.0f;
      this->syncincnt = 0ul;
      this->timegpspps = 0;
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
  using _timesyncin_type =
    uint64_t;
  _timesyncin_type timesyncin;
  using _yawpitchroll_type =
    geometry_msgs::msg::Vector3_<ContainerAllocator>;
  _yawpitchroll_type yawpitchroll;
  using _quaternion_type =
    geometry_msgs::msg::Quaternion_<ContainerAllocator>;
  _quaternion_type quaternion;
  using _angularrate_type =
    geometry_msgs::msg::Vector3_<ContainerAllocator>;
  _angularrate_type angularrate;
  using _position_type =
    geometry_msgs::msg::Point_<ContainerAllocator>;
  _position_type position;
  using _velocity_type =
    geometry_msgs::msg::Vector3_<ContainerAllocator>;
  _velocity_type velocity;
  using _accel_type =
    geometry_msgs::msg::Vector3_<ContainerAllocator>;
  _accel_type accel;
  using _imu_accel_type =
    geometry_msgs::msg::Vector3_<ContainerAllocator>;
  _imu_accel_type imu_accel;
  using _imu_rate_type =
    geometry_msgs::msg::Vector3_<ContainerAllocator>;
  _imu_rate_type imu_rate;
  using _magpres_mag_type =
    geometry_msgs::msg::Vector3_<ContainerAllocator>;
  _magpres_mag_type magpres_mag;
  using _magpres_temp_type =
    float;
  _magpres_temp_type magpres_temp;
  using _magpres_pres_type =
    float;
  _magpres_pres_type magpres_pres;
  using _deltatheta_dtime_type =
    float;
  _deltatheta_dtime_type deltatheta_dtime;
  using _deltatheta_dtheta_type =
    geometry_msgs::msg::Vector3_<ContainerAllocator>;
  _deltatheta_dtheta_type deltatheta_dtheta;
  using _deltatheta_dvel_type =
    geometry_msgs::msg::Vector3_<ContainerAllocator>;
  _deltatheta_dvel_type deltatheta_dvel;
  using _insstatus_type =
    vectornav_msgs::msg::InsStatus_<ContainerAllocator>;
  _insstatus_type insstatus;
  using _syncincnt_type =
    uint32_t;
  _syncincnt_type syncincnt;
  using _timegpspps_type =
    uint16_t;
  _timegpspps_type timegpspps;

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
  Type & set__timesyncin(
    const uint64_t & _arg)
  {
    this->timesyncin = _arg;
    return *this;
  }
  Type & set__yawpitchroll(
    const geometry_msgs::msg::Vector3_<ContainerAllocator> & _arg)
  {
    this->yawpitchroll = _arg;
    return *this;
  }
  Type & set__quaternion(
    const geometry_msgs::msg::Quaternion_<ContainerAllocator> & _arg)
  {
    this->quaternion = _arg;
    return *this;
  }
  Type & set__angularrate(
    const geometry_msgs::msg::Vector3_<ContainerAllocator> & _arg)
  {
    this->angularrate = _arg;
    return *this;
  }
  Type & set__position(
    const geometry_msgs::msg::Point_<ContainerAllocator> & _arg)
  {
    this->position = _arg;
    return *this;
  }
  Type & set__velocity(
    const geometry_msgs::msg::Vector3_<ContainerAllocator> & _arg)
  {
    this->velocity = _arg;
    return *this;
  }
  Type & set__accel(
    const geometry_msgs::msg::Vector3_<ContainerAllocator> & _arg)
  {
    this->accel = _arg;
    return *this;
  }
  Type & set__imu_accel(
    const geometry_msgs::msg::Vector3_<ContainerAllocator> & _arg)
  {
    this->imu_accel = _arg;
    return *this;
  }
  Type & set__imu_rate(
    const geometry_msgs::msg::Vector3_<ContainerAllocator> & _arg)
  {
    this->imu_rate = _arg;
    return *this;
  }
  Type & set__magpres_mag(
    const geometry_msgs::msg::Vector3_<ContainerAllocator> & _arg)
  {
    this->magpres_mag = _arg;
    return *this;
  }
  Type & set__magpres_temp(
    const float & _arg)
  {
    this->magpres_temp = _arg;
    return *this;
  }
  Type & set__magpres_pres(
    const float & _arg)
  {
    this->magpres_pres = _arg;
    return *this;
  }
  Type & set__deltatheta_dtime(
    const float & _arg)
  {
    this->deltatheta_dtime = _arg;
    return *this;
  }
  Type & set__deltatheta_dtheta(
    const geometry_msgs::msg::Vector3_<ContainerAllocator> & _arg)
  {
    this->deltatheta_dtheta = _arg;
    return *this;
  }
  Type & set__deltatheta_dvel(
    const geometry_msgs::msg::Vector3_<ContainerAllocator> & _arg)
  {
    this->deltatheta_dvel = _arg;
    return *this;
  }
  Type & set__insstatus(
    const vectornav_msgs::msg::InsStatus_<ContainerAllocator> & _arg)
  {
    this->insstatus = _arg;
    return *this;
  }
  Type & set__syncincnt(
    const uint32_t & _arg)
  {
    this->syncincnt = _arg;
    return *this;
  }
  Type & set__timegpspps(
    const uint16_t & _arg)
  {
    this->timegpspps = _arg;
    return *this;
  }

  // constant declarations
  static constexpr uint16_t COMMONGROUP_TIMESTARTUP =
    1u;
  static constexpr uint16_t COMMONGROUP_TIMEGPS =
    2u;
  static constexpr uint16_t COMMONGROUP_TIMESYNCIN =
    4u;
  static constexpr uint16_t COMMONGROUP_YAWPITCHROLL =
    8u;
  static constexpr uint16_t COMMONGROUP_QUATERNION =
    16u;
  static constexpr uint16_t COMMONGROUP_ANGULARRATE =
    32u;
  static constexpr uint16_t COMMONGROUP_POSITION =
    64u;
  static constexpr uint16_t COMMONGROUP_VELOCITY =
    128u;
  static constexpr uint16_t COMMONGROUP_ACCEL =
    256u;
  static constexpr uint16_t COMMONGROUP_IMU =
    512u;
  static constexpr uint16_t COMMONGROUP_MAGPRES =
    1024u;
  static constexpr uint16_t COMMONGROUP_DELTATHETA =
    2048u;
  static constexpr uint16_t COMMONGROUP_INSSTATUS =
    4096u;
  static constexpr uint16_t COMMONGROUP_SYNCINCNT =
    8192u;
  static constexpr uint16_t COMMONGROUP_TIMEGPSPPS =
    16384u;

  // pointer types
  using RawPtr =
    vectornav_msgs::msg::CommonGroup_<ContainerAllocator> *;
  using ConstRawPtr =
    const vectornav_msgs::msg::CommonGroup_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<vectornav_msgs::msg::CommonGroup_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<vectornav_msgs::msg::CommonGroup_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      vectornav_msgs::msg::CommonGroup_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<vectornav_msgs::msg::CommonGroup_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      vectornav_msgs::msg::CommonGroup_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<vectornav_msgs::msg::CommonGroup_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<vectornav_msgs::msg::CommonGroup_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<vectornav_msgs::msg::CommonGroup_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__vectornav_msgs__msg__CommonGroup
    std::shared_ptr<vectornav_msgs::msg::CommonGroup_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__vectornav_msgs__msg__CommonGroup
    std::shared_ptr<vectornav_msgs::msg::CommonGroup_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const CommonGroup_ & other) const
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
    if (this->timesyncin != other.timesyncin) {
      return false;
    }
    if (this->yawpitchroll != other.yawpitchroll) {
      return false;
    }
    if (this->quaternion != other.quaternion) {
      return false;
    }
    if (this->angularrate != other.angularrate) {
      return false;
    }
    if (this->position != other.position) {
      return false;
    }
    if (this->velocity != other.velocity) {
      return false;
    }
    if (this->accel != other.accel) {
      return false;
    }
    if (this->imu_accel != other.imu_accel) {
      return false;
    }
    if (this->imu_rate != other.imu_rate) {
      return false;
    }
    if (this->magpres_mag != other.magpres_mag) {
      return false;
    }
    if (this->magpres_temp != other.magpres_temp) {
      return false;
    }
    if (this->magpres_pres != other.magpres_pres) {
      return false;
    }
    if (this->deltatheta_dtime != other.deltatheta_dtime) {
      return false;
    }
    if (this->deltatheta_dtheta != other.deltatheta_dtheta) {
      return false;
    }
    if (this->deltatheta_dvel != other.deltatheta_dvel) {
      return false;
    }
    if (this->insstatus != other.insstatus) {
      return false;
    }
    if (this->syncincnt != other.syncincnt) {
      return false;
    }
    if (this->timegpspps != other.timegpspps) {
      return false;
    }
    return true;
  }
  bool operator!=(const CommonGroup_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct CommonGroup_

// alias to use template instance with default allocator
using CommonGroup =
  vectornav_msgs::msg::CommonGroup_<std::allocator<void>>;

// constant definitions
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t CommonGroup_<ContainerAllocator>::COMMONGROUP_TIMESTARTUP;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t CommonGroup_<ContainerAllocator>::COMMONGROUP_TIMEGPS;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t CommonGroup_<ContainerAllocator>::COMMONGROUP_TIMESYNCIN;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t CommonGroup_<ContainerAllocator>::COMMONGROUP_YAWPITCHROLL;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t CommonGroup_<ContainerAllocator>::COMMONGROUP_QUATERNION;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t CommonGroup_<ContainerAllocator>::COMMONGROUP_ANGULARRATE;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t CommonGroup_<ContainerAllocator>::COMMONGROUP_POSITION;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t CommonGroup_<ContainerAllocator>::COMMONGROUP_VELOCITY;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t CommonGroup_<ContainerAllocator>::COMMONGROUP_ACCEL;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t CommonGroup_<ContainerAllocator>::COMMONGROUP_IMU;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t CommonGroup_<ContainerAllocator>::COMMONGROUP_MAGPRES;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t CommonGroup_<ContainerAllocator>::COMMONGROUP_DELTATHETA;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t CommonGroup_<ContainerAllocator>::COMMONGROUP_INSSTATUS;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t CommonGroup_<ContainerAllocator>::COMMONGROUP_SYNCINCNT;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t CommonGroup_<ContainerAllocator>::COMMONGROUP_TIMEGPSPPS;
#endif  // __cplusplus < 201703L

}  // namespace msg

}  // namespace vectornav_msgs

#endif  // VECTORNAV_MSGS__MSG__DETAIL__COMMON_GROUP__STRUCT_HPP_
