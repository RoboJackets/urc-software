import rclpy
from rclpy.publisher import Publisher
from rclpy.subscription import Subscription
from rclpy.node import Node
from rclpy.parameter import Parameter
from rcl_interfaces.msg import SetParametersResult
from geometry_msgs.msg import TwistStamped
from sensor_msgs.msg import Joy


class JoyDrive(Node):
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
        self.max_linear_vel_ms = self.get_parameter(
            "max_linear_velocity_ms").get_parameter_value().double_value
        self.max_angular_vel_rads = self.get_parameter(
            "max_angular_velocity_radians").get_parameter_value().double_value
        self.joy_command_topic = self.get_parameter(
            "joy_command_topic").get_parameter_value().string_value
        self.cmd_vel_topic = self.get_parameter(
            "cmd_vel_topic").get_parameter_value().string_value
        self.target_axis = self.get_parameter(
            "target_axes").get_parameter_value().integer_array_value
        self.invert_linear_vel = self.get_parameter(
            "invert_linear_velocity").get_parameter_value().double_value
        self.invert_angular_vel = self.get_parameter(
            "invert_angular_velocity").get_parameter_value().double_value

        # register dynamic parameter callbacks
        self.callback_handle = self.add_on_set_parameters_callback(
            self.on_param_update)

        self.current_drive_velocity_target = TwistStamped()
        self.joy_msg_subscriber: Subscription = self.create_subscription(
            Joy, self.joy_command_topic, self.update_vel_target, 10
        )
        self.cmd_vel_publisher: Publisher = self.create_publisher(
            TwistStamped, self.cmd_vel_topic, 10
        )

        self.get_logger().info("Joy Drive Started.")
        self.get_logger().info(
            f"Default Settings: [linear velocity {self.max_linear_vel_ms} m/s], [angular velocity {self.max_angular_vel_rads} rad/s]"
        )

    def update_vel_target(self, msg: Joy):
        self.current_drive_velocity_target.twist.linear.x = msg.axes[
            self.target_axis[0]] * self.max_linear_vel_ms
        self.current_drive_velocity_target.twist.angular.z = msg.axes[
            self.target_axis[1]] * self.max_angular_vel_rads
        self.current_drive_velocity_target.header.stamp = self.get_clock().now().to_msg()

        self.cmd_vel_publisher.publish(self.current_drive_velocity_target)

    def on_param_update(self, params: list[Parameter]) -> SetParametersResult:
        result = SetParametersResult()

        for param in params:
            if param.name == "max_linear_velocity_ms":
                self.max_linear_vel_ms = param.get_parameter_value().double_value
                self.get_logger().info(
                    f"Max linear velocity has been updated to {self.max_linear_vel_ms} m/s."
                )
            if param.name == "max_angular_velocity_radians":
                self.max_angular_vel_rads = param.get_parameter_value().double_value
                self.get_logger().info(
                    f"Max angular velocity has been updated to {self.max_angular_vel_rads} rad/s."
                )
            if param.name == "target_axes":
                self.target_axis = param.get_parameter_value().integer_array_value
                self.get_logger().info(
                    f"Axies has be configured to {self.target_axis}."
                )
            if param.name == "invert_linear_vel":
                self.invert_linear_vel = param.get_parameter_value().bool_value
                self.get_logger().info(
                    f"Linear velocity inversion: {self.invert_linear_vel}"
                )
            if param.name == "invert_angular_vel":
                self.invert_angular_vel = param.get_parameter_value().bool_value
                self.get_logger().info(
                    f"Angular velocity inversion: {self.invert_angular_vel}"
                )
        result.successful = True
        return result


def main(args=None):
    rclpy.init(args=args)
    node = JoyDrive()
    while rclpy.ok():
        rclpy.spin_once(node)
    node.destroy_node()
    rclpy.shutdown()


if __name__ == "__main__":
    main()
