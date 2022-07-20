from launch import LaunchDescription
from launch_ros.actions import Node
from ament_index_python.packages import get_package_share_directory
import os
import yaml


def generate_launch_description():
    parameters_file_path = os.path.join(get_package_share_directory(
        'urc_navigation'), 'config', 'urc_navigation_params.yaml')
    with open(parameters_file_path, 'r') as file:
        wheel_odometer_params = yaml.safe_load(file)['wheel_odometer']['ros_parameters']

    wheel_odometer_node = Node(
            package='urc_navigation',
            executable='urc_navigation_WheelOdometer',
            output='screen',
            parameters=[
                wheel_odometer_params
            ],
            remappings=[
                ("/wheel_odometer/encoders", "/encoders"),
                ("/wheel_odometer/wheel_odometry", "/wheel_odometry")
            ]
        )

    return LaunchDescription([
        wheel_odometer_node
    ])
