// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from vectornav_msgs:msg/TimeStatus.idl
// generated code does not contain a copyright notice

#ifndef VECTORNAV_MSGS__MSG__DETAIL__TIME_STATUS__BUILDER_HPP_
#define VECTORNAV_MSGS__MSG__DETAIL__TIME_STATUS__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "vectornav_msgs/msg/detail/time_status__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace vectornav_msgs
{

namespace msg
{

namespace builder
{

class Init_TimeStatus_utctime_ok
{
public:
  explicit Init_TimeStatus_utctime_ok(::vectornav_msgs::msg::TimeStatus & msg)
  : msg_(msg)
  {}
  ::vectornav_msgs::msg::TimeStatus utctime_ok(::vectornav_msgs::msg::TimeStatus::_utctime_ok_type arg)
  {
    msg_.utctime_ok = std::move(arg);
    return std::move(msg_);
  }

private:
  ::vectornav_msgs::msg::TimeStatus msg_;
};

class Init_TimeStatus_date_ok
{
public:
  explicit Init_TimeStatus_date_ok(::vectornav_msgs::msg::TimeStatus & msg)
  : msg_(msg)
  {}
  Init_TimeStatus_utctime_ok date_ok(::vectornav_msgs::msg::TimeStatus::_date_ok_type arg)
  {
    msg_.date_ok = std::move(arg);
    return Init_TimeStatus_utctime_ok(msg_);
  }

private:
  ::vectornav_msgs::msg::TimeStatus msg_;
};

class Init_TimeStatus_time_ok
{
public:
  Init_TimeStatus_time_ok()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_TimeStatus_date_ok time_ok(::vectornav_msgs::msg::TimeStatus::_time_ok_type arg)
  {
    msg_.time_ok = std::move(arg);
    return Init_TimeStatus_date_ok(msg_);
  }

private:
  ::vectornav_msgs::msg::TimeStatus msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::vectornav_msgs::msg::TimeStatus>()
{
  return vectornav_msgs::msg::builder::Init_TimeStatus_time_ok();
}

}  // namespace vectornav_msgs

#endif  // VECTORNAV_MSGS__MSG__DETAIL__TIME_STATUS__BUILDER_HPP_
