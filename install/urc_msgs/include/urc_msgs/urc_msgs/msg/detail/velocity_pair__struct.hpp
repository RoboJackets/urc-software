// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from urc_msgs:msg/VelocityPair.idl
// generated code does not contain a copyright notice

#ifndef URC_MSGS__MSG__DETAIL__VELOCITY_PAIR__STRUCT_HPP_
#define URC_MSGS__MSG__DETAIL__VELOCITY_PAIR__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__urc_msgs__msg__VelocityPair __attribute__((deprecated))
#else
# define DEPRECATED__urc_msgs__msg__VelocityPair __declspec(deprecated)
#endif

namespace urc_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct VelocityPair_
{
  using Type = VelocityPair_<ContainerAllocator>;

  explicit VelocityPair_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->left_velocity = 0.0;
      this->right_velocity = 0.0;
      this->duration = 0.0;
    }
  }

  explicit VelocityPair_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->left_velocity = 0.0;
      this->right_velocity = 0.0;
      this->duration = 0.0;
    }
  }

  // field types and members
  using _header_type =
    std_msgs::msg::Header_<ContainerAllocator>;
  _header_type header;
  using _left_velocity_type =
    double;
  _left_velocity_type left_velocity;
  using _right_velocity_type =
    double;
  _right_velocity_type right_velocity;
  using _duration_type =
    double;
  _duration_type duration;

  // setters for named parameter idiom
  Type & set__header(
    const std_msgs::msg::Header_<ContainerAllocator> & _arg)
  {
    this->header = _arg;
    return *this;
  }
  Type & set__left_velocity(
    const double & _arg)
  {
    this->left_velocity = _arg;
    return *this;
  }
  Type & set__right_velocity(
    const double & _arg)
  {
    this->right_velocity = _arg;
    return *this;
  }
  Type & set__duration(
    const double & _arg)
  {
    this->duration = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    urc_msgs::msg::VelocityPair_<ContainerAllocator> *;
  using ConstRawPtr =
    const urc_msgs::msg::VelocityPair_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<urc_msgs::msg::VelocityPair_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<urc_msgs::msg::VelocityPair_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      urc_msgs::msg::VelocityPair_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<urc_msgs::msg::VelocityPair_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      urc_msgs::msg::VelocityPair_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<urc_msgs::msg::VelocityPair_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<urc_msgs::msg::VelocityPair_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<urc_msgs::msg::VelocityPair_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__urc_msgs__msg__VelocityPair
    std::shared_ptr<urc_msgs::msg::VelocityPair_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__urc_msgs__msg__VelocityPair
    std::shared_ptr<urc_msgs::msg::VelocityPair_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const VelocityPair_ & other) const
  {
    if (this->header != other.header) {
      return false;
    }
    if (this->left_velocity != other.left_velocity) {
      return false;
    }
    if (this->right_velocity != other.right_velocity) {
      return false;
    }
    if (this->duration != other.duration) {
      return false;
    }
    return true;
  }
  bool operator!=(const VelocityPair_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct VelocityPair_

// alias to use template instance with default allocator
using VelocityPair =
  urc_msgs::msg::VelocityPair_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace urc_msgs

#endif  // URC_MSGS__MSG__DETAIL__VELOCITY_PAIR__STRUCT_HPP_
