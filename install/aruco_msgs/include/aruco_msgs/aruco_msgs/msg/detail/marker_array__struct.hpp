// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from aruco_msgs:msg/MarkerArray.idl
// generated code does not contain a copyright notice

#ifndef ARUCO_MSGS__MSG__DETAIL__MARKER_ARRAY__STRUCT_HPP_
#define ARUCO_MSGS__MSG__DETAIL__MARKER_ARRAY__STRUCT_HPP_

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
// Member 'markers'
#include "aruco_msgs/msg/detail/marker__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__aruco_msgs__msg__MarkerArray __attribute__((deprecated))
#else
# define DEPRECATED__aruco_msgs__msg__MarkerArray __declspec(deprecated)
#endif

namespace aruco_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct MarkerArray_
{
  using Type = MarkerArray_<ContainerAllocator>;

  explicit MarkerArray_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_init)
  {
    (void)_init;
  }

  explicit MarkerArray_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_alloc, _init)
  {
    (void)_init;
  }

  // field types and members
  using _header_type =
    std_msgs::msg::Header_<ContainerAllocator>;
  _header_type header;
  using _markers_type =
    std::vector<aruco_msgs::msg::Marker_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<aruco_msgs::msg::Marker_<ContainerAllocator>>>;
  _markers_type markers;

  // setters for named parameter idiom
  Type & set__header(
    const std_msgs::msg::Header_<ContainerAllocator> & _arg)
  {
    this->header = _arg;
    return *this;
  }
  Type & set__markers(
    const std::vector<aruco_msgs::msg::Marker_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<aruco_msgs::msg::Marker_<ContainerAllocator>>> & _arg)
  {
    this->markers = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    aruco_msgs::msg::MarkerArray_<ContainerAllocator> *;
  using ConstRawPtr =
    const aruco_msgs::msg::MarkerArray_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<aruco_msgs::msg::MarkerArray_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<aruco_msgs::msg::MarkerArray_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      aruco_msgs::msg::MarkerArray_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<aruco_msgs::msg::MarkerArray_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      aruco_msgs::msg::MarkerArray_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<aruco_msgs::msg::MarkerArray_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<aruco_msgs::msg::MarkerArray_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<aruco_msgs::msg::MarkerArray_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__aruco_msgs__msg__MarkerArray
    std::shared_ptr<aruco_msgs::msg::MarkerArray_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__aruco_msgs__msg__MarkerArray
    std::shared_ptr<aruco_msgs::msg::MarkerArray_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const MarkerArray_ & other) const
  {
    if (this->header != other.header) {
      return false;
    }
    if (this->markers != other.markers) {
      return false;
    }
    return true;
  }
  bool operator!=(const MarkerArray_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct MarkerArray_

// alias to use template instance with default allocator
using MarkerArray =
  aruco_msgs::msg::MarkerArray_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace aruco_msgs

#endif  // ARUCO_MSGS__MSG__DETAIL__MARKER_ARRAY__STRUCT_HPP_
