// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from urc_msgs:msg/BatteryInfo.idl
// generated code does not contain a copyright notice

#ifndef URC_MSGS__MSG__DETAIL__BATTERY_INFO__STRUCT_HPP_
#define URC_MSGS__MSG__DETAIL__BATTERY_INFO__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__urc_msgs__msg__BatteryInfo __attribute__((deprecated))
#else
# define DEPRECATED__urc_msgs__msg__BatteryInfo __declspec(deprecated)
#endif

namespace urc_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct BatteryInfo_
{
  using Type = BatteryInfo_<ContainerAllocator>;

  explicit BatteryInfo_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->cell_voltage = 0.0f;
      this->cell_charge_percentage = 0.0f;
      this->cell_discharge_current = 0.0f;
      this->cell_temperature = 0.0f;
    }
  }

  explicit BatteryInfo_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->cell_voltage = 0.0f;
      this->cell_charge_percentage = 0.0f;
      this->cell_discharge_current = 0.0f;
      this->cell_temperature = 0.0f;
    }
  }

  // field types and members
  using _cell_voltage_type =
    float;
  _cell_voltage_type cell_voltage;
  using _cell_charge_percentage_type =
    float;
  _cell_charge_percentage_type cell_charge_percentage;
  using _cell_discharge_current_type =
    float;
  _cell_discharge_current_type cell_discharge_current;
  using _cell_temperature_type =
    float;
  _cell_temperature_type cell_temperature;
  using _cell_voltages_type =
    std::vector<float, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<float>>;
  _cell_voltages_type cell_voltages;

  // setters for named parameter idiom
  Type & set__cell_voltage(
    const float & _arg)
  {
    this->cell_voltage = _arg;
    return *this;
  }
  Type & set__cell_charge_percentage(
    const float & _arg)
  {
    this->cell_charge_percentage = _arg;
    return *this;
  }
  Type & set__cell_discharge_current(
    const float & _arg)
  {
    this->cell_discharge_current = _arg;
    return *this;
  }
  Type & set__cell_temperature(
    const float & _arg)
  {
    this->cell_temperature = _arg;
    return *this;
  }
  Type & set__cell_voltages(
    const std::vector<float, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<float>> & _arg)
  {
    this->cell_voltages = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    urc_msgs::msg::BatteryInfo_<ContainerAllocator> *;
  using ConstRawPtr =
    const urc_msgs::msg::BatteryInfo_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<urc_msgs::msg::BatteryInfo_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<urc_msgs::msg::BatteryInfo_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      urc_msgs::msg::BatteryInfo_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<urc_msgs::msg::BatteryInfo_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      urc_msgs::msg::BatteryInfo_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<urc_msgs::msg::BatteryInfo_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<urc_msgs::msg::BatteryInfo_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<urc_msgs::msg::BatteryInfo_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__urc_msgs__msg__BatteryInfo
    std::shared_ptr<urc_msgs::msg::BatteryInfo_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__urc_msgs__msg__BatteryInfo
    std::shared_ptr<urc_msgs::msg::BatteryInfo_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const BatteryInfo_ & other) const
  {
    if (this->cell_voltage != other.cell_voltage) {
      return false;
    }
    if (this->cell_charge_percentage != other.cell_charge_percentage) {
      return false;
    }
    if (this->cell_discharge_current != other.cell_discharge_current) {
      return false;
    }
    if (this->cell_temperature != other.cell_temperature) {
      return false;
    }
    if (this->cell_voltages != other.cell_voltages) {
      return false;
    }
    return true;
  }
  bool operator!=(const BatteryInfo_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct BatteryInfo_

// alias to use template instance with default allocator
using BatteryInfo =
  urc_msgs::msg::BatteryInfo_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace urc_msgs

#endif  // URC_MSGS__MSG__DETAIL__BATTERY_INFO__STRUCT_HPP_
