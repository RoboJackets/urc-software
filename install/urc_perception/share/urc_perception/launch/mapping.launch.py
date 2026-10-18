from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration, PathJoinSubstitution
from launch_ros.actions import Node
from launch_ros.substitutions import FindPackageShare


def generate_launch_description():
    pointcloud_topic = DeclareLaunchArgument(
        "pointcloud_topic",
        default_value="/scan/points",
        description=(
            "Point cloud input for traversability. Use /cloud_unstructured_fullframe "
            "on hardware (SICK); sim uses /scan/points."
        ),
    )

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
        parameters=[
            traversability_params,
            {"pointcloud_topic": LaunchConfiguration("pointcloud_topic")},
        ],
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
            pointcloud_topic,
            traversability_mapping_node,
            grid_map_visualization_node,
        ]
    )
