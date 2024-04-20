from rclpy.node import Node
from geometry_msgs.msg import Quaternion
from libimu_driver.checksum_utils import check_imu_checksum
import re


class Ros2IMUDriver(Node):
    def __init__(self):
        super().__init__('imu_driver')

        self.imu_pub = self.create_publisher(Quaternion, '/imu', 10)

    # Returns True if we successfully did something with the passed in
    def add_sentence(self, imu_string, frame_id, timestamp=None):
        if not check_imu_checksum(imu_string):
            self.get_logger().warn("Received a sentence with"
                                   " an invalid checksum. "
                                   "Sentence was: %s" % imu_string)
            return False

        self.get_logger().warn("Sentence received: %s" % imu_string)
        things = re.findall(r"-?[0-9]\.[0-9][0-9]", str(imu_string))
        current_imu = Quaternion()
        current_imu.x = float(things[0])
        current_imu.y = float(things[1])
        current_imu.z = float(things[2])
        current_imu.w = float(things[3])
        self.imu_pub.publish(current_imu)

        return True

    """Helper method for getting the frame_id with the correct TF prefix"""
    def get_frame_id(self):
        frame_id = self.declare_parameter('frame_id', 'gps').value
        prefix = self.declare_parameter('tf_prefix', '').value
        if len(prefix):
            return '%s/%s' % (prefix, frame_id)
        return frame_id
