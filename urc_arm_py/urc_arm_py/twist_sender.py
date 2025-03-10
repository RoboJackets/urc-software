#!/usr/bin/env python3
import sys
import select
import termios
import tty

import rclpy
from rclpy.node import Node
from geometry_msgs.msg import Twist

msg = """
Reading from the keyboard and publishing Twist messages.
---------------------------
Use keys:
  w: +x
  s: -x
  a: +y
  d: -y
  c: +z (up)
  z: -z (down)
Press q to quit.
"""


def get_key(timeout=0.1):
    """Get a single key from the terminal (non-blocking)."""
    tty.setraw(sys.stdin.fileno())
    rlist, _, _ = select.select([sys.stdin], [], [], timeout)
    if rlist:
        key = sys.stdin.read(1)
    else:
        key = ''
    termios.tcsetattr(sys.stdin, termios.TCSADRAIN, settings)
    return key


class TwistSender(Node):
    def __init__(self):
        super().__init__('twist_sender')
        self.publisher_ = self.create_publisher(
            Twist, '/qp_ctrl/cmd_twist', 10
        )
        self.timer = self.create_timer(0.01, self.timer_callback)
        self.get_logger().info("Keyboard teleop node started. " + msg)
        self.twist = Twist()

    def timer_callback(self):
        key = get_key()
        # Reset twist each cycle
        self.twist = Twist()

        if key == 'w':
            self.twist.linear.x = 1.0
        elif key == 's':
            self.twist.linear.x = -1.0
        elif key == 'a':
            self.twist.linear.y = 1.0
        elif key == 'd':
            self.twist.linear.y = -1.0
        elif key == 'c':
            self.twist.linear.z = 1.0
        elif key == 'z':
            self.twist.linear.z = -1.0
        elif key == 'q':
            self.get_logger().info("Exiting teleop node.")
            rclpy.shutdown()
            return

        self.publisher_.publish(self.twist)
        if key:
            self.get_logger().info(f"Published Twist: {self.twist}")


def main(args=None):
    global settings
    # Check if standard input is a TTY
    if not sys.stdin.isatty():
        print(
            "Standard input is not a TTY. Keyboard teleop requires an interactive terminal.")
        sys.exit(1)

    settings = termios.tcgetattr(sys.stdin)
    rclpy.init(args=args)
    node = TwistSender()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()
    termios.tcsetattr(sys.stdin, termios.TCSADRAIN, settings)


if __name__ == '__main__':
    main()
