#!/usr/bin/env python3
"""Detect ArUco tags and report camera-, robot-center-, and world-axis data.

`/aruco/poses` is the tag pose relative to the robot center in `target_frame`.
`/aruco/world_poses` contains the same relative displacement, rotated into
`world_frame` axes. It intentionally does not add the robot's world position.
"""

import math

import cv2
import numpy as np
import rclpy
from cv_bridge import CvBridge
from geometry_msgs.msg import Pose, PoseArray, PoseStamped
from rclpy.duration import Duration
from rclpy.node import Node
from rclpy.qos import qos_profile_sensor_data
from rclpy.time import Time
from sensor_msgs.msg import CameraInfo, Image
from std_msgs.msg import (
    Float64MultiArray,
    Int32MultiArray,
    MultiArrayDimension,
)
from tf2_ros import Buffer, TransformException, TransformListener


# ---------------------------------------------------------------------
# Math helpers
# ---------------------------------------------------------------------

# OpenCV optical frame (x right, y down, z forward) -> ROS body-style
# camera frame (x forward, y left, z up).
R_LINK_FROM_OPTICAL = np.array(
    [[0.0, 0.0, 1.0],
     [-1.0, 0.0, 0.0],
     [0.0, -1.0, 0.0]]
)


def make_T(R, t):
    T = np.eye(4)
    T[:3, :3] = R
    T[:3, 3] = np.asarray(t, dtype=float).reshape(3)
    return T


def quat_to_R(x, y, z, w):
    n = math.sqrt(x * x + y * y + z * z + w * w)
    x, y, z, w = x / n, y / n, z / n, w / n
    return np.array([
        [1 - 2 * (y * y + z * z), 2 * (x * y - z * w), 2 * (x * z + y * w)],
        [2 * (x * y + z * w), 1 - 2 * (x * x + z * z), 2 * (y * z - x * w)],
        [2 * (x * z - y * w), 2 * (y * z + x * w), 1 - 2 * (x * x + y * y)],
    ])


def R_to_quat(R):
    """Rotation matrix -> (x, y, z, w)."""
    trace = R[0, 0] + R[1, 1] + R[2, 2]
    if trace > 0.0:
        s = 0.5 / math.sqrt(trace + 1.0)
        return ((R[2, 1] - R[1, 2]) * s,
                (R[0, 2] - R[2, 0]) * s,
                (R[1, 0] - R[0, 1]) * s,
                0.25 / s)
    if R[0, 0] > R[1, 1] and R[0, 0] > R[2, 2]:
        s = 2.0 * math.sqrt(1.0 + R[0, 0] - R[1, 1] - R[2, 2])
        return (0.25 * s,
                (R[0, 1] + R[1, 0]) / s,
                (R[0, 2] + R[2, 0]) / s,
                (R[2, 1] - R[1, 2]) / s)
    if R[1, 1] > R[2, 2]:
        s = 2.0 * math.sqrt(1.0 + R[1, 1] - R[0, 0] - R[2, 2])
        return ((R[0, 1] + R[1, 0]) / s,
                0.25 * s,
                (R[1, 2] + R[2, 1]) / s,
                (R[0, 2] - R[2, 0]) / s)
    s = 2.0 * math.sqrt(1.0 + R[2, 2] - R[0, 0] - R[1, 1])
    return ((R[0, 2] + R[2, 0]) / s,
            (R[1, 2] + R[2, 1]) / s,
            0.25 * s,
            (R[1, 0] - R[0, 1]) / s)


def rpy_to_R(roll, pitch, yaw):
    cr, sr = math.cos(roll), math.sin(roll)
    cp, sp = math.cos(pitch), math.sin(pitch)
    cy, sy = math.cos(yaw), math.sin(yaw)
    return np.array([
        [cy * cp, cy * sp * sr - sy * cr, cy * sp * cr + sy * sr],
        [sy * cp, sy * sp * sr + cy * cr, sy * sp * cr - cy * sr],
        [-sp, cp * sr, cp * cr],
    ])


