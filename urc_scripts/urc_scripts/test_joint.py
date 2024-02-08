import rclpy
from rclpy.publisher import Publisher
from rclpy.node import Node
from geometry_msgs.msg import Twist
from sensor_msgs.msg import Joy
import threading


# Example usage

class TestJoint(Node):
    def __init__(self):
        super().__init__("ff")
        self.joy_subscriber = self.create_subscription(
            Joy, "/joy", self.pub, 10)
        self.cmd_twist_publisher: Publisher = self.create_publisher(
            Twist, "/cmd_twist", 10)

    def pub(self, msg: Joy):
        t = Twist()
        t.linear.x = msg.axes[1] * 0.30
        t.linear.y = msg.axes[0] * 0.30
        t.linear.z = msg.axes[3] * 0.20
        self.cmd_twist_publisher.publish(t)


def main(args=None):
    rclpy.init(args=args)
    node = TestJoint()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()


if __name__ == "__main__":
    main()
