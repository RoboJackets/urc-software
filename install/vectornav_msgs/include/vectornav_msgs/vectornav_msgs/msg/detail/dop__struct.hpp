// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from vectornav_msgs:msg/DOP.idl
// generated code does not contain a copyright notice

#ifndef VECTORNAV_MSGS__MSG__DETAIL__DOP__STRUCT_HPP_
#define VECTORNAV_MSGS__MSG__DETAIL__DOP__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__vectornav_msgs__msg__DOP __attribute__((deprecated))
#else
# define DEPRECATED__vectornav_msgs__msg__DOP __declspec(deprecated)
#endif

namespace vectornav_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct DOP_
{
  using Type = DOP_<ContainerAllocator>;

  explicit DOP_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->g = 0.0f;
      this->p = 0.0f;
      this->t = 0.0f;
      this->v = 0.0f;
      this->h = 0.0f;
      this->n = 0.0f;
      this->e = 0.0f;
    }
  }

  explicit DOP_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->g = 0.0f;
      this->p = 0.0f;
      this->t = 0.0f;
      this->v = 0.0f;
      this->h = 0.0f;
      this->n = 0.0f;
      this->e = 0.0f;
    }
  }

  // field types and members
  using _g_type =
    float;
  _g_type g;
  using _p_type =
    float;
  _p_type p;
  using _t_type =
    float;
  _t_type t;
  using _v_type =
    float;
  _v_type v;
  using _h_type =
    float;
  _h_type h;
  using _n_type =
    float;
  _n_type n;
  using _e_type =
    float;
  _e_type e;

  // setters for named parameter idiom
  Type & set__g(
    const float & _arg)
  {
    this->g = _arg;
    return *this;
  }
  Type & set__p(
    const float & _arg)
  {
    this->p = _arg;
    return *this;
  }
  Type & set__t(
    const float & _arg)
  {
    this->t = _arg;
    return *this;
  }
  Type & set__v(
    const float & _arg)
  {
    this->v = _arg;
    return *this;
  }
  Type & set__h(
    const float & _arg)
  {
    this->h = _arg;
    return *this;
  }
  Type & set__n(
    const float & _arg)
  {
    this->n = _arg;
    return *this;
  }
  Type & set__e(
    const float & _arg)
  {
    this->e = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    vectornav_msgs::msg::DOP_<ContainerAllocator> *;
  using ConstRawPtr =
    const vectornav_msgs::msg::DOP_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<vectornav_msgs::msg::DOP_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<vectornav_msgs::msg::DOP_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      vectornav_msgs::msg::DOP_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<vectornav_msgs::msg::DOP_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      vectornav_msgs::msg::DOP_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<vectornav_msgs::msg::DOP_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<vectornav_msgs::msg::DOP_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<vectornav_msgs::msg::DOP_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__vectornav_msgs__msg__DOP
    std::shared_ptr<vectornav_msgs::msg::DOP_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__vectornav_msgs__msg__DOP
    std::shared_ptr<vectornav_msgs::msg::DOP_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const DOP_ & other) const
  {
    if (this->g != other.g) {
      return false;
    }
    if (this->p != other.p) {
      return false;
    }
    if (this->t != other.t) {
      return false;
    }
    if (this->v != other.v) {
      return false;
    }
    if (this->h != other.h) {
      return false;
    }
    if (this->n != other.n) {
      return false;
    }
    if (this->e != other.e) {
      return false;
    }
    return true;
  }
  bool operator!=(const DOP_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct DOP_

// alias to use template instance with default allocator
using DOP =
  vectornav_msgs::msg::DOP_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace vectornav_msgs

#endif  // VECTORNAV_MSGS__MSG__DETAIL__DOP__STRUCT_HPP_
