// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from urc_msgs:msg/BatteryInfo.idl
// generated code does not contain a copyright notice

#ifndef URC_MSGS__MSG__DETAIL__BATTERY_INFO__BUILDER_HPP_
#define URC_MSGS__MSG__DETAIL__BATTERY_INFO__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "urc_msgs/msg/detail/battery_info__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace urc_msgs
{

namespace msg
{

namespace builder
{

class Init_BatteryInfo_cell_voltages
{
public:
  explicit Init_BatteryInfo_cell_voltages(::urc_msgs::msg::BatteryInfo & msg)
  : msg_(msg)
  {}
  ::urc_msgs::msg::BatteryInfo cell_voltages(::urc_msgs::msg::BatteryInfo::_cell_voltages_type arg)
  {
    msg_.cell_voltages = std::move(arg);
    return std::move(msg_);
  }

private:
  ::urc_msgs::msg::BatteryInfo msg_;
};

class Init_BatteryInfo_cell_temperature
{
public:
  explicit Init_BatteryInfo_cell_temperature(::urc_msgs::msg::BatteryInfo & msg)
  : msg_(msg)
  {}
  Init_BatteryInfo_cell_voltages cell_temperature(::urc_msgs::msg::BatteryInfo::_cell_temperature_type arg)
  {
    msg_.cell_temperature = std::move(arg);
    return Init_BatteryInfo_cell_voltages(msg_);
  }

private:
  ::urc_msgs::msg::BatteryInfo msg_;
};

class Init_BatteryInfo_cell_discharge_current
{
public:
  explicit Init_BatteryInfo_cell_discharge_current(::urc_msgs::msg::BatteryInfo & msg)
  : msg_(msg)
  {}
  Init_BatteryInfo_cell_temperature cell_discharge_current(::urc_msgs::msg::BatteryInfo::_cell_discharge_current_type arg)
  {
    msg_.cell_discharge_current = std::move(arg);
    return Init_BatteryInfo_cell_temperature(msg_);
  }

private:
  ::urc_msgs::msg::BatteryInfo msg_;
};

class Init_BatteryInfo_cell_charge_percentage
{
public:
  explicit Init_BatteryInfo_cell_charge_percentage(::urc_msgs::msg::BatteryInfo & msg)
  : msg_(msg)
  {}
  Init_BatteryInfo_cell_discharge_current cell_charge_percentage(::urc_msgs::msg::BatteryInfo::_cell_charge_percentage_type arg)
  {
    msg_.cell_charge_percentage = std::move(arg);
    return Init_BatteryInfo_cell_discharge_current(msg_);
  }

private:
  ::urc_msgs::msg::BatteryInfo msg_;
};

class Init_BatteryInfo_cell_voltage
{
public:
  Init_BatteryInfo_cell_voltage()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_BatteryInfo_cell_charge_percentage cell_voltage(::urc_msgs::msg::BatteryInfo::_cell_voltage_type arg)
  {
    msg_.cell_voltage = std::move(arg);
    return Init_BatteryInfo_cell_charge_percentage(msg_);
  }

private:
  ::urc_msgs::msg::BatteryInfo msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::urc_msgs::msg::BatteryInfo>()
{
  return urc_msgs::msg::builder::Init_BatteryInfo_cell_voltage();
}

}  // namespace urc_msgs

#endif  // URC_MSGS__MSG__DETAIL__BATTERY_INFO__BUILDER_HPP_
