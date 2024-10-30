// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from urc_msgs:msg/LandingLocations.idl
// generated code does not contain a copyright notice

#ifndef URC_MSGS__MSG__DETAIL__LANDING_LOCATIONS__STRUCT_HPP_
#define URC_MSGS__MSG__DETAIL__LANDING_LOCATIONS__STRUCT_HPP_

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
# define DEPRECATED__urc_msgs__msg__LandingLocations __attribute__((deprecated))
#else
# define DEPRECATED__urc_msgs__msg__LandingLocations __declspec(deprecated)
#endif

namespace urc_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct LandingLocations_
{
  using Type = LandingLocations_<ContainerAllocator>;

  explicit LandingLocations_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->num_locations = 0l;
      std::fill<typename std::array<double, 100>::iterator, double>(this->latitudes.begin(), this->latitudes.end(), 0.0);
      std::fill<typename std::array<double, 100>::iterator, double>(this->longitudes.begin(), this->longitudes.end(), 0.0);
    }
  }

  explicit LandingLocations_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_alloc, _init),
    latitudes(_alloc),
    longitudes(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->num_locations = 0l;
      std::fill<typename std::array<double, 100>::iterator, double>(this->latitudes.begin(), this->latitudes.end(), 0.0);
      std::fill<typename std::array<double, 100>::iterator, double>(this->longitudes.begin(), this->longitudes.end(), 0.0);
    }
  }

  // field types and members
  using _header_type =
    std_msgs::msg::Header_<ContainerAllocator>;
  _header_type header;
  using _num_locations_type =
    int32_t;
  _num_locations_type num_locations;
  using _latitudes_type =
    std::array<double, 100>;
  _latitudes_type latitudes;
  using _longitudes_type =
    std::array<double, 100>;
  _longitudes_type longitudes;

  // setters for named parameter idiom
  Type & set__header(
    const std_msgs::msg::Header_<ContainerAllocator> & _arg)
  {
    this->header = _arg;
    return *this;
  }
  Type & set__num_locations(
    const int32_t & _arg)
  {
    this->num_locations = _arg;
    return *this;
  }
  Type & set__latitudes(
    const std::array<double, 100> & _arg)
  {
    this->latitudes = _arg;
    return *this;
  }
  Type & set__longitudes(
    const std::array<double, 100> & _arg)
  {
    this->longitudes = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    urc_msgs::msg::LandingLocations_<ContainerAllocator> *;
  using ConstRawPtr =
    const urc_msgs::msg::LandingLocations_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<urc_msgs::msg::LandingLocations_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<urc_msgs::msg::LandingLocations_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      urc_msgs::msg::LandingLocations_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<urc_msgs::msg::LandingLocations_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      urc_msgs::msg::LandingLocations_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<urc_msgs::msg::LandingLocations_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<urc_msgs::msg::LandingLocations_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<urc_msgs::msg::LandingLocations_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__urc_msgs__msg__LandingLocations
    std::shared_ptr<urc_msgs::msg::LandingLocations_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__urc_msgs__msg__LandingLocations
    std::shared_ptr<urc_msgs::msg::LandingLocations_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const LandingLocations_ & other) const
  {
    if (this->header != other.header) {
      return false;
    }
    if (this->num_locations != other.num_locations) {
      return false;
    }
    if (this->latitudes != other.latitudes) {
      return false;
    }
    if (this->longitudes != other.longitudes) {
      return false;
    }
    return true;
  }
  bool operator!=(const LandingLocations_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct LandingLocations_

// alias to use template instance with default allocator
using LandingLocations =
  urc_msgs::msg::LandingLocations_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace urc_msgs

#endif  // URC_MSGS__MSG__DETAIL__LANDING_LOCATIONS__STRUCT_HPP_
