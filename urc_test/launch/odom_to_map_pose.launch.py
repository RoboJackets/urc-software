from launch import LaunchDescription
from launch_ros.actions import Node


def generate_launch_description():
    ld = LaunchDescription()

    odom_to_map_pose_node = Node(
        package="urc_test",
        executable="odom_to_map_pose",
        name="odom_to_map_pose",
        output="screen",
    )

    # finalize
    ld.add_action(odom_to_map_pose_node)

    return ld
