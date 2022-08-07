from launch import LaunchDescription
from launch_ros.actions import Node


def generate_launch_description():
    traversability_filter_node = Node(
        package='urc_navigation',
        executable='urc_navigation_TraversabilityFilter',
        output='screen',
        parameters=[],
        remappings=[
            ("/traversability_filter/elevation_mapping/elevation_map_raw", "/elevation_mapping/elevation_map_raw"),
            ("/traversability_filter/slope/gridmap", "/slope/gridmap")
        ]
    )

    return LaunchDescription([
        traversability_filter_node
    ])









