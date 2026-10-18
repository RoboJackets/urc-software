// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from urc_msgs:srv/GeneratePlan.idl
// generated code does not contain a copyright notice

#ifndef URC_MSGS__SRV__DETAIL__GENERATE_PLAN__BUILDER_HPP_
#define URC_MSGS__SRV__DETAIL__GENERATE_PLAN__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "urc_msgs/srv/detail/generate_plan__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace urc_msgs
{

namespace srv
{

namespace builder
{

class Init_GeneratePlan_Request_start
{
public:
  explicit Init_GeneratePlan_Request_start(::urc_msgs::srv::GeneratePlan_Request & msg)
  : msg_(msg)
  {}
  ::urc_msgs::srv::GeneratePlan_Request start(::urc_msgs::srv::GeneratePlan_Request::_start_type arg)
  {
    msg_.start = std::move(arg);
    return std::move(msg_);
  }

private:
  ::urc_msgs::srv::GeneratePlan_Request msg_;
};

class Init_GeneratePlan_Request_goal
{
public:
  Init_GeneratePlan_Request_goal()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_GeneratePlan_Request_start goal(::urc_msgs::srv::GeneratePlan_Request::_goal_type arg)
  {
    msg_.goal = std::move(arg);
    return Init_GeneratePlan_Request_start(msg_);
  }

private:
  ::urc_msgs::srv::GeneratePlan_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::urc_msgs::srv::GeneratePlan_Request>()
{
  return urc_msgs::srv::builder::Init_GeneratePlan_Request_goal();
}

}  // namespace urc_msgs


namespace urc_msgs
{

namespace srv
{

namespace builder
{

class Init_GeneratePlan_Response_error_code
{
public:
  explicit Init_GeneratePlan_Response_error_code(::urc_msgs::srv::GeneratePlan_Response & msg)
  : msg_(msg)
  {}
  ::urc_msgs::srv::GeneratePlan_Response error_code(::urc_msgs::srv::GeneratePlan_Response::_error_code_type arg)
  {
    msg_.error_code = std::move(arg);
    return std::move(msg_);
  }

private:
  ::urc_msgs::srv::GeneratePlan_Response msg_;
};

class Init_GeneratePlan_Response_path
{
public:
  Init_GeneratePlan_Response_path()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_GeneratePlan_Response_error_code path(::urc_msgs::srv::GeneratePlan_Response::_path_type arg)
  {
    msg_.path = std::move(arg);
    return Init_GeneratePlan_Response_error_code(msg_);
  }

private:
  ::urc_msgs::srv::GeneratePlan_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::urc_msgs::srv::GeneratePlan_Response>()
{
  return urc_msgs::srv::builder::Init_GeneratePlan_Response_path();
}

}  // namespace urc_msgs

#endif  // URC_MSGS__SRV__DETAIL__GENERATE_PLAN__BUILDER_HPP_
