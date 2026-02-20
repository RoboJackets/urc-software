from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
import launch_ros.actions
import os

def generate_launch_description():
    params = os.path.join(
        get_package_share_directory("urc_localization"),
        "config",
        "ekf_redemption.yaml",
    )

    # LOCAL EKF: publishes odom -> base_link, and /odometry/filtered
    ekf_node_local = launch_ros.actions.Node(
        package="robot_localization",
        executable="ekf_node",
        name="ekf_filter_node",
        output="screen",
        parameters=[params],
    )

    # NAVSAT: consumes /odometry/filtered_global, publishes /odometry/gps
    navsat = launch_ros.actions.Node(
        package="robot_localization",
        executable="navsat_transform_node",
        name="navsat_transform",
        output="screen",
        parameters=[params],
        remappings=[
            ("imu", "/imu/fused"),
            ("gps/fix", "/gps/covariances"),
            # navsat_transform's /odometry/gps frame_id follows its odometry input frame.
            # Feed the map-frame global EKF output so /odometry/gps is in map.
            ("odometry/filtered", "/odometry/filtered_global"),
        ],
    )

    # GLOBAL EKF: consumes /odometry/gps + /odometry/filtered
    # publishes map -> odom and /odometry/filtered_global
    ekf_node_global = launch_ros.actions.Node(
        package="robot_localization",
        executable="ekf_node",
        namespace="global",
        name="ekf_filter_node_global",
        output="screen",
        parameters=[params],
        remappings=[
            ("odometry/filtered", "/odometry/filtered_global"),
        ],
    )

    return LaunchDescription([ekf_node_local, navsat, ekf_node_global])
