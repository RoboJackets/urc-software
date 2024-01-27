import rclpy
from rclpy.node import Node
from trajectory_msgs.msg import JointTrajectory, JointTrajectoryPoint
import threading


# Example usage

class TestJoint(Node):
    def __init__(self):
        super().__init__("ff")
        self.arm_publisher = self.create_publisher(
            JointTrajectory, "/arm_controller/joint_trajectory", 10
        )
        self.pub()

    def pub(self):
        traj = JointTrajectory()
        pt1 = JointTrajectoryPoint()
        pt1.positions = [1.0, 1.0, 1.0, 1.0, 1.0]
        traj.joint_names = ["shoulderjoint", "bicepjoint",
                            "elbowjoint", "wristjoint", "clawjoint"]
        traj.points = [
            pt1
        ]
        self.arm_publisher.publish(
            traj
        )


def main(args=None):
    rclpy.init(args=args)
    node = TestJoint()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()


if __name__ == "__main__":
    main()
