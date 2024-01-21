from launch import LaunchDescription
from launch_ros.actions import Node
from launch_ros.substitutions import FindPackageShare
from launch.substitutions import LaunchConfiguration
import os


def generate_launch_description():
    pkg_urc_navigation = FindPackageShare("urc_navigation").find
    ("urc_navigation")

    robot_localization_node = Node(
        package='robot_localization',
        executable='ekf_node',
        name='ekf_filter_node',
        output='screen',
        parameters=[
            os.path.join(pkg_urc_navigation, 'config/ekf.yaml'),
            {'use_sim_time': LaunchConfiguration('use_sim_time')}
        ]
    )

    return LaunchDescription([
        robot_localization_node
    ])
