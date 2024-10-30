// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from urc_msgs:msg/ArucoDetection.idl
// generated code does not contain a copyright notice

#ifndef URC_MSGS__MSG__DETAIL__ARUCO_DETECTION__BUILDER_HPP_
#define URC_MSGS__MSG__DETAIL__ARUCO_DETECTION__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "urc_msgs/msg/detail/aruco_detection__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace urc_msgs
{

namespace msg
{

namespace builder
{

class Init_ArucoDetection_which_camera
{
public:
  explicit Init_ArucoDetection_which_camera(::urc_msgs::msg::ArucoDetection & msg)
  : msg_(msg)
  {}
  ::urc_msgs::msg::ArucoDetection which_camera(::urc_msgs::msg::ArucoDetection::_which_camera_type arg)
  {
    msg_.which_camera = std::move(arg);
    return std::move(msg_);
  }

private:
  ::urc_msgs::msg::ArucoDetection msg_;
};

class Init_ArucoDetection_id
{
public:
  explicit Init_ArucoDetection_id(::urc_msgs::msg::ArucoDetection & msg)
  : msg_(msg)
  {}
  Init_ArucoDetection_which_camera id(::urc_msgs::msg::ArucoDetection::_id_type arg)
  {
    msg_.id = std::move(arg);
    return Init_ArucoDetection_which_camera(msg_);
  }

private:
  ::urc_msgs::msg::ArucoDetection msg_;
};

class Init_ArucoDetection_distance
{
public:
  explicit Init_ArucoDetection_distance(::urc_msgs::msg::ArucoDetection & msg)
  : msg_(msg)
  {}
  Init_ArucoDetection_id distance(::urc_msgs::msg::ArucoDetection::_distance_type arg)
  {
    msg_.distance = std::move(arg);
    return Init_ArucoDetection_id(msg_);
  }

private:
  ::urc_msgs::msg::ArucoDetection msg_;
};

class Init_ArucoDetection_y_angle
{
public:
  explicit Init_ArucoDetection_y_angle(::urc_msgs::msg::ArucoDetection & msg)
  : msg_(msg)
  {}
  Init_ArucoDetection_distance y_angle(::urc_msgs::msg::ArucoDetection::_y_angle_type arg)
  {
    msg_.y_angle = std::move(arg);
    return Init_ArucoDetection_distance(msg_);
  }

private:
  ::urc_msgs::msg::ArucoDetection msg_;
};

class Init_ArucoDetection_x_angle
{
public:
  explicit Init_ArucoDetection_x_angle(::urc_msgs::msg::ArucoDetection & msg)
  : msg_(msg)
  {}
  Init_ArucoDetection_y_angle x_angle(::urc_msgs::msg::ArucoDetection::_x_angle_type arg)
  {
    msg_.x_angle = std::move(arg);
    return Init_ArucoDetection_y_angle(msg_);
  }

private:
  ::urc_msgs::msg::ArucoDetection msg_;
};

class Init_ArucoDetection_header
{
public:
  Init_ArucoDetection_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_ArucoDetection_x_angle header(::urc_msgs::msg::ArucoDetection::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_ArucoDetection_x_angle(msg_);
  }

private:
  ::urc_msgs::msg::ArucoDetection msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::urc_msgs::msg::ArucoDetection>()
{
  return urc_msgs::msg::builder::Init_ArucoDetection_header();
}

}  // namespace urc_msgs

#endif  // URC_MSGS__MSG__DETAIL__ARUCO_DETECTION__BUILDER_HPP_
