// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from vectornav_msgs:msg/GpsGroup.idl
// generated code does not contain a copyright notice

#ifndef VECTORNAV_MSGS__MSG__DETAIL__GPS_GROUP__STRUCT_HPP_
#define VECTORNAV_MSGS__MSG__DETAIL__GPS_GROUP__STRUCT_HPP_

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
// Member 'utc'
#include "vectornav_msgs/msg/detail/time_utc__struct.hpp"
// Member 'poslla'
// Member 'posecef'
#include "geometry_msgs/msg/detail/point__struct.hpp"
// Member 'velned'
// Member 'velecef'
// Member 'posu'
#include "geometry_msgs/msg/detail/vector3__struct.hpp"
// Member 'dop'
#include "vectornav_msgs/msg/detail/dop__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__vectornav_msgs__msg__GpsGroup __attribute__((deprecated))
#else
# define DEPRECATED__vectornav_msgs__msg__GpsGroup __declspec(deprecated)
#endif

namespace vectornav_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct GpsGroup_
{
  using Type = GpsGroup_<ContainerAllocator>;

  explicit GpsGroup_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_init),
    utc(_init),
    poslla(_init),
    posecef(_init),
    velned(_init),
    velecef(_init),
    posu(_init),
    dop(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->group_fields = 0;
      this->tow = 0ull;
      this->week = 0;
      this->numsats = 0;
      this->fix = 0;
      this->velu = 0.0f;
      this->timeu = 0ul;
      this->timeinfo_status = 0;
      this->timeinfo_leapseconds = 0;
    }
  }

  explicit GpsGroup_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_alloc, _init),
    utc(_alloc, _init),
    poslla(_alloc, _init),
    posecef(_alloc, _init),
    velned(_alloc, _init),
    velecef(_alloc, _init),
    posu(_alloc, _init),
    dop(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->group_fields = 0;
      this->tow = 0ull;
      this->week = 0;
      this->numsats = 0;
      this->fix = 0;
      this->velu = 0.0f;
      this->timeu = 0ul;
      this->timeinfo_status = 0;
      this->timeinfo_leapseconds = 0;
    }
  }

  // field types and members
  using _header_type =
    std_msgs::msg::Header_<ContainerAllocator>;
  _header_type header;
  using _group_fields_type =
    uint16_t;
  _group_fields_type group_fields;
  using _utc_type =
    vectornav_msgs::msg::TimeUTC_<ContainerAllocator>;
  _utc_type utc;
  using _tow_type =
    uint64_t;
  _tow_type tow;
  using _week_type =
    uint16_t;
  _week_type week;
  using _numsats_type =
    uint8_t;
  _numsats_type numsats;
  using _fix_type =
    uint8_t;
  _fix_type fix;
  using _poslla_type =
    geometry_msgs::msg::Point_<ContainerAllocator>;
  _poslla_type poslla;
  using _posecef_type =
    geometry_msgs::msg::Point_<ContainerAllocator>;
  _posecef_type posecef;
  using _velned_type =
    geometry_msgs::msg::Vector3_<ContainerAllocator>;
  _velned_type velned;
  using _velecef_type =
    geometry_msgs::msg::Vector3_<ContainerAllocator>;
  _velecef_type velecef;
  using _posu_type =
    geometry_msgs::msg::Vector3_<ContainerAllocator>;
  _posu_type posu;
  using _velu_type =
    float;
  _velu_type velu;
  using _timeu_type =
    uint32_t;
  _timeu_type timeu;
  using _timeinfo_status_type =
    uint8_t;
  _timeinfo_status_type timeinfo_status;
  using _timeinfo_leapseconds_type =
    int8_t;
  _timeinfo_leapseconds_type timeinfo_leapseconds;
  using _dop_type =
    vectornav_msgs::msg::DOP_<ContainerAllocator>;
  _dop_type dop;

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
  Type & set__utc(
    const vectornav_msgs::msg::TimeUTC_<ContainerAllocator> & _arg)
  {
    this->utc = _arg;
    return *this;
  }
  Type & set__tow(
    const uint64_t & _arg)
  {
    this->tow = _arg;
    return *this;
  }
  Type & set__week(
    const uint16_t & _arg)
  {
    this->week = _arg;
    return *this;
  }
  Type & set__numsats(
    const uint8_t & _arg)
  {
    this->numsats = _arg;
    return *this;
  }
  Type & set__fix(
    const uint8_t & _arg)
  {
    this->fix = _arg;
    return *this;
  }
  Type & set__poslla(
    const geometry_msgs::msg::Point_<ContainerAllocator> & _arg)
  {
    this->poslla = _arg;
    return *this;
  }
  Type & set__posecef(
    const geometry_msgs::msg::Point_<ContainerAllocator> & _arg)
  {
    this->posecef = _arg;
    return *this;
  }
  Type & set__velned(
    const geometry_msgs::msg::Vector3_<ContainerAllocator> & _arg)
  {
    this->velned = _arg;
    return *this;
  }
  Type & set__velecef(
    const geometry_msgs::msg::Vector3_<ContainerAllocator> & _arg)
  {
    this->velecef = _arg;
    return *this;
  }
  Type & set__posu(
    const geometry_msgs::msg::Vector3_<ContainerAllocator> & _arg)
  {
    this->posu = _arg;
    return *this;
  }
  Type & set__velu(
    const float & _arg)
  {
    this->velu = _arg;
    return *this;
  }
  Type & set__timeu(
    const uint32_t & _arg)
  {
    this->timeu = _arg;
    return *this;
  }
  Type & set__timeinfo_status(
    const uint8_t & _arg)
  {
    this->timeinfo_status = _arg;
    return *this;
  }
  Type & set__timeinfo_leapseconds(
    const int8_t & _arg)
  {
    this->timeinfo_leapseconds = _arg;
    return *this;
  }
  Type & set__dop(
    const vectornav_msgs::msg::DOP_<ContainerAllocator> & _arg)
  {
    this->dop = _arg;
    return *this;
  }

  // constant declarations
  static constexpr uint16_t GPSGROUP_UTC =
    1u;
  static constexpr uint16_t GPSGROUP_TOW =
    2u;
  static constexpr uint16_t GPSGROUP_WEEK =
    4u;
  static constexpr uint16_t GPSGROUP_NUMSATS =
    8u;
  static constexpr uint16_t GPSGROUP_FIX =
    16u;
  static constexpr uint16_t GPSGROUP_POSLLA =
    32u;
  static constexpr uint16_t GPSGROUP_POSECEF =
    64u;
  static constexpr uint16_t GPSGROUP_VELNED =
    128u;
  static constexpr uint16_t GPSGROUP_VELECEF =
    256u;
  static constexpr uint16_t GPSGROUP_POSU =
    512u;
  static constexpr uint16_t GPSGROUP_VELU =
    1024u;
  static constexpr uint16_t GPSGROUP_TIMEU =
    2048u;
  static constexpr uint16_t GPSGROUP_TIMEINFO =
    4096u;
  static constexpr uint16_t GPSGROUP_DOP =
    8192u;
  static constexpr uint8_t GPSFIX_NOFIX =
    0u;
  static constexpr uint8_t GPSFIX_TIMEONLY =
    1u;
  static constexpr uint8_t GPSFIX_2D =
    2u;
  static constexpr uint8_t GPSFIX_3D =
    3u;

  // pointer types
  using RawPtr =
    vectornav_msgs::msg::GpsGroup_<ContainerAllocator> *;
  using ConstRawPtr =
    const vectornav_msgs::msg::GpsGroup_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<vectornav_msgs::msg::GpsGroup_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<vectornav_msgs::msg::GpsGroup_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      vectornav_msgs::msg::GpsGroup_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<vectornav_msgs::msg::GpsGroup_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      vectornav_msgs::msg::GpsGroup_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<vectornav_msgs::msg::GpsGroup_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<vectornav_msgs::msg::GpsGroup_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<vectornav_msgs::msg::GpsGroup_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__vectornav_msgs__msg__GpsGroup
    std::shared_ptr<vectornav_msgs::msg::GpsGroup_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__vectornav_msgs__msg__GpsGroup
    std::shared_ptr<vectornav_msgs::msg::GpsGroup_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const GpsGroup_ & other) const
  {
    if (this->header != other.header) {
      return false;
    }
    if (this->group_fields != other.group_fields) {
      return false;
    }
    if (this->utc != other.utc) {
      return false;
    }
    if (this->tow != other.tow) {
      return false;
    }
    if (this->week != other.week) {
      return false;
    }
    if (this->numsats != other.numsats) {
      return false;
    }
    if (this->fix != other.fix) {
      return false;
    }
    if (this->poslla != other.poslla) {
      return false;
    }
    if (this->posecef != other.posecef) {
      return false;
    }
    if (this->velned != other.velned) {
      return false;
    }
    if (this->velecef != other.velecef) {
      return false;
    }
    if (this->posu != other.posu) {
      return false;
    }
    if (this->velu != other.velu) {
      return false;
    }
    if (this->timeu != other.timeu) {
      return false;
    }
    if (this->timeinfo_status != other.timeinfo_status) {
      return false;
    }
    if (this->timeinfo_leapseconds != other.timeinfo_leapseconds) {
      return false;
    }
    if (this->dop != other.dop) {
      return false;
    }
    return true;
  }
  bool operator!=(const GpsGroup_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct GpsGroup_

// alias to use template instance with default allocator
using GpsGroup =
  vectornav_msgs::msg::GpsGroup_<std::allocator<void>>;

// constant definitions
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t GpsGroup_<ContainerAllocator>::GPSGROUP_UTC;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t GpsGroup_<ContainerAllocator>::GPSGROUP_TOW;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t GpsGroup_<ContainerAllocator>::GPSGROUP_WEEK;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t GpsGroup_<ContainerAllocator>::GPSGROUP_NUMSATS;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t GpsGroup_<ContainerAllocator>::GPSGROUP_FIX;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t GpsGroup_<ContainerAllocator>::GPSGROUP_POSLLA;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t GpsGroup_<ContainerAllocator>::GPSGROUP_POSECEF;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t GpsGroup_<ContainerAllocator>::GPSGROUP_VELNED;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t GpsGroup_<ContainerAllocator>::GPSGROUP_VELECEF;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t GpsGroup_<ContainerAllocator>::GPSGROUP_POSU;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t GpsGroup_<ContainerAllocator>::GPSGROUP_VELU;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t GpsGroup_<ContainerAllocator>::GPSGROUP_TIMEU;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t GpsGroup_<ContainerAllocator>::GPSGROUP_TIMEINFO;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t GpsGroup_<ContainerAllocator>::GPSGROUP_DOP;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t GpsGroup_<ContainerAllocator>::GPSFIX_NOFIX;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t GpsGroup_<ContainerAllocator>::GPSFIX_TIMEONLY;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t GpsGroup_<ContainerAllocator>::GPSFIX_2D;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t GpsGroup_<ContainerAllocator>::GPSFIX_3D;
#endif  // __cplusplus < 201703L

}  // namespace msg

}  // namespace vectornav_msgs

#endif  // VECTORNAV_MSGS__MSG__DETAIL__GPS_GROUP__STRUCT_HPP_
