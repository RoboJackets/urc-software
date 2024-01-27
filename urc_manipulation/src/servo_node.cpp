#include "moveit_servo/servo_node.h"
#include <memory>
#include <rclcpp/logger.hpp>

int main(int argc, char* argv[])
{
  rclcpp::init(argc, argv);

  rclcpp::NodeOptions options;

  auto servo_node = std::make_shared<moveit_servo::ServoNode>(options);
  auto logger = std::make_unique<rclcpp::Logger>(rclcpp::get_logger("Servo"));
  RCLCPP_INFO(*logger, "Starting Servo Node!");

  rclcpp::spin(servo_node->get_node_base_interface());

  rclcpp::shutdown();
}