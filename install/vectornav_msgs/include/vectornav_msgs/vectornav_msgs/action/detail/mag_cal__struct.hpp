// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from vectornav_msgs:action/MagCal.idl
// generated code does not contain a copyright notice

#ifndef VECTORNAV_MSGS__ACTION__DETAIL__MAG_CAL__STRUCT_HPP_
#define VECTORNAV_MSGS__ACTION__DETAIL__MAG_CAL__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__vectornav_msgs__action__MagCal_Goal __attribute__((deprecated))
#else
# define DEPRECATED__vectornav_msgs__action__MagCal_Goal __declspec(deprecated)
#endif

namespace vectornav_msgs
{

namespace action
{

// message struct
template<class ContainerAllocator>
struct MagCal_Goal_
{
  using Type = MagCal_Goal_<ContainerAllocator>;

  explicit MagCal_Goal_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->structure_needs_at_least_one_member = 0;
    }
  }

  explicit MagCal_Goal_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->structure_needs_at_least_one_member = 0;
    }
  }

  // field types and members
  using _structure_needs_at_least_one_member_type =
    uint8_t;
  _structure_needs_at_least_one_member_type structure_needs_at_least_one_member;


  // constant declarations

  // pointer types
  using RawPtr =
    vectornav_msgs::action::MagCal_Goal_<ContainerAllocator> *;
  using ConstRawPtr =
    const vectornav_msgs::action::MagCal_Goal_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<vectornav_msgs::action::MagCal_Goal_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<vectornav_msgs::action::MagCal_Goal_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      vectornav_msgs::action::MagCal_Goal_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<vectornav_msgs::action::MagCal_Goal_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      vectornav_msgs::action::MagCal_Goal_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<vectornav_msgs::action::MagCal_Goal_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<vectornav_msgs::action::MagCal_Goal_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<vectornav_msgs::action::MagCal_Goal_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__vectornav_msgs__action__MagCal_Goal
    std::shared_ptr<vectornav_msgs::action::MagCal_Goal_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__vectornav_msgs__action__MagCal_Goal
    std::shared_ptr<vectornav_msgs::action::MagCal_Goal_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const MagCal_Goal_ & other) const
  {
    if (this->structure_needs_at_least_one_member != other.structure_needs_at_least_one_member) {
      return false;
    }
    return true;
  }
  bool operator!=(const MagCal_Goal_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct MagCal_Goal_

// alias to use template instance with default allocator
using MagCal_Goal =
  vectornav_msgs::action::MagCal_Goal_<std::allocator<void>>;

// constant definitions

}  // namespace action

}  // namespace vectornav_msgs


#ifndef _WIN32
# define DEPRECATED__vectornav_msgs__action__MagCal_Result __attribute__((deprecated))
#else
# define DEPRECATED__vectornav_msgs__action__MagCal_Result __declspec(deprecated)
#endif

namespace vectornav_msgs
{

namespace action
{

// message struct
template<class ContainerAllocator>
struct MagCal_Result_
{
  using Type = MagCal_Result_<ContainerAllocator>;

  explicit MagCal_Result_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      std::fill<typename std::array<float, 12>::iterator, float>(this->avg_dev.begin(), this->avg_dev.end(), 0.0f);
      std::fill<typename std::array<float, 12>::iterator, float>(this->calib.begin(), this->calib.end(), 0.0f);
    }
  }

