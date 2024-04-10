from launch import LaunchDescription
from launch_ros.actions import Node


def generate_launch_description():

    path_planner_server = Node(
            package='path_planning',
            executable='path_planning_PlannerServer',
            output='screen'
        )

    return LaunchDescription([
        path_planner_server
    ])
