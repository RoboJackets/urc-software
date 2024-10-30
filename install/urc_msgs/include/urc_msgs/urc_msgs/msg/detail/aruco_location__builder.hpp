// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from urc_msgs:msg/ArucoLocation.idl
// generated code does not contain a copyright notice

#ifndef URC_MSGS__MSG__DETAIL__ARUCO_LOCATION__BUILDER_HPP_
#define URC_MSGS__MSG__DETAIL__ARUCO_LOCATION__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "urc_msgs/msg/detail/aruco_location__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace urc_msgs
{

namespace msg
{

namespace builder
{

class Init_ArucoLocation_which_camera
{
public:
  explicit Init_ArucoLocation_which_camera(::urc_msgs::msg::ArucoLocation & msg)
  : msg_(msg)
  {}
  ::urc_msgs::msg::ArucoLocation which_camera(::urc_msgs::msg::ArucoLocation::_which_camera_type arg)
  {
    msg_.which_camera = std::move(arg);
    return std::move(msg_);
  }

private:
  ::urc_msgs::msg::ArucoLocation msg_;
};

class Init_ArucoLocation_id
{
public:
  explicit Init_ArucoLocation_id(::urc_msgs::msg::ArucoLocation & msg)
  : msg_(msg)
  {}
  Init_ArucoLocation_which_camera id(::urc_msgs::msg::ArucoLocation::_id_type arg)
  {
    msg_.id = std::move(arg);
    return Init_ArucoLocation_which_camera(msg_);
  }

private:
  ::urc_msgs::msg::ArucoLocation msg_;
};

class Init_ArucoLocation_lat
{
public:
  explicit Init_ArucoLocation_lat(::urc_msgs::msg::ArucoLocation & msg)
  : msg_(msg)
  {}
  Init_ArucoLocation_id lat(::urc_msgs::msg::ArucoLocation::_lat_type arg)
  {
    msg_.lat = std::move(arg);
    return Init_ArucoLocation_id(msg_);
  }

private:
  ::urc_msgs::msg::ArucoLocation msg_;
};

class Init_ArucoLocation_lon
{
public:
  explicit Init_ArucoLocation_lon(::urc_msgs::msg::ArucoLocation & msg)
  : msg_(msg)
  {}
  Init_ArucoLocation_lat lon(::urc_msgs::msg::ArucoLocation::_lon_type arg)
  {
    msg_.lon = std::move(arg);
    return Init_ArucoLocation_lat(msg_);
  }

private:
  ::urc_msgs::msg::ArucoLocation msg_;
};

class Init_ArucoLocation_header
{
public:
  Init_ArucoLocation_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_ArucoLocation_lon header(::urc_msgs::msg::ArucoLocation::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_ArucoLocation_lon(msg_);
  }

private:
  ::urc_msgs::msg::ArucoLocation msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::urc_msgs::msg::ArucoLocation>()
{
  return urc_msgs::msg::builder::Init_ArucoLocation_header();
}

}  // namespace urc_msgs

#endif  // URC_MSGS__MSG__DETAIL__ARUCO_LOCATION__BUILDER_HPP_
