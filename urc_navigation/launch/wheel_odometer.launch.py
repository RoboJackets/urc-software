from launch import LaunchDescription
from launch.substitutions import PathJoinSubstitution
from launch_ros.actions import Node
from launch_ros.substitutions import FindPackageShare


def generate_launch_description():
    wheel_odometer_node = Node(
            package='urc_navigation',
            executable='urc_navigation_WheelOdometer',
            output='screen',
            parameters=[
                PathJoinSubstitution([FindPackageShare('urc_navigation'), 'config',
                                     'wheel_odometer_params.yaml'])
            ],
            remappings=[
                ("/wheel_odometer/encoders", "/encoders"),
                ("/wheel_odometer/wheel_odometry", "/wheel_odometry")
            ]
        )

    return LaunchDescription([
        wheel_odometer_node
    ])
