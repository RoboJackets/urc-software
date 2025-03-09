from launch import LaunchDescription
from launch.substitutions import PathJoinSubstitution
from launch_ros.actions import Node
from launch_ros.substitutions import FindPackageShare

def generate_launch_description():
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

    """
    joy_drive_node = Node(
        package="urc_platform",
        executable="urc_platform_JoyDrive",
        name="joy_drive",
        output="screen",
        parameters=[
            {"max_linear_velocity_ms": 1.0},
            {"max_angular_velocity_radians": 1.57},
            {"joy_command_topic": "/driver/joy"},
            {"cmd_vel_topic": "/cmd_vel"},
            {"target_axes": [1, 3]},
            {"invert_linear_velocity": False},
            {"invert_angular_velocity": False},
        ],
    )
    """

    base_station_gps_node = Node(
        package="urc_platform",
        executable="urc_platform_SimGpsHandler",
        output="screen",
    )

    return LaunchDescription([
        driver_joy_node, joystick_driver_node, base_station_gps_node
    ])