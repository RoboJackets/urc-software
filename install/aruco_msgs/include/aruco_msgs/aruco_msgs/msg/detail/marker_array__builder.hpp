// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from aruco_msgs:msg/MarkerArray.idl
// generated code does not contain a copyright notice

#ifndef ARUCO_MSGS__MSG__DETAIL__MARKER_ARRAY__BUILDER_HPP_
#define ARUCO_MSGS__MSG__DETAIL__MARKER_ARRAY__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "aruco_msgs/msg/detail/marker_array__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace aruco_msgs
{

namespace msg
{

namespace builder
{

class Init_MarkerArray_markers
{
public:
  explicit Init_MarkerArray_markers(::aruco_msgs::msg::MarkerArray & msg)
  : msg_(msg)
  {}
  ::aruco_msgs::msg::MarkerArray markers(::aruco_msgs::msg::MarkerArray::_markers_type arg)
  {
    msg_.markers = std::move(arg);
    return std::move(msg_);
  }

private:
  ::aruco_msgs::msg::MarkerArray msg_;
};

class Init_MarkerArray_header
{
public:
  Init_MarkerArray_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_MarkerArray_markers header(::aruco_msgs::msg::MarkerArray::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_MarkerArray_markers(msg_);
  }

private:
  ::aruco_msgs::msg::MarkerArray msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::aruco_msgs::msg::MarkerArray>()
{
  return aruco_msgs::msg::builder::Init_MarkerArray_header();
}

}  // namespace aruco_msgs

#endif  // ARUCO_MSGS__MSG__DETAIL__MARKER_ARRAY__BUILDER_HPP_
