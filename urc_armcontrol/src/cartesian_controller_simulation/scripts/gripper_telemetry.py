#!/usr/bin/env python3
"""Publish opening width and speed from symmetric gripper joint feedback."""

import math

import rclpy
from ros_gz_interfaces.msg import Contacts
from control_msgs.msg import JointTrajectoryControllerState
from rclpy.node import Node
from rclpy.qos import qos_profile_sensor_data
from urc_msgs.msg import GripperTelemetry


class GripperTelemetryNode(Node):
    def __init__(self):
        super().__init__("gripper_telemetry")

        self.finger_area_m2 = 0.02 * 0.06 # This value might change, its the x * z value for the claw finger dimensions
        self.contact_timeout_s = 0.25 # How long a recieved contact remains usable

        # None means no reading has arrived yet.
        self.contact_readings = {"left": None, "right": None}

        # From gz -> ros bridge, these are the topics
        self.left_contact_subscription = self.create_subscription(
            Contacts,
            "/gripper/left_contact",
            lambda msg: self.on_contact("left", msg),
            qos_profile_sensor_data,
        )
        self.right_contact_subscription = self.create_subscription(
            Contacts,
            "/gripper/right_contact",
            lambda msg: self.on_contact("right", msg),
            qos_profile_sensor_data,
        )

        self.publisher = self.create_publisher(
            GripperTelemetry, "gripper/telemetry", 10
        )
        self.subscription = self.create_subscription(
            JointTrajectoryControllerState,
            "gripper_controller/controller_state",
            self.on_controller_state,
            qos_profile_sensor_data,
        )

    def on_contact(self, side, msg):
        collision_name = f"{side}_finger_collision_collision"
        total_force = 0.0

        for contact in msg.contacts:
            # Gazebo may supply scoped names such as model::link::collision.
            name1 = contact.collision1.name.split("::")[-1]
            name2 = contact.collision2.name.split("::")[-1]

            if name1 == collision_name:
                use_body1 = True
            elif name2 == collision_name:
                use_body1 = False
            else:
                continue

            # Missing force data should not be interpreted as zero force.
            if not contact.wrenches or (
                len(contact.wrenches) != len(contact.normals)
            ):
                total_force = math.nan
                break

            for wrench, normal in zip(contact.wrenches, contact.normals):
                force = (
                    wrench.body_1_wrench.force
                    if use_body1
                    else wrench.body_2_wrench.force
                )

                values = (
                    force.x, force.y, force.z,
                    normal.x, normal.y, normal.z,
                )
                normal_length = math.sqrt(
                    normal.x**2 + normal.y**2 + normal.z**2
                )
                if not all(math.isfinite(v) for v in values) or normal_length == 0:
                    total_force = math.nan
                    break

                # Force perpendicular to the contact surface.
                # Requires force and normal to be expressed in the same frame.
                total_force += abs(
                    force.x * normal.x
                    + force.y * normal.y
                    + force.z * normal.z
                ) / normal_length

        self.contact_readings[side] = (
            self.get_clock().now(),
            total_force,
        )

    def latest_force(self, side):
        reading = self.contact_readings[side]
        if reading is None:
            return math.nan

        received_at, force = reading
        age_s = (self.get_clock().now() - received_at).nanoseconds / 1e9

        if age_s < 0 or age_s > self.contact_timeout_s:
            return math.nan

        return force

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

        left_force = self.latest_force("left")
        right_force = self.latest_force("right")
        area = self.finger_area_m2

        telemetry.left_force_n = left_force
        telemetry.right_force_n = right_force
        telemetry.left_pressure_pa = left_force / area
        telemetry.right_pressure_pa = right_force / area
        telemetry.combined_pressure_pa = (
            (left_force + right_force) / (2.0 * area)
        )

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
