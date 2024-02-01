from launch import LaunchDescription
from launch_ros.actions import Node


def generate_launch_description():

    waypoint_state_machine_node = Node(
            package='urc_navigation',
            executable='urc_navigation_WaypointStateMachine',
            output='screen'
        )

    return LaunchDescription([
        waypoint_state_machine_node
    ])
