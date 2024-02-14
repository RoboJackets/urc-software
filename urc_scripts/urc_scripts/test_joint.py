import rclpy
import numpy as np
from rclpy.publisher import Publisher
from rclpy.subscription import Subscription
from rclpy.client import Client
from rclpy.action import ActionClient
from rclpy.node import Node
from geometry_msgs.msg import Twist
from sensor_msgs.msg import Joy
from std_srvs.srv import Trigger
from control_msgs.action import GripperCommand


import threading


def rpy_to_quaternion(roll, pitch, yaw):
    """
    Convert Roll-Pitch-Yaw (RPY) angles to quaternion.

    Parameters:
        roll (float): Roll angle in radians.
        pitch (float): Pitch angle in radians.
        yaw (float): Yaw angle in radians.

    Returns:
        numpy.array: Quaternion in the form [w, x, y, z].
    """
    cy = np.cos(yaw * 0.5)
    sy = np.sin(yaw * 0.5)
    cr = np.cos(roll * 0.5)
    sr = np.sin(roll * 0.5)
    cp = np.cos(pitch * 0.5)
    sp = np.sin(pitch * 0.5)

    qw = cy * cr * cp + sy * sr * sp
    qx = cy * sr * cp - sy * cr * sp
    qy = cy * cr * sp + sy * sr * cp
    qz = sy * cr * cp - cy * sr * sp

    return qw, qx, qy, qz


# Example usage

class TestJoint(Node):
    def __init__(self):
        super().__init__("ff")
        self.joy_subscriber: Subscription = self.create_subscription(
            Joy, "/joy", self.pub, 10)
        self.cmd_twist_publisher: Publisher = self.create_publisher(
            Twist, "/cmd_twist", 10)
        self.start_servo_service_request: Client = self.create_client(
            Trigger, "/arm_rt_pinocchio/start_servo")
        self.stop_servo_service_request: Client = self.create_client(
            Trigger, "/arm_rt_pinocchio/stop_servo")
        self.left_gripper_action_client: ActionClient = ActionClient(
            self, GripperCommand, "/gripper_controller_left/gripper_cmd"
        )
        self.right_gripper_action_client: ActionClient = ActionClient(
            self, GripperCommand, "/gripper_controller_right/gripper_cmd"
        )
        self.previous_open = False

    def pub(self, msg: Joy):
        t = Twist()
        t.linear.x = msg.axes[1] * 0.30
        t.linear.y = msg.axes[0] * 0.30

        if msg.buttons[4] == 1:
            t.linear.z = 0.10
        elif msg.buttons[5] == 1:
            t.linear.z = -0.10
        else:
            t.linear.z = 0.0

        # t.angular.z = msg.axes[2] * 0.5
        t.angular.y = msg.axes[3] * 0.2

        self.cmd_twist_publisher.publish(t)

        if msg.buttons[1] == 1:
            self.start_servo_service_request.call_async(Trigger.Request())
        if msg.buttons[2] == 1:
            self.stop_servo_service_request.call_async(Trigger.Request())

        if msg.buttons[3] == 1 and not self.previous_open:
            target = GripperCommand.Goal()
            target.command.position = 1.0
            self.previous_open = True
            self.left_gripper_action_client.send_goal_async(target)
            self.right_gripper_action_client.send_goal_async(target)
        elif msg.buttons[3] == 0 and self.previous_open:
            target = GripperCommand.Goal()
            target.command.position = -0.40
            self.previous_open = False
            self.left_gripper_action_client.send_goal_async(target)
            self.right_gripper_action_client.send_goal_async(target)


def main(args=None):
    rclpy.init(args=args)
    node = TestJoint()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()


if __name__ == "__main__":
    main()
