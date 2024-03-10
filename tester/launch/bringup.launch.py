from launch import LaunchDescription
from launch_ros.actions import Node
from launch.substitutions import LaunchConfiguration
from launch.actions import DeclareLaunchArgument
from ament_index_python.packages import get_package_share_directory
import os


def generate_launch_description():
    tester_config = os.path.join(
        get_package_share_directory('tester'),
        'config',
        'tester.yaml'
    )

    tester_la = DeclareLaunchArgument(
        'tester_config',
        default_value=tester_config,
        description='')

    ld = LaunchDescription([tester_la])

    tester_node = Node(
        package='tester',
        executable='tester',
        name='tester',
        output="screen",
        parameters=[LaunchConfiguration('tester_config')]
    )

    trajectory_node_action_server = Node(
        package="trajectory_following",
        executable="trajectory_following_FollowerActionServer",
        name="trajectory_following_FollowerActionServer",
        output="screen",
    )


    path_planner_server = Node(
        package='path_planning',
        executable='path_planning_PlannerServer',
        output='screen'
    )

    # finalize
    ld.add_action(tester_node)
    ld.add_action(trajectory_node_action_server)
    ld.add_action(path_planner_server)

    return ld
