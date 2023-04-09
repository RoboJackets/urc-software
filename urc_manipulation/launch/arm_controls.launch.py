from launch import LaunchDescription
from launch.substitutions import PathJoinSubstitution
from launch_ros.actions import Node
from launch_ros.substitutions import FindPackageShare


def generate_launch_description():

    arm_controls_node = Node(
            package='urc_manipulation',
            executable='urc_manipulation_JoyToServoPub',
            output='screen',
            parameters=[
                PathJoinSubstitution([FindPackageShare('urc_manipulation'), 'config',
                                     'joy_to_servo_pub_params.yaml'])
            ],
            remappings=[]
        )

    return LaunchDescription([
        arm_controls_node
    ])
