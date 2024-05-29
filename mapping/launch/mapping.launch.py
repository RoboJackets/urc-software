from launch import LaunchDescription
from launch.substitutions import PathJoinSubstitution
from launch_ros.actions import Node
from launch_ros.substitutions import FindPackageShare


def generate_launch_description():
    elevation_mapping_node = Node(
        package="mapping",
        executable="mapping_ElevationMapping",
        output="screen",
        parameters=[
            PathJoinSubstitution(
                [
                    FindPackageShare("mapping"),
                    "config",
                    "mapping_params.yaml",
                ]
            )
        ],
    )

    return LaunchDescription(
        [
            elevation_mapping_node,
        ]
    )
