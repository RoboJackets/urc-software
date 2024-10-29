import rclpy
from rclpy.node import Node
from tf_transformations import euler_from_quaternion
from sensor_msgs.msg import Imu


class PubIMURPY(Node):

    def __init__(self):
        super().__init__("pub_imu_rpy")
        self.odom_sub = self.create_subscription(Imu, "/imu/data", self.callback, 10)

    def callback(self, msg):
        orientation_list = [
            msg.orientation.x,
            msg.orientation.y,
            msg.orientation.z,
            msg.orientation.w,
        ]
        (roll, pitch, yaw) = euler_from_quaternion(orientation_list)
        self.get_logger().info(f"Roll: {roll}, Pitch: {pitch}, Yaw: {yaw}")


def main(args=None):
    rclpy.init(args=args)
    tester_node = PubIMURPY()
    rclpy.spin(tester_node)


if __name__ == "__main__":
    main()
