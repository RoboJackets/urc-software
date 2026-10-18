// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from vectornav_msgs:msg/CommonGroup.idl
// generated code does not contain a copyright notice

#ifndef VECTORNAV_MSGS__MSG__DETAIL__COMMON_GROUP__BUILDER_HPP_
#define VECTORNAV_MSGS__MSG__DETAIL__COMMON_GROUP__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "vectornav_msgs/msg/detail/common_group__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace vectornav_msgs
{

namespace msg
{

namespace builder
{

class Init_CommonGroup_timegpspps
{
public:
  explicit Init_CommonGroup_timegpspps(::vectornav_msgs::msg::CommonGroup & msg)
  : msg_(msg)
  {}
  ::vectornav_msgs::msg::CommonGroup timegpspps(::vectornav_msgs::msg::CommonGroup::_timegpspps_type arg)
  {
    msg_.timegpspps = std::move(arg);
    return std::move(msg_);
  }

private:
  ::vectornav_msgs::msg::CommonGroup msg_;
};

class Init_CommonGroup_syncincnt
{
public:
  explicit Init_CommonGroup_syncincnt(::vectornav_msgs::msg::CommonGroup & msg)
  : msg_(msg)
  {}
  Init_CommonGroup_timegpspps syncincnt(::vectornav_msgs::msg::CommonGroup::_syncincnt_type arg)
  {
    msg_.syncincnt = std::move(arg);
    return Init_CommonGroup_timegpspps(msg_);
  }

private:
  ::vectornav_msgs::msg::CommonGroup msg_;
};

class Init_CommonGroup_insstatus
{
public:
  explicit Init_CommonGroup_insstatus(::vectornav_msgs::msg::CommonGroup & msg)
  : msg_(msg)
  {}
  Init_CommonGroup_syncincnt insstatus(::vectornav_msgs::msg::CommonGroup::_insstatus_type arg)
  {
    msg_.insstatus = std::move(arg);
    return Init_CommonGroup_syncincnt(msg_);
  }

private:
  ::vectornav_msgs::msg::CommonGroup msg_;
};

class Init_CommonGroup_deltatheta_dvel
{
public:
  explicit Init_CommonGroup_deltatheta_dvel(::vectornav_msgs::msg::CommonGroup & msg)
  : msg_(msg)
  {}
  Init_CommonGroup_insstatus deltatheta_dvel(::vectornav_msgs::msg::CommonGroup::_deltatheta_dvel_type arg)
  {
    msg_.deltatheta_dvel = std::move(arg);
    return Init_CommonGroup_insstatus(msg_);
  }

private:
  ::vectornav_msgs::msg::CommonGroup msg_;
};

class Init_CommonGroup_deltatheta_dtheta
{
public:
  explicit Init_CommonGroup_deltatheta_dtheta(::vectornav_msgs::msg::CommonGroup & msg)
  : msg_(msg)
  {}
  Init_CommonGroup_deltatheta_dvel deltatheta_dtheta(::vectornav_msgs::msg::CommonGroup::_deltatheta_dtheta_type arg)
  {
    msg_.deltatheta_dtheta = std::move(arg);
    return Init_CommonGroup_deltatheta_dvel(msg_);
  }

private:
  ::vectornav_msgs::msg::CommonGroup msg_;
};

class Init_CommonGroup_deltatheta_dtime
{
public:
  explicit Init_CommonGroup_deltatheta_dtime(::vectornav_msgs::msg::CommonGroup & msg)
  : msg_(msg)
  {}
  Init_CommonGroup_deltatheta_dtheta deltatheta_dtime(::vectornav_msgs::msg::CommonGroup::_deltatheta_dtime_type arg)
  {
    msg_.deltatheta_dtime = std::move(arg);
    return Init_CommonGroup_deltatheta_dtheta(msg_);
  }

private:
  ::vectornav_msgs::msg::CommonGroup msg_;
};

class Init_CommonGroup_magpres_pres
{
public:
  explicit Init_CommonGroup_magpres_pres(::vectornav_msgs::msg::CommonGroup & msg)
  : msg_(msg)
  {}
  Init_CommonGroup_deltatheta_dtime magpres_pres(::vectornav_msgs::msg::CommonGroup::_magpres_pres_type arg)
  {
    msg_.magpres_pres = std::move(arg);
    return Init_CommonGroup_deltatheta_dtime(msg_);
  }

private:
  ::vectornav_msgs::msg::CommonGroup msg_;
};

class Init_CommonGroup_magpres_temp
{
public:
  explicit Init_CommonGroup_magpres_temp(::vectornav_msgs::msg::CommonGroup & msg)
  : msg_(msg)
  {}
  Init_CommonGroup_magpres_pres magpres_temp(::vectornav_msgs::msg::CommonGroup::_magpres_temp_type arg)
  {
    msg_.magpres_temp = std::move(arg);
    return Init_CommonGroup_magpres_pres(msg_);
  }

private:
  ::vectornav_msgs::msg::CommonGroup msg_;
};

class Init_CommonGroup_magpres_mag
{
public:
  explicit Init_CommonGroup_magpres_mag(::vectornav_msgs::msg::CommonGroup & msg)
  : msg_(msg)
  {}
  Init_CommonGroup_magpres_temp magpres_mag(::vectornav_msgs::msg::CommonGroup::_magpres_mag_type arg)
  {
    msg_.magpres_mag = std::move(arg);
    return Init_CommonGroup_magpres_temp(msg_);
  }

private:
  ::vectornav_msgs::msg::CommonGroup msg_;
};

class Init_CommonGroup_imu_rate
{
public:
  explicit Init_CommonGroup_imu_rate(::vectornav_msgs::msg::CommonGroup & msg)
  : msg_(msg)
  {}
  Init_CommonGroup_magpres_mag imu_rate(::vectornav_msgs::msg::CommonGroup::_imu_rate_type arg)
  {
    msg_.imu_rate = std::move(arg);
    return Init_CommonGroup_magpres_mag(msg_);
  }

private:
  ::vectornav_msgs::msg::CommonGroup msg_;
};

class Init_CommonGroup_imu_accel
{
public:
  explicit Init_CommonGroup_imu_accel(::vectornav_msgs::msg::CommonGroup & msg)
  : msg_(msg)
  {}
  Init_CommonGroup_imu_rate imu_accel(::vectornav_msgs::msg::CommonGroup::_imu_accel_type arg)
  {
    msg_.imu_accel = std::move(arg);
    return Init_CommonGroup_imu_rate(msg_);
  }

private:
  ::vectornav_msgs::msg::CommonGroup msg_;
};

class Init_CommonGroup_accel
{
public:
  explicit Init_CommonGroup_accel(::vectornav_msgs::msg::CommonGroup & msg)
  : msg_(msg)
  {}
  Init_CommonGroup_imu_accel accel(::vectornav_msgs::msg::CommonGroup::_accel_type arg)
  {
    msg_.accel = std::move(arg);
    return Init_CommonGroup_imu_accel(msg_);
  }

private:
  ::vectornav_msgs::msg::CommonGroup msg_;
};

class Init_CommonGroup_velocity
{
public:
  explicit Init_CommonGroup_velocity(::vectornav_msgs::msg::CommonGroup & msg)
  : msg_(msg)
  {}
  Init_CommonGroup_accel velocity(::vectornav_msgs::msg::CommonGroup::_velocity_type arg)
  {
    msg_.velocity = std::move(arg);
    return Init_CommonGroup_accel(msg_);
  }

private:
  ::vectornav_msgs::msg::CommonGroup msg_;
};

class Init_CommonGroup_position
{
public:
  explicit Init_CommonGroup_position(::vectornav_msgs::msg::CommonGroup & msg)
  : msg_(msg)
  {}
  Init_CommonGroup_velocity position(::vectornav_msgs::msg::CommonGroup::_position_type arg)
  {
    msg_.position = std::move(arg);
    return Init_CommonGroup_velocity(msg_);
  }

private:
  ::vectornav_msgs::msg::CommonGroup msg_;
};

class Init_CommonGroup_angularrate
{
public:
  explicit Init_CommonGroup_angularrate(::vectornav_msgs::msg::CommonGroup & msg)
  : msg_(msg)
  {}
  Init_CommonGroup_position angularrate(::vectornav_msgs::msg::CommonGroup::_angularrate_type arg)
  {
    msg_.angularrate = std::move(arg);
    return Init_CommonGroup_position(msg_);
  }

private:
  ::vectornav_msgs::msg::CommonGroup msg_;
};

class Init_CommonGroup_quaternion
{
public:
  explicit Init_CommonGroup_quaternion(::vectornav_msgs::msg::CommonGroup & msg)
  : msg_(msg)
  {}
  Init_CommonGroup_angularrate quaternion(::vectornav_msgs::msg::CommonGroup::_quaternion_type arg)
  {
    msg_.quaternion = std::move(arg);
    return Init_CommonGroup_angularrate(msg_);
  }

private:
  ::vectornav_msgs::msg::CommonGroup msg_;
};

class Init_CommonGroup_yawpitchroll
{
public:
  explicit Init_CommonGroup_yawpitchroll(::vectornav_msgs::msg::CommonGroup & msg)
  : msg_(msg)
  {}
  Init_CommonGroup_quaternion yawpitchroll(::vectornav_msgs::msg::CommonGroup::_yawpitchroll_type arg)
  {
    msg_.yawpitchroll = std::move(arg);
    return Init_CommonGroup_quaternion(msg_);
  }

private:
  ::vectornav_msgs::msg::CommonGroup msg_;
};

class Init_CommonGroup_timesyncin
{
public:
  explicit Init_CommonGroup_timesyncin(::vectornav_msgs::msg::CommonGroup & msg)
  : msg_(msg)
  {}
  Init_CommonGroup_yawpitchroll timesyncin(::vectornav_msgs::msg::CommonGroup::_timesyncin_type arg)
  {
    msg_.timesyncin = std::move(arg);
    return Init_CommonGroup_yawpitchroll(msg_);
  }

private:
  ::vectornav_msgs::msg::CommonGroup msg_;
};

class Init_CommonGroup_timegps
{
public:
  explicit Init_CommonGroup_timegps(::vectornav_msgs::msg::CommonGroup & msg)
  : msg_(msg)
  {}
  Init_CommonGroup_timesyncin timegps(::vectornav_msgs::msg::CommonGroup::_timegps_type arg)
  {
    msg_.timegps = std::move(arg);
    return Init_CommonGroup_timesyncin(msg_);
  }

private:
  ::vectornav_msgs::msg::CommonGroup msg_;
};

class Init_CommonGroup_timestartup
{
public:
  explicit Init_CommonGroup_timestartup(::vectornav_msgs::msg::CommonGroup & msg)
  : msg_(msg)
  {}
  Init_CommonGroup_timegps timestartup(::vectornav_msgs::msg::CommonGroup::_timestartup_type arg)
  {
    msg_.timestartup = std::move(arg);
    return Init_CommonGroup_timegps(msg_);
  }

private:
  ::vectornav_msgs::msg::CommonGroup msg_;
};

class Init_CommonGroup_group_fields
{
public:
  explicit Init_CommonGroup_group_fields(::vectornav_msgs::msg::CommonGroup & msg)
  : msg_(msg)
  {}
  Init_CommonGroup_timestartup group_fields(::vectornav_msgs::msg::CommonGroup::_group_fields_type arg)
  {
    msg_.group_fields = std::move(arg);
    return Init_CommonGroup_timestartup(msg_);
  }

private:
  ::vectornav_msgs::msg::CommonGroup msg_;
};

class Init_CommonGroup_header
{
public:
  Init_CommonGroup_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_CommonGroup_group_fields header(::vectornav_msgs::msg::CommonGroup::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_CommonGroup_group_fields(msg_);
  }

private:
  ::vectornav_msgs::msg::CommonGroup msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::vectornav_msgs::msg::CommonGroup>()
{
  return vectornav_msgs::msg::builder::Init_CommonGroup_header();
}

}  // namespace vectornav_msgs

#endif  // VECTORNAV_MSGS__MSG__DETAIL__COMMON_GROUP__BUILDER_HPP_
