from launch import LaunchDescription
from launch.actions import IncludeLaunchDescription
from launch.actions import SetEnvironmentVariable
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch.substitutions import ThisLaunchFileDir
from launch_ros.actions import Node
from ament_index_python.packages import get_package_share_directory

def generate_launch_description():

    SetEnvironmentVariable("GAZEBO_MODEL_PATH", [ThisLaunchFileDir(), "/.."])

    gazebo = IncludeLaunchDescription(
        PythonLaunchDescriptionSource([get_package_share_directory("gazebo_ros"), "/launch/gazebo.launch.py"])
    )

    spawn_entity = Node(package='gazebo_ros', executable='spawn_entity.py',
                        arguments=['-entity', 'barrel', '-database', 'barrel'],
                        output='screen')

    return LaunchDescription([
        gazebo,
        spawn_entity
    ])
