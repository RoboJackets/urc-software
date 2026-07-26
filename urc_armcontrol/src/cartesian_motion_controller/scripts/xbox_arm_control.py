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
import time
import numpy as np
import threading
from tf2_ros import Buffer, TransformListener
from rclpy.node import Node
from sensor_msgs.msg import JointState
from geometry_msgs.msg import PoseStamped
from scipy.spatial.transform import Rotation as R
from controller_manager_msgs.srv import SwitchController
from trajectory_msgs.msg import JointTrajectory, JointTrajectoryPoint

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

# How far into the future each streamed trajectory point is placed, (> 1/PUBLISH_RATE)
JOINT_POINT_TIME  = 0.2 # seconds
JOINT_SPEED       = 0.005 # radians (or meters) per tick per joint (joint mode)

# Xbox axis ranges (inputs library returns integers)
AXIS_MAX = 32768.0
TRIGGER_MAX = 255.0

# These are the different controller modes that can be set
MODE_CARTESIAN = 'cartesian_motion_controller' # Inverse Kinematics
MODE_JOINT = 'joint_trajectory_controller' # Forward Kinematics (incase IK collapses)

# Set names and limits to the default URDF values
# NOTE: These values must match with the URDF exactly
JOINT_NAMES = ['joint1', 'joint2', 'joint3', 'joint4', 'joint5']
JOINT_LIMITS = {
    'joint1': (-0.5, 0.5),
    'joint2': (-2.0 * np.pi, 2.0 * np.pi),
    'joint3': (-np.pi, np.pi),
    'joint4': (-2.0 * np.pi, 2.0 * np.pi),
    'joint5': (-2.0 * np.pi, 2.0 * np.pi),
}


# --- Xbox Arm Control Node ---

class XboxArmController(Node):
    def __init__(self):
        super().__init__('xbox_arm_controller')

        self.publisher = self.create_publisher(
            PoseStamped,
            '/target_frame',
            10
        )

        # Joint trajectory publisher
        self.joint_trajectory_pub = self.create_publisher(
            JointTrajectory, '/joint_trajectory_controller/joint_trajectory', 10
        )

        # Joint state subscriber
        self.joint_state_sub = self.create_subscription(
            JointState, '/joint_states', self._joint_state_callback, 10
        )

        # Switch controller client
        self.switch_controller_client = self.create_client(
            SwitchController, "/controller_manager/switch_controller"
        )

        self._switch_pending = False # If True, execute switch_controller() on next publish
        self._combo_latched = False # If True, the switch_controller combo has been pressed
        self._controller_mode = MODE_CARTESIAN
        self.get_logger().info(f"Controller initialized as: {self._controller_mode}")

        # Current target pose (starts at a neutral upright position), these values get published to the IK topic
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

        # Publish timer, calls self._publish every time the timer elapses
        self.timer = self.create_timer(1.0 / PUBLISH_RATE, self._publish)

        # Current joint values (taken from joint_state_sub), used by joint_trajectory_controller
        self._current_joint_values = {}

        # Target joint values (where we want the joint to go), used by joint_trajectory_controller
        self._target_joint_values = {name: 0.0 for name in JOINT_NAMES}
        self._target_joint_values_seeded = False

        # Create tf buffer/listener pair for position and orientation of the arm
        self._tf_buffer = Buffer()
        self._tf_listener = TransformListener(self._tf_buffer, self)
        self._target_frame_values_seeded = True

        self.get_logger().info("Xbox arm controller started.")
        self.get_logger().info("Left stick: XY | Triggers: Z | Right stick: rotation")

        self._buttons = {'dpad_down': False, 'y': False}

    def _deadzone(self, value):
        if abs(value) < DEADZONE:
            return 0.0
        # Scale so deadzone edge maps to 0 and max maps to 1
        sign = 1.0 if value > 0 else -1.0
        return sign * (abs(value) - DEADZONE) / (1.0 - DEADZONE)

    # Callback function for joint_state_sub
    def _joint_state_callback(self, msg: JointState):
        with self._lock:
            for name, position in zip(msg.name, msg.position):
                self._current_joint_values[name] = position

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
                            # print("left_X command registered!")
                        elif event.code == 'ABS_Y':
                            self._axes['left_y'] = event.state / AXIS_MAX
                            # print("left_Y command registered!")
                        # Right stick
                        elif event.code == 'ABS_RX':
                            self._axes['right_x'] = event.state / AXIS_MAX
                            # print("right_X command registered!")
                        elif event.code == 'ABS_RY':
                            self._axes['right_y'] = event.state / AXIS_MAX
                            # print("right_Y command registered!")
                        # Triggers (0-255)
                        elif event.code == 'ABS_Z':
                            self._axes['lt'] = event.state / TRIGGER_MAX
                            # print("left_trigger command registered!")
                        elif event.code == 'ABS_RZ':
                            self._axes['rt'] = event.state / TRIGGER_MAX
                            # print("right_trigger command registered!")
                        # Dpad down + Y button
                        elif event.code == 'ABS_HAT0Y' and event.state == 1: 
                            # NOTE: event.state == 1 indicates downward dpad press, -1 indicates upward.
                            self._buttons['dpad_down'] = (event.state == 1)
                        elif event.code == 'BTN_WEST':
                            self._buttons['y'] = (event.state == 1)

                        # Switch controllers (press dpad_down + y simultaneously)
                        combo = self._buttons['dpad_down'] and self._buttons['y']
                        if combo and not self._combo_latched:
                            # Uses a latch to prevent a single press from registering as multiple presses.
                            # print("dpad_down + y registered! \nSwitching Controllers...")
                            self._combo_latched = True
                            self._switch_pending = True
                        elif not combo:
                            self._combo_latched = False
                        
            except Exception as e:
                if self._running:
                    self.get_logger().warn(f"Gamepad error: {e}")
                break

