from launch import LaunchDescription
from launch.substitutions import PathJoinSubstitution
from launch_ros.actions import Node
from launch_ros.substitutions import FindPackageShare


def generate_launch_description():
    planner_params = PathJoinSubstitution(
        [FindPackageShare("urc_path_planning"), "config", "planner_params.yaml"]
    )

    path_planner_server = Node(
        package="urc_path_planning",
        executable="urc_path_planning_PlannerServer",
        name="planner_server",
        output="screen",
        parameters=[planner_params],
    )

    return LaunchDescription([path_planner_server])
