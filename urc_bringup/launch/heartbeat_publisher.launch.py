from launch import LaunchDescription
from launch.substitutions import PathJoinSubstitution
from launch_ros.actions import Node
from launch_ros.substitutions import FindPackageShare


def generate_launch_description():
    heartbeat_publisher_node = Node(
            package='urc_bringup',
            executable='urc_bringup_HeartbeatPublisher',
            output='screen',
            parameters=[
                PathJoinSubstitution([
                    FindPackageShare('urc_bringup'),
                    'config',
                    'heartbeat_publisher.yaml'])
            ]
        )
    return LaunchDescription([
        heartbeat_publisher_node
    ])
