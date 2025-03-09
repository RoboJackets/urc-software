import threading
import time

import rclpy
from rclpy.node import Node
import numpy as np
from std_msgs.msg import Float64MultiArray
from std_srvs.srv import Trigger
from geometry_msgs.msg import Twist
from sensor_msgs.msg import JointState
from visualization_msgs.msg import Marker
from urc_arm_py.arm_qp_control_parameters import arm_qp_control_parameters
from scipy.spatial.transform import Rotation
from scipy.linalg import expm

import mujoco
import mujoco.viewer
import mink
from loop_rate_limiters import RateLimiter


def hat_se3(xi):
    """
    Convert a 6x1 twist vector into a 4x4 se(3) matrix.
    """
    omega = xi[:3]  # Angular velocity
    v = xi[3:]      # Linear velocity
    omega_hat = np.array([[0, -omega[2], omega[1]],
                          [omega[2], 0, -omega[0]],
                          [-omega[1], omega[0], 0]])
    se3_mat = np.zeros((4, 4))
    se3_mat[:3, :3] = omega_hat
    se3_mat[:3, 3] = v
    return se3_mat


def transform_se3(T, xi, delta_t):
    """
    Transform an SE(3) matrix T by a twist xi over a small time delta_t.
    """
    xi_hat = hat_se3(xi)
    T_new = expm(xi_hat * delta_t) @ T
    return T_new


class ArmQPController(Node):
    def __init__(self):
        super().__init__("arm_qp_controller")
        self.control_activated = True

        self.param_listener = arm_qp_control_parameters.ParamListener(self)
        self.param = self.param_listener.get_params()
        self.param_updater = self.create_timer(1.0, self.update_params_loop)

        # load robot model
        self.model = mujoco.MjModel.from_xml_path(
            self.param.robot_config.model_path
        )
        self.data_sim = mujoco.MjData(self.model)
        self.data_real = mujoco.MjData(self.model)

        # Create a lock for thread-safe access to simulation data
        self.sim_lock = threading.Lock()

        self.configuration = mink.Configuration(self.model)

        self.task_ee = mink.FrameTask(
            frame_name="attachment_site",
            frame_type="site",
            position_cost=10.0,
            orientation_cost=7.0,
            lm_damping=1.0,
        )
        self.tasks = [self.task_ee]
        self.limits = [mink.ConfigurationLimit(self.model, 0.95, 0.01)]
        self.get_logger().info("Model and controller initialization successful!")

        # ros publishers and subscribers
        self.joint_state_sub = self.create_subscription(
            JointState, "/joint_states", self.update_robot_state, 10
        )
        self.previous_feedback_time = self.get_clock().now()

        self.pos_ctrl_pub = self.create_publisher(
            Float64MultiArray, "~/pos_ctrl", 10,
        )
        self.pos_ctrl_command = Float64MultiArray()

        self.ee_twist_sub = self.create_subscription(
            Twist, "~/cmd_twist", self.on_twist_cmd, 10
        )

        self.synchronize_srv = self.create_service(
            Trigger, "~/sync", self.synchronize
        )

        # targets
        self.twist_target = np.zeros(6)

        # start
        self.init_display()
        mink.move_mocap_to_frame(
            self.model, self.data_sim, "target", "attachment_site", "site"
        )
        self.create_timer(
            1.0 / self.param_listener.get_params().control_config.rate_hz,
            self.control_loop,
        )

        # flag for synchronization on first update
        self.first_updated = False

    def init_display(self):
        if self.param.robot_config.use_visualization:
            # Start a separate visualization thread
            self.visualization_thread = threading.Thread(
                target=self._visualization_loop, daemon=True
            )
            self.visualization_thread.start()

    def _visualization_loop(self):
        with mujoco.viewer.launch_passive(
            model=self.model,
            data=self.data_sim,
            show_left_ui=False,
            show_right_ui=True,
        ) as viewer:
            while rclpy.ok() and self.param.robot_config.use_visualization:
                with self.sim_lock:
                    viewer.sync()
                time.sleep(0.001)

    def on_twist_cmd(self, msg: Twist):
        dt = 1.0 / self.param.control_config.rate_hz
        self.twist_target = np.array([
            msg.linear.x, msg.linear.y, msg.linear.z,
            msg.angular.x, msg.angular.y, msg.angular.z
        ])
        with self.sim_lock:
            # Get current transform of the "target" mocap
            T_current = mink.SE3.from_mocap_name(
                self.model, self.data_sim, "target"
            ).as_matrix()
            T_new = transform_se3(T_current, self.twist_target, dt)

            # Update the simulation mocap position and orientation
            self.data_sim.mocap_pos[0] = T_new[:3, 3]
            quat = Rotation.from_matrix(T_new[:3, :3]).as_quat()
            # convert from [x, y, z, w] to [w, x, y, z]
            quat = np.roll(quat, 1)
            self.data_sim.mocap_quat[0] = quat

    def synchronize(self, request: Trigger.Request, response: Trigger.Response):
        with self.sim_lock:
            self.data_sim = mujoco.MjData(self.data_real)
        response.success = True
        self.get_logger().info("Successfully synchronized!")
        return response

    def update_robot_state(self, msg: JointState):
        with self.sim_lock:
            for jnt, pos, vel, _ in zip(msg.name, msg.position, msg.velocity, msg.effort):
                jnt_id = mujoco.mj_name2id(
                    self.model, mujoco.mjtObj.mjOBJ_JOINT, jnt)
                if jnt_id < 0:
                    self.get_logger().warning(
                        f"Joint '{jnt}' not found in model. Skipping."
                    )
                    continue

                qposadr = self.model.jnt_qposadr[jnt_id]
                qveladr = self.model.jnt_dofadr[jnt_id]
                dof = self.model.jnt_dof[jnt_id]

                if dof == 1:
                    self.data_real.qpos[qposadr] = pos
                    self.data_real.qvel[qveladr] = vel

        if not self.first_updated:
            self.synchronize(Trigger.Request(), Trigger.Response())
            self.first_updated = True

    def control_loop(self):
        if not self.control_activated:
            return

        with self.sim_lock:
            # update state
            T_des = mink.SE3.from_mocap_name(
                self.model, self.data_sim, "target")
            self.task_ee.set_target(T_des)

            for _ in range(self.param.control_config.max_iters):
                qdot = mink.solve_ik(
                    self.configuration,
                    self.tasks,
                    1.0 / self.param.control_config.rate_hz,
                    self.param.control_config.solver,
                    damping=1e-3,
                    limits=self.limits
                )
                self.configuration.integrate_inplace(
                    qdot, 1.0 / self.param.control_config.rate_hz
                )
                err = self.task_ee.compute_error(self.configuration)
                pos_achieved = np.linalg.norm(
                    err[:3]) <= self.param.control_config.pos_threshold
                ori_achieved = np.linalg.norm(
                    err[3:]) <= self.param.control_config.ori_threshold
                if pos_achieved and ori_achieved:
                    break

            # Update control in-place (if needed, use [:] assignment)
            self.data_sim.ctrl = self.configuration.q
            mujoco.mj_step(self.model, self.data_sim)

        self.pos_ctrl_command.data = list(self.configuration.q)
        self.pos_ctrl_pub.publish(self.pos_ctrl_command)

    def update_params_loop(self):
        if self.param_listener.is_old(self.param):
            self.update_params()

    def update_params(self):
        self.param = self.param_listener.get_params()


def main():
    print("Starting ArmQPController...")
    rclpy.init()
    ctrl = ArmQPController()
    rclpy.spin(ctrl)
    rclpy.shutdown()


if __name__ == "__main__":
    main()
