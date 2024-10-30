// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from urc_msgs:msg/NavigationStatus.idl
// generated code does not contain a copyright notice

#ifndef URC_MSGS__MSG__DETAIL__NAVIGATION_STATUS__STRUCT_HPP_
#define URC_MSGS__MSG__DETAIL__NAVIGATION_STATUS__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__urc_msgs__msg__NavigationStatus __attribute__((deprecated))
#else
# define DEPRECATED__urc_msgs__msg__NavigationStatus __declspec(deprecated)
#endif

namespace urc_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct NavigationStatus_
{
  using Type = NavigationStatus_<ContainerAllocator>;

  explicit NavigationStatus_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->message = "";
    }
  }

  explicit NavigationStatus_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : message(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->message = "";
    }
  }

  // field types and members
  using _message_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _message_type message;

  // setters for named parameter idiom
  Type & set__message(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->message = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    urc_msgs::msg::NavigationStatus_<ContainerAllocator> *;
  using ConstRawPtr =
    const urc_msgs::msg::NavigationStatus_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<urc_msgs::msg::NavigationStatus_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<urc_msgs::msg::NavigationStatus_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      urc_msgs::msg::NavigationStatus_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<urc_msgs::msg::NavigationStatus_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      urc_msgs::msg::NavigationStatus_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<urc_msgs::msg::NavigationStatus_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<urc_msgs::msg::NavigationStatus_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<urc_msgs::msg::NavigationStatus_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__urc_msgs__msg__NavigationStatus
    std::shared_ptr<urc_msgs::msg::NavigationStatus_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__urc_msgs__msg__NavigationStatus
    std::shared_ptr<urc_msgs::msg::NavigationStatus_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const NavigationStatus_ & other) const
  {
    if (this->message != other.message) {
      return false;
    }
    return true;
  }
  bool operator!=(const NavigationStatus_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct NavigationStatus_

// alias to use template instance with default allocator
using NavigationStatus =
  urc_msgs::msg::NavigationStatus_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace urc_msgs

#endif  // URC_MSGS__MSG__DETAIL__NAVIGATION_STATUS__STRUCT_HPP_
