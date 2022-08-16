from launch import LaunchDescription
from launch.substitutions import PathJoinSubstitution
from launch_ros.actions import Node
from launch_ros.substitutions import FindPackageShare


def generate_launch_description():

    chassis_control_node = Node(
            package='urc_platform',
            executable='urc_platform_ChassisControlROSWrapper',
            output='screen',
            parameters=[
                PathJoinSubstitution([FindPackageShare('urc_platform'), 'config',
                                     'chassis_control_driver_params.yaml'])
            ],
            remappings=[
                ("/chassis_control_driver/encoders", "/encoders")
            ]
        )

    return LaunchDescription([
        chassis_control_node
    ])
