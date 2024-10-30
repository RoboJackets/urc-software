// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from urc_msgs:msg/ArucoLocation.idl
// generated code does not contain a copyright notice

#ifndef URC_MSGS__MSG__DETAIL__ARUCO_LOCATION__STRUCT_HPP_
#define URC_MSGS__MSG__DETAIL__ARUCO_LOCATION__STRUCT_HPP_

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
# define DEPRECATED__urc_msgs__msg__ArucoLocation __attribute__((deprecated))
#else
# define DEPRECATED__urc_msgs__msg__ArucoLocation __declspec(deprecated)
#endif

namespace urc_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct ArucoLocation_
{
  using Type = ArucoLocation_<ContainerAllocator>;

  explicit ArucoLocation_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->lon = 0.0;
      this->lat = 0.0;
      this->id = 0ull;
      this->which_camera = "";
    }
  }

  explicit ArucoLocation_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_alloc, _init),
    which_camera(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->lon = 0.0;
      this->lat = 0.0;
      this->id = 0ull;
      this->which_camera = "";
    }
  }

  // field types and members
  using _header_type =
    std_msgs::msg::Header_<ContainerAllocator>;
  _header_type header;
  using _lon_type =
    double;
  _lon_type lon;
  using _lat_type =
    double;
  _lat_type lat;
  using _id_type =
    uint64_t;
  _id_type id;
  using _which_camera_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _which_camera_type which_camera;

  // setters for named parameter idiom
  Type & set__header(
    const std_msgs::msg::Header_<ContainerAllocator> & _arg)
  {
    this->header = _arg;
    return *this;
  }
  Type & set__lon(
    const double & _arg)
  {
    this->lon = _arg;
    return *this;
  }
  Type & set__lat(
    const double & _arg)
  {
    this->lat = _arg;
    return *this;
  }
  Type & set__id(
    const uint64_t & _arg)
  {
    this->id = _arg;
    return *this;
  }
  Type & set__which_camera(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->which_camera = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    urc_msgs::msg::ArucoLocation_<ContainerAllocator> *;
  using ConstRawPtr =
    const urc_msgs::msg::ArucoLocation_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<urc_msgs::msg::ArucoLocation_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<urc_msgs::msg::ArucoLocation_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      urc_msgs::msg::ArucoLocation_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<urc_msgs::msg::ArucoLocation_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      urc_msgs::msg::ArucoLocation_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<urc_msgs::msg::ArucoLocation_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<urc_msgs::msg::ArucoLocation_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<urc_msgs::msg::ArucoLocation_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__urc_msgs__msg__ArucoLocation
    std::shared_ptr<urc_msgs::msg::ArucoLocation_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__urc_msgs__msg__ArucoLocation
    std::shared_ptr<urc_msgs::msg::ArucoLocation_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const ArucoLocation_ & other) const
  {
    if (this->header != other.header) {
      return false;
    }
    if (this->lon != other.lon) {
      return false;
    }
    if (this->lat != other.lat) {
      return false;
    }
    if (this->id != other.id) {
      return false;
    }
    if (this->which_camera != other.which_camera) {
      return false;
    }
    return true;
  }
  bool operator!=(const ArucoLocation_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct ArucoLocation_

// alias to use template instance with default allocator
using ArucoLocation =
  urc_msgs::msg::ArucoLocation_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace urc_msgs

#endif  // URC_MSGS__MSG__DETAIL__ARUCO_LOCATION__STRUCT_HPP_