  explicit MagCal_Result_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : avg_dev(_alloc),
    calib(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      std::fill<typename std::array<float, 12>::iterator, float>(this->avg_dev.begin(), this->avg_dev.end(), 0.0f);
      std::fill<typename std::array<float, 12>::iterator, float>(this->calib.begin(), this->calib.end(), 0.0f);
    }
  }

  // field types and members
  using _avg_dev_type =
    std::array<float, 12>;
  _avg_dev_type avg_dev;
  using _calib_type =
    std::array<float, 12>;
  _calib_type calib;

  // setters for named parameter idiom
  Type & set__avg_dev(
    const std::array<float, 12> & _arg)
  {
    this->avg_dev = _arg;
    return *this;
  }
  Type & set__calib(
    const std::array<float, 12> & _arg)
  {
    this->calib = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    vectornav_msgs::action::MagCal_Result_<ContainerAllocator> *;
  using ConstRawPtr =
    const vectornav_msgs::action::MagCal_Result_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<vectornav_msgs::action::MagCal_Result_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<vectornav_msgs::action::MagCal_Result_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      vectornav_msgs::action::MagCal_Result_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<vectornav_msgs::action::MagCal_Result_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      vectornav_msgs::action::MagCal_Result_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<vectornav_msgs::action::MagCal_Result_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<vectornav_msgs::action::MagCal_Result_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<vectornav_msgs::action::MagCal_Result_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__vectornav_msgs__action__MagCal_Result
    std::shared_ptr<vectornav_msgs::action::MagCal_Result_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__vectornav_msgs__action__MagCal_Result
    std::shared_ptr<vectornav_msgs::action::MagCal_Result_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const MagCal_Result_ & other) const
  {
    if (this->avg_dev != other.avg_dev) {
      return false;
    }
    if (this->calib != other.calib) {
      return false;
    }
    return true;
  }
  bool operator!=(const MagCal_Result_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct MagCal_Result_

// alias to use template instance with default allocator
using MagCal_Result =
  vectornav_msgs::action::MagCal_Result_<std::allocator<void>>;

// constant definitions

}  // namespace action

}  // namespace vectornav_msgs


#ifndef _WIN32
# define DEPRECATED__vectornav_msgs__action__MagCal_Feedback __attribute__((deprecated))
#else
# define DEPRECATED__vectornav_msgs__action__MagCal_Feedback __declspec(deprecated)
#endif

namespace vectornav_msgs
{

namespace action
{

// message struct
template<class ContainerAllocator>
struct MagCal_Feedback_
{
  using Type = MagCal_Feedback_<ContainerAllocator>;

  explicit MagCal_Feedback_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      std::fill<typename std::array<float, 12>::iterator, float>(this->curr_avg_dev.begin(), this->curr_avg_dev.end(), 0.0f);
      std::fill<typename std::array<float, 12>::iterator, float>(this->curr_calib.begin(), this->curr_calib.end(), 0.0f);
      this->samples = 0ul;
    }
  }

  explicit MagCal_Feedback_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : curr_avg_dev(_alloc),
    curr_calib(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      std::fill<typename std::array<float, 12>::iterator, float>(this->curr_avg_dev.begin(), this->curr_avg_dev.end(), 0.0f);
      std::fill<typename std::array<float, 12>::iterator, float>(this->curr_calib.begin(), this->curr_calib.end(), 0.0f);
      this->samples = 0ul;
    }
  }

  // field types and members
  using _curr_avg_dev_type =
    std::array<float, 12>;
  _curr_avg_dev_type curr_avg_dev;
  using _curr_calib_type =
    std::array<float, 12>;
  _curr_calib_type curr_calib;
  using _samples_type =
    uint32_t;
  _samples_type samples;

  // setters for named parameter idiom
  Type & set__curr_avg_dev(
    const std::array<float, 12> & _arg)
  {
    this->curr_avg_dev = _arg;
    return *this;
  }
  Type & set__curr_calib(
    const std::array<float, 12> & _arg)
  {
    this->curr_calib = _arg;
    return *this;
  }
  Type & set__samples(
    const uint32_t & _arg)
  {
    this->samples = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    vectornav_msgs::action::MagCal_Feedback_<ContainerAllocator> *;
  using ConstRawPtr =
    const vectornav_msgs::action::MagCal_Feedback_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<vectornav_msgs::action::MagCal_Feedback_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<vectornav_msgs::action::MagCal_Feedback_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      vectornav_msgs::action::MagCal_Feedback_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<vectornav_msgs::action::MagCal_Feedback_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      vectornav_msgs::action::MagCal_Feedback_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<vectornav_msgs::action::MagCal_Feedback_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<vectornav_msgs::action::MagCal_Feedback_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<vectornav_msgs::action::MagCal_Feedback_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__vectornav_msgs__action__MagCal_Feedback
    std::shared_ptr<vectornav_msgs::action::MagCal_Feedback_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__vectornav_msgs__action__MagCal_Feedback
    std::shared_ptr<vectornav_msgs::action::MagCal_Feedback_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const MagCal_Feedback_ & other) const
  {
    if (this->curr_avg_dev != other.curr_avg_dev) {
      return false;
    }
    if (this->curr_calib != other.curr_calib) {
      return false;
    }
    if (this->samples != other.samples) {
      return false;
    }
    return true;
  }
  bool operator!=(const MagCal_Feedback_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct MagCal_Feedback_

// alias to use template instance with default allocator
using MagCal_Feedback =
  vectornav_msgs::action::MagCal_Feedback_<std::allocator<void>>;

// constant definitions

}  // namespace action

}  // namespace vectornav_msgs


