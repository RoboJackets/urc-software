// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from urc_msgs:srv/UpdateBehaviorTree.idl
// generated code does not contain a copyright notice

#ifndef URC_MSGS__SRV__DETAIL__UPDATE_BEHAVIOR_TREE__BUILDER_HPP_
#define URC_MSGS__SRV__DETAIL__UPDATE_BEHAVIOR_TREE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "urc_msgs/srv/detail/update_behavior_tree__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace urc_msgs
{

namespace srv
{

namespace builder
{

class Init_UpdateBehaviorTree_Request_use_dir
{
public:
  explicit Init_UpdateBehaviorTree_Request_use_dir(::urc_msgs::srv::UpdateBehaviorTree_Request & msg)
  : msg_(msg)
  {}
  ::urc_msgs::srv::UpdateBehaviorTree_Request use_dir(::urc_msgs::srv::UpdateBehaviorTree_Request::_use_dir_type arg)
  {
    msg_.use_dir = std::move(arg);
    return std::move(msg_);
  }

private:
  ::urc_msgs::srv::UpdateBehaviorTree_Request msg_;
};

class Init_UpdateBehaviorTree_Request_tree_dir
{
public:
  explicit Init_UpdateBehaviorTree_Request_tree_dir(::urc_msgs::srv::UpdateBehaviorTree_Request & msg)
  : msg_(msg)
  {}
  Init_UpdateBehaviorTree_Request_use_dir tree_dir(::urc_msgs::srv::UpdateBehaviorTree_Request::_tree_dir_type arg)
  {
    msg_.tree_dir = std::move(arg);
    return Init_UpdateBehaviorTree_Request_use_dir(msg_);
  }

private:
  ::urc_msgs::srv::UpdateBehaviorTree_Request msg_;
};

class Init_UpdateBehaviorTree_Request_tree_content
{
public:
  Init_UpdateBehaviorTree_Request_tree_content()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_UpdateBehaviorTree_Request_tree_dir tree_content(::urc_msgs::srv::UpdateBehaviorTree_Request::_tree_content_type arg)
  {
    msg_.tree_content = std::move(arg);
    return Init_UpdateBehaviorTree_Request_tree_dir(msg_);
  }

private:
  ::urc_msgs::srv::UpdateBehaviorTree_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::urc_msgs::srv::UpdateBehaviorTree_Request>()
{
  return urc_msgs::srv::builder::Init_UpdateBehaviorTree_Request_tree_content();
}

}  // namespace urc_msgs


namespace urc_msgs
{

namespace srv
{

namespace builder
{

class Init_UpdateBehaviorTree_Response_success
{
public:
  Init_UpdateBehaviorTree_Response_success()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::urc_msgs::srv::UpdateBehaviorTree_Response success(::urc_msgs::srv::UpdateBehaviorTree_Response::_success_type arg)
  {
    msg_.success = std::move(arg);
    return std::move(msg_);
  }

private:
  ::urc_msgs::srv::UpdateBehaviorTree_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::urc_msgs::srv::UpdateBehaviorTree_Response>()
{
  return urc_msgs::srv::builder::Init_UpdateBehaviorTree_Response_success();
}

}  // namespace urc_msgs

#endif  // URC_MSGS__SRV__DETAIL__UPDATE_BEHAVIOR_TREE__BUILDER_HPP_
