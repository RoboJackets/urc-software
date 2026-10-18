from launch import LaunchDescription
from launch.substitutions import PathJoinSubstitution
from launch_ros.actions import Node
from launch_ros.substitutions import FindPackageShare
from launch.actions import IncludeLaunchDescription
from launch.launch_description_sources import PythonLaunchDescriptionSource
from ament_index_python.packages import get_package_share_directory
import os


def generate_launch_description():
    pkg_ublox_dgnss = get_package_share_directory("ublox_dgnss")

    driver_joy_node = Node(
        package="joy",
        executable="joy_node",
        remappings=(
            ("/joy", "/driver/joy"),
            ("/joy/set_feedback", "/driver/joy/set_feedback"),
        ),
    )

    joystick_driver_node = Node(
        name="joy_drive",
        package="urc_platform",
        executable="urc_platform_JoystickDriver",
        output="screen",
        parameters=[
            PathJoinSubstitution(
                [
                    FindPackageShare("urc_bringup"),
                    "config/",
                    "controller_config.yaml",
                ]
            )
        ],
        remappings=[
            ("/joystick_driver/joy", "/driver/joy"),
        ],
    )

    base_station_gps_launch = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            os.path.join(pkg_ublox_dgnss, "launch", "ublox_fb+r_base.launch.py")
        ),
        launch_arguments={"device_serial_string": "base"}.items(),
    )
    return LaunchDescription(
        [driver_joy_node, joystick_driver_node, base_station_gps_launch]
    )
