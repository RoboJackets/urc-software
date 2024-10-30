// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from urc_msgs:msg/Waypoint.idl
// generated code does not contain a copyright notice

#ifndef URC_MSGS__MSG__DETAIL__WAYPOINT__BUILDER_HPP_
#define URC_MSGS__MSG__DETAIL__WAYPOINT__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "urc_msgs/msg/detail/waypoint__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace urc_msgs
{

namespace msg
{

namespace builder
{

class Init_Waypoint_longitude
{
public:
  explicit Init_Waypoint_longitude(::urc_msgs::msg::Waypoint & msg)
  : msg_(msg)
  {}
  ::urc_msgs::msg::Waypoint longitude(::urc_msgs::msg::Waypoint::_longitude_type arg)
  {
    msg_.longitude = std::move(arg);
    return std::move(msg_);
  }

private:
  ::urc_msgs::msg::Waypoint msg_;
};

class Init_Waypoint_latitude
{
public:
  Init_Waypoint_latitude()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Waypoint_longitude latitude(::urc_msgs::msg::Waypoint::_latitude_type arg)
  {
    msg_.latitude = std::move(arg);
    return Init_Waypoint_longitude(msg_);
  }

private:
  ::urc_msgs::msg::Waypoint msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::urc_msgs::msg::Waypoint>()
{
  return urc_msgs::msg::builder::Init_Waypoint_latitude();
}

}  // namespace urc_msgs

#endif  // URC_MSGS__MSG__DETAIL__WAYPOINT__BUILDER_HPP_
