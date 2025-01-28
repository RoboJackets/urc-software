import rclpy
from rclpy.node import Node
import placo
import pinocchio as pin
from placo_utils.visualization import robot_viz, robot_frame_viz, point_viz
import numpy as np
import rclpy.qos
from std_msgs.msg import String
from std_msgs.msg import Float64MultiArray
from std_srvs.srv import Trigger
from geometry_msgs.msg import Twist
from sensor_msgs.msg import JointState
from visualization_msgs.msg import Marker
from urc_arm_py.arm_qp_control_parameters import arm_qp_control_parameters
from urc_arm_py.pd_ctrl import PDController
from scipy.spatial.transform import Rotation


class ArmQPController(Node):
    def __init__(self):
        super().__init__("arm_qp_controller")
        self.initialized = False
        self.control_activated = True

        self.param_listener = arm_qp_control_parameters.ParamListener(self)
        self.param = self.param_listener.get_params()
        self.param_updater = self.create_timer(1.0, self.update_params_loop)

        # load robot model
        self.robot_exec = placo.RobotWrapper(
            self.param.robot_config.model_path,
            placo.Flags.ignore_collisions
        )
        self.get_logger().info("Model initialization successful!")

        # ros pub / subs
        self.joint_state_sub = self.create_subscription(
            JointState, "/joint_states", self.update_robot_state, 10
        )
        self.previous_feedback_time = self.get_clock().now()

        self.pos_ctrl_pub = self.create_publisher(
            Float64MultiArray,
            "~/pos_ctrl",
            10,
        )
        self.pos_ctrl_command = Float64MultiArray()
        self.pos_ctrl_command = Float64MultiArray()
        self.pd_ctrl = PDController(
            [str(x) for x in self.robot_exec.joint_names(False)]
        )
        for joint in self.param.joints:
            gain = self.param.gains.get_entry(joint)
            self.pd_ctrl.set_gain(joint, gain.kp, gain.kd)
        self.torque_ctrl_pub = self.create_publisher(
            Float64MultiArray,
            "~/torque_ctrl",
            10,
        )
        self.torque_ctrl_command = Float64MultiArray()
        self.ee_twist_sub = self.create_subscription(
            Twist, "~/cmd_twist", self.on_twist_cmd, 10
        )
        self.target_marker_pub = self.create_publisher(
            Marker, "~/ee_target", 10
        )

        # ros services
        self.activation_service = self.create_service(
            Trigger, "~/activate", self.activate_control
        )
        self.deactivation_service = self.create_service(
            Trigger, "~/deactivate", self.deactivate_control
        )

        # targets
        self.se3_ee_curr = np.eye(4)
        self.se3_ee_target = np.eye(4)
        self.twist_target = np.zeros(6)
        self.target_maker = Marker()

        # placo related
        self.setup_tasks()
        self.first_updated = False

        # start
        self.create_timer(
            1.0 / self.param_listener.get_params().control_config.rate_hz,
            self.control_loop,
        )

    def on_twist_cmd(self, msg: Twist):
        self.twist_target = 

    def setup_tasks(self):
        self.solver = placo.KinematicsSolver(self.robot_exec)
        self.solver.mask_fbase(True)
        self.solver.dt = 1.0 / self.param_listener.get_params().control_config.rate_hz

        self.ee_name = self.param.robot_config.end_effector_frame_name
        self.se3_ee_curr = self.robot_exec.get_T_world_frame(self.ee_name)
        self.se3_ee_target = self.se3_ee_curr.copy()

        self.ee_frame_task = self.solver.add_frame_task(
            self.ee_name, self.se3_ee_target
        )
        self.ee_frame_task.configure("frame::ee", "soft", 10.0, 3.0)
        self.solver.add_kinetic_energy_regularization_task(1e-4)
        self.solver.add_regularization_task(1e2)

        self.manipulability_task = self.solver.add_manipulability_task(
            self.ee_name, "position", 1.0
        )
        self.manipulability_task.configure("manip", "soft", 1e-3)

        self.joint_task = self.solver.add_joints_task()
        self.joint_task.configure("joint::ee", "soft", 10.0)
        self.joint_task.set_joint("ee_roll_joint", 0.0)
        self.initialized = True

    def activate_control(self, request: Trigger.Request, response: Trigger.Response):
        self.control_activated = True
        response.success = True
        self.se3_ee_target = self.robot_exec.get_T_world_frame(
            self.ee_name).copy()
        self.get_logger().info("Activated control!")
        return response

    def deactivate_control(self, request: Trigger.Request, response: Trigger.Response):
        self.control_activated = False
        response.success = True
        self.get_logger().info("Deactivated control!")
        return response

    def update_robot_state(self, msg: JointState):
        if not self.initialized:
            return
        for jnt, pos, vel, _ in zip(msg.name, msg.position, msg.velocity, msg.effort):
            self.robot_exec.set_joint(jnt, pos)
            self.robot_exec.set_joint_velocity(jnt, vel)
            self.previous_feedback_time = self.get_clock().now()
            self.robot_exec.update_kinematics()
        if not self.first_updated:
            self.synchronize()
            self.get_logger().info(
                f"{self.robot_exec.get_T_world_frame(self.ee_name)}, {self.ee_name}"
            )
            self.se3_ee_curr = self.robot_exec.get_T_world_frame(self.ee_name)
            self.se3_ee_target = self.se3_ee_curr.copy()
            self.first_updated = True

    def control_loop(self):
        self.target_marker_pub.publish(self.target_maker)
        if not self.initialized or not self.control_activated:
            return

        # update state
        self.robot_exec.update_kinematics()
        self.ee_frame_task.T_world_frame = self.se3_ee_target.copy()
        self.solver.solve(True)
        point_viz("target", self.se3_ee_target[0:3, 3])

        q_des = self.robot_plan.state.q[7:]
        for val in q_des:
            self.pos_ctrl_command.data.append(val)
        self.pos_ctrl_pub.publish(self.pos_ctrl_command)

        # compute desired torque
        torque_fb = self.pd_ctrl.compute_torque(
            np.zeros(5), np.zeros(5),
            self.robot_exec.state.q[7:], self.robot_exec.state.qd[6:]
        )
        torque_ff = self.robot_exec.generalized_gravity()[6:]
        torque_des = torque_fb + torque_ff

        # publish results
        self.torque_ctrl_command.data = torque_des.tolist()
        self.torque_ctrl_pub.publish(self.torque_ctrl_command)

    def update_params_loop(self):
        if self.param_listener.is_old(self.param):
            self.update_params()

    def update_params(self):
        self.param = self.param_listener.get_params()
        for joint in self.param.joints:
            gain = self.param.gains.get_entry(joint)
            self.pd_ctrl.set_gain(joint, gain.kp, gain.kd)


def main():
    print("Starting ArmQPController...")
    rclpy.init()
    ctrl = ArmQPController()
    rclpy.spin(ctrl)
    rclpy.shutdown()


if __name__ == "__main__":
    main()
