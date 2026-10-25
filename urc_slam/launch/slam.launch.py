import os

from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch_ros.actions import Node


def generate_launch_description():
    parameters_file = os.path.join(
        get_package_share_directory("urc_slam"),
        "config",
        "slam_params.yaml",
    )

    navsat_node = Node(
        package = "robot_localization",
        executable = "navsat_transform_node",
        name = "slam_navsat_transform",
        output = "screen",
        parameters = [parameters_file],
        remappings = [
            ("gps/fix", "/gps"),
            ("imu", "/imu/fused"),
            ("odometry/filtered", "/slam/odometry"),
            ("odometry/gps", "/slam/gps_odometry"),
        ],
    )

    slam_node = Node(
        package="urc_slam",
        executable="SlamNode",
        name="slam_node",
        output="screen",
        parameters=[parameters_file],
    )

    return LaunchDescription([
        slam_node,
        navsat_node,
    ])