// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from vectornav_msgs:msg/TimeGroup.idl
// generated code does not contain a copyright notice

#ifndef VECTORNAV_MSGS__MSG__DETAIL__TIME_GROUP__BUILDER_HPP_
#define VECTORNAV_MSGS__MSG__DETAIL__TIME_GROUP__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "vectornav_msgs/msg/detail/time_group__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace vectornav_msgs
{

namespace msg
{

namespace builder
{

class Init_TimeGroup_timestatus
{
public:
  explicit Init_TimeGroup_timestatus(::vectornav_msgs::msg::TimeGroup & msg)
  : msg_(msg)
  {}
  ::vectornav_msgs::msg::TimeGroup timestatus(::vectornav_msgs::msg::TimeGroup::_timestatus_type arg)
  {
    msg_.timestatus = std::move(arg);
    return std::move(msg_);
  }

private:
  ::vectornav_msgs::msg::TimeGroup msg_;
};

class Init_TimeGroup_syncoutcnt
{
public:
  explicit Init_TimeGroup_syncoutcnt(::vectornav_msgs::msg::TimeGroup & msg)
  : msg_(msg)
  {}
  Init_TimeGroup_timestatus syncoutcnt(::vectornav_msgs::msg::TimeGroup::_syncoutcnt_type arg)
  {
    msg_.syncoutcnt = std::move(arg);
    return Init_TimeGroup_timestatus(msg_);
  }

private:
  ::vectornav_msgs::msg::TimeGroup msg_;
};

class Init_TimeGroup_syncincnt
{
public:
  explicit Init_TimeGroup_syncincnt(::vectornav_msgs::msg::TimeGroup & msg)
  : msg_(msg)
  {}
  Init_TimeGroup_syncoutcnt syncincnt(::vectornav_msgs::msg::TimeGroup::_syncincnt_type arg)
  {
    msg_.syncincnt = std::move(arg);
    return Init_TimeGroup_syncoutcnt(msg_);
  }

private:
  ::vectornav_msgs::msg::TimeGroup msg_;
};

class Init_TimeGroup_timeutc
{
public:
  explicit Init_TimeGroup_timeutc(::vectornav_msgs::msg::TimeGroup & msg)
  : msg_(msg)
  {}
  Init_TimeGroup_syncincnt timeutc(::vectornav_msgs::msg::TimeGroup::_timeutc_type arg)
  {
    msg_.timeutc = std::move(arg);
    return Init_TimeGroup_syncincnt(msg_);
  }

private:
  ::vectornav_msgs::msg::TimeGroup msg_;
};

class Init_TimeGroup_timegpspps
{
public:
  explicit Init_TimeGroup_timegpspps(::vectornav_msgs::msg::TimeGroup & msg)
  : msg_(msg)
  {}
  Init_TimeGroup_timeutc timegpspps(::vectornav_msgs::msg::TimeGroup::_timegpspps_type arg)
  {
    msg_.timegpspps = std::move(arg);
    return Init_TimeGroup_timeutc(msg_);
  }

private:
  ::vectornav_msgs::msg::TimeGroup msg_;
};

class Init_TimeGroup_timesyncin
{
public:
  explicit Init_TimeGroup_timesyncin(::vectornav_msgs::msg::TimeGroup & msg)
  : msg_(msg)
  {}
  Init_TimeGroup_timegpspps timesyncin(::vectornav_msgs::msg::TimeGroup::_timesyncin_type arg)
  {
    msg_.timesyncin = std::move(arg);
    return Init_TimeGroup_timegpspps(msg_);
  }

private:
  ::vectornav_msgs::msg::TimeGroup msg_;
};

class Init_TimeGroup_gpsweek
{
public:
  explicit Init_TimeGroup_gpsweek(::vectornav_msgs::msg::TimeGroup & msg)
  : msg_(msg)
  {}
  Init_TimeGroup_timesyncin gpsweek(::vectornav_msgs::msg::TimeGroup::_gpsweek_type arg)
  {
    msg_.gpsweek = std::move(arg);
    return Init_TimeGroup_timesyncin(msg_);
  }

private:
  ::vectornav_msgs::msg::TimeGroup msg_;
};

class Init_TimeGroup_gpstow
{
public:
  explicit Init_TimeGroup_gpstow(::vectornav_msgs::msg::TimeGroup & msg)
  : msg_(msg)
  {}
  Init_TimeGroup_gpsweek gpstow(::vectornav_msgs::msg::TimeGroup::_gpstow_type arg)
  {
    msg_.gpstow = std::move(arg);
    return Init_TimeGroup_gpsweek(msg_);
  }

private:
  ::vectornav_msgs::msg::TimeGroup msg_;
};

class Init_TimeGroup_timegps
{
public:
  explicit Init_TimeGroup_timegps(::vectornav_msgs::msg::TimeGroup & msg)
  : msg_(msg)
  {}
  Init_TimeGroup_gpstow timegps(::vectornav_msgs::msg::TimeGroup::_timegps_type arg)
  {
    msg_.timegps = std::move(arg);
    return Init_TimeGroup_gpstow(msg_);
  }

private:
  ::vectornav_msgs::msg::TimeGroup msg_;
};

class Init_TimeGroup_timestartup
{
public:
  explicit Init_TimeGroup_timestartup(::vectornav_msgs::msg::TimeGroup & msg)
  : msg_(msg)
  {}
  Init_TimeGroup_timegps timestartup(::vectornav_msgs::msg::TimeGroup::_timestartup_type arg)
  {
    msg_.timestartup = std::move(arg);
    return Init_TimeGroup_timegps(msg_);
  }

private:
  ::vectornav_msgs::msg::TimeGroup msg_;
};

class Init_TimeGroup_group_fields
{
public:
  explicit Init_TimeGroup_group_fields(::vectornav_msgs::msg::TimeGroup & msg)
  : msg_(msg)
  {}
  Init_TimeGroup_timestartup group_fields(::vectornav_msgs::msg::TimeGroup::_group_fields_type arg)
  {
    msg_.group_fields = std::move(arg);
    return Init_TimeGroup_timestartup(msg_);
  }

private:
  ::vectornav_msgs::msg::TimeGroup msg_;
};

class Init_TimeGroup_header
{
public:
  Init_TimeGroup_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_TimeGroup_group_fields header(::vectornav_msgs::msg::TimeGroup::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_TimeGroup_group_fields(msg_);
  }

private:
  ::vectornav_msgs::msg::TimeGroup msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::vectornav_msgs::msg::TimeGroup>()
{
  return vectornav_msgs::msg::builder::Init_TimeGroup_header();
}

}  // namespace vectornav_msgs

#endif  // VECTORNAV_MSGS__MSG__DETAIL__TIME_GROUP__BUILDER_HPP_
