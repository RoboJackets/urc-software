from launch import LaunchDescription
from launch.substitutions import PathJoinSubstitution
from launch_ros.actions import Node
from launch_ros.substitutions import FindPackageShare


def generate_launch_description():
    trajectory_follower_action_server = Node(
        package="trajectory_following",
        executable="trajectory_following_FollowerActionServer",
        output="screen",
        parameters=[
            PathJoinSubstitution(
                [
                    FindPackageShare("trajectory_following"),
                    "config",
                    "pure_pursuit_config.yaml",
                ]
            )
        ],
    )

    return LaunchDescription([trajectory_follower_action_server])
