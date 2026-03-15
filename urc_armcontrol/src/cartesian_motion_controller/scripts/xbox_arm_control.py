#!/usr/bin/env python3
"""
Xbox Controller -> Arm Cartesian Control
-----------------------------------------
Left stick  : X/Y translation
Triggers    : Z up (RT) / Z down (LT)
Right stick : Yaw (left/right) and Pitch (up/down) rotation

Publishes incremental pose updates to /cartesian_motion_controller/target_frame

Dependencies:
    pip install inputs
    or
    sudo apt install python3-inputs

Usage:
    python3 xbox_arm_control.py
    or as a ROS2 node:
    ros2 run <your_package> xbox_arm_control
"""

import rclpy
from rclpy.node import Node
from geometry_msgs.msg import PoseStamped
from scipy.spatial.transform import Rotation as R
import numpy as np
import threading

try:
    from inputs import get_gamepad
    INPUTS_AVAILABLE = True
except ImportError:
    INPUTS_AVAILABLE = False
    print("[WARN] 'inputs' library not found. Install with: pip install inputs")


# --- Tuning ---
TRANSLATION_SPEED = 0.002   # meters per tick
ROTATION_SPEED    = 0.01    # radians per tick
DEADZONE          = 0.1     # ignore stick values below this
PUBLISH_RATE      = 50.0    # Hz

# Xbox axis ranges (inputs library returns integers)
AXIS_MAX = 32768.0
TRIGGER_MAX = 255.0


class XboxArmController(Node):
    def __init__(self):
        super().__init__('xbox_arm_controller')

        self.publisher = self.create_publisher(
            PoseStamped,
            '/cartesian_motion_controller/target_frame',
            10
        )

        # Current target pose (starts at a neutral upright position)
        self.position = np.array([0.0, 0.0, 0.3])   # x, y, z in base_link frame
        self.orientation = R.from_euler('xyz', [0.0, 0.0, 0.0])  # roll, pitch, yaw

        # Raw axis states from gamepad thread
        self._axes = {
            'left_x':  0.0,   # left stick horizontal  -> Y translation
            'left_y':  0.0,   # left stick vertical    -> X translation
            'right_x': 0.0,   # right stick horizontal -> yaw rotation
            'right_y': 0.0,   # right stick vertical   -> pitch rotation
            'lt':      0.0,   # left trigger           -> Z down
            'rt':      0.0,   # right trigger          -> Z up
        }
        self._lock = threading.Lock()
        self._running = True

        # Start gamepad polling thread
        self._gamepad_thread = threading.Thread(
            target=self._poll_gamepad, daemon=True
        )
        self._gamepad_thread.start()

        # Publish timer
        self.timer = self.create_timer(1.0 / PUBLISH_RATE, self._publish)

        self.get_logger().info("Xbox arm controller started.")
        self.get_logger().info("Left stick: XY | Triggers: Z | Right stick: rotation")

    def _deadzone(self, value):
        if abs(value) < DEADZONE:
            return 0.0
        # Scale so deadzone edge maps to 0 and max maps to 1
        sign = 1.0 if value > 0 else -1.0
        return sign * (abs(value) - DEADZONE) / (1.0 - DEADZONE)

    def _poll_gamepad(self):
        if not INPUTS_AVAILABLE:
            self.get_logger().error("'inputs' library not available. No gamepad input.")
            return

        self.get_logger().info("Waiting for gamepad events...")
        while self._running:
            try:
                events = get_gamepad()
                for event in events:
                    with self._lock:
                        # Left stick
                        if event.code == 'ABS_X':
                            self._axes['left_x'] = event.state / AXIS_MAX
                        elif event.code == 'ABS_Y':
                            self._axes['left_y'] = event.state / AXIS_MAX
                        # Right stick
                        elif event.code == 'ABS_RX':
                            self._axes['right_x'] = event.state / AXIS_MAX
                        elif event.code == 'ABS_RY':
                            self._axes['right_y'] = event.state / AXIS_MAX
                        # Triggers (0-255)
                        elif event.code == 'ABS_Z':
                            self._axes['lt'] = event.state / TRIGGER_MAX
                        elif event.code == 'ABS_RZ':
                            self._axes['rt'] = event.state / TRIGGER_MAX
            except Exception as e:
                if self._running:
                    self.get_logger().warn(f"Gamepad error: {e}")
                break

    def _publish(self):
        with self._lock:
            axes = dict(self._axes)

        # --- Translation ---
        dx =  self._deadzone(axes['left_y']) * -TRANSLATION_SPEED   # forward/back
        dy =  self._deadzone(axes['left_x']) * -TRANSLATION_SPEED   # left/right
        dz = (axes['rt'] - axes['lt']) * TRANSLATION_SPEED          # up/down

        # --- Rotation (applied as incremental euler angles) ---
        d_yaw   =  self._deadzone(axes['right_x']) * -ROTATION_SPEED
        d_pitch =  self._deadzone(axes['right_y']) * -ROTATION_SPEED

        # Update position
        self.position += np.array([dx, dy, dz])

        # Update orientation incrementally
        delta_rot = R.from_euler('xyz', [0.0, d_pitch, d_yaw])
        self.orientation = self.orientation * delta_rot

        # Build and publish PoseStamped
        msg = PoseStamped()
        msg.header.stamp = self.get_clock().now().to_msg()
        msg.header.frame_id = 'base_link'

        msg.pose.position.x = float(self.position[0])
        msg.pose.position.y = float(self.position[1])
        msg.pose.position.z = float(self.position[2])

        q = self.orientation.as_quat()  # [x, y, z, w]
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
    node = XboxArmController()
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    finally:
        node.destroy_node()
        rclpy.shutdown()


if __name__ == '__main__':
    main()