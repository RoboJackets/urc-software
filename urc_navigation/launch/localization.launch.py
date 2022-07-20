from launch import LaunchDescription
from launch.actions import IncludeLaunchDescription
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch_ros.actions import Node
from ament_index_python.packages import get_package_share_directory
import os
import yaml


def generate_launch_description():
    parameters_file_path = os.path.join(get_package_share_directory(
        'urc_navigation'), 'config', 'ekf_localization_node_params.yaml')
    with open(parameters_file_path, 'r') as file:
        ekf_localization_node_params = yaml.safe_load(file)['ekf_localization']['ros_parameters']

    # launch odometry
    wheel_odometer_node = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            os.path.join(get_package_share_directory('urc_navigation'), "launch", "wheel_odometer.launch.py")
        )
    )

    # launch ekf localization node
    ekf_localization_node = Node(
            package='robot_localization',
            executable='ekf_node',
            name='ekf_filter_node',
            output='screen',
            parameters=[
                ekf_localization_node_params
            ]
        )

    # launch quaternion to rpy here

    return LaunchDescription([
        ekf_localization_node,
        wheel_odometer_node
    ])
