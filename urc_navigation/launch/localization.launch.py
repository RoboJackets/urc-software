from launch import LaunchDescription
from launch.substitutions import PathJoinSubstitution
from launch_ros.actions import Node
from launch_ros.substitutions import FindPackageShare


def generate_launch_description():

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

    # launch quaternion to rpy here

    return LaunchDescription([
        ekf_localization_node,
    ])
