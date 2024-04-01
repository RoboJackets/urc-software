from launch import LaunchDescription
from launch_ros.actions import Node
from launch.substitutions import LaunchConfiguration
from launch.actions import DeclareLaunchArgument, IncludeLaunchDescription
from ament_index_python.packages import get_package_share_directory
import os
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch_ros.actions import Node
from launch_ros.substitutions import FindPackageShare


def generate_launch_description():
    tester_config = os.path.join(
        get_package_share_directory("tester"), "config", "tester.yaml"
    )

    tester_la = DeclareLaunchArgument(
        "tester_config", default_value=tester_config, description=""
    )

    ld = LaunchDescription([tester_la])

    tester_node = Node(
        package="tester",
        executable="tester",
        name="tester",
        output="screen",
        parameters=[LaunchConfiguration("tester_config")],
    )

    trajectory_follower_launch = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            [
                FindPackageShare("trajectory_following"),
                "/launch/trajectory_following.launch.py",
            ]
        )
    )

    path_planner_server = Node(
        package="path_planning",
        executable="path_planning_PlannerServer",
        output="screen",
    )

    # finalize
    ld.add_action(tester_node)
    ld.add_action(trajectory_follower_launch)
    ld.add_action(path_planner_server)

    return ld
