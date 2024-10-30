// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from urc_msgs:msg/StatusLightCommand.idl
// generated code does not contain a copyright notice

#ifndef URC_MSGS__MSG__DETAIL__STATUS_LIGHT_COMMAND__STRUCT_HPP_
#define URC_MSGS__MSG__DETAIL__STATUS_LIGHT_COMMAND__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__urc_msgs__msg__StatusLightCommand __attribute__((deprecated))
#else
# define DEPRECATED__urc_msgs__msg__StatusLightCommand __declspec(deprecated)
#endif

namespace urc_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct StatusLightCommand_
{
  using Type = StatusLightCommand_<ContainerAllocator>;

  explicit StatusLightCommand_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->color = 0;
      this->state = 0;
    }
  }

  explicit StatusLightCommand_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->color = 0;
      this->state = 0;
    }
  }

  // field types and members
  using _color_type =
    uint8_t;
  _color_type color;
  using _state_type =
    uint8_t;
  _state_type state;

  // setters for named parameter idiom
  Type & set__color(
    const uint8_t & _arg)
  {
    this->color = _arg;
    return *this;
  }
  Type & set__state(
    const uint8_t & _arg)
  {
    this->state = _arg;
    return *this;
  }

  // constant declarations
  static constexpr uint8_t RED =
    0u;
  static constexpr uint8_t GREEN =
    1u;
  static constexpr uint8_t BLUE =
    2u;
  static constexpr uint8_t OFF =
    0u;
  static constexpr uint8_t ON =
    1u;
  static constexpr uint8_t BLINK =
    2u;

  // pointer types
  using RawPtr =
    urc_msgs::msg::StatusLightCommand_<ContainerAllocator> *;
  using ConstRawPtr =
    const urc_msgs::msg::StatusLightCommand_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<urc_msgs::msg::StatusLightCommand_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<urc_msgs::msg::StatusLightCommand_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      urc_msgs::msg::StatusLightCommand_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<urc_msgs::msg::StatusLightCommand_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      urc_msgs::msg::StatusLightCommand_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<urc_msgs::msg::StatusLightCommand_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<urc_msgs::msg::StatusLightCommand_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<urc_msgs::msg::StatusLightCommand_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__urc_msgs__msg__StatusLightCommand
    std::shared_ptr<urc_msgs::msg::StatusLightCommand_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__urc_msgs__msg__StatusLightCommand
    std::shared_ptr<urc_msgs::msg::StatusLightCommand_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const StatusLightCommand_ & other) const
  {
    if (this->color != other.color) {
      return false;
    }
    if (this->state != other.state) {
      return false;
    }
    return true;
  }
  bool operator!=(const StatusLightCommand_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct StatusLightCommand_

// alias to use template instance with default allocator
using StatusLightCommand =
  urc_msgs::msg::StatusLightCommand_<std::allocator<void>>;

// constant definitions
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t StatusLightCommand_<ContainerAllocator>::RED;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t StatusLightCommand_<ContainerAllocator>::GREEN;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t StatusLightCommand_<ContainerAllocator>::BLUE;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t StatusLightCommand_<ContainerAllocator>::OFF;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t StatusLightCommand_<ContainerAllocator>::ON;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t StatusLightCommand_<ContainerAllocator>::BLINK;
#endif  // __cplusplus < 201703L

}  // namespace msg

}  // namespace urc_msgs

#endif  // URC_MSGS__MSG__DETAIL__STATUS_LIGHT_COMMAND__STRUCT_HPP_
