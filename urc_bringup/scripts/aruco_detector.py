#!/usr/bin/env python3

import rclpy
from rclpy.node import Node

from sensor_msgs.msg import Image, CameraInfo
from std_msgs.msg import Int32MultiArray
from geometry_msgs.msg import Pose, PoseArray, PoseStamped

from cv_bridge import CvBridge
from rclpy.qos import qos_profile_sensor_data

import cv2
import numpy as np


def rvec_to_quaternion(rvec):
    """Convert an OpenCV rotation vector to a ROS quaternion."""

    R, _ = cv2.Rodrigues(rvec)

    trace = R[0, 0] + R[1, 1] + R[2, 2]

    if trace > 0.0:
        s = 0.5 / np.sqrt(trace + 1.0)
        qw = 0.25 / s
        qx = (R[2, 1] - R[1, 2]) * s
        qy = (R[0, 2] - R[2, 0]) * s
        qz = (R[1, 0] - R[0, 1]) * s

    else:
        if R[0, 0] > R[1, 1] and R[0, 0] > R[2, 2]:
            s = 2.0 * np.sqrt(
                1.0 + R[0, 0] - R[1, 1] - R[2, 2]
            )
            qw = (R[2, 1] - R[1, 2]) / s
            qx = 0.25 * s
            qy = (R[0, 1] + R[1, 0]) / s
            qz = (R[0, 2] + R[2, 0]) / s

        elif R[1, 1] > R[2, 2]:
            s = 2.0 * np.sqrt(
                1.0 + R[1, 1] - R[0, 0] - R[2, 2]
            )
            qw = (R[0, 2] - R[2, 0]) / s
            qx = (R[0, 1] + R[1, 0]) / s
            qy = 0.25 * s
            qz = (R[1, 2] + R[2, 1]) / s

        else:
            s = 2.0 * np.sqrt(
                1.0 + R[2, 2] - R[0, 0] - R[1, 1]
            )
            qw = (R[1, 0] - R[0, 1]) / s
            qx = (R[0, 2] + R[2, 0]) / s
            qy = (R[1, 2] + R[2, 1]) / s
            qz = 0.25 * s

    return qx, qy, qz, qw


