from launch import LaunchDescription
from launch_ros.actions import Node
from ament_index_python.packages import get_package_share_directory
import os
import yaml


def generate_launch_description():
    parameters_file_path = os.path.join(get_package_share_directory(
        'urc_platform'), 'config', 'urc_platform_params.yaml')
    with open(parameters_file_path, 'r') as file:
        joystick_driver_params = yaml.safe_load(file)['joystick_driver']['ros_parameters']

    joystick_driver_node = Node(
            package='urc_platform',
            executable='urc_platform_JoystickDriver',
            output='screen',
            parameters=[
                joystick_driver_params
            ],
            remappings=[
                ("/joystick_driver/joy", "/joy"),
                ("/joystick_driver/motors", "/motors")
            ]
        )
    
    return LaunchDescription([
        joystick_driver_node
    ])
