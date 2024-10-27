from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
import launch_ros.actions
import os


def generate_launch_description():
    return LaunchDescription([
        launch_ros.actions.Node( 
            package='robot_localization',
            executable='ekf_node',
            name='ekf_filter_node',
            output='screen',
            parameters=[os.path.join(get_package_share_directory("robot_localization"), 'config', 'ekf.yaml')],
        )
    ])

    