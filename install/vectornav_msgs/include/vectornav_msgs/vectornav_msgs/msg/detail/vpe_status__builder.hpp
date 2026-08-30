// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from vectornav_msgs:msg/VpeStatus.idl
// generated code does not contain a copyright notice

#ifndef VECTORNAV_MSGS__MSG__DETAIL__VPE_STATUS__BUILDER_HPP_
#define VECTORNAV_MSGS__MSG__DETAIL__VPE_STATUS__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "vectornav_msgs/msg/detail/vpe_status__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace vectornav_msgs
{

namespace msg
{

namespace builder
{

class Init_VpeStatus_known_accel_disturbance
{
public:
  explicit Init_VpeStatus_known_accel_disturbance(::vectornav_msgs::msg::VpeStatus & msg)
  : msg_(msg)
  {}
  ::vectornav_msgs::msg::VpeStatus known_accel_disturbance(::vectornav_msgs::msg::VpeStatus::_known_accel_disturbance_type arg)
  {
    msg_.known_accel_disturbance = std::move(arg);
    return std::move(msg_);
  }

private:
  ::vectornav_msgs::msg::VpeStatus msg_;
};

class Init_VpeStatus_known_mag_disturbance
{
public:
  explicit Init_VpeStatus_known_mag_disturbance(::vectornav_msgs::msg::VpeStatus & msg)
  : msg_(msg)
  {}
  Init_VpeStatus_known_accel_disturbance known_mag_disturbance(::vectornav_msgs::msg::VpeStatus::_known_mag_disturbance_type arg)
  {
    msg_.known_mag_disturbance = std::move(arg);
    return Init_VpeStatus_known_accel_disturbance(msg_);
  }

private:
  ::vectornav_msgs::msg::VpeStatus msg_;
};

class Init_VpeStatus_acc_saturation
{
public:
  explicit Init_VpeStatus_acc_saturation(::vectornav_msgs::msg::VpeStatus & msg)
  : msg_(msg)
  {}
  Init_VpeStatus_known_mag_disturbance acc_saturation(::vectornav_msgs::msg::VpeStatus::_acc_saturation_type arg)
  {
    msg_.acc_saturation = std::move(arg);
    return Init_VpeStatus_known_mag_disturbance(msg_);
  }

private:
  ::vectornav_msgs::msg::VpeStatus msg_;
};

class Init_VpeStatus_acc_disturbance
{
public:
  explicit Init_VpeStatus_acc_disturbance(::vectornav_msgs::msg::VpeStatus & msg)
  : msg_(msg)
  {}
  Init_VpeStatus_acc_saturation acc_disturbance(::vectornav_msgs::msg::VpeStatus::_acc_disturbance_type arg)
  {
    msg_.acc_disturbance = std::move(arg);
    return Init_VpeStatus_acc_saturation(msg_);
  }

private:
  ::vectornav_msgs::msg::VpeStatus msg_;
};

class Init_VpeStatus_mag_saturation
{
public:
  explicit Init_VpeStatus_mag_saturation(::vectornav_msgs::msg::VpeStatus & msg)
  : msg_(msg)
  {}
  Init_VpeStatus_acc_disturbance mag_saturation(::vectornav_msgs::msg::VpeStatus::_mag_saturation_type arg)
  {
    msg_.mag_saturation = std::move(arg);
    return Init_VpeStatus_acc_disturbance(msg_);
  }

private:
  ::vectornav_msgs::msg::VpeStatus msg_;
};

class Init_VpeStatus_mag_disturbance
{
public:
  explicit Init_VpeStatus_mag_disturbance(::vectornav_msgs::msg::VpeStatus & msg)
  : msg_(msg)
  {}
  Init_VpeStatus_mag_saturation mag_disturbance(::vectornav_msgs::msg::VpeStatus::_mag_disturbance_type arg)
  {
    msg_.mag_disturbance = std::move(arg);
    return Init_VpeStatus_mag_saturation(msg_);
  }

private:
  ::vectornav_msgs::msg::VpeStatus msg_;
};

class Init_VpeStatus_gyro_saturation_recovery
{
public:
  explicit Init_VpeStatus_gyro_saturation_recovery(::vectornav_msgs::msg::VpeStatus & msg)
  : msg_(msg)
  {}
  Init_VpeStatus_mag_disturbance gyro_saturation_recovery(::vectornav_msgs::msg::VpeStatus::_gyro_saturation_recovery_type arg)
  {
    msg_.gyro_saturation_recovery = std::move(arg);
    return Init_VpeStatus_mag_disturbance(msg_);
  }

private:
  ::vectornav_msgs::msg::VpeStatus msg_;
};

class Init_VpeStatus_gyro_saturation
{
public:
  explicit Init_VpeStatus_gyro_saturation(::vectornav_msgs::msg::VpeStatus & msg)
  : msg_(msg)
  {}
  Init_VpeStatus_gyro_saturation_recovery gyro_saturation(::vectornav_msgs::msg::VpeStatus::_gyro_saturation_type arg)
  {
    msg_.gyro_saturation = std::move(arg);
    return Init_VpeStatus_gyro_saturation_recovery(msg_);
  }

private:
  ::vectornav_msgs::msg::VpeStatus msg_;
};

class Init_VpeStatus_attitude_quality
{
public:
  Init_VpeStatus_attitude_quality()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_VpeStatus_gyro_saturation attitude_quality(::vectornav_msgs::msg::VpeStatus::_attitude_quality_type arg)
  {
    msg_.attitude_quality = std::move(arg);
    return Init_VpeStatus_gyro_saturation(msg_);
  }

private:
  ::vectornav_msgs::msg::VpeStatus msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::vectornav_msgs::msg::VpeStatus>()
{
  return vectornav_msgs::msg::builder::Init_VpeStatus_attitude_quality();
}

}  // namespace vectornav_msgs

#endif  // VECTORNAV_MSGS__MSG__DETAIL__VPE_STATUS__BUILDER_HPP_
