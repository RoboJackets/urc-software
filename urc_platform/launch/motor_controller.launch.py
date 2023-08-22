from launch import LaunchDescription
from launch.substitutions import PathJoinSubstitution
from launch_ros.actions import Node
from launch_ros.substitutions import FindPackageShare


def generate_launch_description():

    motor_controller_node = Node(
            package='urc_platform',
            executable='urc_platform_MotorController',
            output='screen',
            parameters=[
                PathJoinSubstitution([FindPackageShare('urc_platform'), 'config',
                                     'motor_controller_params.yaml'])
            ],
            remappings=[
                ("/motor_controller/encoders", "/encoders"),
                ("/motor_controller/motors", "/motors")
            ]
        )

    return LaunchDescription([
        motor_controller_node
    ])
