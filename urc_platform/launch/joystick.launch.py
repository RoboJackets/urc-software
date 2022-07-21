from launch import LaunchDescription
from launch.substitutions import PathJoinSubstitution
from launch_ros.actions import Node
from launch_ros.substitutions import FindPackageShare


def generate_launch_description():

    joystick_driver_node = Node(
            package='urc_platform',
            executable='urc_platform_JoystickDriver',
            output='screen',
            parameters=[
                PathJoinSubstitution([FindPackageShare('urc_platform'), 'config',
                                     'joystick_driver_params.yaml'])
            ],
            remappings=[
                ("/joystick_driver/joy", "/joy"),
                ("/joystick_driver/motors", "/motors")
            ]
        )

    return LaunchDescription([
        joystick_driver_node
    ])
