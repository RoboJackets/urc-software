import os

from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node


def generate_launch_description():
    config = os.path.join(get_package_share_directory('urc_perception'), 'config', 'aruco.yaml')
    return LaunchDescription([
        DeclareLaunchArgument('config', default_value=config),
        Node(package='urc_perception', executable='aruco_detector.py',
             name='aruco_detector', parameters=[LaunchConfiguration('config')], output='screen'),
    ])
