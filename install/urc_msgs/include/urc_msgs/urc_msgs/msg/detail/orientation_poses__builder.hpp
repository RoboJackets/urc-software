// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from urc_msgs:msg/OrientationPoses.idl
// generated code does not contain a copyright notice

#ifndef URC_MSGS__MSG__DETAIL__ORIENTATION_POSES__BUILDER_HPP_
#define URC_MSGS__MSG__DETAIL__ORIENTATION_POSES__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "urc_msgs/msg/detail/orientation_poses__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace urc_msgs
{

namespace msg
{

namespace builder
{

class Init_OrientationPoses_poses
{
public:
  explicit Init_OrientationPoses_poses(::urc_msgs::msg::OrientationPoses & msg)
  : msg_(msg)
  {}
  ::urc_msgs::msg::OrientationPoses poses(::urc_msgs::msg::OrientationPoses::_poses_type arg)
  {
    msg_.poses = std::move(arg);
    return std::move(msg_);
  }

private:
  ::urc_msgs::msg::OrientationPoses msg_;
};

class Init_OrientationPoses_names
{
public:
  explicit Init_OrientationPoses_names(::urc_msgs::msg::OrientationPoses & msg)
  : msg_(msg)
  {}
  Init_OrientationPoses_poses names(::urc_msgs::msg::OrientationPoses::_names_type arg)
  {
    msg_.names = std::move(arg);
    return Init_OrientationPoses_poses(msg_);
  }

private:
  ::urc_msgs::msg::OrientationPoses msg_;
};

class Init_OrientationPoses_header
{
public:
  Init_OrientationPoses_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_OrientationPoses_names header(::urc_msgs::msg::OrientationPoses::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_OrientationPoses_names(msg_);
  }

private:
  ::urc_msgs::msg::OrientationPoses msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::urc_msgs::msg::OrientationPoses>()
{
  return urc_msgs::msg::builder::Init_OrientationPoses_header();
}

}  // namespace urc_msgs

#endif  // URC_MSGS__MSG__DETAIL__ORIENTATION_POSES__BUILDER_HPP_
