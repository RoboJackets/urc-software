#include "urc_hw/rover_interface.hpp"

namespace rover_interface
{

namespace ip = boost::asio::ip;

hardware_interface::CallbackReturn rover_interface::RoverInterface::on_init(
    const hardware_interface::HardwareInfo &info)
{
    std::string ip_addr_server = info_.hardware_parameters["id_addr_server"];
    int port = std::stoi(info_.hardware_parameters["port"]);
    this->ip_addr_server_ = ip_addr_server;
    this->port_ = port;
    this->client_endpoint_.address(ip::address_v4::from_string(ip_addr_server));
    this->client_endpoint_.port(port);
    this->server_endpoint_.address(ip::address_v4::from_string("192.168.8.167"));
    this->server_endpoint_.port(port);
    this->sock_ = std::make_unique<ip::udp::socket>(io_service_, client_endpoint_);

    return hardware_interface::CallbackReturn();
}

std::vector<hardware_interface::StateInterface> rover_interface::RoverInterface::export_state_interfaces()
{
    return std::vector<hardware_interface::StateInterface>();
}

hardware_interface::CallbackReturn RoverInterface::on_activate(const rclcpp_lifecycle::State &previous_state)
{
    return hardware_interface::CallbackReturn();
}

hardware_interface::CallbackReturn RoverInterface::on_deactivate(const rclcpp_lifecycle::State &previous_state)
{
    return hardware_interface::CallbackReturn();
}

hardware_interface::return_type RoverInterface::read(const rclcpp::Time &time, const rclcpp::Duration &period)
{
    return hardware_interface::return_type();
}

hardware_interface::return_type RoverInterface::write(const rclcpp::Time &time, const rclcpp::Duration &period)
{
    return hardware_interface::return_type();
}

} // namespace rover_interface