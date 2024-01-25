from launch import LaunchDescription
from launch_ros.actions import Node
from launch_ros.substitutions import FindPackageShare
from launch.substitutions import LaunchConfiguration
import os


def generate_launch_description():
    pkg_urc_navigation = FindPackageShare("urc_navigation").find("urc_navigation")

    ekf_local = Node(
        package='robot_localization',
        executable='ekf_node',
        name='ekf_filter_node_local',
        output='screen',
        parameters=[
            os.path.join(pkg_urc_navigation, 'config/ekf.yaml')
            # {'use_sim_time': LaunchConfiguration('use_sim_time')}
        ],
        remappings=[('odometry/filtered', 'odometry/local')]           

    )

    ekf_global = Node(
        package='robot_localization',
        executable='ekf_node',
        name='ekf_filter_node_global',
        output='screen',
        parameters=[
            os.path.join(pkg_urc_navigation, 'config/ekf.yaml')
        ],
        remappings=[
            ('odometry/filtered', 'odometry/global')]           

    )

    navsat_node = Node(
        package="robot_localization",
        executable="navsat_transform_node",
        name="navsat_transform",
        output="screen",
        parameters=[
            os.path.join(pkg_urc_navigation, 'config/ekf.yaml')
        ],
        remappings=[('/imu', 'imu/data'),
            ('gps/fix', 'gps/data'), 
            ('gps/filtered', 'gps/filtered'),
            ('odometry/gps', 'odometry/gps'),
            ('odometry/filtered', 'odometry/global')]            

    )

    return LaunchDescription([
        ekf_local,
        ekf_global,
        navsat_node
    ])
