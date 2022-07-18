from launch import LaunchDescription
from launch_ros.actions import Node
from ament_index_python.packages import get_package_share_directory
import os
import yaml


def generate_launch_description():
    parameters_file_path = os.path.join(get_package_share_directory(
        'urc_navigation'), 'config', 'ekf_localization_node_params.yaml')
    with open(parameters_file_path, 'r') as file:
        ekf_localization_node_params = yaml.safe_load(file)['ekf_localization']['ros_parameters']

    # launch odometry here

    ekf_localization_node = Node(
            package='urc_localization',
            executable='urc_localization_EkfLocalization',
            output='screen',
            parameters=[
                ekf_localization_node_params
            ],
            remappings=[
                ("/joystick_driver/joy", "/joy"),
                ("/joystick_driver/motors", "/motors")
            ]
        )

    # launch quaternion to rpy here

    return LaunchDescription([
        ekf_localization_node
    ])
