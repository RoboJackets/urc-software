from launch import LaunchDescription
from launch_ros.actions import Node
from launch_ros.substitutions import FindPackageShare
from launch.substitutions import PathJoinSubstitution


def generate_launch_description():
    bt_executor_params = PathJoinSubstitution(
        [
            FindPackageShare("urc_behavior"),
            "config",
            "bt_executor_params.yaml",
        ]
    )

    bt_executor_node = Node(
        package="urc_behavior",
        executable="urc_behavior_BTExecutor",
        parameters=[bt_executor_params],
    )

    return LaunchDescription(
        [
            bt_executor_node,
        ]
    )