// Include directives for member types
// Member 'goal_id'
#include "unique_identifier_msgs/msg/detail/uuid__struct.hpp"
// Member 'goal'
#include "vectornav_msgs/action/detail/mag_cal__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__vectornav_msgs__action__MagCal_SendGoal_Request __attribute__((deprecated))
#else
# define DEPRECATED__vectornav_msgs__action__MagCal_SendGoal_Request __declspec(deprecated)
#endif

namespace vectornav_msgs
{

namespace action
{

// message struct
template<class ContainerAllocator>
struct MagCal_SendGoal_Request_
{
  using Type = MagCal_SendGoal_Request_<ContainerAllocator>;

  explicit MagCal_SendGoal_Request_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : goal_id(_init),
    goal(_init)
  {
    (void)_init;
  }

  explicit MagCal_SendGoal_Request_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : goal_id(_alloc, _init),
    goal(_alloc, _init)
  {
    (void)_init;
  }

  // field types and members
  using _goal_id_type =
    unique_identifier_msgs::msg::UUID_<ContainerAllocator>;
  _goal_id_type goal_id;
  using _goal_type =
    vectornav_msgs::action::MagCal_Goal_<ContainerAllocator>;
  _goal_type goal;

  // setters for named parameter idiom
  Type & set__goal_id(
    const unique_identifier_msgs::msg::UUID_<ContainerAllocator> & _arg)
  {
    this->goal_id = _arg;
    return *this;
  }
  Type & set__goal(
    const vectornav_msgs::action::MagCal_Goal_<ContainerAllocator> & _arg)
  {
    this->goal = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    vectornav_msgs::action::MagCal_SendGoal_Request_<ContainerAllocator> *;
  using ConstRawPtr =
    const vectornav_msgs::action::MagCal_SendGoal_Request_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<vectornav_msgs::action::MagCal_SendGoal_Request_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<vectornav_msgs::action::MagCal_SendGoal_Request_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      vectornav_msgs::action::MagCal_SendGoal_Request_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<vectornav_msgs::action::MagCal_SendGoal_Request_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      vectornav_msgs::action::MagCal_SendGoal_Request_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<vectornav_msgs::action::MagCal_SendGoal_Request_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<vectornav_msgs::action::MagCal_SendGoal_Request_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<vectornav_msgs::action::MagCal_SendGoal_Request_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__vectornav_msgs__action__MagCal_SendGoal_Request
    std::shared_ptr<vectornav_msgs::action::MagCal_SendGoal_Request_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__vectornav_msgs__action__MagCal_SendGoal_Request
    std::shared_ptr<vectornav_msgs::action::MagCal_SendGoal_Request_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const MagCal_SendGoal_Request_ & other) const
  {
    if (this->goal_id != other.goal_id) {
      return false;
    }
    if (this->goal != other.goal) {
      return false;
    }
    return true;
  }
  bool operator!=(const MagCal_SendGoal_Request_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct MagCal_SendGoal_Request_

// alias to use template instance with default allocator
using MagCal_SendGoal_Request =
  vectornav_msgs::action::MagCal_SendGoal_Request_<std::allocator<void>>;

// constant definitions

}  // namespace action

}  // namespace vectornav_msgs


// Include directives for member types
// Member 'stamp'
#include "builtin_interfaces/msg/detail/time__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__vectornav_msgs__action__MagCal_SendGoal_Response __attribute__((deprecated))
#else
# define DEPRECATED__vectornav_msgs__action__MagCal_SendGoal_Response __declspec(deprecated)
#endif

namespace vectornav_msgs
{

namespace action
{

// message struct
template<class ContainerAllocator>
struct MagCal_SendGoal_Response_
{
  using Type = MagCal_SendGoal_Response_<ContainerAllocator>;

  explicit MagCal_SendGoal_Response_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : stamp(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->accepted = false;
    }
  }

