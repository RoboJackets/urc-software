// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from vectornav_msgs:msg/InsGroup.idl
// generated code does not contain a copyright notice

#ifndef VECTORNAV_MSGS__MSG__DETAIL__INS_GROUP__STRUCT_HPP_
#define VECTORNAV_MSGS__MSG__DETAIL__INS_GROUP__STRUCT_HPP_

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
// Member 'insstatus'
#include "vectornav_msgs/msg/detail/ins_status__struct.hpp"
// Member 'poslla'
// Member 'posecef'
#include "geometry_msgs/msg/detail/point__struct.hpp"
// Member 'velbody'
// Member 'velned'
// Member 'velecef'
// Member 'magecef'
// Member 'accelecef'
// Member 'linearaccelecef'
#include "geometry_msgs/msg/detail/vector3__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__vectornav_msgs__msg__InsGroup __attribute__((deprecated))
#else
# define DEPRECATED__vectornav_msgs__msg__InsGroup __declspec(deprecated)
#endif

namespace vectornav_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct InsGroup_
{
  using Type = InsGroup_<ContainerAllocator>;

  explicit InsGroup_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_init),
    insstatus(_init),
    poslla(_init),
    posecef(_init),
    velbody(_init),
    velned(_init),
    velecef(_init),
    magecef(_init),
    accelecef(_init),
    linearaccelecef(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->group_fields = 0;
      this->posu = 0.0f;
      this->velu = 0.0f;
    }
  }

  explicit InsGroup_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_alloc, _init),
    insstatus(_alloc, _init),
    poslla(_alloc, _init),
    posecef(_alloc, _init),
    velbody(_alloc, _init),
    velned(_alloc, _init),
    velecef(_alloc, _init),
    magecef(_alloc, _init),
    accelecef(_alloc, _init),
    linearaccelecef(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->group_fields = 0;
      this->posu = 0.0f;
      this->velu = 0.0f;
    }
  }

  // field types and members
  using _header_type =
    std_msgs::msg::Header_<ContainerAllocator>;
  _header_type header;
  using _group_fields_type =
    uint16_t;
  _group_fields_type group_fields;
  using _insstatus_type =
    vectornav_msgs::msg::InsStatus_<ContainerAllocator>;
  _insstatus_type insstatus;
  using _poslla_type =
    geometry_msgs::msg::Point_<ContainerAllocator>;
  _poslla_type poslla;
  using _posecef_type =
    geometry_msgs::msg::Point_<ContainerAllocator>;
  _posecef_type posecef;
  using _velbody_type =
    geometry_msgs::msg::Vector3_<ContainerAllocator>;
  _velbody_type velbody;
  using _velned_type =
    geometry_msgs::msg::Vector3_<ContainerAllocator>;
  _velned_type velned;
  using _velecef_type =
    geometry_msgs::msg::Vector3_<ContainerAllocator>;
  _velecef_type velecef;
  using _magecef_type =
    geometry_msgs::msg::Vector3_<ContainerAllocator>;
  _magecef_type magecef;
  using _accelecef_type =
    geometry_msgs::msg::Vector3_<ContainerAllocator>;
  _accelecef_type accelecef;
  using _linearaccelecef_type =
    geometry_msgs::msg::Vector3_<ContainerAllocator>;
  _linearaccelecef_type linearaccelecef;
  using _posu_type =
    float;
  _posu_type posu;
  using _velu_type =
    float;
  _velu_type velu;

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
  Type & set__insstatus(
    const vectornav_msgs::msg::InsStatus_<ContainerAllocator> & _arg)
  {
    this->insstatus = _arg;
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
  Type & set__velbody(
    const geometry_msgs::msg::Vector3_<ContainerAllocator> & _arg)
  {
    this->velbody = _arg;
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
  Type & set__magecef(
    const geometry_msgs::msg::Vector3_<ContainerAllocator> & _arg)
  {
    this->magecef = _arg;
    return *this;
  }
  Type & set__accelecef(
    const geometry_msgs::msg::Vector3_<ContainerAllocator> & _arg)
  {
    this->accelecef = _arg;
    return *this;
  }
  Type & set__linearaccelecef(
    const geometry_msgs::msg::Vector3_<ContainerAllocator> & _arg)
  {
    this->linearaccelecef = _arg;
    return *this;
  }
  Type & set__posu(
    const float & _arg)
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

  // constant declarations
  static constexpr uint16_t INSGROUP_INSSTATUS =
    1u;
  static constexpr uint16_t INSGROUP_POSLLA =
    2u;
  static constexpr uint16_t INSGROUP_POSECEF =
    4u;
  static constexpr uint16_t INSGROUP_VELBODY =
    8u;
  static constexpr uint16_t INSGROUP_VELNED =
    16u;
  static constexpr uint16_t INSGROUP_VELECEF =
    32u;
  static constexpr uint16_t INSGROUP_MAGECEF =
    64u;
  static constexpr uint16_t INSGROUP_ACCELECEF =
    128u;
  static constexpr uint16_t INSGROUP_LINEARACCELECEF =
    256u;
  static constexpr uint16_t INSGROUP_POSU =
    512u;
  static constexpr uint16_t INSGROUP_VELU =
    1024u;

  // pointer types
  using RawPtr =
    vectornav_msgs::msg::InsGroup_<ContainerAllocator> *;
  using ConstRawPtr =
    const vectornav_msgs::msg::InsGroup_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<vectornav_msgs::msg::InsGroup_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<vectornav_msgs::msg::InsGroup_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      vectornav_msgs::msg::InsGroup_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<vectornav_msgs::msg::InsGroup_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      vectornav_msgs::msg::InsGroup_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<vectornav_msgs::msg::InsGroup_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<vectornav_msgs::msg::InsGroup_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<vectornav_msgs::msg::InsGroup_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__vectornav_msgs__msg__InsGroup
    std::shared_ptr<vectornav_msgs::msg::InsGroup_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__vectornav_msgs__msg__InsGroup
    std::shared_ptr<vectornav_msgs::msg::InsGroup_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const InsGroup_ & other) const
  {
    if (this->header != other.header) {
      return false;
    }
    if (this->group_fields != other.group_fields) {
      return false;
    }
    if (this->insstatus != other.insstatus) {
      return false;
    }
    if (this->poslla != other.poslla) {
      return false;
    }
    if (this->posecef != other.posecef) {
      return false;
    }
    if (this->velbody != other.velbody) {
      return false;
    }
    if (this->velned != other.velned) {
      return false;
    }
    if (this->velecef != other.velecef) {
      return false;
    }
    if (this->magecef != other.magecef) {
      return false;
    }
    if (this->accelecef != other.accelecef) {
      return false;
    }
    if (this->linearaccelecef != other.linearaccelecef) {
      return false;
    }
    if (this->posu != other.posu) {
      return false;
    }
    if (this->velu != other.velu) {
      return false;
    }
    return true;
  }
  bool operator!=(const InsGroup_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct InsGroup_

// alias to use template instance with default allocator
using InsGroup =
  vectornav_msgs::msg::InsGroup_<std::allocator<void>>;

// constant definitions
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t InsGroup_<ContainerAllocator>::INSGROUP_INSSTATUS;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t InsGroup_<ContainerAllocator>::INSGROUP_POSLLA;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t InsGroup_<ContainerAllocator>::INSGROUP_POSECEF;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t InsGroup_<ContainerAllocator>::INSGROUP_VELBODY;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t InsGroup_<ContainerAllocator>::INSGROUP_VELNED;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t InsGroup_<ContainerAllocator>::INSGROUP_VELECEF;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t InsGroup_<ContainerAllocator>::INSGROUP_MAGECEF;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t InsGroup_<ContainerAllocator>::INSGROUP_ACCELECEF;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t InsGroup_<ContainerAllocator>::INSGROUP_LINEARACCELECEF;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t InsGroup_<ContainerAllocator>::INSGROUP_POSU;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t InsGroup_<ContainerAllocator>::INSGROUP_VELU;
#endif  // __cplusplus < 201703L

}  // namespace msg

}  // namespace vectornav_msgs

#endif  // VECTORNAV_MSGS__MSG__DETAIL__INS_GROUP__STRUCT_HPP_
