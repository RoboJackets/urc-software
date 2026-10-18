// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from urc_msgs:srv/GenerateSpiralSearch.idl
// generated code does not contain a copyright notice

#ifndef URC_MSGS__SRV__DETAIL__GENERATE_SPIRAL_SEARCH__BUILDER_HPP_
#define URC_MSGS__SRV__DETAIL__GENERATE_SPIRAL_SEARCH__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "urc_msgs/srv/detail/generate_spiral_search__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace urc_msgs
{

namespace srv
{

namespace builder
{

class Init_GenerateSpiralSearch_Request_waypoint_spacing
{
public:
  explicit Init_GenerateSpiralSearch_Request_waypoint_spacing(::urc_msgs::srv::GenerateSpiralSearch_Request & msg)
  : msg_(msg)
  {}
  ::urc_msgs::srv::GenerateSpiralSearch_Request waypoint_spacing(::urc_msgs::srv::GenerateSpiralSearch_Request::_waypoint_spacing_type arg)
  {
    msg_.waypoint_spacing = std::move(arg);
    return std::move(msg_);
  }

private:
  ::urc_msgs::srv::GenerateSpiralSearch_Request msg_;
};

class Init_GenerateSpiralSearch_Request_track_spacing
{
public:
  explicit Init_GenerateSpiralSearch_Request_track_spacing(::urc_msgs::srv::GenerateSpiralSearch_Request & msg)
  : msg_(msg)
  {}
  Init_GenerateSpiralSearch_Request_waypoint_spacing track_spacing(::urc_msgs::srv::GenerateSpiralSearch_Request::_track_spacing_type arg)
  {
    msg_.track_spacing = std::move(arg);
    return Init_GenerateSpiralSearch_Request_waypoint_spacing(msg_);
  }

private:
  ::urc_msgs::srv::GenerateSpiralSearch_Request msg_;
};

class Init_GenerateSpiralSearch_Request_search_radius
{
public:
  explicit Init_GenerateSpiralSearch_Request_search_radius(::urc_msgs::srv::GenerateSpiralSearch_Request & msg)
  : msg_(msg)
  {}
  Init_GenerateSpiralSearch_Request_track_spacing search_radius(::urc_msgs::srv::GenerateSpiralSearch_Request::_search_radius_type arg)
  {
    msg_.search_radius = std::move(arg);
    return Init_GenerateSpiralSearch_Request_track_spacing(msg_);
  }

private:
  ::urc_msgs::srv::GenerateSpiralSearch_Request msg_;
};

class Init_GenerateSpiralSearch_Request_center
{
public:
  Init_GenerateSpiralSearch_Request_center()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_GenerateSpiralSearch_Request_search_radius center(::urc_msgs::srv::GenerateSpiralSearch_Request::_center_type arg)
  {
    msg_.center = std::move(arg);
    return Init_GenerateSpiralSearch_Request_search_radius(msg_);
  }

private:
  ::urc_msgs::srv::GenerateSpiralSearch_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::urc_msgs::srv::GenerateSpiralSearch_Request>()
{
  return urc_msgs::srv::builder::Init_GenerateSpiralSearch_Request_center();
}

}  // namespace urc_msgs


namespace urc_msgs
{

namespace srv
{

namespace builder
{

class Init_GenerateSpiralSearch_Response_error_code
{
public:
  explicit Init_GenerateSpiralSearch_Response_error_code(::urc_msgs::srv::GenerateSpiralSearch_Response & msg)
  : msg_(msg)
  {}
  ::urc_msgs::srv::GenerateSpiralSearch_Response error_code(::urc_msgs::srv::GenerateSpiralSearch_Response::_error_code_type arg)
  {
    msg_.error_code = std::move(arg);
    return std::move(msg_);
  }

private:
  ::urc_msgs::srv::GenerateSpiralSearch_Response msg_;
};

class Init_GenerateSpiralSearch_Response_skipped_waypoints
{
public:
  explicit Init_GenerateSpiralSearch_Response_skipped_waypoints(::urc_msgs::srv::GenerateSpiralSearch_Response & msg)
  : msg_(msg)
  {}
  Init_GenerateSpiralSearch_Response_error_code skipped_waypoints(::urc_msgs::srv::GenerateSpiralSearch_Response::_skipped_waypoints_type arg)
  {
    msg_.skipped_waypoints = std::move(arg);
    return Init_GenerateSpiralSearch_Response_error_code(msg_);
  }

private:
  ::urc_msgs::srv::GenerateSpiralSearch_Response msg_;
};

class Init_GenerateSpiralSearch_Response_truncated
{
public:
  explicit Init_GenerateSpiralSearch_Response_truncated(::urc_msgs::srv::GenerateSpiralSearch_Response & msg)
  : msg_(msg)
  {}
  Init_GenerateSpiralSearch_Response_skipped_waypoints truncated(::urc_msgs::srv::GenerateSpiralSearch_Response::_truncated_type arg)
  {
    msg_.truncated = std::move(arg);
    return Init_GenerateSpiralSearch_Response_skipped_waypoints(msg_);
  }

private:
  ::urc_msgs::srv::GenerateSpiralSearch_Response msg_;
};

class Init_GenerateSpiralSearch_Response_traversability_checked
{
public:
  explicit Init_GenerateSpiralSearch_Response_traversability_checked(::urc_msgs::srv::GenerateSpiralSearch_Response & msg)
  : msg_(msg)
  {}
  Init_GenerateSpiralSearch_Response_truncated traversability_checked(::urc_msgs::srv::GenerateSpiralSearch_Response::_traversability_checked_type arg)
  {
    msg_.traversability_checked = std::move(arg);
    return Init_GenerateSpiralSearch_Response_truncated(msg_);
  }

private:
  ::urc_msgs::srv::GenerateSpiralSearch_Response msg_;
};

class Init_GenerateSpiralSearch_Response_path_length
{
public:
  explicit Init_GenerateSpiralSearch_Response_path_length(::urc_msgs::srv::GenerateSpiralSearch_Response & msg)
  : msg_(msg)
  {}
  Init_GenerateSpiralSearch_Response_traversability_checked path_length(::urc_msgs::srv::GenerateSpiralSearch_Response::_path_length_type arg)
  {
    msg_.path_length = std::move(arg);
    return Init_GenerateSpiralSearch_Response_traversability_checked(msg_);
  }

private:
  ::urc_msgs::srv::GenerateSpiralSearch_Response msg_;
};

class Init_GenerateSpiralSearch_Response_track_spacing
{
public:
  explicit Init_GenerateSpiralSearch_Response_track_spacing(::urc_msgs::srv::GenerateSpiralSearch_Response & msg)
  : msg_(msg)
  {}
  Init_GenerateSpiralSearch_Response_path_length track_spacing(::urc_msgs::srv::GenerateSpiralSearch_Response::_track_spacing_type arg)
  {
    msg_.track_spacing = std::move(arg);
    return Init_GenerateSpiralSearch_Response_path_length(msg_);
  }

private:
  ::urc_msgs::srv::GenerateSpiralSearch_Response msg_;
};

class Init_GenerateSpiralSearch_Response_path
{
public:
  Init_GenerateSpiralSearch_Response_path()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_GenerateSpiralSearch_Response_track_spacing path(::urc_msgs::srv::GenerateSpiralSearch_Response::_path_type arg)
  {
    msg_.path = std::move(arg);
    return Init_GenerateSpiralSearch_Response_track_spacing(msg_);
  }

private:
  ::urc_msgs::srv::GenerateSpiralSearch_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::urc_msgs::srv::GenerateSpiralSearch_Response>()
{
  return urc_msgs::srv::builder::Init_GenerateSpiralSearch_Response_path();
}

}  // namespace urc_msgs

#endif  // URC_MSGS__SRV__DETAIL__GENERATE_SPIRAL_SEARCH__BUILDER_HPP_
