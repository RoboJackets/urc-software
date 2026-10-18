// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from vectornav_msgs:msg/AttitudeGroup.idl
// generated code does not contain a copyright notice

#ifndef VECTORNAV_MSGS__MSG__DETAIL__ATTITUDE_GROUP__STRUCT_HPP_
#define VECTORNAV_MSGS__MSG__DETAIL__ATTITUDE_GROUP__STRUCT_HPP_

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
// Member 'vpestatus'
#include "vectornav_msgs/msg/detail/vpe_status__struct.hpp"
// Member 'yawpitchroll'
// Member 'magned'
// Member 'accelned'
// Member 'linearaccelbody'
// Member 'linearaccelned'
// Member 'ypru'
#include "geometry_msgs/msg/detail/vector3__struct.hpp"
// Member 'quaternion'
#include "geometry_msgs/msg/detail/quaternion__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__vectornav_msgs__msg__AttitudeGroup __attribute__((deprecated))
#else
# define DEPRECATED__vectornav_msgs__msg__AttitudeGroup __declspec(deprecated)
#endif

namespace vectornav_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct AttitudeGroup_
{
  using Type = AttitudeGroup_<ContainerAllocator>;

  explicit AttitudeGroup_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_init),
    vpestatus(_init),
    yawpitchroll(_init),
    quaternion(_init),
    magned(_init),
    accelned(_init),
    linearaccelbody(_init),
    linearaccelned(_init),
    ypru(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->group_fields = 0;
      std::fill<typename std::array<float, 9>::iterator, float>(this->dcm.begin(), this->dcm.end(), 0.0f);
    }
  }

  explicit AttitudeGroup_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_alloc, _init),
    vpestatus(_alloc, _init),
    yawpitchroll(_alloc, _init),
    quaternion(_alloc, _init),
    dcm(_alloc),
    magned(_alloc, _init),
    accelned(_alloc, _init),
    linearaccelbody(_alloc, _init),
    linearaccelned(_alloc, _init),
    ypru(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->group_fields = 0;
      std::fill<typename std::array<float, 9>::iterator, float>(this->dcm.begin(), this->dcm.end(), 0.0f);
    }
  }

  // field types and members
  using _header_type =
    std_msgs::msg::Header_<ContainerAllocator>;
  _header_type header;
  using _group_fields_type =
    uint16_t;
  _group_fields_type group_fields;
  using _vpestatus_type =
    vectornav_msgs::msg::VpeStatus_<ContainerAllocator>;
  _vpestatus_type vpestatus;
  using _yawpitchroll_type =
    geometry_msgs::msg::Vector3_<ContainerAllocator>;
  _yawpitchroll_type yawpitchroll;
  using _quaternion_type =
    geometry_msgs::msg::Quaternion_<ContainerAllocator>;
  _quaternion_type quaternion;
  using _dcm_type =
    std::array<float, 9>;
  _dcm_type dcm;
  using _magned_type =
    geometry_msgs::msg::Vector3_<ContainerAllocator>;
  _magned_type magned;
  using _accelned_type =
    geometry_msgs::msg::Vector3_<ContainerAllocator>;
  _accelned_type accelned;
  using _linearaccelbody_type =
    geometry_msgs::msg::Vector3_<ContainerAllocator>;
  _linearaccelbody_type linearaccelbody;
  using _linearaccelned_type =
    geometry_msgs::msg::Vector3_<ContainerAllocator>;
  _linearaccelned_type linearaccelned;
  using _ypru_type =
    geometry_msgs::msg::Vector3_<ContainerAllocator>;
  _ypru_type ypru;

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
  Type & set__vpestatus(
    const vectornav_msgs::msg::VpeStatus_<ContainerAllocator> & _arg)
  {
    this->vpestatus = _arg;
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
  Type & set__dcm(
    const std::array<float, 9> & _arg)
  {
    this->dcm = _arg;
    return *this;
  }
  Type & set__magned(
    const geometry_msgs::msg::Vector3_<ContainerAllocator> & _arg)
  {
    this->magned = _arg;
    return *this;
  }
  Type & set__accelned(
    const geometry_msgs::msg::Vector3_<ContainerAllocator> & _arg)
  {
    this->accelned = _arg;
    return *this;
  }
  Type & set__linearaccelbody(
    const geometry_msgs::msg::Vector3_<ContainerAllocator> & _arg)
  {
    this->linearaccelbody = _arg;
    return *this;
  }
  Type & set__linearaccelned(
    const geometry_msgs::msg::Vector3_<ContainerAllocator> & _arg)
  {
    this->linearaccelned = _arg;
    return *this;
  }
  Type & set__ypru(
    const geometry_msgs::msg::Vector3_<ContainerAllocator> & _arg)
  {
    this->ypru = _arg;
    return *this;
  }

  // constant declarations
  static constexpr uint16_t ATTITUDEGROUP_VPESTATUS =
    1u;
  static constexpr uint16_t ATTITUDEGROUP_YAWPITCHROLL =
    2u;
  static constexpr uint16_t ATTITUDEGROUP_QUATERNION =
    4u;
  static constexpr uint16_t ATTITUDEGROUP_DCM =
    8u;
  static constexpr uint16_t ATTITUDEGROUP_MAGNED =
    16u;
  static constexpr uint16_t ATTITUDEGROUP_ACCELNED =
    32u;
  static constexpr uint16_t ATTITUDEGROUP_LINEARACCELBODY =
    64u;
  static constexpr uint16_t ATTITUDEGROUP_LINEARACCELNED =
    128u;
  static constexpr uint16_t ATTITUDEGROUP_YPRU =
    256u;

  // pointer types
  using RawPtr =
    vectornav_msgs::msg::AttitudeGroup_<ContainerAllocator> *;
  using ConstRawPtr =
    const vectornav_msgs::msg::AttitudeGroup_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<vectornav_msgs::msg::AttitudeGroup_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<vectornav_msgs::msg::AttitudeGroup_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      vectornav_msgs::msg::AttitudeGroup_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<vectornav_msgs::msg::AttitudeGroup_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      vectornav_msgs::msg::AttitudeGroup_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<vectornav_msgs::msg::AttitudeGroup_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<vectornav_msgs::msg::AttitudeGroup_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<vectornav_msgs::msg::AttitudeGroup_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__vectornav_msgs__msg__AttitudeGroup
    std::shared_ptr<vectornav_msgs::msg::AttitudeGroup_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__vectornav_msgs__msg__AttitudeGroup
    std::shared_ptr<vectornav_msgs::msg::AttitudeGroup_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const AttitudeGroup_ & other) const
  {
    if (this->header != other.header) {
      return false;
    }
    if (this->group_fields != other.group_fields) {
      return false;
    }
    if (this->vpestatus != other.vpestatus) {
      return false;
    }
    if (this->yawpitchroll != other.yawpitchroll) {
      return false;
    }
    if (this->quaternion != other.quaternion) {
      return false;
    }
    if (this->dcm != other.dcm) {
      return false;
    }
    if (this->magned != other.magned) {
      return false;
    }
    if (this->accelned != other.accelned) {
      return false;
    }
    if (this->linearaccelbody != other.linearaccelbody) {
      return false;
    }
    if (this->linearaccelned != other.linearaccelned) {
      return false;
    }
    if (this->ypru != other.ypru) {
      return false;
    }
    return true;
  }
  bool operator!=(const AttitudeGroup_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct AttitudeGroup_

// alias to use template instance with default allocator
using AttitudeGroup =
  vectornav_msgs::msg::AttitudeGroup_<std::allocator<void>>;

// constant definitions
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t AttitudeGroup_<ContainerAllocator>::ATTITUDEGROUP_VPESTATUS;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t AttitudeGroup_<ContainerAllocator>::ATTITUDEGROUP_YAWPITCHROLL;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t AttitudeGroup_<ContainerAllocator>::ATTITUDEGROUP_QUATERNION;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t AttitudeGroup_<ContainerAllocator>::ATTITUDEGROUP_DCM;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t AttitudeGroup_<ContainerAllocator>::ATTITUDEGROUP_MAGNED;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t AttitudeGroup_<ContainerAllocator>::ATTITUDEGROUP_ACCELNED;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t AttitudeGroup_<ContainerAllocator>::ATTITUDEGROUP_LINEARACCELBODY;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t AttitudeGroup_<ContainerAllocator>::ATTITUDEGROUP_LINEARACCELNED;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t AttitudeGroup_<ContainerAllocator>::ATTITUDEGROUP_YPRU;
#endif  // __cplusplus < 201703L

}  // namespace msg

}  // namespace vectornav_msgs

#endif  // VECTORNAV_MSGS__MSG__DETAIL__ATTITUDE_GROUP__STRUCT_HPP_
