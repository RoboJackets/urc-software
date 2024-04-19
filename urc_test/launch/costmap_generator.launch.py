import os
from launch import LaunchDescription
from launch_ros.actions import Node
from launch.substitutions import LaunchConfiguration
from launch.actions import DeclareLaunchArgument
from ament_index_python.packages import get_package_share_directory


def generate_launch_description():
    tester_config = os.path.join(
        get_package_share_directory("urc_test"), "config", "tester.yaml"
    )

    tester_la = DeclareLaunchArgument(
        "tester_config", default_value=tester_config, description=""
    )

    ld = LaunchDescription([tester_la])

    costmap_generator_node = Node(
        package="urc_test",
        executable="costmap_generator",
        name="costmap_generator",
        output="screen",
        parameters=[LaunchConfiguration("tester_config")],
    )

    # finalize
    ld.add_action(costmap_generator_node)

    return ld
