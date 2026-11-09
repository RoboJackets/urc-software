from launch import LaunchDescription
from launch.substitutions import PathJoinSubstitution
from launch_ros.actions import Node
from launch_ros.substitutions import FindPackageShare


def generate_launch_description():
    planner_parameters = PathJoinSubstitution(
        [
            FindPackageShare("urc_path_planning"),
            "config",
            "planner_params.yaml",
        ]
    )

    path_planner_server = Node(
        package="urc_path_planning",
        executable="urc_path_planning_PlannerServer",
        output="screen",
        parameters=[planner_parameters],
    )

    return LaunchDescription([path_planner_server])
