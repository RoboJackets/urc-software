from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    # Define the JoyDrive node
    joy_drive_node = Node(
        package="urc_platform",
        executable="urc_platform_JoyDrive",
        name="joy_drive",
        output="screen",
        parameters=[
            {"max_linear_velocity_ms": 1.0},
            {"max_angular_velocity_radians": 1.57},
            {"joy_command_topic": "/joy"},
            {"cmd_vel_topic": "/cmd_vel"},
            {"target_axes": [1, 3]},
            {"invert_linear_velocity": False},
            {"invert_angular_velocity": False},
        ],
    )

    return LaunchDescription([
        joy_drive_node,
    ])