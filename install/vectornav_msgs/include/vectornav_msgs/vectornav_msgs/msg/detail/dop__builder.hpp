// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from vectornav_msgs:msg/DOP.idl
// generated code does not contain a copyright notice

#ifndef VECTORNAV_MSGS__MSG__DETAIL__DOP__BUILDER_HPP_
#define VECTORNAV_MSGS__MSG__DETAIL__DOP__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "vectornav_msgs/msg/detail/dop__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace vectornav_msgs
{

namespace msg
{

namespace builder
{

class Init_DOP_e
{
public:
  explicit Init_DOP_e(::vectornav_msgs::msg::DOP & msg)
  : msg_(msg)
  {}
  ::vectornav_msgs::msg::DOP e(::vectornav_msgs::msg::DOP::_e_type arg)
  {
    msg_.e = std::move(arg);
    return std::move(msg_);
  }

private:
  ::vectornav_msgs::msg::DOP msg_;
};

class Init_DOP_n
{
public:
  explicit Init_DOP_n(::vectornav_msgs::msg::DOP & msg)
  : msg_(msg)
  {}
  Init_DOP_e n(::vectornav_msgs::msg::DOP::_n_type arg)
  {
    msg_.n = std::move(arg);
    return Init_DOP_e(msg_);
  }

private:
  ::vectornav_msgs::msg::DOP msg_;
};

class Init_DOP_h
{
public:
  explicit Init_DOP_h(::vectornav_msgs::msg::DOP & msg)
  : msg_(msg)
  {}
  Init_DOP_n h(::vectornav_msgs::msg::DOP::_h_type arg)
  {
    msg_.h = std::move(arg);
    return Init_DOP_n(msg_);
  }

private:
  ::vectornav_msgs::msg::DOP msg_;
};

class Init_DOP_v
{
public:
  explicit Init_DOP_v(::vectornav_msgs::msg::DOP & msg)
  : msg_(msg)
  {}
  Init_DOP_h v(::vectornav_msgs::msg::DOP::_v_type arg)
  {
    msg_.v = std::move(arg);
    return Init_DOP_h(msg_);
  }

private:
  ::vectornav_msgs::msg::DOP msg_;
};

class Init_DOP_t
{
public:
  explicit Init_DOP_t(::vectornav_msgs::msg::DOP & msg)
  : msg_(msg)
  {}
  Init_DOP_v t(::vectornav_msgs::msg::DOP::_t_type arg)
  {
    msg_.t = std::move(arg);
    return Init_DOP_v(msg_);
  }

private:
  ::vectornav_msgs::msg::DOP msg_;
};

class Init_DOP_p
{
public:
  explicit Init_DOP_p(::vectornav_msgs::msg::DOP & msg)
  : msg_(msg)
  {}
  Init_DOP_t p(::vectornav_msgs::msg::DOP::_p_type arg)
  {
    msg_.p = std::move(arg);
    return Init_DOP_t(msg_);
  }

private:
  ::vectornav_msgs::msg::DOP msg_;
};

class Init_DOP_g
{
public:
  Init_DOP_g()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_DOP_p g(::vectornav_msgs::msg::DOP::_g_type arg)
  {
    msg_.g = std::move(arg);
    return Init_DOP_p(msg_);
  }

private:
  ::vectornav_msgs::msg::DOP msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::vectornav_msgs::msg::DOP>()
{
  return vectornav_msgs::msg::builder::Init_DOP_g();
}

}  // namespace vectornav_msgs

#endif  // VECTORNAV_MSGS__MSG__DETAIL__DOP__BUILDER_HPP_
