import os

from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.conditions import IfCondition
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node


def generate_launch_description():
    package_share = get_package_share_directory("urc_slam")
    parameters_file = os.path.join(package_share, "config", "slam_params.yaml")
    rviz_config = os.path.join(package_share, "rviz", "slam.rviz")

    gps_fix_topic_arg = DeclareLaunchArgument(
        "gps_fix_topic",
        default_value="/gps/covariances",
        description="NavSatFix topic with a populated position covariance",
    )
    rviz_arg = DeclareLaunchArgument(
        "rviz",
        default_value="false",
        description="Open RViz with SLAM and ground-truth odometry",
    )

    navsat_node = Node(
        package="robot_localization",
        executable="navsat_transform_node",
        name="slam_navsat_transform",
        output="screen",
        parameters=[parameters_file],
        remappings=[
            ("gps/fix", LaunchConfiguration("gps_fix_topic")),
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

    rviz_node = Node(
        package="rviz2",
        executable="rviz2",
        name="slam_rviz",
        arguments=["-d", rviz_config],
        parameters=[{"use_sim_time": True}],
        condition=IfCondition(LaunchConfiguration("rviz")),
    )

    return LaunchDescription([
        gps_fix_topic_arg,
        rviz_arg,
        slam_node,
        navsat_node,
        rviz_node,
    ])