  explicit MagCal_SendGoal_Response_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : stamp(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->accepted = false;
    }
  }

  // field types and members
  using _accepted_type =
    bool;
  _accepted_type accepted;
  using _stamp_type =
    builtin_interfaces::msg::Time_<ContainerAllocator>;
  _stamp_type stamp;

  // setters for named parameter idiom
  Type & set__accepted(
    const bool & _arg)
  {
    this->accepted = _arg;
    return *this;
  }
  Type & set__stamp(
    const builtin_interfaces::msg::Time_<ContainerAllocator> & _arg)
  {
    this->stamp = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    vectornav_msgs::action::MagCal_SendGoal_Response_<ContainerAllocator> *;
  using ConstRawPtr =
    const vectornav_msgs::action::MagCal_SendGoal_Response_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<vectornav_msgs::action::MagCal_SendGoal_Response_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<vectornav_msgs::action::MagCal_SendGoal_Response_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      vectornav_msgs::action::MagCal_SendGoal_Response_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<vectornav_msgs::action::MagCal_SendGoal_Response_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      vectornav_msgs::action::MagCal_SendGoal_Response_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<vectornav_msgs::action::MagCal_SendGoal_Response_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<vectornav_msgs::action::MagCal_SendGoal_Response_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<vectornav_msgs::action::MagCal_SendGoal_Response_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__vectornav_msgs__action__MagCal_SendGoal_Response
    std::shared_ptr<vectornav_msgs::action::MagCal_SendGoal_Response_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__vectornav_msgs__action__MagCal_SendGoal_Response
    std::shared_ptr<vectornav_msgs::action::MagCal_SendGoal_Response_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const MagCal_SendGoal_Response_ & other) const
  {
    if (this->accepted != other.accepted) {
      return false;
    }
    if (this->stamp != other.stamp) {
      return false;
    }
    return true;
  }
  bool operator!=(const MagCal_SendGoal_Response_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct MagCal_SendGoal_Response_

// alias to use template instance with default allocator
using MagCal_SendGoal_Response =
  vectornav_msgs::action::MagCal_SendGoal_Response_<std::allocator<void>>;

// constant definitions

}  // namespace action

}  // namespace vectornav_msgs

namespace vectornav_msgs
{

namespace action
{

struct MagCal_SendGoal
{
  using Request = vectornav_msgs::action::MagCal_SendGoal_Request;
  using Response = vectornav_msgs::action::MagCal_SendGoal_Response;
};

}  // namespace action

}  // namespace vectornav_msgs


// Include directives for member types
// Member 'goal_id'
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__vectornav_msgs__action__MagCal_GetResult_Request __attribute__((deprecated))
#else
# define DEPRECATED__vectornav_msgs__action__MagCal_GetResult_Request __declspec(deprecated)
#endif

namespace vectornav_msgs
{

namespace action
{

// message struct
template<class ContainerAllocator>
struct MagCal_GetResult_Request_
{
  using Type = MagCal_GetResult_Request_<ContainerAllocator>;

  explicit MagCal_GetResult_Request_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : goal_id(_init)
  {
    (void)_init;
  }

  explicit MagCal_GetResult_Request_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : goal_id(_alloc, _init)
  {
    (void)_init;
  }

  // field types and members
  using _goal_id_type =
    unique_identifier_msgs::msg::UUID_<ContainerAllocator>;
  _goal_id_type goal_id;

