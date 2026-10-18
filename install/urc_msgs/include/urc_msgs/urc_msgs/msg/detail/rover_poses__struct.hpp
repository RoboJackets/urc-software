// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from urc_msgs:msg/RoverPoses.idl
// generated code does not contain a copyright notice

#ifndef URC_MSGS__MSG__DETAIL__ROVER_POSES__STRUCT_HPP_
#define URC_MSGS__MSG__DETAIL__ROVER_POSES__STRUCT_HPP_

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
// Member 'poses'
#include "geometry_msgs/msg/detail/pose__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__urc_msgs__msg__RoverPoses __attribute__((deprecated))
#else
# define DEPRECATED__urc_msgs__msg__RoverPoses __declspec(deprecated)
#endif

namespace urc_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct RoverPoses_
{
  using Type = RoverPoses_<ContainerAllocator>;

  explicit RoverPoses_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_init)
  {
    (void)_init;
  }

  explicit RoverPoses_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_alloc, _init)
  {
    (void)_init;
  }

  // field types and members
  using _header_type =
    std_msgs::msg::Header_<ContainerAllocator>;
  _header_type header;
  using _names_type =
    std::vector<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>>>;
  _names_type names;
  using _poses_type =
    std::vector<geometry_msgs::msg::Pose_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<geometry_msgs::msg::Pose_<ContainerAllocator>>>;
  _poses_type poses;

  // setters for named parameter idiom
  Type & set__header(
    const std_msgs::msg::Header_<ContainerAllocator> & _arg)
  {
    this->header = _arg;
    return *this;
  }
  Type & set__names(
    const std::vector<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>>> & _arg)
  {
    this->names = _arg;
    return *this;
  }
  Type & set__poses(
    const std::vector<geometry_msgs::msg::Pose_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<geometry_msgs::msg::Pose_<ContainerAllocator>>> & _arg)
  {
    this->poses = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    urc_msgs::msg::RoverPoses_<ContainerAllocator> *;
  using ConstRawPtr =
    const urc_msgs::msg::RoverPoses_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<urc_msgs::msg::RoverPoses_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<urc_msgs::msg::RoverPoses_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      urc_msgs::msg::RoverPoses_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<urc_msgs::msg::RoverPoses_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      urc_msgs::msg::RoverPoses_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<urc_msgs::msg::RoverPoses_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<urc_msgs::msg::RoverPoses_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<urc_msgs::msg::RoverPoses_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__urc_msgs__msg__RoverPoses
    std::shared_ptr<urc_msgs::msg::RoverPoses_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__urc_msgs__msg__RoverPoses
    std::shared_ptr<urc_msgs::msg::RoverPoses_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const RoverPoses_ & other) const
  {
    if (this->header != other.header) {
      return false;
    }
    if (this->names != other.names) {
      return false;
    }
    if (this->poses != other.poses) {
      return false;
    }
    return true;
  }
  bool operator!=(const RoverPoses_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct RoverPoses_

// alias to use template instance with default allocator
using RoverPoses =
  urc_msgs::msg::RoverPoses_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace urc_msgs

#endif  // URC_MSGS__MSG__DETAIL__ROVER_POSES__STRUCT_HPP_
