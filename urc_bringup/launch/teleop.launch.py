import os
from launch import LaunchDescription
from launch.actions import IncludeLaunchDescription
from launch_ros.actions import Node
from launch_ros.substitutions import FindPackageShare
from launch_xml.launch_description_sources import XMLLaunchDescriptionSource
from ament_index_python.packages import get_package_share_directory


def generate_launch_description():
    pkg_urc_bringup = get_package_share_directory("urc_bringup")
    controller_config_file_dir = os.path.join(
        pkg_urc_bringup, "config", "controller_config.yaml"
    )

    driver_joy_node = Node(
        package="joy",
        executable="joy_node",
        remappings=(
            ("/joy", "/driver/joy"),
            ("/joy/set_feedback", "/driver/joy/set_feedback"),
        ),
    )

    joy_drive = Node(
        package="urc_scripts",
        executable="joy_drive",
        parameters=[controller_config_file_dir],
    )

    return LaunchDescription(
        [
            IncludeLaunchDescription(
                XMLLaunchDescriptionSource(
                    [
                        FindPackageShare("foxglove_bridge"),
                        "/launch",
                        "/foxglove_bridge_launch.xml",
                    ]
                ),
                launch_arguments={"port": "8765"}.items(),
            ),
            driver_joy_node,
            joy_drive,
        ]
    )
