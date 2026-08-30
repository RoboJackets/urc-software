// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from vectornav_msgs:msg/AttitudeGroup.idl
// generated code does not contain a copyright notice

#ifndef VECTORNAV_MSGS__MSG__DETAIL__ATTITUDE_GROUP__BUILDER_HPP_
#define VECTORNAV_MSGS__MSG__DETAIL__ATTITUDE_GROUP__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "vectornav_msgs/msg/detail/attitude_group__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace vectornav_msgs
{

namespace msg
{

namespace builder
{

class Init_AttitudeGroup_ypru
{
public:
  explicit Init_AttitudeGroup_ypru(::vectornav_msgs::msg::AttitudeGroup & msg)
  : msg_(msg)
  {}
  ::vectornav_msgs::msg::AttitudeGroup ypru(::vectornav_msgs::msg::AttitudeGroup::_ypru_type arg)
  {
    msg_.ypru = std::move(arg);
    return std::move(msg_);
  }

private:
  ::vectornav_msgs::msg::AttitudeGroup msg_;
};

class Init_AttitudeGroup_linearaccelned
{
public:
  explicit Init_AttitudeGroup_linearaccelned(::vectornav_msgs::msg::AttitudeGroup & msg)
  : msg_(msg)
  {}
  Init_AttitudeGroup_ypru linearaccelned(::vectornav_msgs::msg::AttitudeGroup::_linearaccelned_type arg)
  {
    msg_.linearaccelned = std::move(arg);
    return Init_AttitudeGroup_ypru(msg_);
  }

private:
  ::vectornav_msgs::msg::AttitudeGroup msg_;
};

class Init_AttitudeGroup_linearaccelbody
{
public:
  explicit Init_AttitudeGroup_linearaccelbody(::vectornav_msgs::msg::AttitudeGroup & msg)
  : msg_(msg)
  {}
  Init_AttitudeGroup_linearaccelned linearaccelbody(::vectornav_msgs::msg::AttitudeGroup::_linearaccelbody_type arg)
  {
    msg_.linearaccelbody = std::move(arg);
    return Init_AttitudeGroup_linearaccelned(msg_);
  }

private:
  ::vectornav_msgs::msg::AttitudeGroup msg_;
};

class Init_AttitudeGroup_accelned
{
public:
  explicit Init_AttitudeGroup_accelned(::vectornav_msgs::msg::AttitudeGroup & msg)
  : msg_(msg)
  {}
  Init_AttitudeGroup_linearaccelbody accelned(::vectornav_msgs::msg::AttitudeGroup::_accelned_type arg)
  {
    msg_.accelned = std::move(arg);
    return Init_AttitudeGroup_linearaccelbody(msg_);
  }

private:
  ::vectornav_msgs::msg::AttitudeGroup msg_;
};

class Init_AttitudeGroup_magned
{
public:
  explicit Init_AttitudeGroup_magned(::vectornav_msgs::msg::AttitudeGroup & msg)
  : msg_(msg)
  {}
  Init_AttitudeGroup_accelned magned(::vectornav_msgs::msg::AttitudeGroup::_magned_type arg)
  {
    msg_.magned = std::move(arg);
    return Init_AttitudeGroup_accelned(msg_);
  }

private:
  ::vectornav_msgs::msg::AttitudeGroup msg_;
};

class Init_AttitudeGroup_dcm
{
public:
  explicit Init_AttitudeGroup_dcm(::vectornav_msgs::msg::AttitudeGroup & msg)
  : msg_(msg)
  {}
  Init_AttitudeGroup_magned dcm(::vectornav_msgs::msg::AttitudeGroup::_dcm_type arg)
  {
    msg_.dcm = std::move(arg);
    return Init_AttitudeGroup_magned(msg_);
  }

private:
  ::vectornav_msgs::msg::AttitudeGroup msg_;
};

class Init_AttitudeGroup_quaternion
{
public:
  explicit Init_AttitudeGroup_quaternion(::vectornav_msgs::msg::AttitudeGroup & msg)
  : msg_(msg)
  {}
  Init_AttitudeGroup_dcm quaternion(::vectornav_msgs::msg::AttitudeGroup::_quaternion_type arg)
  {
    msg_.quaternion = std::move(arg);
    return Init_AttitudeGroup_dcm(msg_);
  }

private:
  ::vectornav_msgs::msg::AttitudeGroup msg_;
};

class Init_AttitudeGroup_yawpitchroll
{
public:
  explicit Init_AttitudeGroup_yawpitchroll(::vectornav_msgs::msg::AttitudeGroup & msg)
  : msg_(msg)
  {}
  Init_AttitudeGroup_quaternion yawpitchroll(::vectornav_msgs::msg::AttitudeGroup::_yawpitchroll_type arg)
  {
    msg_.yawpitchroll = std::move(arg);
    return Init_AttitudeGroup_quaternion(msg_);
  }

private:
  ::vectornav_msgs::msg::AttitudeGroup msg_;
};

class Init_AttitudeGroup_vpestatus
{
public:
  explicit Init_AttitudeGroup_vpestatus(::vectornav_msgs::msg::AttitudeGroup & msg)
  : msg_(msg)
  {}
  Init_AttitudeGroup_yawpitchroll vpestatus(::vectornav_msgs::msg::AttitudeGroup::_vpestatus_type arg)
  {
    msg_.vpestatus = std::move(arg);
    return Init_AttitudeGroup_yawpitchroll(msg_);
  }

private:
  ::vectornav_msgs::msg::AttitudeGroup msg_;
};

class Init_AttitudeGroup_group_fields
{
public:
  explicit Init_AttitudeGroup_group_fields(::vectornav_msgs::msg::AttitudeGroup & msg)
  : msg_(msg)
  {}
  Init_AttitudeGroup_vpestatus group_fields(::vectornav_msgs::msg::AttitudeGroup::_group_fields_type arg)
  {
    msg_.group_fields = std::move(arg);
    return Init_AttitudeGroup_vpestatus(msg_);
  }

private:
  ::vectornav_msgs::msg::AttitudeGroup msg_;
};

class Init_AttitudeGroup_header
{
public:
  Init_AttitudeGroup_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_AttitudeGroup_group_fields header(::vectornav_msgs::msg::AttitudeGroup::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_AttitudeGroup_group_fields(msg_);
  }

private:
  ::vectornav_msgs::msg::AttitudeGroup msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::vectornav_msgs::msg::AttitudeGroup>()
{
  return vectornav_msgs::msg::builder::Init_AttitudeGroup_header();
}

}  // namespace vectornav_msgs

#endif  // VECTORNAV_MSGS__MSG__DETAIL__ATTITUDE_GROUP__BUILDER_HPP_
