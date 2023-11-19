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
            ("/joy/set_feedback", "/driver/joy/set_feedback")
        )
    )

    joystick_driver_node = Node(
        package='urc_platform',
        executable='urc_platform_JoystickDriver',
        output='screen',
        parameters=[
                PathJoinSubstitution([FindPackageShare('urc_platform'), 'config',
                                     'joystick_config.yaml'])
        ],
        remappings=[
            ("/joystick_driver/joy", "/driver/joy"),
        ]
    )

    return LaunchDescription([
        driver_joy_node,
        joystick_driver_node
    ])
