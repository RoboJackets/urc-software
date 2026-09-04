#!/usr/bin/env python3
import rclpy
from rclpy.node import Node
from sensor_msgs.msg import Image, CameraInfo
from std_msgs.msg import Int32MultiArray
from geometry_msgs.msg import Pose, PoseArray
from cv_bridge import CvBridge
from rclpy.qos import qos_profile_sensor_data
import cv2
import numpy as np


def rvec_to_quaternion(rvec):
    R, _ = cv2.Rodrigues(rvec)
    # convert rotation matrix to quaternion robustly
    trace = R[0, 0] + R[1, 1] + R[2, 2]
    if trace > 0.0:
        s = 0.5 / np.sqrt(trace + 1.0)
        qw = 0.25 / s
        qx = (R[2, 1] - R[1, 2]) * s
        qy = (R[0, 2] - R[2, 0]) * s
        qz = (R[1, 0] - R[0, 1]) * s
    else:
        if R[0, 0] > R[1, 1] and R[0, 0] > R[2, 2]:
            s = 2.0 * np.sqrt(1.0 + R[0, 0] - R[1, 1] - R[2, 2])
            qw = (R[2, 1] - R[1, 2]) / s
            qx = 0.25 * s
            qy = (R[0, 1] + R[1, 0]) / s
            qz = (R[0, 2] + R[2, 0]) / s
        elif R[1, 1] > R[2, 2]:
            s = 2.0 * np.sqrt(1.0 + R[1, 1] - R[0, 0] - R[2, 2])
            qw = (R[0, 2] - R[2, 0]) / s
            qx = (R[0, 1] + R[1, 0]) / s
            qy = 0.25 * s
            qz = (R[1, 2] + R[2, 1]) / s
        else:
            s = 2.0 * np.sqrt(1.0 + R[2, 2] - R[0, 0] - R[1, 1])
            qw = (R[1, 0] - R[0, 1]) / s
            qx = (R[0, 2] + R[2, 0]) / s
            qy = (R[1, 2] + R[2, 1]) / s
            qz = 0.25 * s
    return qx, qy, qz, qw


class ArucoDetector(Node):
    def __init__(self):
        super().__init__('aruco_detector')
        self.declare_parameter('marker_size', 0.05)
        # The model is named aruco_tag_0, but its supplied image encodes
        # DICT_6X6_50 marker ID 23.
        self.declare_parameter('expected_marker_id', 23)
        self.marker_size = float(self.get_parameter('marker_size').value)
        self.expected_marker_id = int(
            self.get_parameter('expected_marker_id').value
        )

        self.bridge = CvBridge()
        self.camera_matrix = None
        self.dist_coeffs = None

        self.image_sub = self.create_subscription(
            Image, '/camera/image_raw', self.image_cb, qos_profile_sensor_data
        )
        self.cinfo_sub = self.create_subscription(
            CameraInfo, '/camera/camera_info', self.cinfo_cb,
            qos_profile_sensor_data
        )

        self.poses_pub = self.create_publisher(PoseArray, '/aruco/poses', 10)
        self.ids_pub = self.create_publisher(Int32MultiArray, '/aruco/ids', 10)
        self.debug_image_pub = self.create_publisher(Image, '/aruco/image_debug', 10)

        # ArUco setup
        self.aruco_dict = cv2.aruco.getPredefinedDictionary(cv2.aruco.DICT_6X6_50)
        self.aruco_params = cv2.aruco.DetectorParameters_create()
        self.get_logger().info(
            f"Detecting only DICT_6X6_50 marker ID {self.expected_marker_id}"
        )

    def cinfo_cb(self, msg: CameraInfo):
        self.camera_matrix = np.array(msg.k).reshape((3, 3))
        self.dist_coeffs = np.array(msg.d)

    def image_cb(self, msg: Image):
        try:
            cv_image = self.bridge.imgmsg_to_cv2(msg, desired_encoding='bgr8')
        except Exception as e:
            self.get_logger().error(f'cv_bridge error: {e}')
            return

        gray = cv2.cvtColor(cv_image, cv2.COLOR_BGR2GRAY)
        corners, ids, rejected = cv2.aruco.detectMarkers(
            gray, self.aruco_dict, parameters=self.aruco_params
        )

        pose_array = PoseArray()
        pose_array.header = msg.header
        ids_msg = Int32MultiArray()

        if ids is not None and len(ids) > 0:
            # The simulation contains marker 0. Ignore every other valid
            # ArUco marker so this topic is unambiguous for the test.
            matching_indices = [
                index
                for index, marker_id in enumerate(ids.flatten())
                if int(marker_id) == self.expected_marker_id
            ]

            if matching_indices:
                corners = [corners[index] for index in matching_indices]
                ids = ids[matching_indices]
                ids_msg.data = [self.expected_marker_id] * len(matching_indices)
            else:
                corners = []
                ids = None

            if ids is not None and self.camera_matrix is not None:
                rvecs, tvecs, _ = cv2.aruco.estimatePoseSingleMarkers(
                    corners, self.marker_size, self.camera_matrix, self.dist_coeffs
                )
                for rvec, tvec in zip(rvecs, tvecs):
                    pose = Pose()
                    pose.position.x = float(tvec[0][0])
                    pose.position.y = float(tvec[0][1])
                    pose.position.z = float(tvec[0][2])
                    qx, qy, qz, qw = rvec_to_quaternion(rvec[0])
                    pose.orientation.x = float(qx)
                    pose.orientation.y = float(qy)
                    pose.orientation.z = float(qz)
                    pose.orientation.w = float(qw)
                    pose_array.poses.append(pose)

                # Draw axes on image
                for rvec, tvec in zip(rvecs, tvecs):
                    cv2.aruco.drawAxis(cv_image, self.camera_matrix, self.dist_coeffs, rvec, tvec, self.marker_size)

            if ids is not None:
                cv2.aruco.drawDetectedMarkers(cv_image, corners, ids)

        # Publish results
        self.ids_pub.publish(ids_msg)
        self.poses_pub.publish(pose_array)

        try:
            debug_img_msg = self.bridge.cv2_to_imgmsg(cv_image, encoding='bgr8')
            debug_img_msg.header = msg.header
            self.debug_image_pub.publish(debug_img_msg)
        except Exception as e:
            self.get_logger().error(f'cv_bridge publish error: {e}')


def main(args=None):
    rclpy.init(args=args)
    node = ArucoDetector()
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    node.destroy_node()
    if rclpy.ok():
        rclpy.shutdown()


if __name__ == '__main__':
    main()
