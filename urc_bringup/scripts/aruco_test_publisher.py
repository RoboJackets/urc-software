#!/usr/bin/env python3
import rclpy
from rclpy.node import Node
from sensor_msgs.msg import Image, CameraInfo
from cv_bridge import CvBridge
import cv2
import numpy as np


class ArucoTestPublisher(Node):
    def __init__(self):
        super().__init__('aruco_test_publisher')
        self.bridge = CvBridge()
        self.image_pub = self.create_publisher(Image, '/camera/image_raw', 10)
        self.cinfo_pub = self.create_publisher(CameraInfo, '/camera/camera_info', 10)

        self.camera_info = self._make_camera_info()
        self.image = self._make_marker_image()

        self.timer = self.create_timer(1.0, self.publish_messages)
        self.get_logger().info('Aruco test publisher started; publishing test image to /camera/image_raw')

    def _make_camera_info(self) -> CameraInfo:
        width = 640
        height = 480
        fx = 320.0
        fy = 320.0
        cx = width / 2.0
        cy = height / 2.0

        camera_info = CameraInfo()
        camera_info.width = width
        camera_info.height = height
        camera_info.distortion_model = 'plumb_bob'
        camera_info.d = [0.0, 0.0, 0.0, 0.0, 0.0]
        camera_info.k = [fx, 0.0, cx, 0.0, fy, cy, 0.0, 0.0, 1.0]
        camera_info.r = [1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0]
        camera_info.p = [fx, 0.0, cx, 0.0, 0.0, fy, cy, 0.0, 0.0, 0.0, 1.0, 0.0]
        camera_info.header.frame_id = 'camera_link'
        return camera_info

    def _make_marker_image(self) -> np.ndarray:
        image = np.ones((480, 640), dtype=np.uint8) * 255
        aruco_dict = cv2.aruco.getPredefinedDictionary(cv2.aruco.DICT_4X4_50)
        marker_size_pixels = 300
        marker = cv2.aruco.drawMarker(aruco_dict, 0, marker_size_pixels)
        y = (image.shape[0] - marker_size_pixels) // 2
        x = (image.shape[1] - marker_size_pixels) // 2
        image[y:y + marker_size_pixels, x:x + marker_size_pixels] = marker
        return cv2.cvtColor(image, cv2.COLOR_GRAY2BGR)

    def publish_messages(self):
        now = self.get_clock().now().to_msg()
        self.camera_info.header.stamp = now

        image_msg = self.bridge.cv2_to_imgmsg(self.image, encoding='bgr8')
        image_msg.header.stamp = now
        image_msg.header.frame_id = 'camera_link'

        self.image_pub.publish(image_msg)
        self.cinfo_pub.publish(self.camera_info)
        self.get_logger().debug('Published test ArUco image and camera_info')


def main(args=None):
    rclpy.init(args=args)
    node = ArucoTestPublisher()
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    node.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()
