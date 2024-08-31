from launch import LaunchDescription
from launch.substitutions import PathJoinSubstitution
from launch_ros.actions import Node
from launch_ros.substitutions import FindPackageShare


def generate_launch_description():
    elevation_mapping_node = Node(
        package="urc_perception",
        executable="urc_perception_ElevationMapping",
        output="screen",
        parameters=[
            PathJoinSubstitution(
                [
                    FindPackageShare("urc_perception"),
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
