// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from urc_msgs:srv/GeneratePlan.idl
// generated code does not contain a copyright notice

#ifndef URC_MSGS__SRV__DETAIL__GENERATE_PLAN__STRUCT_HPP_
#define URC_MSGS__SRV__DETAIL__GENERATE_PLAN__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'goal'
// Member 'start'
#include "geometry_msgs/msg/detail/pose_stamped__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__urc_msgs__srv__GeneratePlan_Request __attribute__((deprecated))
#else
# define DEPRECATED__urc_msgs__srv__GeneratePlan_Request __declspec(deprecated)
#endif

namespace urc_msgs
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct GeneratePlan_Request_
{
  using Type = GeneratePlan_Request_<ContainerAllocator>;

  explicit GeneratePlan_Request_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : goal(_init),
    start(_init)
  {
    (void)_init;
  }

  explicit GeneratePlan_Request_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : goal(_alloc, _init),
    start(_alloc, _init)
  {
    (void)_init;
  }

  // field types and members
  using _goal_type =
    geometry_msgs::msg::PoseStamped_<ContainerAllocator>;
  _goal_type goal;
  using _start_type =
    geometry_msgs::msg::PoseStamped_<ContainerAllocator>;
  _start_type start;

  // setters for named parameter idiom
  Type & set__goal(
    const geometry_msgs::msg::PoseStamped_<ContainerAllocator> & _arg)
  {
    this->goal = _arg;
    return *this;
  }
  Type & set__start(
    const geometry_msgs::msg::PoseStamped_<ContainerAllocator> & _arg)
  {
    this->start = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    urc_msgs::srv::GeneratePlan_Request_<ContainerAllocator> *;
  using ConstRawPtr =
    const urc_msgs::srv::GeneratePlan_Request_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<urc_msgs::srv::GeneratePlan_Request_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<urc_msgs::srv::GeneratePlan_Request_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      urc_msgs::srv::GeneratePlan_Request_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<urc_msgs::srv::GeneratePlan_Request_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      urc_msgs::srv::GeneratePlan_Request_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<urc_msgs::srv::GeneratePlan_Request_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<urc_msgs::srv::GeneratePlan_Request_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<urc_msgs::srv::GeneratePlan_Request_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__urc_msgs__srv__GeneratePlan_Request
    std::shared_ptr<urc_msgs::srv::GeneratePlan_Request_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__urc_msgs__srv__GeneratePlan_Request
    std::shared_ptr<urc_msgs::srv::GeneratePlan_Request_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const GeneratePlan_Request_ & other) const
  {
    if (this->goal != other.goal) {
      return false;
    }
    if (this->start != other.start) {
      return false;
    }
    return true;
  }
  bool operator!=(const GeneratePlan_Request_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct GeneratePlan_Request_

// alias to use template instance with default allocator
using GeneratePlan_Request =
  urc_msgs::srv::GeneratePlan_Request_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace urc_msgs


// Include directives for member types
// Member 'path'
#include "nav_msgs/msg/detail/path__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__urc_msgs__srv__GeneratePlan_Response __attribute__((deprecated))
#else
# define DEPRECATED__urc_msgs__srv__GeneratePlan_Response __declspec(deprecated)
#endif

namespace urc_msgs
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct GeneratePlan_Response_
{
  using Type = GeneratePlan_Response_<ContainerAllocator>;

  explicit GeneratePlan_Response_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : path(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->error_code = 0;
    }
  }

  explicit GeneratePlan_Response_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : path(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->error_code = 0;
    }
  }

  // field types and members
  using _path_type =
    nav_msgs::msg::Path_<ContainerAllocator>;
  _path_type path;
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
  Type & set__error_code(
    const uint16_t & _arg)
  {
    this->error_code = _arg;
    return *this;
  }

  // constant declarations
  static constexpr uint16_t SUCCESS =
    0u;
  static constexpr uint16_t FAILURE =
    1u;

  // pointer types
  using RawPtr =
    urc_msgs::srv::GeneratePlan_Response_<ContainerAllocator> *;
  using ConstRawPtr =
    const urc_msgs::srv::GeneratePlan_Response_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<urc_msgs::srv::GeneratePlan_Response_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<urc_msgs::srv::GeneratePlan_Response_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      urc_msgs::srv::GeneratePlan_Response_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<urc_msgs::srv::GeneratePlan_Response_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      urc_msgs::srv::GeneratePlan_Response_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<urc_msgs::srv::GeneratePlan_Response_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<urc_msgs::srv::GeneratePlan_Response_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<urc_msgs::srv::GeneratePlan_Response_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__urc_msgs__srv__GeneratePlan_Response
    std::shared_ptr<urc_msgs::srv::GeneratePlan_Response_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__urc_msgs__srv__GeneratePlan_Response
    std::shared_ptr<urc_msgs::srv::GeneratePlan_Response_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const GeneratePlan_Response_ & other) const
  {
    if (this->path != other.path) {
      return false;
    }
    if (this->error_code != other.error_code) {
      return false;
    }
    return true;
  }
  bool operator!=(const GeneratePlan_Response_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct GeneratePlan_Response_

// alias to use template instance with default allocator
using GeneratePlan_Response =
  urc_msgs::srv::GeneratePlan_Response_<std::allocator<void>>;

// constant definitions
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t GeneratePlan_Response_<ContainerAllocator>::SUCCESS;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t GeneratePlan_Response_<ContainerAllocator>::FAILURE;
#endif  // __cplusplus < 201703L

}  // namespace srv

}  // namespace urc_msgs

namespace urc_msgs
{

namespace srv
{

struct GeneratePlan
{
  using Request = urc_msgs::srv::GeneratePlan_Request;
  using Response = urc_msgs::srv::GeneratePlan_Response;
};

}  // namespace srv

}  // namespace urc_msgs

#endif  // URC_MSGS__SRV__DETAIL__GENERATE_PLAN__STRUCT_HPP_
