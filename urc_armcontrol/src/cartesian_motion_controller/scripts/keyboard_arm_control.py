#!/usr/bin/env python3
"""
Keyboard -> Arm Cartesian/Joint Control with IK/FK switching
-------------------------------------------------------------
IK MODE (cartesian_motion_controller):
  W/S         : X translation (forward/back)
  A/D         : Y translation (left/right)
  Q/E         : Z translation (up/down)
  T/G         : Pitch rotation
  F/H         : Yaw rotation

FK MODE (joint_trajectory_controller):
  W/S         : Joint 1 (base slide)
  A/D         : Joint 2 (shoulder pitch)
  Q/E         : Joint 3 (elbow pitch)
  T/G         : Joint 4 (wrist pitch)
  F/H         : Joint 5 (wrist roll)

BOTH MODES:
  M           : Switch between IK and FK mode
  R           : Reset to home position
  Ctrl+C      : Quit

Publishes to:
  IK: /cartesian_motion_controller/target_frame  (PoseStamped)
  FK: /joint_trajectory_controller/joint_trajectory  (JointTrajectory)

TODO: Yaw control is intentionally mapped here but may be handed off to
      robot base rotation as a separate joint/controller in future.
"""

import rclpy
import numpy as np
import threading
import select
import sys
import tty
import termios
from rclpy.node import Node
from sensor_msgs.msg import JointState
from geometry_msgs.msg import PoseStamped
from scipy.spatial.transform import Rotation as R
from controller_manager_msgs.srv import SwitchController
from trajectory_msgs.msg import JointTrajectory, JointTrajectoryPoint


# --- Tuning ---
TRANSLATION_STEP  = 0.005   # meters per keypress (IK mode)
ROTATION_STEP     = 0.03    # radians per keypress (IK mode)
JOINT_STEP        = 0.05    # radians (or meters) per keypress (FK mode)
PUBLISH_RATE      = 50.0    # Hz

# How far into the future each streamed trajectory point is placed (> 1/PUBLISH_RATE)
JOINT_POINT_TIME  = 0.2     # seconds

# Controller mode names — must match controller_manager config exactly
MODE_CARTESIAN = 'cartesian_motion_controller'
MODE_JOINT     = 'joint_trajectory_controller'

# Home position for IK mode
HOME_POSITION    = np.array([0.0, 0.0, 0.3])
HOME_ORIENTATION = R.from_euler('xyz', [0.0, 0.0, 0.0])

# Joint names and limits — must match URDF exactly
JOINT_NAMES  = ['joint1', 'joint2', 'joint3', 'joint4', 'joint5']
JOINT_LIMITS = {
    'joint1': (-0.5,          0.5),
    'joint2': (-2.0 * np.pi, 2.0 * np.pi),
    'joint3': (-np.pi,        np.pi),
    'joint4': (-2.0 * np.pi, 2.0 * np.pi),
    'joint5': (-2.0 * np.pi, 2.0 * np.pi),
}

# Key bindings per mode — maps key -> (axis/joint, direction)
IK_BINDINGS = {
    'w': ('x',     +1),
    's': ('x',     -1),
    'a': ('y',     +1),
    'd': ('y',     -1),
    'q': ('z',     +1),
    'e': ('z',     -1),
    't': ('pitch', +1),
    'g': ('pitch', -1),
    'f': ('yaw',   +1),  # TODO: may move yaw to robot base controller
    'h': ('yaw',   -1),
}

FK_BINDINGS = {
    'w': ('joint1', +1),
    's': ('joint1', -1),
    'a': ('joint2', +1),
    'd': ('joint2', -1),
    'q': ('joint3', +1),
    'e': ('joint3', -1),
    't': ('joint4', +1),
    'g': ('joint4', -1),
    'f': ('joint5', +1),
    'h': ('joint5', -1),
}

HELP_IK = """
=== IK MODE (Cartesian / Inverse Kinematics) ===
w/s   : X (forward/back)
a/d   : Y (left/right)
q/e   : Z (up/down)
t/g   : Pitch
f/h   : Yaw
r     : Reset to home
m     : Switch to FK mode
Ctrl+C: Quit
"""

HELP_FK = """
=== FK MODE (Joint / Forward Kinematics) ===
w/s   : Joint 1 (base slide)
a/d   : Joint 2 (shoulder pitch)
q/e   : Joint 3 (elbow pitch)
t/g   : Joint 4 (wrist pitch)
f/h   : Joint 5 (wrist roll)
r     : Reset joints to 0
m     : Switch to IK mode
Ctrl+C: Quit
"""


