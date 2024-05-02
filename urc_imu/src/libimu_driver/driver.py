from rclpy.node import Node
from sensor_msgs.msg import Imu
from std_msgs.msg import Int32
from libimu_driver.checksum_utils import check_imu_checksum
import re


class Ros2IMUDriver(Node):
    def __init__(self):
        super().__init__('imu_driver')

        self.imu_pub = self.create_publisher(Imu, '/imu', 10)
        self.yaw_pub = self.create_publisher(Int32, '/yaw', 10)

    # Returns True if we successfully did something with the passed in
    def add_sentence(self, imu_string, frame_id, timestamp=None):
        if not check_imu_checksum(imu_string):
            self.get_logger().warn("Received a sentence with"
                                   " an invalid checksum. "
                                   "Sentence was: %s" % imu_string)
            return False

        self.get_logger().info("Sentence received: %s" % imu_string)
        things = re.findall(r"-?[0-9]?[0-9]?[0-9]\.[0-9][0-9]", str(imu_string))
        current_imu = Imu()
        current_yaw = Int32()
        current_imu.orientation.x = float(things[0])
        current_imu.orientation.y = float(things[1])
        current_imu.orientation.z = float(things[2])
        current_imu.orientation.w = float(things[3])
        current_yaw.data = int(float(things[4]))
        current_imu.linear_acceleration.x = float(things[5])
        current_imu.linear_acceleration.y = float(things[6])
        current_imu.linear_acceleration.z = float(things[7])
        current_imu.angular_velocity.x = float(things[8])
        current_imu.angular_velocity.y = float(things[9])
        current_imu.angular_velocity.z = float(things[10])
        if len(things) > 11:
            print("Too many items received in IMU driver message!")
        self.imu_pub.publish(current_imu)
        self.yaw_pub.publish(current_yaw)

        return True

    """Helper method for getting the frame_id with the correct TF prefix"""
    def get_frame_id(self):
        frame_id = self.declare_parameter('frame_id', 'gps').value
        prefix = self.declare_parameter('tf_prefix', '').value
        if len(prefix):
            return '%s/%s' % (prefix, frame_id)
        return frame_id
