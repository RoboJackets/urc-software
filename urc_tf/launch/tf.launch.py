from launch import LaunchDescription
from launch_ros.actions import Node


def generate_launch_description():
    world_frame_node = Node(
        package="urc_tf", executable="urc_tf_WorldFrameBroadcaster", output="screen"
    )

    return LaunchDescription([world_frame_node])
