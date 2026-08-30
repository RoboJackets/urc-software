// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from urc_msgs:msg/RoverPoses.idl
// generated code does not contain a copyright notice

#ifndef URC_MSGS__MSG__DETAIL__ROVER_POSES__BUILDER_HPP_
#define URC_MSGS__MSG__DETAIL__ROVER_POSES__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "urc_msgs/msg/detail/rover_poses__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace urc_msgs
{

namespace msg
{

namespace builder
{

class Init_RoverPoses_poses
{
public:
  explicit Init_RoverPoses_poses(::urc_msgs::msg::RoverPoses & msg)
  : msg_(msg)
  {}
  ::urc_msgs::msg::RoverPoses poses(::urc_msgs::msg::RoverPoses::_poses_type arg)
  {
    msg_.poses = std::move(arg);
    return std::move(msg_);
  }

private:
  ::urc_msgs::msg::RoverPoses msg_;
};

class Init_RoverPoses_names
{
public:
  explicit Init_RoverPoses_names(::urc_msgs::msg::RoverPoses & msg)
  : msg_(msg)
  {}
  Init_RoverPoses_poses names(::urc_msgs::msg::RoverPoses::_names_type arg)
  {
    msg_.names = std::move(arg);
    return Init_RoverPoses_poses(msg_);
  }

private:
  ::urc_msgs::msg::RoverPoses msg_;
};

class Init_RoverPoses_header
{
public:
  Init_RoverPoses_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_RoverPoses_names header(::urc_msgs::msg::RoverPoses::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_RoverPoses_names(msg_);
  }

private:
  ::urc_msgs::msg::RoverPoses msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::urc_msgs::msg::RoverPoses>()
{
  return urc_msgs::msg::builder::Init_RoverPoses_header();
}

}  // namespace urc_msgs

#endif  // URC_MSGS__MSG__DETAIL__ROVER_POSES__BUILDER_HPP_
