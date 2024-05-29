import rclpy
from rclpy.node import Node

from geometry_msgs.msg import PoseStamped
from nav_msgs.msg import Odometry

from tf2_ros import TransformException
from tf2_ros.buffer import Buffer
from tf2_ros.transform_listener import TransformListener
import tf2_geometry_msgs


class OdomToMapPose(Node):

    def __init__(self):
        super().__init__("odom_to_map_pose_node")

        # Declare and acquire `target_frame` parameter
        self.target_frame = "map"

        self.tf_buffer = Buffer()
        self.tf_listener = TransformListener(self.tf_buffer, self)

        self.publisher = self.create_publisher(PoseStamped, "/map/pose", 1)
        self.subscription = self.create_subscription(
            Odometry, "/rover_drivetrain_controller/odom", self.odom_callback, 1
        )

    def odom_callback(self, msg):
        from_frame_rel = "odom"
        to_frame_rel = self.target_frame

        try:
            t = self.tf_buffer.lookup_transform(
                to_frame_rel, from_frame_rel, rclpy.time.Time()
            )
        except TransformException as ex:
            self.get_logger().info(
                f"Could not transform {to_frame_rel} to {from_frame_rel}: {ex}"
            )
            return

        pose_msg = PoseStamped()
        pose_msg.header = msg.header

        # transform pose in msg to target_frame
        pose_msg.pose = tf2_geometry_msgs.do_transform_pose(msg.pose.pose, t)

        self.publisher.publish(pose_msg)


def main():
    rclpy.init()
    node = OdomToMapPose()
    rclpy.spin(node)

    rclpy.shutdown()
