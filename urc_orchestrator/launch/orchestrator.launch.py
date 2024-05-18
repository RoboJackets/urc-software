from launch import LaunchDescription
from launch_ros.actions import Node


def generate_launch_description():

    orchestrator = Node(
            package='urc_orchestrator',
            executable='urc_orchestrator_Orchestrator',
            output='screen'
        )

    return LaunchDescription([
        orchestrator
    ])
