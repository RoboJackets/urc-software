from launch import LaunchDescription
from launch_ros.actions import Node
# from launch.substitutions import Command
from launch.substitutions import LaunchConfiguration
from launch.actions import DeclareLaunchArgument
from launch.actions import IncludeLaunchDescription
from launch_xml.launch_description_sources import XMLLaunchDescriptionSource
from ament_index_python.packages import get_package_share_directory
import os

def generate_launch_description():
    
    tester_config = os.path.join(
        get_package_share_directory('tester'),
        'config',
        'tester.yaml'
    )

    tester_la = DeclareLaunchArgument(
        'tester_config',
        default_value=tester_config,
        description='')

    ld = LaunchDescription([tester_la])
    
    tester_node = Node(
        package='tester',
        node_executable='tester',
        name='tester',
        output="screen",
        parameters=[LaunchConfiguration('tester_config')]
    )

    # finalize
    ld.add_action(tester_node)

    return ld