def get_key(timeout=0.1):
    """
    Non-blocking keypress read using select(). Returns None on timeout
    so the keyboard thread can check _running and exit cleanly.
    """
    fd = sys.stdin.fileno()
    old = termios.tcgetattr(fd)
    try:
        tty.setraw(fd)
        ready, _, _ = select.select([sys.stdin], [], [], timeout)
        key = sys.stdin.read(1) if ready else None
    finally:
        termios.tcsetattr(fd, termios.TCSADRAIN, old)
    return key


class KeyboardArmController(Node):
    def __init__(self):
        super().__init__('keyboard_arm_controller')

        # IK publisher
        self.cartesian_pub = self.create_publisher(
            PoseStamped,
            '/cartesian_motion_controller/target_frame',
            10
        )

        # FK publisher
        self.joint_pub = self.create_publisher(
            JointTrajectory,
            '/joint_trajectory_controller/joint_trajectory',
            10
        )

        # Joint state subscriber — needed for seeding FK from current joint positions
        self.joint_state_sub = self.create_subscription(
            JointState, '/joint_states', self._joint_state_callback, 10
        )

        # Switch controller service client
        self.switch_client = self.create_client(
            SwitchController, '/controller_manager/switch_controller'
        )

        # IK state
        self.position    = HOME_POSITION.copy()
        self.orientation = HOME_ORIENTATION

        # FK state
        self._current_joint_values = {}                             # live from /joint_states
        self._target_joint_values  = {n: 0.0 for n in JOINT_NAMES} # where we want joints to go
        self._target_joint_values_seeded = False

        # Controller mode
        self._controller_mode = MODE_CARTESIAN
        self._switch_pending  = False

        self._lock    = threading.Lock()
        self._running = True

        # Keyboard thread
        self._kb_thread = threading.Thread(target=self._poll_keyboard, daemon=True)
        self._kb_thread.start()

        # Publish timer
        self.timer = self.create_timer(1.0 / PUBLISH_RATE, self._publish)

        print(HELP_IK)
        self.get_logger().info(f"Started in mode: {self._controller_mode}")

    # ------------------------------------------------------------------
    # Joint state callback
    # ------------------------------------------------------------------

    def _joint_state_callback(self, msg: JointState):
        with self._lock:
            for name, position in zip(msg.name, msg.position):
                self._current_joint_values[name] = position

    # ------------------------------------------------------------------
    # Keyboard polling
    # ------------------------------------------------------------------

    def _poll_keyboard(self):
        while self._running:
            key = get_key(timeout=0.1)

            if key is None:
                continue

            if key == '\x03':  # Ctrl+C — let main() handle shutdown
                self._running = False
                break

            # Mode switch
            if key == 'm':
                with self._lock:
                    self._switch_pending = True
                continue

            # Reset
            if key == 'r':
                with self._lock:
                    if self._controller_mode == MODE_CARTESIAN:
                        self.position    = HOME_POSITION.copy()
                        self.orientation = HOME_ORIENTATION
                    else:
                        self._target_joint_values = {n: 0.0 for n in JOINT_NAMES}
                self.get_logger().info("Reset to home.")
                continue

            # Movement keys
            with self._lock:
                mode = self._controller_mode

            if mode == MODE_CARTESIAN and key in IK_BINDINGS:
                axis, direction = IK_BINDINGS[key]
                with self._lock:
                    if axis in ('x', 'y', 'z'):
                        idx = {'x': 0, 'y': 1, 'z': 2}[axis]
                        self.position[idx] += direction * TRANSLATION_STEP
                        pos = self.position.copy()
                self.get_logger().info(
                    f"pos: x={pos[0]:.3f} y={pos[1]:.3f} z={pos[2]:.3f}"
                )

                if axis == 'pitch':
                    with self._lock:
                        delta = R.from_euler('y', direction * ROTATION_STEP)
                        self.orientation = self.orientation * delta
                        euler = self.orientation.as_euler('xyz', degrees=True)
                    self.get_logger().info(
                        f"ori: pitch={euler[1]:.1f}° yaw={euler[2]:.1f}°"
                    )

                elif axis == 'yaw':
                    with self._lock:
                        delta = R.from_euler('z', direction * ROTATION_STEP)
                        self.orientation = self.orientation * delta
                        euler = self.orientation.as_euler('xyz', degrees=True)
                    self.get_logger().info(
                        f"ori: pitch={euler[1]:.1f}° yaw={euler[2]:.1f}°"
                    )

            elif mode == MODE_JOINT and key in FK_BINDINGS:
                joint_name, direction = FK_BINDINGS[key]
                with self._lock:
                    lo, hi    = JOINT_LIMITS[joint_name]
                    new_val   = float(np.clip(
                        self._target_joint_values[joint_name] + direction * JOINT_STEP,
                        lo, hi
                    ))
                    self._target_joint_values[joint_name] = new_val
                    snapshot  = dict(self._target_joint_values)
                self.get_logger().info(
                    f"j1={snapshot['joint1']:.3f} j2={snapshot['joint2']:.2f} "
                    f"j3={snapshot['joint3']:.2f} j4={snapshot['joint4']:.2f} "
                    f"j5={snapshot['joint5']:.2f}"
                )

    # ------------------------------------------------------------------
    # Controller switching
    # ------------------------------------------------------------------

    def switch_controller(self):
        if self._controller_mode == MODE_CARTESIAN:
            self._seed_target_joint_values()
            self._do_switch(activate=[MODE_JOINT], deactivate=[MODE_CARTESIAN])
            self._controller_mode = MODE_JOINT
            print(HELP_FK)

        elif self._controller_mode == MODE_JOINT:
            self._do_switch(activate=[MODE_CARTESIAN], deactivate=[MODE_JOINT])
            self._controller_mode = MODE_CARTESIAN
            print(HELP_IK)

    def _do_switch(self, activate, deactivate):
        if not self.switch_client.wait_for_service(timeout_sec=2.0):
            self.get_logger().error("/controller_manager/switch_controller unavailable.")
            return

        request = SwitchController.Request()
        if hasattr(request, 'activate_controllers'):
            request.activate_controllers = activate
            request.deactivate_controllers = deactivate
        else:
            self.get_logger().error("Request missing 'activate_controllers' attribute.")
            return

        request.strictness    = SwitchController.Request.STRICT
        request.activate_asap = True
        request.timeout.sec   = 5

        future = self.switch_client.call_async(request)

        def _done(future):
            if future.result() is not None:
                ok = future.result().ok
                if ok:
                    label = (
                        "Cartesian Motion Controller (IK)"
                        if activate == [MODE_CARTESIAN]
                        else "Joint Trajectory Controller (FK)"
                    )
                    self.get_logger().info(f"Switched to: \033[1m{label}\033[0m")
                    if activate == [MODE_CARTESIAN]:
                        self._target_joint_values_seeded = False
                else:
                    self.get_logger().error(f"Switch failed — could not deactivate {deactivate}")
            else:
                self.get_logger().error(f"Service call failed: {future.exception()}")

        future.add_done_callback(_done)

    def _seed_target_joint_values(self):
        """
        Copy current joint positions into _target_joint_values so FK mode
        starts from where the arm actually is, not zero.
        """
        with self._lock:
            current = dict(self._current_joint_values)

        missing = [n for n in JOINT_NAMES if n not in current]
        if missing:
            self.get_logger().warn(
                f"No /joint_states data for {missing}, keeping previous targets."
            )

        for name in JOINT_NAMES:
            if name in current:
                lo, hi = JOINT_LIMITS[name]
                self._target_joint_values[name] = float(np.clip(current[name], lo, hi))

        self._target_joint_values_seeded = True
        self.get_logger().info("Target joint values seeded from current joint states.")

    # ------------------------------------------------------------------
    # Publish timer
    # ------------------------------------------------------------------

    def _publish(self):
        with self._lock:
            switch_pending = self._switch_pending
            self._switch_pending = False

        if switch_pending:
            self.switch_controller()

        with self._lock:
            mode = self._controller_mode

        if mode == MODE_CARTESIAN:
            self._publish_cartesian()
        elif mode == MODE_JOINT:
            self._publish_joint()

    def _publish_cartesian(self):
        with self._lock:
            pos = self.position.copy()
            q   = self.orientation.as_quat()

        msg = PoseStamped()
        msg.header.stamp    = self.get_clock().now().to_msg()
        msg.header.frame_id = 'base_link'

        msg.pose.position.x = float(pos[0])
        msg.pose.position.y = float(pos[1])
        msg.pose.position.z = float(pos[2])

        msg.pose.orientation.x = float(q[0])
        msg.pose.orientation.y = float(q[1])
        msg.pose.orientation.z = float(q[2])
        msg.pose.orientation.w = float(q[3])

        self.cartesian_pub.publish(msg)

    def _publish_joint(self):
        if not self._target_joint_values_seeded:
            self._seed_target_joint_values()
            if not self._target_joint_values_seeded:
                self.get_logger().error("Cannot seed target joint values — no /joint_states yet.")
                return

        with self._lock:
            targets = dict(self._target_joint_values)

        msg = JointTrajectory()
        msg.joint_names = list(JOINT_NAMES)

        point = JointTrajectoryPoint()
        point.positions = [targets[n] for n in JOINT_NAMES]
        point.time_from_start.sec    = int(JOINT_POINT_TIME)
        point.time_from_start.nanosec = int(
            (JOINT_POINT_TIME - int(JOINT_POINT_TIME)) * 1e9
        )
        msg.points = [point]

        self.joint_pub.publish(msg)

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
        if rclpy.ok():
            rclpy.shutdown()


if __name__ == '__main__':
    main()