def T_to_pose(T):
    pose = Pose()
    pose.position.x, pose.position.y, pose.position.z = (
        float(v) for v in T[:3, 3]
    )
    qx, qy, qz, qw = R_to_quat(T[:3, :3])
    pose.orientation.x = float(qx)
    pose.orientation.y = float(qy)
    pose.orientation.z = float(qz)
    pose.orientation.w = float(qw)
    return pose


def tf_msg_to_T(tf_stamped):
    t = tf_stamped.transform.translation
    q = tf_stamped.transform.rotation
    return make_T(quat_to_R(q.x, q.y, q.z, q.w), [t.x, t.y, t.z])


# ---------------------------------------------------------------------
# Node
# ---------------------------------------------------------------------

class ArucoDetector(Node):
    def __init__(self):
        super().__init__('aruco_detector')

        # ---- parameters ------------------------------------------------
        self.declare_parameter('marker_size', 0.05)
        # Frame whose origin is (approximately) the robot center.
        self.declare_parameter('target_frame', 'base_link')
        # A world-aligned frame supplied by localization TF (for example map).
        self.declare_parameter('world_frame', 'map')
        # Robot-centered frame whose orientation is used for world-axis output.
        self.declare_parameter('robot_world_frame', 'base_link')
        # If target_frame's origin is NOT the physical robot center, give the
        # center's position expressed in target_frame (x forward, y left, z up).
        self.declare_parameter('center_offset_xyz', [0.0, 0.0, 0.0])
        # 'auto' : optical if the image frame_id contains "optical"
        # 'optical' : image frame is an OpenCV frame (z forward)
        # 'ros'  : image frame is x-forward/y-left/z-up (Gazebo default link)
        self.declare_parameter('camera_frame_convention', 'auto')
        # Fallback if TF camera->target_frame is unavailable: camera position
        # and orientation in target_frame (camera link, x-forward convention).
        self.declare_parameter('use_manual_fallback', False)
        self.declare_parameter('camera_offset_xyz', [0.0, 0.0, 0.0])
        self.declare_parameter('camera_rpy', [0.0, 0.0, 0.0])

        gp = self.get_parameter
        self.marker_size = float(gp('marker_size').value)
        self.target_frame = str(gp('target_frame').value)
        self.world_frame = str(gp('world_frame').value)
        self.robot_world_frame = str(gp('robot_world_frame').value)
        self.center_offset = np.array(
            gp('center_offset_xyz').value, dtype=float
        )
        self.cam_convention = str(gp('camera_frame_convention').value)
        self.use_manual_fallback = bool(gp('use_manual_fallback').value)
        self.manual_T_base_cam = make_T(
            rpy_to_R(*[float(v) for v in gp('camera_rpy').value]),
            [float(v) for v in gp('camera_offset_xyz').value],
        )

        self.bridge = CvBridge()
        self.camera_matrix = None
        self.dist_coeffs = np.zeros(5)
        self.tf_buffer = Buffer()
        self.tf_listener = TransformListener(self.tf_buffer, self)

        s = self.marker_size / 2.0
        self.obj_points = np.array(
            [[-s, s, 0], [s, s, 0], [s, -s, 0], [-s, -s, 0]],
            dtype=np.float32,
        )

        # ---- ROS interfaces -------------------------------------------
        self.create_subscription(
            Image, '/camera/image_raw', self.image_cb,
            qos_profile_sensor_data)
        self.create_subscription(
            CameraInfo, '/camera/camera_info', self.cinfo_cb,
            qos_profile_sensor_data)

        # Robot-center-relative (camera offset removed)
        self.poses_pub = self.create_publisher(PoseArray, '/aruco/poses', 10)
        self.pose_pub = self.create_publisher(PoseStamped, '/aruco/pose', 10)
        # Gazebo world coordinates
        self.world_poses_pub = self.create_publisher(
            PoseArray, '/aruco/world_poses', 10)
        self.ids_pub = self.create_publisher(
            Int32MultiArray, '/aruco/ids', 10)
        # Unchanged: distance from the CAMERA to each tag
        self.distances_pub = self.create_publisher(
            Float64MultiArray, '/aruco/distances', 10)
        # New: distance from the ROBOT CENTER to each tag.
        # Per marker, 3 values: [range_3d_m, range_xy_m, bearing_rad]
        # (bearing: 0 = straight ahead, positive = to the left)
        self.center_distances_pub = self.create_publisher(
            Float64MultiArray, '/aruco/center_distances', 10)
        self.debug_image_pub = self.create_publisher(
            Image, '/aruco/image_debug', 10)

        # ---- ArUco -----------------------------------------------------
        self.aruco_dict = cv2.aruco.getPredefinedDictionary(
            cv2.aruco.DICT_6X6_50)
        if hasattr(cv2.aruco, 'DetectorParameters_create'):
            self.aruco_params = cv2.aruco.DetectorParameters_create()
        else:
            self.aruco_params = cv2.aruco.DetectorParameters()

        self.get_logger().info(
            f'Detecting DICT_6X6_50, marker {self.marker_size:.3f} m | '
            f'center frame={self.target_frame}, world={self.world_frame}, '
            f'robot-in-world frame={self.robot_world_frame}')

    # -----------------------------------------------------------------
    def cinfo_cb(self, msg: CameraInfo):
        self.camera_matrix = np.array(msg.k, dtype=np.float64).reshape(3, 3)
        if len(msg.d) > 0:
            self.dist_coeffs = np.array(msg.d, dtype=np.float64)

    # -----------------------------------------------------------------
    def lookup_T(self, target, source, stamp):
        """Return the transform at the message timestamp, or None."""
        try:
            tf = self.tf_buffer.lookup_transform(
                target,
                source,
                Time.from_msg(stamp),
                timeout=Duration(seconds=0.05),
            )
            return tf_msg_to_T(tf)
        except TransformException as e:
            self.get_logger().warning(
                f'TF {source} -> {target} unavailable at image timestamp: {e}',
                throttle_duration_sec=2.0)
            return None

    def is_optical(self, frame_id):
        if self.cam_convention == 'optical':
            return True
        if self.cam_convention == 'ros':
            return False
        return 'optical' in frame_id.lower()

    # -----------------------------------------------------------------
    def image_cb(self, msg: Image):
        try:
            cv_image = self.bridge.imgmsg_to_cv2(msg, desired_encoding='bgr8')
        except Exception as e:
            self.get_logger().error(f'cv_bridge error: {e}')
            return

        gray = cv2.cvtColor(cv_image, cv2.COLOR_BGR2GRAY)
        try:
            corners, ids, _ = cv2.aruco.detectMarkers(
                gray, self.aruco_dict, parameters=self.aruco_params)
        except cv2.error as e:
            self.get_logger().error(f'Marker detection failed: {e}')
            corners, ids = [], None

        center_array = PoseArray()
        center_array.header.stamp = msg.header.stamp
        center_array.header.frame_id = self.target_frame
        world_array = PoseArray()
        world_array.header.stamp = msg.header.stamp
        world_array.header.frame_id = self.world_frame

        ids_msg = Int32MultiArray()
        cam_dist = Float64MultiArray()
        cen_dist = Float64MultiArray()

        if ids is not None and len(ids) > 0 and self.camera_matrix is not None:
            detected_ids = [int(i) for i in ids.flatten()]
            ids_msg.data = detected_ids

            # camera frame -> robot base frame (camera offset lives here)
            T_base_cam_tf = self.lookup_T(
                self.target_frame, msg.header.frame_id, msg.header.stamp)
            if T_base_cam_tf is None and self.use_manual_fallback:
                T_base_cam_tf = self.manual_T_base_cam
            # Robot orientation in the selected world-aligned frame.
            T_world_base = self.lookup_T(
                self.world_frame, self.robot_world_frame, msg.header.stamp)

            optical = self.is_optical(msg.header.frame_id)
            T_conv = np.eye(4)
            if not optical:
                T_conv[:3, :3] = R_LINK_FROM_OPTICAL

            for marker_id, c in zip(detected_ids, corners):
                ok, rvec, tvec = cv2.solvePnP(
                    self.obj_points, c.reshape(4, 2).astype(np.float32),
                    self.camera_matrix, self.dist_coeffs,
                    flags=cv2.SOLVEPNP_IPPE_SQUARE)
                if not ok:
                    continue

                cv2.drawFrameAxes(
                    cv_image, self.camera_matrix, self.dist_coeffs,
                    rvec, tvec, self.marker_size)

                if T_base_cam_tf is None:
                    continue

                # marker in the camera frame
                T_cam_marker = make_T(cv2.Rodrigues(rvec)[0], tvec)
                # marker in robot base frame, then shift origin to the center
                T_base_marker = T_base_cam_tf @ T_conv @ T_cam_marker
                T_center_marker = T_base_marker.copy()
                T_center_marker[:3, 3] -= self.center_offset

                p = T_center_marker[:3, 3]
                range_3d = float(np.linalg.norm(p))
                range_xy = float(np.hypot(p[0], p[1]))
                bearing = float(math.atan2(p[1], p[0]))

                center_pose = T_to_pose(T_center_marker)
                center_array.poses.append(center_pose)
                cam_dist.data.append(float(np.linalg.norm(tvec)))
                cen_dist.data.extend([range_3d, range_xy, bearing])

                ps = PoseStamped()
                ps.header = center_array.header
                ps.pose = center_pose
                self.pose_pub.publish(ps)

                log = (
                    f'ArUco {marker_id}: robot-center x={p[0]:.3f} '
                    f'y={p[1]:.3f} z={p[2]:.3f} m | '
                    f'orientation xyzw=('
                    f'{center_pose.orientation.x:.3f}, '
                    f'{center_pose.orientation.y:.3f}, '
                    f'{center_pose.orientation.z:.3f}, '
                    f'{center_pose.orientation.w:.3f}) | '
                    f'range={range_3d:.3f} m (xy {range_xy:.3f} m) '
                    f'bearing={math.degrees(bearing):.1f} deg')

                if T_world_base is not None:
                    T_world_base_rotation = np.eye(4)
                    T_world_base_rotation[:3, :3] = T_world_base[:3, :3]
                    T_world_center_marker = (
                        T_world_base_rotation @ T_center_marker
                    )
                    world_pose = T_to_pose(T_world_center_marker)
                    world_array.poses.append(world_pose)
                    w = T_world_center_marker[:3, 3]
                    log += (f' | {self.world_frame}: x={w[0]:.3f} '
                            f'y={w[1]:.3f} z={w[2]:.3f} m, '
                            f'orientation xyzw=('
                            f'{world_pose.orientation.x:.3f}, '
                            f'{world_pose.orientation.y:.3f}, '
                            f'{world_pose.orientation.z:.3f}, '
                            f'{world_pose.orientation.w:.3f})')

                self.get_logger().info(log, throttle_duration_sec=1.0)

            cv2.aruco.drawDetectedMarkers(cv_image, corners, ids)

        n = len(cam_dist.data)
        cam_dist.layout.dim = [MultiArrayDimension(
            label='camera_range_m_per_marker', size=n, stride=n)]
        m = len(cen_dist.data) // 3
        cen_dist.layout.dim = [
            MultiArrayDimension(label='marker', size=m, stride=m * 3),
            MultiArrayDimension(
                label='range_3d_m,range_xy_m,bearing_rad', size=3, stride=3),
        ]

        self.ids_pub.publish(ids_msg)
        self.poses_pub.publish(center_array)
        self.world_poses_pub.publish(world_array)
        self.distances_pub.publish(cam_dist)
        self.center_distances_pub.publish(cen_dist)

        try:
            dbg = self.bridge.cv2_to_imgmsg(cv_image, encoding='bgr8')
            dbg.header = msg.header
            self.debug_image_pub.publish(dbg)
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