class ArucoDetector(Node):

    def __init__(self):
        super().__init__('aruco_detector')

        # Parameters
        self.declare_parameter('marker_size', 0.05)

        # DICT_6X6_50 marker ID used by the simulated tag
        self.declare_parameter('expected_marker_id', 23)

        self.marker_size = float(
            self.get_parameter('marker_size').value
        )

        self.expected_marker_id = int(
            self.get_parameter('expected_marker_id').value
        )

        self.bridge = CvBridge()

        self.camera_matrix = None
        self.dist_coeffs = None

        # ---------------------------------------------------------
        # Subscribers
        # ---------------------------------------------------------

        self.image_sub = self.create_subscription(
            Image,
            '/camera/image_raw',
            self.image_cb,
            qos_profile_sensor_data
        )

        self.cinfo_sub = self.create_subscription(
            CameraInfo,
            '/camera/camera_info',
            self.cinfo_cb,
            qos_profile_sensor_data
        )

        # ---------------------------------------------------------
        # Publishers
        # ---------------------------------------------------------

        self.poses_pub = self.create_publisher(
            PoseArray,
            '/aruco/poses',
            10
        )

        self.pose_pub = self.create_publisher(
            PoseStamped,
            '/aruco/pose',
            10
        )

        self.ids_pub = self.create_publisher(
            Int32MultiArray,
            '/aruco/ids',
            10
        )

        self.debug_image_pub = self.create_publisher(
            Image,
            '/aruco/image_debug',
            10
        )

        # ---------------------------------------------------------
        # ArUco setup
        # ---------------------------------------------------------

        self.aruco_dict = cv2.aruco.getPredefinedDictionary(
            cv2.aruco.DICT_6X6_50
        )

        self.aruco_params = cv2.aruco.DetectorParameters_create()

        self.get_logger().info(
            f'Detecting DICT_6X6_50 marker ID '
            f'{self.expected_marker_id}'
        )

        self.get_logger().info(
            f'Marker size: {self.marker_size:.3f} m'
        )

    # -------------------------------------------------------------
    # Camera calibration
    # -------------------------------------------------------------

    def cinfo_cb(self, msg: CameraInfo):

        self.camera_matrix = np.array(
            msg.k,
            dtype=np.float64
        ).reshape((3, 3))

        self.dist_coeffs = np.array(
            msg.d,
            dtype=np.float64
        )

    # -------------------------------------------------------------
    # Image callback
    # -------------------------------------------------------------

    def image_cb(self, msg: Image):

        try:
            cv_image = self.bridge.imgmsg_to_cv2(
                msg,
                desired_encoding='bgr8'
            )

        except Exception as e:
            self.get_logger().error(
                f'cv_bridge error: {e}'
            )
            return

        gray = cv2.cvtColor(
            cv_image,
            cv2.COLOR_BGR2GRAY
        )

        corners, ids, rejected = cv2.aruco.detectMarkers(
            gray,
            self.aruco_dict,
            parameters=self.aruco_params
        )

        pose_array = PoseArray()
        pose_array.header = msg.header

        ids_msg = Int32MultiArray()

        # ---------------------------------------------------------
        # Detect marker
        # ---------------------------------------------------------

        if ids is not None and len(ids) > 0:

            matching_indices = [
                index
                for index, marker_id in enumerate(ids.flatten())
                if int(marker_id) == self.expected_marker_id
            ]

            if matching_indices:

                matching_corners = [
                    corners[index]
                    for index in matching_indices
                ]

                matching_ids = ids[matching_indices]

                ids_msg.data = [
                    self.expected_marker_id
                    for _ in matching_indices
                ]

                # -------------------------------------------------
                # Pose estimation
                # -------------------------------------------------

                if self.camera_matrix is not None:

                    rvecs, tvecs, _ = (
                        cv2.aruco.estimatePoseSingleMarkers(
                            matching_corners,
                            self.marker_size,
                            self.camera_matrix,
                            self.dist_coeffs
                        )
                    )

                    for rvec, tvec in zip(rvecs, tvecs):

                        # -----------------------------------------
                        # Position
                        # -----------------------------------------

                        x = float(tvec[0][0])
                        y = float(tvec[0][1])
                        z = float(tvec[0][2])

                        # -----------------------------------------
                        # Orientation
                        # -----------------------------------------

                        qx, qy, qz, qw = (
                            rvec_to_quaternion(rvec[0])
                        )

                        # -----------------------------------------
                        # Pose message
                        # -----------------------------------------

                        pose = Pose()

                        pose.position.x = x
                        pose.position.y = y
                        pose.position.z = z

                        pose.orientation.x = float(qx)
                        pose.orientation.y = float(qy)
                        pose.orientation.z = float(qz)
                        pose.orientation.w = float(qw)

                        pose_array.poses.append(pose)

                        # -----------------------------------------
                        # PoseStamped
                        # -----------------------------------------

                        pose_stamped = PoseStamped()

                        pose_stamped.header = msg.header

                        pose_stamped.pose = pose

                        self.pose_pub.publish(
                            pose_stamped
                        )

                        # -----------------------------------------
                        # Log pose
                        # -----------------------------------------

                        self.get_logger().info(
                            f'ArUco {self.expected_marker_id} pose: '
                            f'x={x:.3f} m, '
                            f'y={y:.3f} m, '
                            f'z={z:.3f} m | '
                            f'quaternion='
                            f'({qx:.3f}, '
                            f'{qy:.3f}, '
                            f'{qz:.3f}, '
                            f'{qw:.3f})'
                        )

                        # -----------------------------------------
                        # Draw coordinate axes
                        # -----------------------------------------

                        cv2.aruco.drawAxis(
                            cv_image,
                            self.camera_matrix,
                            self.dist_coeffs,
                            rvec,
                            tvec,
                            self.marker_size
                        )

                    # Draw detected marker
                    cv2.aruco.drawDetectedMarkers(
                        cv_image,
                        matching_corners,
                        matching_ids
                    )

            else:
                ids = None

        # ---------------------------------------------------------
        # Publish results
        # ---------------------------------------------------------

        self.ids_pub.publish(ids_msg)

        self.poses_pub.publish(pose_array)

        # ---------------------------------------------------------
        # Publish debug image
        # ---------------------------------------------------------

        try:
            debug_img_msg = self.bridge.cv2_to_imgmsg(
                cv_image,
                encoding='bgr8'
            )

            debug_img_msg.header = msg.header

            self.debug_image_pub.publish(
                debug_img_msg
            )

        except Exception as e:
            self.get_logger().error(
                f'cv_bridge publish error: {e}'
            )


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