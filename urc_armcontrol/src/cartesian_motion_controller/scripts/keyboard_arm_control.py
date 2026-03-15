#!/usr/bin/env python3
"""
Keyboard -> Arm Cartesian Control
-----------------------------------
W/S       : X translation (forward/back)
A/D       : Y translation (left/right)
Q/E       : Z translation (up/down)
I/K       : Pitch rotation (up/down)
J/L       : Yaw rotation (left/right)
R         : Reset to home position
Ctrl+C    : Quit

Publishes incremental pose updates to /cartesian_motion_controller/target_frame
"""

import rclpy
from rclpy.node import Node
from geometry_msgs.msg import PoseStamped
from scipy.spatial.transform import Rotation as R
import numpy as np
import sys
import tty
import termios
import threading


# --- Tuning ---
TRANSLATION_STEP = 0.005   # meters per keypress
ROTATION_STEP    = 0.05    # radians per keypress
PUBLISH_RATE     = 50.0    # Hz

# Home position
HOME_POSITION    = np.array([0.0, 0.0, 0.3])

BINDINGS = {
    'w': ('x', +1),
    's': ('x', -1),
    'a': ('y', +1),
    'd': ('y', -1),
    'q': ('z', +1),
    'e': ('z', -1),
    'i': ('pitch', +1),
    'k': ('pitch', -1),
    'j': ('yaw', +1),
    'l': ('yaw', -1),
}

HELP = """
Keyboard Arm Controller
-----------------------
W/S  : X (forward/back)
A/D  : Y (left/right)
Q/E  : Z (up/down)
I/K  : Pitch
J/L  : Yaw
R    : Reset to home
Ctrl+C : Quit
"""


def get_key():
    """Read a single keypress without blocking."""
    fd = sys.stdin.fileno()
    old = termios.tcgetattr(fd)
    try:
        tty.setraw(fd)
        key = sys.stdin.read(1)
    finally:
        termios.tcsetattr(fd, termios.TCSADRAIN, old)
    return key


class KeyboardArmController(Node):
    def __init__(self):
        super().__init__('keyboard_arm_controller')

        self.publisher = self.create_publisher(
            PoseStamped,
            '/cartesian_motion_controller/target_frame',
            10
        )

        self.position = HOME_POSITION.copy()
        self.orientation = R.from_euler('xyz', [0.0, 0.0, 0.0])

        self._lock = threading.Lock()
        self._running = True

        # Keyboard polling thread
        self._kb_thread = threading.Thread(target=self._poll_keyboard, daemon=True)
        self._kb_thread.start()

        # Publish timer
        self.timer = self.create_timer(1.0 / PUBLISH_RATE, self._publish)

        print(HELP)
        self.get_logger().info("Keyboard arm controller started.")

    def _poll_keyboard(self):
        while self._running:
            key = get_key()

            if key == '\x03':  # Ctrl+C
                self._running = False
                rclpy.shutdown()
                break

            with self._lock:
                if key == 'r':
                    self.position = HOME_POSITION.copy()
                    self.orientation = R.from_euler('xyz', [0.0, 0.0, 0.0])
                    self.get_logger().info("Reset to home position.")

                elif key in BINDINGS:
                    axis, direction = BINDINGS[key]

                    if axis in ('x', 'y', 'z'):
                        idx = {'x': 0, 'y': 1, 'z': 2}[axis]
                        self.position[idx] += direction * TRANSLATION_STEP
                        self.get_logger().info(
                            f"pos: x={self.position[0]:.3f} "
                            f"y={self.position[1]:.3f} "
                            f"z={self.position[2]:.3f}"
                        )

                    elif axis == 'pitch':
                        delta = R.from_euler('y', direction * ROTATION_STEP)
                        self.orientation = self.orientation * delta

                    elif axis == 'yaw':
                        delta = R.from_euler('z', direction * ROTATION_STEP)
                        self.orientation = self.orientation * delta

    def _publish(self):
        with self._lock:
            pos = self.position.copy()
            q = self.orientation.as_quat()

        msg = PoseStamped()
        msg.header.stamp = self.get_clock().now().to_msg()
        msg.header.frame_id = 'base_link'

        msg.pose.position.x = float(pos[0])
        msg.pose.position.y = float(pos[1])
        msg.pose.position.z = float(pos[2])

        msg.pose.orientation.x = float(q[0])
        msg.pose.orientation.y = float(q[1])
        msg.pose.orientation.z = float(q[2])
        msg.pose.orientation.w = float(q[3])

        self.publisher.publish(msg)

    def destroy_node(self):
        self._running = False
        super().destroy_node()


def main(args=None):
    rclpy.init(args=args)
    node = KeyboardArmController()
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    finally:
        node.destroy_node()
        rclpy.shutdown()


if __name__ == '__main__':
    main()