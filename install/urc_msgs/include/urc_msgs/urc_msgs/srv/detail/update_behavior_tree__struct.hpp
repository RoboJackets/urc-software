// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from urc_msgs:srv/UpdateBehaviorTree.idl
// generated code does not contain a copyright notice

#ifndef URC_MSGS__SRV__DETAIL__UPDATE_BEHAVIOR_TREE__STRUCT_HPP_
#define URC_MSGS__SRV__DETAIL__UPDATE_BEHAVIOR_TREE__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__urc_msgs__srv__UpdateBehaviorTree_Request __attribute__((deprecated))
#else
# define DEPRECATED__urc_msgs__srv__UpdateBehaviorTree_Request __declspec(deprecated)
#endif

namespace urc_msgs
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct UpdateBehaviorTree_Request_
{
  using Type = UpdateBehaviorTree_Request_<ContainerAllocator>;

  explicit UpdateBehaviorTree_Request_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->tree_content = "";
      this->tree_dir = "";
      this->use_dir = false;
    }
  }

  explicit UpdateBehaviorTree_Request_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : tree_content(_alloc),
    tree_dir(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->tree_content = "";
      this->tree_dir = "";
      this->use_dir = false;
    }
  }

  // field types and members
  using _tree_content_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _tree_content_type tree_content;
  using _tree_dir_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _tree_dir_type tree_dir;
  using _use_dir_type =
    bool;
  _use_dir_type use_dir;

  // setters for named parameter idiom
  Type & set__tree_content(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->tree_content = _arg;
    return *this;
  }
  Type & set__tree_dir(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->tree_dir = _arg;
    return *this;
  }
  Type & set__use_dir(
    const bool & _arg)
  {
    this->use_dir = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    urc_msgs::srv::UpdateBehaviorTree_Request_<ContainerAllocator> *;
  using ConstRawPtr =
    const urc_msgs::srv::UpdateBehaviorTree_Request_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<urc_msgs::srv::UpdateBehaviorTree_Request_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<urc_msgs::srv::UpdateBehaviorTree_Request_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      urc_msgs::srv::UpdateBehaviorTree_Request_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<urc_msgs::srv::UpdateBehaviorTree_Request_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      urc_msgs::srv::UpdateBehaviorTree_Request_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<urc_msgs::srv::UpdateBehaviorTree_Request_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<urc_msgs::srv::UpdateBehaviorTree_Request_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<urc_msgs::srv::UpdateBehaviorTree_Request_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__urc_msgs__srv__UpdateBehaviorTree_Request
    std::shared_ptr<urc_msgs::srv::UpdateBehaviorTree_Request_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__urc_msgs__srv__UpdateBehaviorTree_Request
    std::shared_ptr<urc_msgs::srv::UpdateBehaviorTree_Request_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const UpdateBehaviorTree_Request_ & other) const
  {
    if (this->tree_content != other.tree_content) {
      return false;
    }
    if (this->tree_dir != other.tree_dir) {
      return false;
    }
    if (this->use_dir != other.use_dir) {
      return false;
    }
    return true;
  }
  bool operator!=(const UpdateBehaviorTree_Request_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct UpdateBehaviorTree_Request_

// alias to use template instance with default allocator
using UpdateBehaviorTree_Request =
  urc_msgs::srv::UpdateBehaviorTree_Request_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace urc_msgs


#ifndef _WIN32
# define DEPRECATED__urc_msgs__srv__UpdateBehaviorTree_Response __attribute__((deprecated))
#else
# define DEPRECATED__urc_msgs__srv__UpdateBehaviorTree_Response __declspec(deprecated)
#endif

namespace urc_msgs
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct UpdateBehaviorTree_Response_
{
  using Type = UpdateBehaviorTree_Response_<ContainerAllocator>;

  explicit UpdateBehaviorTree_Response_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->success = false;
    }
  }

  explicit UpdateBehaviorTree_Response_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->success = false;
    }
  }

  // field types and members
  using _success_type =
    bool;
  _success_type success;

  // setters for named parameter idiom
  Type & set__success(
    const bool & _arg)
  {
    this->success = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    urc_msgs::srv::UpdateBehaviorTree_Response_<ContainerAllocator> *;
  using ConstRawPtr =
    const urc_msgs::srv::UpdateBehaviorTree_Response_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<urc_msgs::srv::UpdateBehaviorTree_Response_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<urc_msgs::srv::UpdateBehaviorTree_Response_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      urc_msgs::srv::UpdateBehaviorTree_Response_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<urc_msgs::srv::UpdateBehaviorTree_Response_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      urc_msgs::srv::UpdateBehaviorTree_Response_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<urc_msgs::srv::UpdateBehaviorTree_Response_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<urc_msgs::srv::UpdateBehaviorTree_Response_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<urc_msgs::srv::UpdateBehaviorTree_Response_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__urc_msgs__srv__UpdateBehaviorTree_Response
    std::shared_ptr<urc_msgs::srv::UpdateBehaviorTree_Response_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__urc_msgs__srv__UpdateBehaviorTree_Response
    std::shared_ptr<urc_msgs::srv::UpdateBehaviorTree_Response_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const UpdateBehaviorTree_Response_ & other) const
  {
    if (this->success != other.success) {
      return false;
    }
    return true;
  }
  bool operator!=(const UpdateBehaviorTree_Response_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct UpdateBehaviorTree_Response_

// alias to use template instance with default allocator
using UpdateBehaviorTree_Response =
  urc_msgs::srv::UpdateBehaviorTree_Response_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace urc_msgs

namespace urc_msgs
{

namespace srv
{

struct UpdateBehaviorTree
{
  using Request = urc_msgs::srv::UpdateBehaviorTree_Request;
  using Response = urc_msgs::srv::UpdateBehaviorTree_Response;
};

}  // namespace srv

}  // namespace urc_msgs

#endif  // URC_MSGS__SRV__DETAIL__UPDATE_BEHAVIOR_TREE__STRUCT_HPP_
