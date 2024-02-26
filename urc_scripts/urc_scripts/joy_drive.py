import rclpy
from rclpy.publisher import Publisher
from rclpy.subscription import Subscription
from rclpy.node import Node
from rclpy.parameter import Parameter
from rcl_interfaces.msg import SetParametersResult
from geometry_msgs.msg import TwistStamped
from sensor_msgs.msg import Joy


class JoyDrive(Node):
    """
    Use joystick to command the drivetrain.

    Args:
        Node (_type_): node from ros2.
    """

    def __init__(self):
        super().__init__("joy_drive")

        # declare parameters
        self.declare_parameter("max_linear_velocity_ms", 0.0)
        self.declare_parameter("max_angular_velocity_radians", 0.0)
        self.declare_parameter("joy_command_topic", "/joy")
        self.declare_parameter("cmd_vel_topic", "/cmd_vel")
        self.declare_parameter("target_axes", [1, 3])
        self.declare_parameter("invert_linear_velocity", False)
        self.declare_parameter("invert_angular_velocity", False)

        # get parameters
        self.max_linear = self.get_parameter(
            "max_linear_velocity_ms").get_parameter_value().double_value
        self.max_angular = self.get_parameter(
            "max_angular_velocity_radians").get_parameter_value().double_value
        self.joy_command_topic = self.get_parameter(
            "joy_command_topic").get_parameter_value().string_value
        self.cmd_vel_topic = self.get_parameter(
            "cmd_vel_topic").get_parameter_value().string_value
        self.op_axes = self.get_parameter(
            "target_axes").get_parameter_value().integer_array_value
        self.inv_linvel = self.get_parameter(
            "invert_linear_velocity").get_parameter_value().double_value
        self.inv_angvel = self.get_parameter(
            "invert_angular_velocity").get_parameter_value().double_value

        # register dynamic parameter callbacks
        self.add_on_set_parameters_callback(self.on_param_update)

        self.curr_twist = TwistStamped()
        self.joy_msg_subscriber: Subscription = self.create_subscription(
            Joy, self.joy_command_topic, self.update_vel_target, 10
        )
        self.cmd_vel_publisher: Publisher = self.create_publisher(
            TwistStamped, self.cmd_vel_topic, 10
        )

        self.get_logger().info("Joy Drive Started.")
        self.get_logger().info(
            f"Default Settings: [linear velocity {self.max_linear} m/s],"
            + f"[angular velocity {self.max_angular} rad/s]"
        )

    def update_vel_target(self, msg: Joy):
        """Update velocity target for the drivetrain.

        Args:
            msg (Joy): joy message from the controller.
        """
        self.curr_twist.twist.linear.x = msg.axes[
            self.op_axes[0]
        ] * self.max_linear * (-1 if self.inv_linvel else 1)
        self.curr_twist.twist.angular.z = msg.axes[
            self.op_axes[1]
        ] * self.max_angular * (-1 if self.inv_angvel else 1)
        self.curr_twist.header.stamp = self.get_clock().now().to_msg()

        self.cmd_vel_publisher.publish(self.curr_twist)

    def on_param_update(self, params: list[Parameter]) -> SetParametersResult:
        """When parameter is updated.

        Args:
            params (list[Parameter]): list of updated parameters

        Returns:
            SetParametersResult: result for setting the parameters.
        """
        result = SetParametersResult()

        for param in params:
            if param.name == "max_linear_velocity_ms":
                self.max_linear = param.get_parameter_value().double_value
                self.get_logger().info(
                    f"Max linvel updated to {self.max_linear} m/s."
                )
            if param.name == "max_angular_velocity_radians":
                self.max_angular = param.get_parameter_value().double_value
                self.get_logger().info(
                    f"Max angvel updated to {self.max_angular} rad/s."
                )
            if param.name == "target_axes":
                self.op_axes = param.get_parameter_value().integer_array_value
                self.get_logger().info(
                    f"Axies has be configured to {self.op_axes}."
                )
            if param.name == "invert_linear_vel":
                self.inv_linvel = param.get_parameter_value().bool_value
                self.get_logger().info(
                    f"Linear velocity inversion: {self.inv_linvel}"
                )
            if param.name == "invert_angular_vel":
                self.inv_angvel = param.get_parameter_value().bool_value
                self.get_logger().info(
                    f"Angular velocity inversion: {self.inv_angvel}"
                )
        result.successful = True
        return result


def main(args=None):
    """Entry function

    Args:
        args (_type_, optional): Arguments. Defaults to None.
    """
    rclpy.init(args=args)
    node = JoyDrive()
    while rclpy.ok():
        rclpy.spin_once(node)
    node.destroy_node()
    rclpy.shutdown()


if __name__ == "__main__":
    main()
