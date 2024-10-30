// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from urc_msgs:msg/StatusLightCommand.idl
// generated code does not contain a copyright notice

#ifndef URC_MSGS__MSG__DETAIL__STATUS_LIGHT_COMMAND__BUILDER_HPP_
#define URC_MSGS__MSG__DETAIL__STATUS_LIGHT_COMMAND__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "urc_msgs/msg/detail/status_light_command__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace urc_msgs
{

namespace msg
{

namespace builder
{

class Init_StatusLightCommand_state
{
public:
  explicit Init_StatusLightCommand_state(::urc_msgs::msg::StatusLightCommand & msg)
  : msg_(msg)
  {}
  ::urc_msgs::msg::StatusLightCommand state(::urc_msgs::msg::StatusLightCommand::_state_type arg)
  {
    msg_.state = std::move(arg);
    return std::move(msg_);
  }

private:
  ::urc_msgs::msg::StatusLightCommand msg_;
};

class Init_StatusLightCommand_color
{
public:
  Init_StatusLightCommand_color()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_StatusLightCommand_state color(::urc_msgs::msg::StatusLightCommand::_color_type arg)
  {
    msg_.color = std::move(arg);
    return Init_StatusLightCommand_state(msg_);
  }

private:
  ::urc_msgs::msg::StatusLightCommand msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::urc_msgs::msg::StatusLightCommand>()
{
  return urc_msgs::msg::builder::Init_StatusLightCommand_color();
}

}  // namespace urc_msgs

#endif  // URC_MSGS__MSG__DETAIL__STATUS_LIGHT_COMMAND__BUILDER_HPP_
