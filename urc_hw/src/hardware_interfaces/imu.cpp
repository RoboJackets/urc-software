#include "urc_hw/hardware_interfaces/imu.hpp"
#include "hardware_interface/hardware_info.hpp"
#include "hardware_interface/sensor_interface.hpp"
#include "pluginlib/class_list_macros.hpp"
#include <rclcpp/logger.hpp>
#include <rclcpp/logging.hpp>

PLUGINLIB_EXPORT_CLASS(urc_hardware::hardware_interfaces::IMU, hardware_interface::SensorInterface);

namespace urc_hardware::hardware_interfaces
{

IMU::IMU() : hardware_interface_name("IMU"){};
IMU::~IMU() = default;

hardware_interface::CallbackReturn IMU::on_init(const hardware_interface::HardwareInfo& info)
{
  RCLCPP_INFO(rclcpp::get_logger(hardware_interface_name), "Initializing IMU for robot %s..", info_.name.c_str());

  if (hardware_interface::SensorInterface::on_init(info) != hardware_interface::CallbackReturn::SUCCESS)
  {
    return hardware_interface::CallbackReturn::ERROR;
  }

  if (info_.hardware_parameters.find("udp_address") == info_.hardware_parameters.end())
  {
    RCLCPP_ERROR(rclcpp::get_logger(hardware_interface_name),
                 "Error during initialization: 'udp_address' configuration not "
                 "found. Expect to enter the udp server address.");
    return hardware_interface::CallbackReturn::ERROR;
  }
  if (info_.hardware_parameters.find("udp_port") == info_.hardware_parameters.end())
  {
    RCLCPP_ERROR(rclcpp::get_logger(hardware_interface_name),
                 "Error during initialization: 'udp_port' configuration not "
                 "found. Expect to enter the port number.");
    return hardware_interface::CallbackReturn::ERROR;
  }

  udp_address = info_.hardware_parameters["udp_address"];
  udp_port = info_.hardware_parameters["udp_port"];

  if (info.sensors.size() == 0)
  {
    RCLCPP_ERROR(rclcpp::get_logger(hardware_interface_name), "Should have at least one sensor to be the imu.");
    return CallbackReturn::ERROR;
  }

  bool find_imu = false;
  for (hardware_interface::ComponentInfo component : info_.sensors)
  {
    if (component.name == "imu_sensor")
    {
      find_imu = true;
      break;
    }
  }

  if (!find_imu)
  {
    RCLCPP_ERROR(rclcpp::get_logger(hardware_interface_name), "Not able to find sensor named 'imu_sensor'.");
    return CallbackReturn::ERROR;
  }

  quaternions.resize(4);
  linear_accelerations.resize(3);
  angular_accelerations.resize(3);
  RCLCPP_INFO(rclcpp::get_logger(hardware_interface_name), "IMU initialization success.");
  return hardware_interface::CallbackReturn::SUCCESS;
}

hardware_interface::CallbackReturn IMU::on_configure(const rclcpp_lifecycle::State&)
{
  std::fill(quaternions.begin(), quaternions.end(), 0.0);
  std::fill(linear_accelerations.begin(), linear_accelerations.end(), 0.0);
  std::fill(angular_accelerations.begin(), angular_accelerations.end(), 0.0);

  RCLCPP_INFO_ONCE(rclcpp::get_logger(hardware_interface_name), "Succesfully zeroed all states on configure.");
  return hardware_interface::CallbackReturn::SUCCESS;
}

std::vector<hardware_interface::StateInterface> IMU::export_state_interfaces()
{
  RCLCPP_INFO(rclcpp::get_logger(hardware_interface_name), "Exporting state interfaces...");

  std::vector<hardware_interface::StateInterface> state_interfaces;

  state_interfaces.emplace_back("imu_sensor", "orientation.x", &this->quaternions[0]);
  state_interfaces.emplace_back("imu_sensor", "orientation.y", &this->quaternions[1]);
  state_interfaces.emplace_back("imu_sensor", "orientation.z", &this->quaternions[2]);
  state_interfaces.emplace_back("imu_sensor", "orientation.w", &this->quaternions[3]);
  state_interfaces.emplace_back("imu_sensor", "linear_acceleration.x", &this->linear_accelerations[0]);
  state_interfaces.emplace_back("imu_sensor", "linear_acceleration.y", &this->linear_accelerations[1]);
  state_interfaces.emplace_back("imu_sensor", "linear_acceleration.z", &this->linear_accelerations[2]);
  state_interfaces.emplace_back("imu_sensor", "angular_velocity.x", &this->angular_accelerations[0]);
  state_interfaces.emplace_back("imu_sensor", "angular_velocity.y", &this->angular_accelerations[1]);
  state_interfaces.emplace_back("imu_sensor", "angular_velocity.z", &this->angular_accelerations[2]);

  return state_interfaces;
}

hardware_interface::CallbackReturn IMU::on_activate(const rclcpp_lifecycle::State&)
{
  udp_ = std::make_shared<UDPSocket<1024>>(true);
  udp_->Connect(udp_address, std::stoi(udp_port));
  RCLCPP_INFO(rclcpp::get_logger(hardware_interface_name), "IMU started!");
  return hardware_interface::CallbackReturn::SUCCESS;
}

hardware_interface::CallbackReturn IMU::on_deactivate(const rclcpp_lifecycle::State&)
{
  RCLCPP_INFO(rclcpp::get_logger(hardware_interface_name), "IMU stopping...");
  udp_->Close();
  RCLCPP_INFO(rclcpp::get_logger(hardware_interface_name), "IMU stopped.");
  return hardware_interface::CallbackReturn::SUCCESS;
}

hardware_interface::return_type IMU::read(const rclcpp::Time&, const rclcpp::Duration&)
{
  return hardware_interface::return_type::OK;
}

}  // namespace urc_hardware::hardware_interfaces
