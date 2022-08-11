from launch import LaunchDescription
from launch.substitutions import PathJoinSubstitution
from launch_ros.actions import Node
from launch_ros.substitutions import FindPackageShare


def generate_launch_description():
    octomap_to_gridmap_node = Node(
        package='urc_navigation',
        executable='urc_navigation_OctomapToGridmap',
        output='screen',
        parameters=[
            PathJoinSubstitution([FindPackageShare('urc_navigation'), 'config',
                                 'octomap_to_gridmap_params.yaml'])
        ],
        remappings=[
            ("/octomap_to_gridmap/octomap_full", "/octomap_full"),
            ("/octomap_to_gridmap/slope/gridmap", "/slope/gridmap")
        ]
    )

    return LaunchDescription([
        octomap_to_gridmap_node
    ])
