from launch import LaunchDescription
from launch.actions import IncludeLaunchDescription
from launch.substitutions import PathJoinSubstitution
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch_ros.actions import Node
from launch_ros.substitutions import FindPackageShare


def generate_launch_description():

    # launch odometry
    wheel_odometer_node = IncludeLaunchDescription(PythonLaunchDescriptionSource(
            PathJoinSubstitution([FindPackageShare('urc_navigation'), 'launch',
                                 'wheel_odometer.launch.py'])))

    # launch ekf localization node
    ekf_localization_node = Node(
            package='robot_localization',
            executable='ekf_node',
            name='ekf_filter_node',
            output='screen',
            parameters=[
                PathJoinSubstitution([FindPackageShare('urc_navigation'), 'config',
                                     'ekf_localization_node_params.yaml'])
            ]
    )

    # launch traversability filter
    traversability_filter_node = IncludeLaunchDescription(PythonLaunchDescriptionSource(
            PathJoinSubstitution([FindPackageShare('urc_navigation'), 'launch',
                                 'traversability_filter.launch.py'])))

    return LaunchDescription([
        ekf_localization_node,
        wheel_odometer_node,
        traversability_filter_node
    ])
