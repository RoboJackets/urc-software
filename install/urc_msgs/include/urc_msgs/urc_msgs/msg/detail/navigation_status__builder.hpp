// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from urc_msgs:msg/NavigationStatus.idl
// generated code does not contain a copyright notice

#ifndef URC_MSGS__MSG__DETAIL__NAVIGATION_STATUS__BUILDER_HPP_
#define URC_MSGS__MSG__DETAIL__NAVIGATION_STATUS__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "urc_msgs/msg/detail/navigation_status__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace urc_msgs
{

namespace msg
{

namespace builder
{

class Init_NavigationStatus_message
{
public:
  Init_NavigationStatus_message()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::urc_msgs::msg::NavigationStatus message(::urc_msgs::msg::NavigationStatus::_message_type arg)
  {
    msg_.message = std::move(arg);
    return std::move(msg_);
  }

private:
  ::urc_msgs::msg::NavigationStatus msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::urc_msgs::msg::NavigationStatus>()
{
  return urc_msgs::msg::builder::Init_NavigationStatus_message();
}

}  // namespace urc_msgs

#endif  // URC_MSGS__MSG__DETAIL__NAVIGATION_STATUS__BUILDER_HPP_
