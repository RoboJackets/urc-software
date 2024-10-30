// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from urc_msgs:msg/LandingLocations.idl
// generated code does not contain a copyright notice

#ifndef URC_MSGS__MSG__DETAIL__LANDING_LOCATIONS__BUILDER_HPP_
#define URC_MSGS__MSG__DETAIL__LANDING_LOCATIONS__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "urc_msgs/msg/detail/landing_locations__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace urc_msgs
{

namespace msg
{

namespace builder
{

class Init_LandingLocations_longitudes
{
public:
  explicit Init_LandingLocations_longitudes(::urc_msgs::msg::LandingLocations & msg)
  : msg_(msg)
  {}
  ::urc_msgs::msg::LandingLocations longitudes(::urc_msgs::msg::LandingLocations::_longitudes_type arg)
  {
    msg_.longitudes = std::move(arg);
    return std::move(msg_);
  }

private:
  ::urc_msgs::msg::LandingLocations msg_;
};

class Init_LandingLocations_latitudes
{
public:
  explicit Init_LandingLocations_latitudes(::urc_msgs::msg::LandingLocations & msg)
  : msg_(msg)
  {}
  Init_LandingLocations_longitudes latitudes(::urc_msgs::msg::LandingLocations::_latitudes_type arg)
  {
    msg_.latitudes = std::move(arg);
    return Init_LandingLocations_longitudes(msg_);
  }

private:
  ::urc_msgs::msg::LandingLocations msg_;
};

class Init_LandingLocations_num_locations
{
public:
  explicit Init_LandingLocations_num_locations(::urc_msgs::msg::LandingLocations & msg)
  : msg_(msg)
  {}
  Init_LandingLocations_latitudes num_locations(::urc_msgs::msg::LandingLocations::_num_locations_type arg)
  {
    msg_.num_locations = std::move(arg);
    return Init_LandingLocations_latitudes(msg_);
  }

private:
  ::urc_msgs::msg::LandingLocations msg_;
};

class Init_LandingLocations_header
{
public:
  Init_LandingLocations_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_LandingLocations_num_locations header(::urc_msgs::msg::LandingLocations::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_LandingLocations_num_locations(msg_);
  }

private:
  ::urc_msgs::msg::LandingLocations msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::urc_msgs::msg::LandingLocations>()
{
  return urc_msgs::msg::builder::Init_LandingLocations_header();
}

}  // namespace urc_msgs

#endif  // URC_MSGS__MSG__DETAIL__LANDING_LOCATIONS__BUILDER_HPP_
