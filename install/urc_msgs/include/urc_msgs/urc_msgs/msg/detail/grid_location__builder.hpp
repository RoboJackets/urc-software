// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from urc_msgs:msg/GridLocation.idl
// generated code does not contain a copyright notice

#ifndef URC_MSGS__MSG__DETAIL__GRID_LOCATION__BUILDER_HPP_
#define URC_MSGS__MSG__DETAIL__GRID_LOCATION__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "urc_msgs/msg/detail/grid_location__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace urc_msgs
{

namespace msg
{

namespace builder
{

class Init_GridLocation_y
{
public:
  explicit Init_GridLocation_y(::urc_msgs::msg::GridLocation & msg)
  : msg_(msg)
  {}
  ::urc_msgs::msg::GridLocation y(::urc_msgs::msg::GridLocation::_y_type arg)
  {
    msg_.y = std::move(arg);
    return std::move(msg_);
  }

private:
  ::urc_msgs::msg::GridLocation msg_;
};

class Init_GridLocation_x
{
public:
  Init_GridLocation_x()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_GridLocation_y x(::urc_msgs::msg::GridLocation::_x_type arg)
  {
    msg_.x = std::move(arg);
    return Init_GridLocation_y(msg_);
  }

private:
  ::urc_msgs::msg::GridLocation msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::urc_msgs::msg::GridLocation>()
{
  return urc_msgs::msg::builder::Init_GridLocation_x();
}

}  // namespace urc_msgs

#endif  // URC_MSGS__MSG__DETAIL__GRID_LOCATION__BUILDER_HPP_
