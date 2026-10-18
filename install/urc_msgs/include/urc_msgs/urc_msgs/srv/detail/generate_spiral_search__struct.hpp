// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from urc_msgs:srv/GenerateSpiralSearch.idl
// generated code does not contain a copyright notice

#ifndef URC_MSGS__SRV__DETAIL__GENERATE_SPIRAL_SEARCH__STRUCT_HPP_
#define URC_MSGS__SRV__DETAIL__GENERATE_SPIRAL_SEARCH__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'center'
#include "geometry_msgs/msg/detail/pose_stamped__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__urc_msgs__srv__GenerateSpiralSearch_Request __attribute__((deprecated))
#else
# define DEPRECATED__urc_msgs__srv__GenerateSpiralSearch_Request __declspec(deprecated)
#endif

namespace urc_msgs
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct GenerateSpiralSearch_Request_
{
  using Type = GenerateSpiralSearch_Request_<ContainerAllocator>;

  explicit GenerateSpiralSearch_Request_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : center(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->search_radius = 0.0;
      this->track_spacing = 0.0;
      this->waypoint_spacing = 0.0;
    }
  }

  explicit GenerateSpiralSearch_Request_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : center(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->search_radius = 0.0;
      this->track_spacing = 0.0;
      this->waypoint_spacing = 0.0;
    }
  }

  // field types and members
  using _center_type =
    geometry_msgs::msg::PoseStamped_<ContainerAllocator>;
  _center_type center;
  using _search_radius_type =
    double;
  _search_radius_type search_radius;
  using _track_spacing_type =
    double;
  _track_spacing_type track_spacing;
  using _waypoint_spacing_type =
    double;
  _waypoint_spacing_type waypoint_spacing;

  // setters for named parameter idiom
  Type & set__center(
    const geometry_msgs::msg::PoseStamped_<ContainerAllocator> & _arg)
  {
    this->center = _arg;
    return *this;
  }
  Type & set__search_radius(
    const double & _arg)
  {
    this->search_radius = _arg;
    return *this;
  }
  Type & set__track_spacing(
    const double & _arg)
  {
    this->track_spacing = _arg;
    return *this;
  }
  Type & set__waypoint_spacing(
    const double & _arg)
  {
    this->waypoint_spacing = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    urc_msgs::srv::GenerateSpiralSearch_Request_<ContainerAllocator> *;
  using ConstRawPtr =
    const urc_msgs::srv::GenerateSpiralSearch_Request_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<urc_msgs::srv::GenerateSpiralSearch_Request_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<urc_msgs::srv::GenerateSpiralSearch_Request_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      urc_msgs::srv::GenerateSpiralSearch_Request_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<urc_msgs::srv::GenerateSpiralSearch_Request_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      urc_msgs::srv::GenerateSpiralSearch_Request_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<urc_msgs::srv::GenerateSpiralSearch_Request_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<urc_msgs::srv::GenerateSpiralSearch_Request_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<urc_msgs::srv::GenerateSpiralSearch_Request_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__urc_msgs__srv__GenerateSpiralSearch_Request
    std::shared_ptr<urc_msgs::srv::GenerateSpiralSearch_Request_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__urc_msgs__srv__GenerateSpiralSearch_Request
    std::shared_ptr<urc_msgs::srv::GenerateSpiralSearch_Request_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const GenerateSpiralSearch_Request_ & other) const
  {
    if (this->center != other.center) {
      return false;
    }
    if (this->search_radius != other.search_radius) {
      return false;
    }
    if (this->track_spacing != other.track_spacing) {
      return false;
    }
    if (this->waypoint_spacing != other.waypoint_spacing) {
      return false;
    }
    return true;
  }
  bool operator!=(const GenerateSpiralSearch_Request_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct GenerateSpiralSearch_Request_

// alias to use template instance with default allocator
using GenerateSpiralSearch_Request =
  urc_msgs::srv::GenerateSpiralSearch_Request_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace urc_msgs


// Include directives for member types
// Member 'path'
#include "nav_msgs/msg/detail/path__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__urc_msgs__srv__GenerateSpiralSearch_Response __attribute__((deprecated))
#else
# define DEPRECATED__urc_msgs__srv__GenerateSpiralSearch_Response __declspec(deprecated)
#endif

namespace urc_msgs
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct GenerateSpiralSearch_Response_
{
  using Type = GenerateSpiralSearch_Response_<ContainerAllocator>;

  explicit GenerateSpiralSearch_Response_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : path(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->track_spacing = 0.0;
      this->path_length = 0.0;
      this->error_code = 0;
    }
  }

  explicit GenerateSpiralSearch_Response_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : path(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->track_spacing = 0.0;
      this->path_length = 0.0;
      this->error_code = 0;
    }
  }

  // field types and members
  using _path_type =
    nav_msgs::msg::Path_<ContainerAllocator>;
  _path_type path;
  using _track_spacing_type =
    double;
  _track_spacing_type track_spacing;
  using _path_length_type =
    double;
  _path_length_type path_length;
  using _error_code_type =
    uint16_t;
  _error_code_type error_code;

  // setters for named parameter idiom
  Type & set__path(
    const nav_msgs::msg::Path_<ContainerAllocator> & _arg)
  {
    this->path = _arg;
    return *this;
  }
  Type & set__track_spacing(
    const double & _arg)
  {
    this->track_spacing = _arg;
    return *this;
  }
  Type & set__path_length(
    const double & _arg)
  {
    this->path_length = _arg;
    return *this;
  }
  Type & set__error_code(
    const uint16_t & _arg)
  {
    this->error_code = _arg;
    return *this;
  }

  // constant declarations
  static constexpr uint16_t SUCCESS =
    0u;
  static constexpr uint16_t INVALID_REQUEST =
    1u;
  static constexpr uint16_t FAILURE =
    2u;

  // pointer types
  using RawPtr =
    urc_msgs::srv::GenerateSpiralSearch_Response_<ContainerAllocator> *;
  using ConstRawPtr =
    const urc_msgs::srv::GenerateSpiralSearch_Response_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<urc_msgs::srv::GenerateSpiralSearch_Response_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<urc_msgs::srv::GenerateSpiralSearch_Response_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      urc_msgs::srv::GenerateSpiralSearch_Response_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<urc_msgs::srv::GenerateSpiralSearch_Response_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      urc_msgs::srv::GenerateSpiralSearch_Response_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<urc_msgs::srv::GenerateSpiralSearch_Response_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<urc_msgs::srv::GenerateSpiralSearch_Response_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<urc_msgs::srv::GenerateSpiralSearch_Response_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__urc_msgs__srv__GenerateSpiralSearch_Response
    std::shared_ptr<urc_msgs::srv::GenerateSpiralSearch_Response_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__urc_msgs__srv__GenerateSpiralSearch_Response
    std::shared_ptr<urc_msgs::srv::GenerateSpiralSearch_Response_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const GenerateSpiralSearch_Response_ & other) const
  {
    if (this->path != other.path) {
      return false;
    }
    if (this->track_spacing != other.track_spacing) {
      return false;
    }
    if (this->path_length != other.path_length) {
      return false;
    }
    if (this->error_code != other.error_code) {
      return false;
    }
    return true;
  }
  bool operator!=(const GenerateSpiralSearch_Response_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct GenerateSpiralSearch_Response_

// alias to use template instance with default allocator
using GenerateSpiralSearch_Response =
  urc_msgs::srv::GenerateSpiralSearch_Response_<std::allocator<void>>;

// constant definitions
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t GenerateSpiralSearch_Response_<ContainerAllocator>::SUCCESS;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t GenerateSpiralSearch_Response_<ContainerAllocator>::INVALID_REQUEST;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t GenerateSpiralSearch_Response_<ContainerAllocator>::FAILURE;
#endif  // __cplusplus < 201703L

}  // namespace srv

}  // namespace urc_msgs

namespace urc_msgs
{

namespace srv
{

struct GenerateSpiralSearch
{
  using Request = urc_msgs::srv::GenerateSpiralSearch_Request;
  using Response = urc_msgs::srv::GenerateSpiralSearch_Response;
};

}  // namespace srv

}  // namespace urc_msgs

#endif  // URC_MSGS__SRV__DETAIL__GENERATE_SPIRAL_SEARCH__STRUCT_HPP_
