// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from vectornav_msgs:msg/ImuGroup.idl
// generated code does not contain a copyright notice

#ifndef VECTORNAV_MSGS__MSG__DETAIL__IMU_GROUP__BUILDER_HPP_
#define VECTORNAV_MSGS__MSG__DETAIL__IMU_GROUP__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "vectornav_msgs/msg/detail/imu_group__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace vectornav_msgs
{

namespace msg
{

namespace builder
{

class Init_ImuGroup_sensat
{
public:
  explicit Init_ImuGroup_sensat(::vectornav_msgs::msg::ImuGroup & msg)
  : msg_(msg)
  {}
  ::vectornav_msgs::msg::ImuGroup sensat(::vectornav_msgs::msg::ImuGroup::_sensat_type arg)
  {
    msg_.sensat = std::move(arg);
    return std::move(msg_);
  }

private:
  ::vectornav_msgs::msg::ImuGroup msg_;
};

class Init_ImuGroup_angularrate
{
public:
  explicit Init_ImuGroup_angularrate(::vectornav_msgs::msg::ImuGroup & msg)
  : msg_(msg)
  {}
  Init_ImuGroup_sensat angularrate(::vectornav_msgs::msg::ImuGroup::_angularrate_type arg)
  {
    msg_.angularrate = std::move(arg);
    return Init_ImuGroup_sensat(msg_);
  }

private:
  ::vectornav_msgs::msg::ImuGroup msg_;
};

class Init_ImuGroup_accel
{
public:
  explicit Init_ImuGroup_accel(::vectornav_msgs::msg::ImuGroup & msg)
  : msg_(msg)
  {}
  Init_ImuGroup_angularrate accel(::vectornav_msgs::msg::ImuGroup::_accel_type arg)
  {
    msg_.accel = std::move(arg);
    return Init_ImuGroup_angularrate(msg_);
  }

private:
  ::vectornav_msgs::msg::ImuGroup msg_;
};

class Init_ImuGroup_mag
{
public:
  explicit Init_ImuGroup_mag(::vectornav_msgs::msg::ImuGroup & msg)
  : msg_(msg)
  {}
  Init_ImuGroup_accel mag(::vectornav_msgs::msg::ImuGroup::_mag_type arg)
  {
    msg_.mag = std::move(arg);
    return Init_ImuGroup_accel(msg_);
  }

private:
  ::vectornav_msgs::msg::ImuGroup msg_;
};

class Init_ImuGroup_deltavel
{
public:
  explicit Init_ImuGroup_deltavel(::vectornav_msgs::msg::ImuGroup & msg)
  : msg_(msg)
  {}
  Init_ImuGroup_mag deltavel(::vectornav_msgs::msg::ImuGroup::_deltavel_type arg)
  {
    msg_.deltavel = std::move(arg);
    return Init_ImuGroup_mag(msg_);
  }

private:
  ::vectornav_msgs::msg::ImuGroup msg_;
};

class Init_ImuGroup_deltatheta_dtheta
{
public:
  explicit Init_ImuGroup_deltatheta_dtheta(::vectornav_msgs::msg::ImuGroup & msg)
  : msg_(msg)
  {}
  Init_ImuGroup_deltavel deltatheta_dtheta(::vectornav_msgs::msg::ImuGroup::_deltatheta_dtheta_type arg)
  {
    msg_.deltatheta_dtheta = std::move(arg);
    return Init_ImuGroup_deltavel(msg_);
  }

private:
  ::vectornav_msgs::msg::ImuGroup msg_;
};

class Init_ImuGroup_deltatheta_time
{
public:
  explicit Init_ImuGroup_deltatheta_time(::vectornav_msgs::msg::ImuGroup & msg)
  : msg_(msg)
  {}
  Init_ImuGroup_deltatheta_dtheta deltatheta_time(::vectornav_msgs::msg::ImuGroup::_deltatheta_time_type arg)
  {
    msg_.deltatheta_time = std::move(arg);
    return Init_ImuGroup_deltatheta_dtheta(msg_);
  }

private:
  ::vectornav_msgs::msg::ImuGroup msg_;
};

class Init_ImuGroup_pres
{
public:
  explicit Init_ImuGroup_pres(::vectornav_msgs::msg::ImuGroup & msg)
  : msg_(msg)
  {}
  Init_ImuGroup_deltatheta_time pres(::vectornav_msgs::msg::ImuGroup::_pres_type arg)
  {
    msg_.pres = std::move(arg);
    return Init_ImuGroup_deltatheta_time(msg_);
  }

private:
  ::vectornav_msgs::msg::ImuGroup msg_;
};

class Init_ImuGroup_temp
{
public:
  explicit Init_ImuGroup_temp(::vectornav_msgs::msg::ImuGroup & msg)
  : msg_(msg)
  {}
  Init_ImuGroup_pres temp(::vectornav_msgs::msg::ImuGroup::_temp_type arg)
  {
    msg_.temp = std::move(arg);
    return Init_ImuGroup_pres(msg_);
  }

private:
  ::vectornav_msgs::msg::ImuGroup msg_;
};

class Init_ImuGroup_uncompgyro
{
public:
  explicit Init_ImuGroup_uncompgyro(::vectornav_msgs::msg::ImuGroup & msg)
  : msg_(msg)
  {}
  Init_ImuGroup_temp uncompgyro(::vectornav_msgs::msg::ImuGroup::_uncompgyro_type arg)
  {
    msg_.uncompgyro = std::move(arg);
    return Init_ImuGroup_temp(msg_);
  }

private:
  ::vectornav_msgs::msg::ImuGroup msg_;
};

class Init_ImuGroup_uncompaccel
{
public:
  explicit Init_ImuGroup_uncompaccel(::vectornav_msgs::msg::ImuGroup & msg)
  : msg_(msg)
  {}
  Init_ImuGroup_uncompgyro uncompaccel(::vectornav_msgs::msg::ImuGroup::_uncompaccel_type arg)
  {
    msg_.uncompaccel = std::move(arg);
    return Init_ImuGroup_uncompgyro(msg_);
  }

private:
  ::vectornav_msgs::msg::ImuGroup msg_;
};

class Init_ImuGroup_uncompmag
{
public:
  explicit Init_ImuGroup_uncompmag(::vectornav_msgs::msg::ImuGroup & msg)
  : msg_(msg)
  {}
  Init_ImuGroup_uncompaccel uncompmag(::vectornav_msgs::msg::ImuGroup::_uncompmag_type arg)
  {
    msg_.uncompmag = std::move(arg);
    return Init_ImuGroup_uncompaccel(msg_);
  }

private:
  ::vectornav_msgs::msg::ImuGroup msg_;
};

class Init_ImuGroup_imustatus
{
public:
  explicit Init_ImuGroup_imustatus(::vectornav_msgs::msg::ImuGroup & msg)
  : msg_(msg)
  {}
  Init_ImuGroup_uncompmag imustatus(::vectornav_msgs::msg::ImuGroup::_imustatus_type arg)
  {
    msg_.imustatus = std::move(arg);
    return Init_ImuGroup_uncompmag(msg_);
  }

private:
  ::vectornav_msgs::msg::ImuGroup msg_;
};

class Init_ImuGroup_group_fields
{
public:
  explicit Init_ImuGroup_group_fields(::vectornav_msgs::msg::ImuGroup & msg)
  : msg_(msg)
  {}
  Init_ImuGroup_imustatus group_fields(::vectornav_msgs::msg::ImuGroup::_group_fields_type arg)
  {
    msg_.group_fields = std::move(arg);
    return Init_ImuGroup_imustatus(msg_);
  }

private:
  ::vectornav_msgs::msg::ImuGroup msg_;
};

class Init_ImuGroup_header
{
public:
  Init_ImuGroup_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_ImuGroup_group_fields header(::vectornav_msgs::msg::ImuGroup::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_ImuGroup_group_fields(msg_);
  }

private:
  ::vectornav_msgs::msg::ImuGroup msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::vectornav_msgs::msg::ImuGroup>()
{
  return vectornav_msgs::msg::builder::Init_ImuGroup_header();
}

}  // namespace vectornav_msgs

#endif  // VECTORNAV_MSGS__MSG__DETAIL__IMU_GROUP__BUILDER_HPP_
