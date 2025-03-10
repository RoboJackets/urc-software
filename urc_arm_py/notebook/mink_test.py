from pathlib import Path

import mujoco
import mujoco.viewer
import numpy as np

import mink


from functools import partial

import mujoco
import numpy as np
from loop_rate_limiters import RateLimiter
from keycodes import *


class TeleopMocap:
    """
    Class to handle keyboard input for teleoperation.
    The class provides methods to toggle teleoperation on/off,
    switch between manual and non-manual modes,
    adjust step sizes / speed for movement and rotation,
    and select movements based on key presses.
    """

    def __init__(self, data):
        self.on = False
        self.data = data
        self.reset_state()
        self.actions = {
            KEY_N: self.toggle_manual,  # n: toggle non-manual mode
            KEY_PERIOD: self.toggle_rotation,  # .: toggle rotation mode
            KEY_8: self.toggle_mocap,  # 8: toggle mocap data
            # =/+: increase speed
            KEY_EQUAL: partial(self.toggle_speed, 1),
            # -: decrease speed
            KEY_MINUS: partial(self.toggle_speed, -1),
            KEY_UP: partial(
                self.movement_select, KEY_UP, 0, 1
            ),  # Up arrow
            KEY_DOWN: partial(
                self.movement_select, KEY_DOWN, 0, -1
            ),  # Down arrow
            KEY_RIGHT: partial(
                self.movement_select, KEY_RIGHT, 1, 1
            ),  # Right arrow
            KEY_LEFT: partial(
                self.movement_select, KEY_LEFT, 1, -1
            ),  # Left arrow
            # 6
            KEY_7: partial(self.movement_select, KEY_7, 2, 1),
            # 7
            KEY_6: partial(self.movement_select, KEY_6, 2, -1),
        }
        self.movements = {
            # Up arrow
            KEY_UP: partial(self.movement_select, -1, 0, 1),
            # Down arrow
            KEY_DOWN: partial(self.movement_select, -1, 0, -1),
            # Right arrow
            KEY_RIGHT: partial(self.movement_select, -1, 1, 1),
            # Left arrow
            KEY_LEFT: partial(self.movement_select, -1, 1, -1),
            KEY_7: partial(self.movement_select, -1, 2, 1),  # 6
            KEY_6: partial(self.movement_select, -1, 2, -1),  # 7
        }
        self.opposite_keys = {
            KEY_UP: KEY_DOWN,
            KEY_DOWN: KEY_UP,
            KEY_RIGHT: KEY_LEFT,
            KEY_LEFT: KEY_RIGHT,
            KEY_7: KEY_6,
            KEY_6: KEY_7,
        }

    def __call__(self, key):
        # Toggle teleop on/off
        if key == KEY_9:  # 9
            self.toggle_on()
            return

        # Do nothing if teleop is off
        if not self.on:
            return

        if key in self.actions:
            self.actions[key]()

    def auto_key_move(self):
        """
        Automatically move the mocap body based on key presses.
        """

        if not self.on:
            return

        for key, action in self.movements.items():
            if self.keys[key]:
                action()

    def movement_select(self, key, axis, direction):
        """
        Select the movement direction based on the key pressed.
        """

        if not self.manual and key != -1:
            self.keys[key] = not self.keys[key]
            self.keys[self.opposite_keys[key]] = False
        elif not self.manual and key == -1:
            self.rot_or_trans(key, axis, direction)
        elif self.manual:
            self.rot_or_trans(key, axis, direction)

    def rot_or_trans(self, key, axis, direction):
        """
        Adjust the position or rotation of the mocap body based on rotation mode.
        """

        if self.rotation:
            self.adjust_rotation(key, axis, direction)
        else:
            self.adjust_position(key, axis, direction)

    def adjust_position(self, key, axis, direction):
        """
        Adjust the position of the mocap body in the specified direction
        based on the axis and step size.
        """

        q = self.data.mocap_quat[self.mocap_idx].copy()
        rot = np.zeros(shape=(9,), dtype=np.float64)
        mujoco.mju_quat2Mat(rot, q)
        rot = rot.reshape((3, 3))
        unit_vec = rot[:, axis]
        step_size = self.m_step_size if self.manual else self.nm_step_size
        self.data.mocap_pos[self.mocap_idx] += direction * step_size * unit_vec

    def adjust_rotation(self, key, axis, direction):
        """
        Adjust the rotation of the mocap body in the specified direction
        based on the axis and step size.
        """

        step_size = self.m_rotation_step if self.manual else self.nm_rotation_step
        self.data.mocap_quat[self.mocap_idx] = self.rotate_quaternion(
            self.data.mocap_quat[self.mocap_idx], axis, direction * step_size
        )

    def rotate_quaternion(self, quat, axis, angle):
        """
        Rotate a quaternion by an angle around an axis.
        """
        rot = np.zeros(shape=(4,), dtype=np.float64)
        result = np.zeros(shape=(4,), dtype=np.float64)

        unit_axis = np.zeros(shape=(3,), dtype=np.float64)
        if axis == 0:
            unit_axis[0] = 1.0
        elif axis == 1:
            unit_axis[1] = 1.0
        elif axis == 2:
            unit_axis[2] = 1.0

        angle_rad = np.deg2rad(angle)
        unit_axis = unit_axis / np.linalg.norm(unit_axis)
        mujoco.mju_axisAngle2Quat(rot, unit_axis, angle_rad)
        mujoco.mju_mulQuat(result, rot, quat)
        return result

    def toggle_on(self):
        self.on = not self.on
        state = "On" if self.on else "Off"
        print(f"Keyboard Teleoperation toggled: {state}!")
        self.reset_state()
        print()

    def toggle_manual(self):
        self.manual = not self.manual
        manual_state = "On" if self.manual else "Off"
        print(f"Manual mode toggled: {manual_state}!")
        self.reset_keys()
        print()

    def toggle_rotation(self):
        self.rotation = not self.rotation
        state = "On" if self.rotation else "Off"
        print(f"Rotation mode toggled: {state}!")
        self.reset_keys()
        print()

    def toggle_speed(self, direction):
        factor = 1.10 if direction == 1 else 0.9
        if self.manual:
            if self.rotation:
                self.m_rotation_step *= factor
            else:
                self.m_step_size *= factor
        else:
            if self.rotation:
                self.nm_rotation_step *= factor
            else:
                self.nm_step_size *= factor

        output = "Manual" if self.manual else "Non-manual"
        mode = "Rotation" if self.rotation else "Translation"
        if self.manual:
            step_size = self.m_rotation_step if self.rotation else self.m_step_size
        else:
            step_size = self.nm_rotation_step if self.rotation else self.nm_step_size
        print(f"{output} {mode} step size: {step_size:.8f}")

    def toggle_mocap(self):
        self.mocap_idx = (self.mocap_idx + 1) % self.data.mocap_pos.shape[
            0
        ]  # cycle through mocap data
        print(f"Current mocap index: {self.mocap_idx}")

    def reset_keys(self):
        self.keys = {
            KEY_UP: False,
            KEY_DOWN: False,
            KEY_RIGHT: False,
            KEY_LEFT: False,
            KEY_7: False,
            KEY_6: False,
        }

    def reset_step_size(self):
        self.m_step_size = 0.01  # manual step size
        self.m_rotation_step = 10  # manual rotation step
        self.nm_step_size = 1e-4  # non-manual step size
        self.nm_rotation_step = 5e-2  # non-manual rotation step
        print("Step sizes have been reset!")

    def reset_state(self):
        self.reset_keys()
        self.reset_step_size()
        self.manual = True
        self.rotation = False
        self.mocap_idx = 0
        str = f"States have been reset: \n \
        - Manual mode: {self.manual} \
        - Rotation mode: {self.rotation} \n \
        - Mocap index: {self.mocap_idx}"

        print(str)