# --- Switch Controller ---

    # Call the function to switch controllers and change the mode depending on which controller is currently active. 
    def switch_controller(self):
        if self._controller_mode == MODE_CARTESIAN:
            self._seed_target_joint_values()
            self._do_switch(activate = [MODE_JOINT], deactivate = [MODE_CARTESIAN])
            self._controller_mode = MODE_JOINT

        elif self._controller_mode == MODE_JOINT:
            self._seed_target_frame_values()
            self._do_switch(activate = [MODE_CARTESIAN], deactivate = [MODE_JOINT])
            self._controller_mode = MODE_CARTESIAN

    # Switches controllers, between cartesian/joint
    def _do_switch(self, activate, deactivate):
        if not self.switch_controller_client.wait_for_service(timeout_sec=2.0):
            self.get_logger().error("/controller_manager/switch_controller unavailable.")
            return

        request = SwitchController.Request()

        if hasattr(request, "activate_controllers"):
            request.activate_controllers = activate
            request.deactivate_controllers = deactivate
        else:
            self.get_logger().error("request doesn't have attribute 'activate_controllers'.")

        request.strictness = SwitchController.Request.STRICT
        request.activate_asap = True
        request.timeout.sec = 5
 
        future = self.switch_controller_client.call_async(request)

        def _done_callback(future):
            if future.result() is not None:
                if future.result().ok:
                    status = "Success!"
                else:
                    status = "Failed"
                self.get_logger().info(f"Switch result: {status}")
                if(future.result().ok == True):
                    if activate == [MODE_CARTESIAN]:
                        output = ("\033[1m" + "Cartesian Motion Controller (IK)" + "\033[0m")
                        self._target_joint_values_seeded = False
                    elif activate == [MODE_JOINT]:
                        output = ("\033[1m" +"Joint Trajectory Controller (FK)" + "\033[0m")
                        self._target_frame_values_seeded = False
                    self.get_logger().info(f"Controller switched to: {output}")
                        
                else:
                    self.get_logger().error(f"Controller NOT switched to: {deactivate}")
            else:
                self.get_logger().error(f"Service call failed: {future.exception()}")

        future.add_done_callback(_done_callback)

    # Seeds target_joint_values with current_joint_values IK -> FK
    def _seed_target_joint_values(self):
        with self._lock:
            current_joint_values = dict(self._current_joint_values)
        
        # Make sure the names match up (could probably delete this but it doesn't hurt to keep it)
        missing = [n for n in JOINT_NAMES if n not in current_joint_values]
        if missing:
            self.get_logger().warn(
                f"No /joint_states data for {missing}, keeping previous targets for those joints."
            )

        # Ensure that when target_joint_values is seeded, the values fit within the limits
        for name in JOINT_NAMES:
            if name in current_joint_values:
                lower_limit, upper_limit = JOINT_LIMITS[name]
                self._target_joint_values[name] = float(np.clip(current_joint_values[name], lower_limit, upper_limit))

        self._target_joint_values_seeded = True

    # Seeds the target frame values with values from the tf listener FK -> IK
    def _seed_target_frame_values(self):
        try:
            # Get the target frame values from the tf buffer
            t = self._tf_buffer.lookup_transform('base_link', 'tool0', rclpy.time.Time())
        except Exception as e:
            self.get_logger().error(f"No TF base_link->tool0 yet, keeping previous target: {e}")
            return
        # Get position and orientation of the target frame
        tr, q = t.transform.translation, t.transform.rotation

        # Set the position and orientation using the values from the buffer
        self.position = np.array([tr.x, tr.y, tr.z])
        self.orientation = R.from_quat([q.x, q.y, q.z, q.w])

        self._target_frame_values_seeded = True
        
