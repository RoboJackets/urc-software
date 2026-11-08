import os

from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node
from launch_ros.parameter_descriptions import ParameterValue


def generate_launch_description():
    config = os.path.join(
        get_package_share_directory('urc_perception'), 'config', 'yolo_detector.yaml')

    return LaunchDescription([

        DeclareLaunchArgument('config', default_value=config),
        DeclareLaunchArgument('model_path'),
        DeclareLaunchArgument('use_sim_time', default_value='false'),

        Node(
            package='urc_perception',
            executable='yolo_detector.py',
            name='yolo_detector',
            parameters=[
                LaunchConfiguration('config'),
                {
                    'model_path': ParameterValue(LaunchConfiguration('model_path'), value_type=str),

                    'use_sim_time': ParameterValue(LaunchConfiguration('use_sim_time'), value_type=bool),
                },
            ],
            output='screen',
        ),
    ])
