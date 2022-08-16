from launch import LaunchDescription
from launch.substitutions import PathJoinSubstitution
from launch_ros.actions import Node
from launch_ros.substitutions import FindPackageShare


def generate_launch_description():

    chassis_controller_node = Node(
            package='urc_platform',
            executable='urc_platform_ChassisController',
            output='screen',
            parameters=[
                PathJoinSubstitution([FindPackageShare('urc_platform'), 'config',
                                     'chassis_controller_params.yaml'])
            ],
            remappings=[
                ("/chassis_controller/encoders", "/encoders")
            ]
        )

    return LaunchDescription([
        chassis_controller_node
    ])
