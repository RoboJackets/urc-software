// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from vectornav_msgs:msg/InsGroup.idl
// generated code does not contain a copyright notice

#ifndef VECTORNAV_MSGS__MSG__DETAIL__INS_GROUP__BUILDER_HPP_
#define VECTORNAV_MSGS__MSG__DETAIL__INS_GROUP__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "vectornav_msgs/msg/detail/ins_group__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace vectornav_msgs
{

namespace msg
{

namespace builder
{

class Init_InsGroup_velu
{
public:
  explicit Init_InsGroup_velu(::vectornav_msgs::msg::InsGroup & msg)
  : msg_(msg)
  {}
  ::vectornav_msgs::msg::InsGroup velu(::vectornav_msgs::msg::InsGroup::_velu_type arg)
  {
    msg_.velu = std::move(arg);
    return std::move(msg_);
  }

private:
  ::vectornav_msgs::msg::InsGroup msg_;
};

class Init_InsGroup_posu
{
public:
  explicit Init_InsGroup_posu(::vectornav_msgs::msg::InsGroup & msg)
  : msg_(msg)
  {}
  Init_InsGroup_velu posu(::vectornav_msgs::msg::InsGroup::_posu_type arg)
  {
    msg_.posu = std::move(arg);
    return Init_InsGroup_velu(msg_);
  }

private:
  ::vectornav_msgs::msg::InsGroup msg_;
};

class Init_InsGroup_linearaccelecef
{
public:
  explicit Init_InsGroup_linearaccelecef(::vectornav_msgs::msg::InsGroup & msg)
  : msg_(msg)
  {}
  Init_InsGroup_posu linearaccelecef(::vectornav_msgs::msg::InsGroup::_linearaccelecef_type arg)
  {
    msg_.linearaccelecef = std::move(arg);
    return Init_InsGroup_posu(msg_);
  }

private:
  ::vectornav_msgs::msg::InsGroup msg_;
};

class Init_InsGroup_accelecef
{
public:
  explicit Init_InsGroup_accelecef(::vectornav_msgs::msg::InsGroup & msg)
  : msg_(msg)
  {}
  Init_InsGroup_linearaccelecef accelecef(::vectornav_msgs::msg::InsGroup::_accelecef_type arg)
  {
    msg_.accelecef = std::move(arg);
    return Init_InsGroup_linearaccelecef(msg_);
  }

private:
  ::vectornav_msgs::msg::InsGroup msg_;
};

class Init_InsGroup_magecef
{
public:
  explicit Init_InsGroup_magecef(::vectornav_msgs::msg::InsGroup & msg)
  : msg_(msg)
  {}
  Init_InsGroup_accelecef magecef(::vectornav_msgs::msg::InsGroup::_magecef_type arg)
  {
    msg_.magecef = std::move(arg);
    return Init_InsGroup_accelecef(msg_);
  }

private:
  ::vectornav_msgs::msg::InsGroup msg_;
};

class Init_InsGroup_velecef
{
public:
  explicit Init_InsGroup_velecef(::vectornav_msgs::msg::InsGroup & msg)
  : msg_(msg)
  {}
  Init_InsGroup_magecef velecef(::vectornav_msgs::msg::InsGroup::_velecef_type arg)
  {
    msg_.velecef = std::move(arg);
    return Init_InsGroup_magecef(msg_);
  }

private:
  ::vectornav_msgs::msg::InsGroup msg_;
};

class Init_InsGroup_velned
{
public:
  explicit Init_InsGroup_velned(::vectornav_msgs::msg::InsGroup & msg)
  : msg_(msg)
  {}
  Init_InsGroup_velecef velned(::vectornav_msgs::msg::InsGroup::_velned_type arg)
  {
    msg_.velned = std::move(arg);
    return Init_InsGroup_velecef(msg_);
  }

private:
  ::vectornav_msgs::msg::InsGroup msg_;
};

class Init_InsGroup_velbody
{
public:
  explicit Init_InsGroup_velbody(::vectornav_msgs::msg::InsGroup & msg)
  : msg_(msg)
  {}
  Init_InsGroup_velned velbody(::vectornav_msgs::msg::InsGroup::_velbody_type arg)
  {
    msg_.velbody = std::move(arg);
    return Init_InsGroup_velned(msg_);
  }

private:
  ::vectornav_msgs::msg::InsGroup msg_;
};

class Init_InsGroup_posecef
{
public:
  explicit Init_InsGroup_posecef(::vectornav_msgs::msg::InsGroup & msg)
  : msg_(msg)
  {}
  Init_InsGroup_velbody posecef(::vectornav_msgs::msg::InsGroup::_posecef_type arg)
  {
    msg_.posecef = std::move(arg);
    return Init_InsGroup_velbody(msg_);
  }

private:
  ::vectornav_msgs::msg::InsGroup msg_;
};

class Init_InsGroup_poslla
{
public:
  explicit Init_InsGroup_poslla(::vectornav_msgs::msg::InsGroup & msg)
  : msg_(msg)
  {}
  Init_InsGroup_posecef poslla(::vectornav_msgs::msg::InsGroup::_poslla_type arg)
  {
    msg_.poslla = std::move(arg);
    return Init_InsGroup_posecef(msg_);
  }

private:
  ::vectornav_msgs::msg::InsGroup msg_;
};

class Init_InsGroup_insstatus
{
public:
  explicit Init_InsGroup_insstatus(::vectornav_msgs::msg::InsGroup & msg)
  : msg_(msg)
  {}
  Init_InsGroup_poslla insstatus(::vectornav_msgs::msg::InsGroup::_insstatus_type arg)
  {
    msg_.insstatus = std::move(arg);
    return Init_InsGroup_poslla(msg_);
  }

private:
  ::vectornav_msgs::msg::InsGroup msg_;
};

class Init_InsGroup_group_fields
{
public:
  explicit Init_InsGroup_group_fields(::vectornav_msgs::msg::InsGroup & msg)
  : msg_(msg)
  {}
  Init_InsGroup_insstatus group_fields(::vectornav_msgs::msg::InsGroup::_group_fields_type arg)
  {
    msg_.group_fields = std::move(arg);
    return Init_InsGroup_insstatus(msg_);
  }

private:
  ::vectornav_msgs::msg::InsGroup msg_;
};

class Init_InsGroup_header
{
public:
  Init_InsGroup_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_InsGroup_group_fields header(::vectornav_msgs::msg::InsGroup::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_InsGroup_group_fields(msg_);
  }

private:
  ::vectornav_msgs::msg::InsGroup msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::vectornav_msgs::msg::InsGroup>()
{
  return vectornav_msgs::msg::builder::Init_InsGroup_header();
}

}  // namespace vectornav_msgs

#endif  // VECTORNAV_MSGS__MSG__DETAIL__INS_GROUP__BUILDER_HPP_
