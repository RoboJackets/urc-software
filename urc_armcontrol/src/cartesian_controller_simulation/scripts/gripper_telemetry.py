#!/usr/bin/env python3
"""Publish opening width and speed from symmetric gripper joint feedback."""

import math

import rclpy
from control_msgs.msg import JointTrajectoryControllerState
from rclpy.node import Node
from rclpy.qos import qos_profile_sensor_data
from urc_msgs.msg import GripperTelemetry


class GripperTelemetryNode(Node):
    def __init__(self):
        super().__init__("gripper_telemetry")
        self.publisher = self.create_publisher(
            GripperTelemetry, "gripper/telemetry", 10
        )
        self.subscription = self.create_subscription(
            JointTrajectoryControllerState,
            "gripper_controller/controller_state",
            self.on_controller_state,
            qos_profile_sensor_data,
        )

    def on_controller_state(self, msg):
        try:
            index = msg.joint_names.index("left_finger_joint")
        except ValueError:
            return

        if (index >= len(msg.feedback.positions)
                or index >= len(msg.feedback.velocities)):
            return
        position = msg.feedback.positions[index]
        velocity = msg.feedback.velocities[index]
        if not math.isfinite(position) or not math.isfinite(velocity):
            return

        telemetry = GripperTelemetry()
        telemetry.header = msg.header
        telemetry.opening_width_m = 2.0 * position
        telemetry.opening_speed_mps = 2.0 * velocity

        self.publisher.publish(telemetry)


def main(args=None):
    rclpy.init(args=args)
    node = GripperTelemetryNode()
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    finally:
        node.destroy_node()
        rclpy.try_shutdown()


if __name__ == "__main__":
    main()
