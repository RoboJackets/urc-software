#!/usr/bin/env python3
"""Branch detector outputs plus an atomic marker ID/pose for mission consumers."""

import math

import cv2
from cv_bridge import CvBridge, CvBridgeError
from geometry_msgs.msg import Pose, PoseArray, PoseStamped
import numpy as np
import rclpy
from rclpy.node import Node
from rclpy.qos import qos_profile_sensor_data
from sensor_msgs.msg import CameraInfo, Image
from std_msgs.msg import Int32MultiArray
from urc_msgs.msg import ArucoDetection


def marker_pose(rotation, translation):
    # Rodrigues is axis-angle: its magnitude is the angle in radians.
    angle = float(np.linalg.norm(rotation))
    scale = math.sin(angle / 2.0) / angle if angle > 1e-12 else 0.5
    vector = np.asarray(rotation).reshape(3) * scale
    pose = Pose()
    pose.position.x, pose.position.y, pose.position.z = map(float, translation.reshape(3))
    pose.orientation.x, pose.orientation.y, pose.orientation.z = map(float, vector)
    pose.orientation.w = math.cos(angle / 2.0)
    return pose


class ArucoDetector(Node):
    def __init__(self):
        super().__init__('aruco_detector')
        self.marker_size = self.declare_parameter('marker_size', 0.05).value
        dictionary_name = self.declare_parameter('dictionary', 'DICT_4X4_50').value
        self.expected_id = self.declare_parameter('expected_marker_id', -1).value
        self.publish_debug = self.declare_parameter('publish_debug', False).value
        if not math.isfinite(self.marker_size) or self.marker_size <= 0.0:
            raise ValueError('marker_size must be finite and positive')
        dictionary_id = getattr(cv2.aruco, dictionary_name, None)
        if dictionary_id is None:
            raise ValueError('Unknown ArUco dictionary: ' + dictionary_name)
        self.dictionary = cv2.aruco.getPredefinedDictionary(dictionary_id)
        self.bridge = CvBridge()
        self.camera_matrix = None
        self.distortion = None
        self.create_subscription(Image, self.topic('image_topic', '/camera/image_raw'),
                                 self.image, qos_profile_sensor_data)
        self.create_subscription(
            CameraInfo, self.topic('camera_info_topic', '/camera/camera_info'),
            self.calibration, qos_profile_sensor_data)
        self.detections = self.create_publisher(
            ArucoDetection, self.topic('detections_topic', '/aruco/detections'), 10)
        self.poses = self.create_publisher(
            PoseArray, self.topic('poses_topic', '/aruco/poses'), 10)
        self.pose = self.create_publisher(PoseStamped, self.topic('pose_topic', '/aruco/pose'), 10)
        self.ids = self.create_publisher(
            Int32MultiArray, self.topic('ids_topic', '/aruco/ids'), 10)
        self.debug = self.create_publisher(
            Image, self.topic('debug_topic', '/aruco/image_debug'), 10)

    def topic(self, name, default):
        value = self.declare_parameter(name, default).value
        if not value:
            raise ValueError(name + ' must not be empty')
        return value

    def calibration(self, message):
        matrix = np.asarray(message.k).reshape(3, 3)
        distortion = np.asarray(message.d)
        if (np.isfinite(matrix).all() and np.isfinite(distortion).all()
                and matrix[0, 0] > 0 and matrix[1, 1] > 0):
            self.camera_matrix = matrix
            self.distortion = distortion

    def image(self, message):
        if self.camera_matrix is None or not message.header.frame_id:
            return
        try:
            image = self.bridge.imgmsg_to_cv2(message, desired_encoding='bgr8')
            corners, ids, _ = cv2.aruco.detectMarkers(
                cv2.cvtColor(image, cv2.COLOR_BGR2GRAY), self.dictionary)
            self.publish_detections(message.header, corners, ids)
            if self.publish_debug:
                if ids is not None:
                    cv2.aruco.drawDetectedMarkers(image, corners, ids)
                debug = self.bridge.cv2_to_imgmsg(image, encoding='bgr8')
                debug.header = message.header
                self.debug.publish(debug)
        except (CvBridgeError, cv2.error) as error:
            self.get_logger().warning(str(error), throttle_duration_sec=5.0)

    def publish_detections(self, header, corners, ids):
        poses = PoseArray(header=header)
        published_ids = Int32MultiArray()
        if ids is not None:
            rotations, translations, _ = cv2.aruco.estimatePoseSingleMarkers(
                corners, self.marker_size, self.camera_matrix, self.distortion)
            for marker_id, rotation, translation in zip(ids.flatten(), rotations, translations):
                if self.expected_id >= 0 and marker_id != self.expected_id:
                    continue
                pose = marker_pose(rotation, translation)
                stamped = PoseStamped(header=header, pose=pose)
                self.detections.publish(ArucoDetection(marker_id=int(marker_id), pose=stamped))
                self.pose.publish(stamped)
                poses.poses.append(pose)
                published_ids.data.append(int(marker_id))
        self.poses.publish(poses)
        self.ids.publish(published_ids)


def main():
    rclpy.init()
    node = ArucoDetector()
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    finally:
        node.destroy_node()
        if rclpy.ok():
            rclpy.shutdown()


if __name__ == '__main__':
    main()