  // setters for named parameter idiom
  Type & set__goal_id(
    const unique_identifier_msgs::msg::UUID_<ContainerAllocator> & _arg)
  {
    this->goal_id = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    vectornav_msgs::action::MagCal_GetResult_Request_<ContainerAllocator> *;
  using ConstRawPtr =
    const vectornav_msgs::action::MagCal_GetResult_Request_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<vectornav_msgs::action::MagCal_GetResult_Request_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<vectornav_msgs::action::MagCal_GetResult_Request_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      vectornav_msgs::action::MagCal_GetResult_Request_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<vectornav_msgs::action::MagCal_GetResult_Request_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      vectornav_msgs::action::MagCal_GetResult_Request_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<vectornav_msgs::action::MagCal_GetResult_Request_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<vectornav_msgs::action::MagCal_GetResult_Request_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<vectornav_msgs::action::MagCal_GetResult_Request_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__vectornav_msgs__action__MagCal_GetResult_Request
    std::shared_ptr<vectornav_msgs::action::MagCal_GetResult_Request_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__vectornav_msgs__action__MagCal_GetResult_Request
    std::shared_ptr<vectornav_msgs::action::MagCal_GetResult_Request_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const MagCal_GetResult_Request_ & other) const
  {
    if (this->goal_id != other.goal_id) {
      return false;
    }
    return true;
  }
  bool operator!=(const MagCal_GetResult_Request_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct MagCal_GetResult_Request_

// alias to use template instance with default allocator
using MagCal_GetResult_Request =
  vectornav_msgs::action::MagCal_GetResult_Request_<std::allocator<void>>;

// constant definitions

}  // namespace action

}  // namespace vectornav_msgs


// Include directives for member types
// Member 'result'
// already included above
// #include "vectornav_msgs/action/detail/mag_cal__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__vectornav_msgs__action__MagCal_GetResult_Response __attribute__((deprecated))
#else
# define DEPRECATED__vectornav_msgs__action__MagCal_GetResult_Response __declspec(deprecated)
#endif

namespace vectornav_msgs
{

namespace action
{

// message struct
template<class ContainerAllocator>
struct MagCal_GetResult_Response_
{
  using Type = MagCal_GetResult_Response_<ContainerAllocator>;

  explicit MagCal_GetResult_Response_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : result(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->status = 0;
    }
  }

  explicit MagCal_GetResult_Response_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : result(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->status = 0;
    }
  }

  // field types and members
  using _status_type =
    int8_t;
  _status_type status;
  using _result_type =
    vectornav_msgs::action::MagCal_Result_<ContainerAllocator>;
  _result_type result;

  // setters for named parameter idiom
  Type & set__status(
    const int8_t & _arg)
  {
    this->status = _arg;
    return *this;
  }
  Type & set__result(
    const vectornav_msgs::action::MagCal_Result_<ContainerAllocator> & _arg)
  {
    this->result = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    vectornav_msgs::action::MagCal_GetResult_Response_<ContainerAllocator> *;
  using ConstRawPtr =
    const vectornav_msgs::action::MagCal_GetResult_Response_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<vectornav_msgs::action::MagCal_GetResult_Response_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<vectornav_msgs::action::MagCal_GetResult_Response_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      vectornav_msgs::action::MagCal_GetResult_Response_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<vectornav_msgs::action::MagCal_GetResult_Response_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      vectornav_msgs::action::MagCal_GetResult_Response_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<vectornav_msgs::action::MagCal_GetResult_Response_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<vectornav_msgs::action::MagCal_GetResult_Response_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<vectornav_msgs::action::MagCal_GetResult_Response_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__vectornav_msgs__action__MagCal_GetResult_Response
    std::shared_ptr<vectornav_msgs::action::MagCal_GetResult_Response_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__vectornav_msgs__action__MagCal_GetResult_Response
    std::shared_ptr<vectornav_msgs::action::MagCal_GetResult_Response_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const MagCal_GetResult_Response_ & other) const
  {
    if (this->status != other.status) {
      return false;
    }
    if (this->result != other.result) {
      return false;
    }
    return true;
  }
  bool operator!=(const MagCal_GetResult_Response_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct MagCal_GetResult_Response_

// alias to use template instance with default allocator
using MagCal_GetResult_Response =
  vectornav_msgs::action::MagCal_GetResult_Response_<std::allocator<void>>;

// constant definitions

}  // namespace action

}  // namespace vectornav_msgs

namespace vectornav_msgs
{

namespace action
{

struct MagCal_GetResult
{
  using Request = vectornav_msgs::action::MagCal_GetResult_Request;
  using Response = vectornav_msgs::action::MagCal_GetResult_Response;
};

}  // namespace action

}  // namespace vectornav_msgs


// Include directives for member types
// Member 'goal_id'
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__struct.hpp"
// Member 'feedback'
// already included above
// #include "vectornav_msgs/action/detail/mag_cal__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__vectornav_msgs__action__MagCal_FeedbackMessage __attribute__((deprecated))
#else
# define DEPRECATED__vectornav_msgs__action__MagCal_FeedbackMessage __declspec(deprecated)
#endif

namespace vectornav_msgs
{

namespace action
{

// message struct
template<class ContainerAllocator>
struct MagCal_FeedbackMessage_
{
  using Type = MagCal_FeedbackMessage_<ContainerAllocator>;