# --- Publish ---

    def _publish(self):

        with self._lock:
            switch_pending = self._switch_pending
            self._switch_pending = False

        if switch_pending:
            self.switch_controller()

        with self._lock:
            axes = dict(self._axes)

        if self._controller_mode == MODE_CARTESIAN:
            self._publish_cartesian(axes)
        elif self._controller_mode == MODE_JOINT:
            self._publish_joint(axes)
        else:
            print("ERROR: Problem with resolving controller mode.")

    def _publish_cartesian(self, axes):

        # --- IK Translation ---
        dx =  self._deadzone(axes['left_y']) * -TRANSLATION_SPEED   # forward/back
        dy =  self._deadzone(axes['left_x']) * -TRANSLATION_SPEED   # left/right
        dz = (axes['rt'] - axes['lt']) * TRANSLATION_SPEED          # up/down

        # --- IK Rotation (applied as incremental euler angles) ---
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

        # TODO: For IK (cartesian controller), the y value should stay between -0.5 and 0.5 but it doesn't.
        # This behavior can be observed with the /target_frame topic, using np.clip() doesn't solve this issue.
        msg.pose.position.x = float(self.position[0])
        msg.pose.position.y = float(self.position[1])
        msg.pose.position.z = float(self.position[2])

        q = self.orientation.as_quat()  # [x, y, z, w]
        msg.pose.orientation.x = float(q[0])
        msg.pose.orientation.y = float(q[1])
        msg.pose.orientation.z = float(q[2])
        msg.pose.orientation.w = float(q[3])

        self.publisher.publish(msg)

    def _publish_joint(self, axes):

        if self._target_joint_values_seeded is False:
            self._seed_target_joint_values()
            if self._target_joint_values_seeded is False:
                self.get_logger().error("Target joint values cannot be seeded.")
                return

        # --- FK joint value increments ---
        increments = {
            'joint1': self._deadzone(axes['left_x'])  * -JOINT_SPEED,
            'joint2': self._deadzone(axes['left_y'])  *  JOINT_SPEED, 
            'joint3': (axes['rt'] - axes['lt'])       *  JOINT_SPEED,
            'joint4': self._deadzone(axes['right_y']) * -JOINT_SPEED,
            'joint5': self._deadzone(axes['right_x']) * -JOINT_SPEED,
        }

        # Add the increment for each joint onto their respective _target_joint_values, clipping to handle joint limits
        for name in JOINT_NAMES:
            joint_increment = increments[name]
            if joint_increment != 0.0:
                lower_limit, upper_limit = JOINT_LIMITS[name]
                self._target_joint_values[name] = float(
                    np.clip(self._target_joint_values[name] + joint_increment, lower_limit, upper_limit)
                )
        
        # Build and publish joint trajectory
        msg = JointTrajectory()

        msg.joint_names = list(JOINT_NAMES)

        point = JointTrajectoryPoint()
        point.positions = [self._target_joint_values[name] for name in JOINT_NAMES]
        point.time_from_start.sec = int(JOINT_POINT_TIME)
        point.time_from_start.nanosec = int(
            (JOINT_POINT_TIME - int(JOINT_POINT_TIME)) * 1e9
        )
        msg.points = [point]
 
        self.joint_trajectory_pub.publish(msg)

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