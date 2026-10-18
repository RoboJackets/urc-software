from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument, IncludeLaunchDescription
from launch.conditions import IfCondition
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch.substitutions import LaunchConfiguration, PathJoinSubstitution
from launch_ros.actions import Node
from launch_ros.substitutions import FindPackageShare


def generate_launch_description():
    spiral_search_params = PathJoinSubstitution(
        [
            FindPackageShare("urc_perception"),
            "config",
            "spiral_search_params.yaml",
        ]
    )

    with_mapping = DeclareLaunchArgument(
        "with_mapping",
        default_value="true",
        description="Also start traversability mapping, which publishes the map the spiral avoids.",
    )

    pointcloud_topic = DeclareLaunchArgument(
        "pointcloud_topic",
        default_value="/scan/points",
        description=(
            "Point cloud for traversability. On hardware with SICK, use "
            "/cloud_unstructured_fullframe instead of a topic_tools relay."
        ),
    )

    mapping = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            PathJoinSubstitution(
                [FindPackageShare("urc_perception"), "launch", "mapping.launch.py"]
            )
        ),
        launch_arguments={
            "pointcloud_topic": LaunchConfiguration("pointcloud_topic"),
        }.items(),
        condition=IfCondition(LaunchConfiguration("with_mapping")),
    )

    spiral_search_server_node = Node(
        package="urc_perception",
        executable="spiral_search_server",
        output="screen",
        parameters=[spiral_search_params],
    )

    return LaunchDescription(
        [
            with_mapping,
            pointcloud_topic,
            mapping,
            spiral_search_server_node,
        ]
    )