  explicit MagCal_FeedbackMessage_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : goal_id(_init),
    feedback(_init)
  {
    (void)_init;
  }

  explicit MagCal_FeedbackMessage_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : goal_id(_alloc, _init),
    feedback(_alloc, _init)
  {
    (void)_init;
  }

  // field types and members
  using _goal_id_type =
    unique_identifier_msgs::msg::UUID_<ContainerAllocator>;
  _goal_id_type goal_id;
  using _feedback_type =
    vectornav_msgs::action::MagCal_Feedback_<ContainerAllocator>;
  _feedback_type feedback;

  // setters for named parameter idiom
  Type & set__goal_id(
    const unique_identifier_msgs::msg::UUID_<ContainerAllocator> & _arg)
  {
    this->goal_id = _arg;
    return *this;
  }
  Type & set__feedback(
    const vectornav_msgs::action::MagCal_Feedback_<ContainerAllocator> & _arg)
  {
    this->feedback = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    vectornav_msgs::action::MagCal_FeedbackMessage_<ContainerAllocator> *;
  using ConstRawPtr =
    const vectornav_msgs::action::MagCal_FeedbackMessage_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<vectornav_msgs::action::MagCal_FeedbackMessage_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<vectornav_msgs::action::MagCal_FeedbackMessage_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      vectornav_msgs::action::MagCal_FeedbackMessage_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<vectornav_msgs::action::MagCal_FeedbackMessage_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      vectornav_msgs::action::MagCal_FeedbackMessage_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<vectornav_msgs::action::MagCal_FeedbackMessage_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<vectornav_msgs::action::MagCal_FeedbackMessage_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<vectornav_msgs::action::MagCal_FeedbackMessage_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__vectornav_msgs__action__MagCal_FeedbackMessage
    std::shared_ptr<vectornav_msgs::action::MagCal_FeedbackMessage_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__vectornav_msgs__action__MagCal_FeedbackMessage
    std::shared_ptr<vectornav_msgs::action::MagCal_FeedbackMessage_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const MagCal_FeedbackMessage_ & other) const
  {
    if (this->goal_id != other.goal_id) {
      return false;
    }
    if (this->feedback != other.feedback) {
      return false;
    }
    return true;
  }
  bool operator!=(const MagCal_FeedbackMessage_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct MagCal_FeedbackMessage_

// alias to use template instance with default allocator
using MagCal_FeedbackMessage =
  vectornav_msgs::action::MagCal_FeedbackMessage_<std::allocator<void>>;

// constant definitions

}  // namespace action

}  // namespace vectornav_msgs

#include "action_msgs/srv/cancel_goal.hpp"
#include "action_msgs/msg/goal_info.hpp"
#include "action_msgs/msg/goal_status_array.hpp"

namespace vectornav_msgs
{

namespace action
{

struct MagCal
{
  /// The goal message defined in the action definition.
  using Goal = vectornav_msgs::action::MagCal_Goal;
  /// The result message defined in the action definition.
  using Result = vectornav_msgs::action::MagCal_Result;
  /// The feedback message defined in the action definition.
  using Feedback = vectornav_msgs::action::MagCal_Feedback;

  struct Impl
  {
    /// The send_goal service using a wrapped version of the goal message as a request.
    using SendGoalService = vectornav_msgs::action::MagCal_SendGoal;
    /// The get_result service using a wrapped version of the result message as a response.
    using GetResultService = vectornav_msgs::action::MagCal_GetResult;
    /// The feedback message with generic fields which wraps the feedback message.
    using FeedbackMessage = vectornav_msgs::action::MagCal_FeedbackMessage;

    /// The generic service to cancel a goal.
    using CancelGoalService = action_msgs::srv::CancelGoal;
    /// The generic message for the status of a goal.
    using GoalStatusMessage = action_msgs::msg::GoalStatusArray;
  };
};

typedef struct MagCal MagCal;

}  // namespace action

}  // namespace vectornav_msgs

#endif  // VECTORNAV_MSGS__ACTION__DETAIL__MAG_CAL__STRUCT_HPP_
