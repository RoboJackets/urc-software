from launch import LaunchDescription
from launch.substitutions import PathJoinSubstitution
from launch_ros.actions import Node
from launch_ros.substitutions import FindPackageShare


def generate_launch_description():
    traversability_params = PathJoinSubstitution(
        [
            FindPackageShare("urc_perception"),
            "config",
            "traversability_params.yaml",
        ]
    )

    traversability_mapping_node = Node(
        package="urc_perception",
        executable="urc_perception_TraversabilityMapping",
        output="screen",
        parameters=[traversability_params],
    )

    grid_map_visualization_node = Node(
        package="grid_map_visualization",
        executable="grid_map_visualization",
        name="grid_map_visualization",
        output="screen",
        parameters=[traversability_params],
    )

    return LaunchDescription(
        [
            traversability_mapping_node,
            grid_map_visualization_node,
            # elevation_mapping_node,
        ]
    )
