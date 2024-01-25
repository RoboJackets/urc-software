#include "moveit_servo/servo_node.h"

int main(int argc, char* argv[])
{
  rclcpp::init(argc, argv);

  rclcpp::NodeOptions options;

  auto servo_node = std::make_shared<moveit_servo::ServoNode>(options);

  rclcpp::spin(servo_node->get_node_base_interface());

  rclcpp::shutdown();
}