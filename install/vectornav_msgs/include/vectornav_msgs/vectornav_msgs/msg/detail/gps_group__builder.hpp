// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from vectornav_msgs:msg/GpsGroup.idl
// generated code does not contain a copyright notice

#ifndef VECTORNAV_MSGS__MSG__DETAIL__GPS_GROUP__BUILDER_HPP_
#define VECTORNAV_MSGS__MSG__DETAIL__GPS_GROUP__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "vectornav_msgs/msg/detail/gps_group__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace vectornav_msgs
{

namespace msg
{

namespace builder
{

class Init_GpsGroup_dop
{
public:
  explicit Init_GpsGroup_dop(::vectornav_msgs::msg::GpsGroup & msg)
  : msg_(msg)
  {}
  ::vectornav_msgs::msg::GpsGroup dop(::vectornav_msgs::msg::GpsGroup::_dop_type arg)
  {
    msg_.dop = std::move(arg);
    return std::move(msg_);
  }

private:
  ::vectornav_msgs::msg::GpsGroup msg_;
};

class Init_GpsGroup_timeinfo_leapseconds
{
public:
  explicit Init_GpsGroup_timeinfo_leapseconds(::vectornav_msgs::msg::GpsGroup & msg)
  : msg_(msg)
  {}
  Init_GpsGroup_dop timeinfo_leapseconds(::vectornav_msgs::msg::GpsGroup::_timeinfo_leapseconds_type arg)
  {
    msg_.timeinfo_leapseconds = std::move(arg);
    return Init_GpsGroup_dop(msg_);
  }

private:
  ::vectornav_msgs::msg::GpsGroup msg_;
};

class Init_GpsGroup_timeinfo_status
{
public:
  explicit Init_GpsGroup_timeinfo_status(::vectornav_msgs::msg::GpsGroup & msg)
  : msg_(msg)
  {}
  Init_GpsGroup_timeinfo_leapseconds timeinfo_status(::vectornav_msgs::msg::GpsGroup::_timeinfo_status_type arg)
  {
    msg_.timeinfo_status = std::move(arg);
    return Init_GpsGroup_timeinfo_leapseconds(msg_);
  }

private:
  ::vectornav_msgs::msg::GpsGroup msg_;
};

class Init_GpsGroup_timeu
{
public:
  explicit Init_GpsGroup_timeu(::vectornav_msgs::msg::GpsGroup & msg)
  : msg_(msg)
  {}
  Init_GpsGroup_timeinfo_status timeu(::vectornav_msgs::msg::GpsGroup::_timeu_type arg)
  {
    msg_.timeu = std::move(arg);
    return Init_GpsGroup_timeinfo_status(msg_);
  }

private:
  ::vectornav_msgs::msg::GpsGroup msg_;
};

class Init_GpsGroup_velu
{
public:
  explicit Init_GpsGroup_velu(::vectornav_msgs::msg::GpsGroup & msg)
  : msg_(msg)
  {}
  Init_GpsGroup_timeu velu(::vectornav_msgs::msg::GpsGroup::_velu_type arg)
  {
    msg_.velu = std::move(arg);
    return Init_GpsGroup_timeu(msg_);
  }

private:
  ::vectornav_msgs::msg::GpsGroup msg_;
};

class Init_GpsGroup_posu
{
public:
  explicit Init_GpsGroup_posu(::vectornav_msgs::msg::GpsGroup & msg)
  : msg_(msg)
  {}
  Init_GpsGroup_velu posu(::vectornav_msgs::msg::GpsGroup::_posu_type arg)
  {
    msg_.posu = std::move(arg);
    return Init_GpsGroup_velu(msg_);
  }

private:
  ::vectornav_msgs::msg::GpsGroup msg_;
};

class Init_GpsGroup_velecef
{
public:
  explicit Init_GpsGroup_velecef(::vectornav_msgs::msg::GpsGroup & msg)
  : msg_(msg)
  {}
  Init_GpsGroup_posu velecef(::vectornav_msgs::msg::GpsGroup::_velecef_type arg)
  {
    msg_.velecef = std::move(arg);
    return Init_GpsGroup_posu(msg_);
  }

private:
  ::vectornav_msgs::msg::GpsGroup msg_;
};

class Init_GpsGroup_velned
{
public:
  explicit Init_GpsGroup_velned(::vectornav_msgs::msg::GpsGroup & msg)
  : msg_(msg)
  {}
  Init_GpsGroup_velecef velned(::vectornav_msgs::msg::GpsGroup::_velned_type arg)
  {
    msg_.velned = std::move(arg);
    return Init_GpsGroup_velecef(msg_);
  }

private:
  ::vectornav_msgs::msg::GpsGroup msg_;
};

class Init_GpsGroup_posecef
{
public:
  explicit Init_GpsGroup_posecef(::vectornav_msgs::msg::GpsGroup & msg)
  : msg_(msg)
  {}
  Init_GpsGroup_velned posecef(::vectornav_msgs::msg::GpsGroup::_posecef_type arg)
  {
    msg_.posecef = std::move(arg);
    return Init_GpsGroup_velned(msg_);
  }

private:
  ::vectornav_msgs::msg::GpsGroup msg_;
};

class Init_GpsGroup_poslla
{
public:
  explicit Init_GpsGroup_poslla(::vectornav_msgs::msg::GpsGroup & msg)
  : msg_(msg)
  {}
  Init_GpsGroup_posecef poslla(::vectornav_msgs::msg::GpsGroup::_poslla_type arg)
  {
    msg_.poslla = std::move(arg);
    return Init_GpsGroup_posecef(msg_);
  }

private:
  ::vectornav_msgs::msg::GpsGroup msg_;
};

class Init_GpsGroup_fix
{
public:
  explicit Init_GpsGroup_fix(::vectornav_msgs::msg::GpsGroup & msg)
  : msg_(msg)
  {}
  Init_GpsGroup_poslla fix(::vectornav_msgs::msg::GpsGroup::_fix_type arg)
  {
    msg_.fix = std::move(arg);
    return Init_GpsGroup_poslla(msg_);
  }

private:
  ::vectornav_msgs::msg::GpsGroup msg_;
};

class Init_GpsGroup_numsats
{
public:
  explicit Init_GpsGroup_numsats(::vectornav_msgs::msg::GpsGroup & msg)
  : msg_(msg)
  {}
  Init_GpsGroup_fix numsats(::vectornav_msgs::msg::GpsGroup::_numsats_type arg)
  {
    msg_.numsats = std::move(arg);
    return Init_GpsGroup_fix(msg_);
  }

private:
  ::vectornav_msgs::msg::GpsGroup msg_;
};

class Init_GpsGroup_week
{
public:
  explicit Init_GpsGroup_week(::vectornav_msgs::msg::GpsGroup & msg)
  : msg_(msg)
  {}
  Init_GpsGroup_numsats week(::vectornav_msgs::msg::GpsGroup::_week_type arg)
  {
    msg_.week = std::move(arg);
    return Init_GpsGroup_numsats(msg_);
  }

private:
  ::vectornav_msgs::msg::GpsGroup msg_;
};

class Init_GpsGroup_tow
{
public:
  explicit Init_GpsGroup_tow(::vectornav_msgs::msg::GpsGroup & msg)
  : msg_(msg)
  {}
  Init_GpsGroup_week tow(::vectornav_msgs::msg::GpsGroup::_tow_type arg)
  {
    msg_.tow = std::move(arg);
    return Init_GpsGroup_week(msg_);
  }

private:
  ::vectornav_msgs::msg::GpsGroup msg_;
};

class Init_GpsGroup_utc
{
public:
  explicit Init_GpsGroup_utc(::vectornav_msgs::msg::GpsGroup & msg)
  : msg_(msg)
  {}
  Init_GpsGroup_tow utc(::vectornav_msgs::msg::GpsGroup::_utc_type arg)
  {
    msg_.utc = std::move(arg);
    return Init_GpsGroup_tow(msg_);
  }

private:
  ::vectornav_msgs::msg::GpsGroup msg_;
};

class Init_GpsGroup_group_fields
{
public:
  explicit Init_GpsGroup_group_fields(::vectornav_msgs::msg::GpsGroup & msg)
  : msg_(msg)
  {}
  Init_GpsGroup_utc group_fields(::vectornav_msgs::msg::GpsGroup::_group_fields_type arg)
  {
    msg_.group_fields = std::move(arg);
    return Init_GpsGroup_utc(msg_);
  }

private:
  ::vectornav_msgs::msg::GpsGroup msg_;
};

class Init_GpsGroup_header
{
public:
  Init_GpsGroup_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_GpsGroup_group_fields header(::vectornav_msgs::msg::GpsGroup::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_GpsGroup_group_fields(msg_);
  }

private:
  ::vectornav_msgs::msg::GpsGroup msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::vectornav_msgs::msg::GpsGroup>()
{
  return vectornav_msgs::msg::builder::Init_GpsGroup_header();
}

}  // namespace vectornav_msgs

#endif  // VECTORNAV_MSGS__MSG__DETAIL__GPS_GROUP__BUILDER_HPP_