if __name__ == "__main__":
    model = mujoco.MjModel.from_xml_path(
        "/home/keseterg/Documents/RoboJackets/urc_ws/src/urc-software/urc_arm_models/urdf/walli_arm_v2/scene.xml")
    data = mujoco.MjData(model)

    ## =================== ##
    # Setup IK.
    ## =================== ##

    configuration = mink.Configuration(model)

    tasks = [
        end_effector_task := mink.FrameTask(
            frame_name="attachment_site",
            frame_type="site",
            position_cost=10.0,
            orientation_cost=7.0,
            lm_damping=1.0,
        )
    ]

    limits = [
        mink.ConfigurationLimit(model=configuration.model),
    ]

    ## =================== ##

    # IK settings.
    solver = "osqp"
    pos_threshold = 1e-5
    ori_threshold = 1e-5
    max_iters = 30

    # Initialize key_callback function.
    key_callback = TeleopMocap(data)

    with mujoco.viewer.launch_passive(
        model=model,
        data=data,
        show_left_ui=False,
        show_right_ui=True,
        key_callback=key_callback,
    ) as viewer:
        mujoco.mjv_defaultFreeCamera(model, viewer.cam)
        configuration.update(data.qpos)
        mujoco.mj_forward(model, data)

        # Initialize the mocap target at the end-effector site.
        mink.move_mocap_to_frame(
            model, data, "target", "attachment_site", "site"
        )

        rate = RateLimiter(frequency=500.0, warn=False)
        while viewer.is_running():
            # Update task target.
            T_wt = mink.SE3.from_mocap_name(model, data, "target")
            end_effector_task.set_target(T_wt)

            # Continuously check for autonomous key movement.
            key_callback.auto_key_move()

            # Compute velocity and integrate into the next configuration.
            for i in range(max_iters):
                vel = mink.solve_ik(
                    configuration, tasks, rate.dt, solver, damping=1e-3, limits=limits
                )
                configuration.integrate_inplace(vel, rate.dt)
                err = end_effector_task.compute_error(configuration)
                pos_achieved = np.linalg.norm(err[:3]) <= pos_threshold
                ori_achieved = np.linalg.norm(err[3:]) <= ori_threshold
                if pos_achieved and ori_achieved:
                    break

            data.ctrl = configuration.q
            mujoco.mj_step(model, data)

            # Visualize at fixed FPS.
            viewer.sync()
            rate.sleep()
