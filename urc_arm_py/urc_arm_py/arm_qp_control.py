import rclpy
from rclpy.node import Node
import placo
import numpy as np
import rclpy.qos
from std_msgs.msg import String
from std_msgs.msg import Float64MultiArray
from std_srvs.srv import Trigger
from sensor_msgs.msg import JointState
from urc_arm_py.arm_qp_control_parameters import arm_qp_control_parameters


class ArmQPController(Node):
    def __init__(self):
        super().__init__("arm_qp_controller")
        self.initialized = False
        self.control_activated = False

        self.param_listener = arm_qp_control_parameters.ParamListener(self)
        latching_qos = rclpy.qos.QoSProfile(
            depth=1,
            durability=rclpy.qos.QoSDurabilityPolicy.TRANSIENT_LOCAL,
        )

        self.joint_state_sub = self.create_subscription(
            JointState, "/arm_joint_states", self.update_robot_state, 10
        )
        self.previous_feedback_time = self.get_clock().now()

        print(self.param_listener.get_params().control_config.control_topic)
        self.pos_ctrl_pub = self.create_publisher(
            Float64MultiArray,
            self.param_listener.get_params().control_config.control_topic,
            10,
        )
        self.pos_ctrl_command = Float64MultiArray()

        self.robot_description_sub = self.create_subscription(
            String, "/robot_description", self.on_init, latching_qos
        )
        self.activation_service = self.create_service(
            Trigger, "~/activate", self.activate_control
        )
        self.deactivation_service = self.create_service(
            Trigger, "~/deactivate", self.deactivate_control
        )

        # placo related
        self.robot = None
        self.ee_twist_target = np.zeros(6)

    def on_init(self, msg: String):
        self.get_logger().info(
            "Get robot description! Start to initialize the models and control..."
        )

        # load robot model
        self.robot = placo.RobotWrapper(
            "./robot.urdf", placo.Flags.ignore_collisions, msg.data
        )
        self.get_logger().info("Model initialization successfull!")

        # invalidate the subscription
        self.robot_description_sub = None

        # setup tasks
        self.setup_tasks()
        self.initialized = True

        # start control loop
        self.create_timer(
            1.0 / self.param_listener.get_params().control_config.rate_hz,
            self.control_loop,
        )
        self.robot_description_sub = None

    def setup_tasks(self):
        self.solver = placo.KinematicsSolver(self.robot)
        self.solver.mask_fbase(True)
        self.solver.dt = 1.0 / self.param_listener.get_params().control_config.rate_hz

        param = self.param_listener.get_params()
        self.ee_name = param.robot_config.end_effector_frame_name
        self.se3_ee_curr = self.robot.get_T_world_frame(self.ee_name)
        self.se3_ee_target = self.se3_ee_curr

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

    def activate_control(self, request: Trigger.Request, response: Trigger.Response):
        self.control_activated = True
        response.success = True
        self.se3_ee_target = self.robot.get_T_world_frame(self.ee_name)
        self.se3_ee_target[0][3] = 0.5
        self.se3_ee_target[1][3] = 0.5
        self.se3_ee_target[2][3] = 0.5
        self.get_logger().info("Activated control!")
        return response

    def deactivate_control(self, request: Trigger.Request, response: Trigger.Response):
        self.control_activated = False
        response.success = True
        self.get_logger().info("Deactivated control!")
        return response

    def update_robot_state(self, msg: JointState):
        for jnt, pos, vel, _ in zip(msg.name, msg.position, msg.velocity, msg.effort):
            self.robot.set_joint(jnt, pos)
            self.robot.set_joint_velocity(jnt, vel)
            self.previous_feedback_time = self.get_clock().now()

    def control_loop(self):
        if not self.control_activated:
            return

        self.robot.update_kinematics()
        res = self.solver.solve(True)
        self.pos_ctrl_command.data = []
        for val in res[6:]:
            self.pos_ctrl_command.data.append(val)
        self.pos_ctrl_pub.publish(self.pos_ctrl_command)


def main():
    print("Starting ArmQPController...")
    rclpy.init()
    ctrl = ArmQPController()
    rclpy.spin(ctrl)
    rclpy.shutdown()


if __name__ == "__main__":
    main()
