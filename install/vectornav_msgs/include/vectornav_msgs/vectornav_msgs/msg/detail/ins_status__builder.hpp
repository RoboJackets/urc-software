// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from vectornav_msgs:msg/InsStatus.idl
// generated code does not contain a copyright notice

#ifndef VECTORNAV_MSGS__MSG__DETAIL__INS_STATUS__BUILDER_HPP_
#define VECTORNAV_MSGS__MSG__DETAIL__INS_STATUS__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "vectornav_msgs/msg/detail/ins_status__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace vectornav_msgs
{

namespace msg
{

namespace builder
{

class Init_InsStatus_gps_compass
{
public:
  explicit Init_InsStatus_gps_compass(::vectornav_msgs::msg::InsStatus & msg)
  : msg_(msg)
  {}
  ::vectornav_msgs::msg::InsStatus gps_compass(::vectornav_msgs::msg::InsStatus::_gps_compass_type arg)
  {
    msg_.gps_compass = std::move(arg);
    return std::move(msg_);
  }

private:
  ::vectornav_msgs::msg::InsStatus msg_;
};

class Init_InsStatus_gps_heading_ins
{
public:
  explicit Init_InsStatus_gps_heading_ins(::vectornav_msgs::msg::InsStatus & msg)
  : msg_(msg)
  {}
  Init_InsStatus_gps_compass gps_heading_ins(::vectornav_msgs::msg::InsStatus::_gps_heading_ins_type arg)
  {
    msg_.gps_heading_ins = std::move(arg);
    return Init_InsStatus_gps_compass(msg_);
  }

private:
  ::vectornav_msgs::msg::InsStatus msg_;
};

class Init_InsStatus_gps_error
{
public:
  explicit Init_InsStatus_gps_error(::vectornav_msgs::msg::InsStatus & msg)
  : msg_(msg)
  {}
  Init_InsStatus_gps_heading_ins gps_error(::vectornav_msgs::msg::InsStatus::_gps_error_type arg)
  {
    msg_.gps_error = std::move(arg);
    return Init_InsStatus_gps_heading_ins(msg_);
  }

private:
  ::vectornav_msgs::msg::InsStatus msg_;
};

class Init_InsStatus_mag_pres_error
{
public:
  explicit Init_InsStatus_mag_pres_error(::vectornav_msgs::msg::InsStatus & msg)
  : msg_(msg)
  {}
  Init_InsStatus_gps_error mag_pres_error(::vectornav_msgs::msg::InsStatus::_mag_pres_error_type arg)
  {
    msg_.mag_pres_error = std::move(arg);
    return Init_InsStatus_gps_error(msg_);
  }

private:
  ::vectornav_msgs::msg::InsStatus msg_;
};

class Init_InsStatus_imu_error
{
public:
  explicit Init_InsStatus_imu_error(::vectornav_msgs::msg::InsStatus & msg)
  : msg_(msg)
  {}
  Init_InsStatus_mag_pres_error imu_error(::vectornav_msgs::msg::InsStatus::_imu_error_type arg)
  {
    msg_.imu_error = std::move(arg);
    return Init_InsStatus_mag_pres_error(msg_);
  }

private:
  ::vectornav_msgs::msg::InsStatus msg_;
};

class Init_InsStatus_time_error
{
public:
  explicit Init_InsStatus_time_error(::vectornav_msgs::msg::InsStatus & msg)
  : msg_(msg)
  {}
  Init_InsStatus_imu_error time_error(::vectornav_msgs::msg::InsStatus::_time_error_type arg)
  {
    msg_.time_error = std::move(arg);
    return Init_InsStatus_imu_error(msg_);
  }

private:
  ::vectornav_msgs::msg::InsStatus msg_;
};

class Init_InsStatus_gps_fix
{
public:
  explicit Init_InsStatus_gps_fix(::vectornav_msgs::msg::InsStatus & msg)
  : msg_(msg)
  {}
  Init_InsStatus_time_error gps_fix(::vectornav_msgs::msg::InsStatus::_gps_fix_type arg)
  {
    msg_.gps_fix = std::move(arg);
    return Init_InsStatus_time_error(msg_);
  }

private:
  ::vectornav_msgs::msg::InsStatus msg_;
};

class Init_InsStatus_mode
{
public:
  Init_InsStatus_mode()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_InsStatus_gps_fix mode(::vectornav_msgs::msg::InsStatus::_mode_type arg)
  {
    msg_.mode = std::move(arg);
    return Init_InsStatus_gps_fix(msg_);
  }

private:
  ::vectornav_msgs::msg::InsStatus msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::vectornav_msgs::msg::InsStatus>()
{
  return vectornav_msgs::msg::builder::Init_InsStatus_mode();
}

}  // namespace vectornav_msgs

#endif  // VECTORNAV_MSGS__MSG__DETAIL__INS_STATUS__BUILDER_HPP_
