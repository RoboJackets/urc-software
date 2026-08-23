from launch import LaunchDescription
from launch_ros.actions import Node


def generate_launch_description():

    path_planner_server = Node(
            package='urc_path_planning',
            executable='urc_path_planning_PlannerServer',
            output='screen'
        )

    return LaunchDescription([
        path_planner_server
    ])
