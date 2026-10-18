// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from vectornav_msgs:msg/TimeUTC.idl
// generated code does not contain a copyright notice

#ifndef VECTORNAV_MSGS__MSG__DETAIL__TIME_UTC__BUILDER_HPP_
#define VECTORNAV_MSGS__MSG__DETAIL__TIME_UTC__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "vectornav_msgs/msg/detail/time_utc__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace vectornav_msgs
{

namespace msg
{

namespace builder
{

class Init_TimeUTC_ms
{
public:
  explicit Init_TimeUTC_ms(::vectornav_msgs::msg::TimeUTC & msg)
  : msg_(msg)
  {}
  ::vectornav_msgs::msg::TimeUTC ms(::vectornav_msgs::msg::TimeUTC::_ms_type arg)
  {
    msg_.ms = std::move(arg);
    return std::move(msg_);
  }

private:
  ::vectornav_msgs::msg::TimeUTC msg_;
};

class Init_TimeUTC_sec
{
public:
  explicit Init_TimeUTC_sec(::vectornav_msgs::msg::TimeUTC & msg)
  : msg_(msg)
  {}
  Init_TimeUTC_ms sec(::vectornav_msgs::msg::TimeUTC::_sec_type arg)
  {
    msg_.sec = std::move(arg);
    return Init_TimeUTC_ms(msg_);
  }

private:
  ::vectornav_msgs::msg::TimeUTC msg_;
};

class Init_TimeUTC_min
{
public:
  explicit Init_TimeUTC_min(::vectornav_msgs::msg::TimeUTC & msg)
  : msg_(msg)
  {}
  Init_TimeUTC_sec min(::vectornav_msgs::msg::TimeUTC::_min_type arg)
  {
    msg_.min = std::move(arg);
    return Init_TimeUTC_sec(msg_);
  }

private:
  ::vectornav_msgs::msg::TimeUTC msg_;
};

class Init_TimeUTC_hour
{
public:
  explicit Init_TimeUTC_hour(::vectornav_msgs::msg::TimeUTC & msg)
  : msg_(msg)
  {}
  Init_TimeUTC_min hour(::vectornav_msgs::msg::TimeUTC::_hour_type arg)
  {
    msg_.hour = std::move(arg);
    return Init_TimeUTC_min(msg_);
  }

private:
  ::vectornav_msgs::msg::TimeUTC msg_;
};

class Init_TimeUTC_day
{
public:
  explicit Init_TimeUTC_day(::vectornav_msgs::msg::TimeUTC & msg)
  : msg_(msg)
  {}
  Init_TimeUTC_hour day(::vectornav_msgs::msg::TimeUTC::_day_type arg)
  {
    msg_.day = std::move(arg);
    return Init_TimeUTC_hour(msg_);
  }

private:
  ::vectornav_msgs::msg::TimeUTC msg_;
};

class Init_TimeUTC_month
{
public:
  explicit Init_TimeUTC_month(::vectornav_msgs::msg::TimeUTC & msg)
  : msg_(msg)
  {}
  Init_TimeUTC_day month(::vectornav_msgs::msg::TimeUTC::_month_type arg)
  {
    msg_.month = std::move(arg);
    return Init_TimeUTC_day(msg_);
  }

private:
  ::vectornav_msgs::msg::TimeUTC msg_;
};

class Init_TimeUTC_year
{
public:
  Init_TimeUTC_year()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_TimeUTC_month year(::vectornav_msgs::msg::TimeUTC::_year_type arg)
  {
    msg_.year = std::move(arg);
    return Init_TimeUTC_month(msg_);
  }

private:
  ::vectornav_msgs::msg::TimeUTC msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::vectornav_msgs::msg::TimeUTC>()
{
  return vectornav_msgs::msg::builder::Init_TimeUTC_year();
}

}  // namespace vectornav_msgs

#endif  // VECTORNAV_MSGS__MSG__DETAIL__TIME_UTC__BUILDER_HPP_
