from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        Node(
            package='autonomy_core',
            executable='asm_demo_node',
            name='asm_demo_node',
            output='screen'
        )
    ])

